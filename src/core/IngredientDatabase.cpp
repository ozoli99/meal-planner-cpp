#include "core/IngredientDatabase.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <stdexcept>

using json = nlohmann::json;

void IngredientDatabase::loadFromFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open ingredient database: " + path);
    }

    json data;
    file >> data;

    for (const auto& entry : data) {
        IngredientDatabaseEntry ingredient;
        ingredient.name = entry.at("name").get<std::string>();
        ingredient.kcalPer100g = entry.value("kcal_per_100g", 0.0);
        ingredient.proteinPer100g = entry.value("protein_per_100g", 0.0);
        ingredient.carbsPer100g = entry.value("carbs_per_100g", 0.0);
        ingredient.fatPer100g = entry.value("fat_per_100g", 0.0);

        ingredient.defaultUnit = entry.value("unit", "g");
        ingredient.category = entry.value("category", "");

        if (entry.contains("tags")) {
            ingredient.tags = entry["tags"].get<std::vector<std::string>>();
        }

        if (entry.contains("substitutions")) {
            ingredient.substitutions = entry["substitutions"].get<std::unordered_map<std::string, std::string>>();
        }
        m_ingredients[ingredient.name] = std::move(ingredient);
    }
}

bool IngredientDatabase::has(const std::string& name) const {
    return m_ingredients.find(name) != m_ingredients.end();
}

IngredientDatabaseEntry IngredientDatabase::getPerUnitInfo(const std::string& name) const {
    auto it = m_ingredients.find(name);
    if (it == m_ingredients.end()) {
        throw std::runtime_error("Ingredient not found in database: " + name);
    }
    return it->second;
}