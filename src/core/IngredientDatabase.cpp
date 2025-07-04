#include "core/IngredientDatabase.h"
#include "core/IngredientDatabaseEntry.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <stdexcept>

using json = nlohmann::json;
using namespace mealplanner::model;

void IngredientDatabase::loadFromFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open ingredient database: " + path);
    }

    json data;
    file >> data;

    for (const auto& entry : data) {
        auto name = entry.at("name").get<std::string>();
        auto defaultUnit = entry.value("unit", "g");
        double kcalPer100g = entry.value("kcal_per_100g", 0.0);
        double proteinPer100g = entry.value("protein_per_100g", 0.0);
        double carbsPer100g = entry.value("carbs_per_100g", 0.0);
        double fatPer100g = entry.value("fat_per_100g", 0.0);
        auto form = entry.value("form", "");
        auto category = entry.value("category", "");

        std::optional<std::string> brand;
        if (entry.contains("brand")) {
            brand = entry["brand"].get<std::string>();
        }
        
        auto tags = entry.value("tags", std::vector<std::string>{});
        auto substitutions = entry.value("substitutions", std::unordered_map<std::string, std::string>{});
        
        Unit unit = unitFromString(defaultUnit);
        Calories kcal{static_cast<int>(kcalPer100g + 0.5)};
        Grams protein{static_cast<int>(proteinPer100g + 0.5)};
        Grams carbs{static_cast<int>(carbsPer100g + 0.5)};
        Grams fat{static_cast<int>(fatPer100g + 0.5)};

        IngredientDatabaseEntry ingredient(
            std::move(name), unit, kcal, protein, carbs, fat,
            std::move(form), std::move(category), std::move(brand), std::move(tags), std::move(substitutions)
        );

        m_ingredients.emplace(ingredient.GetName(), std::move(ingredient));
    }
}

bool IngredientDatabase::has(const std::string& name) const {
    return m_ingredients.find(name) != m_ingredients.end();
}

std::optional<IngredientDatabaseEntry> IngredientDatabase::getPerUnitInfo(const std::string& name) const {
    auto it = m_ingredients.find(name);
    if (it == m_ingredients.end()) {
        return std::nullopt;
    }
    return it->second;
}