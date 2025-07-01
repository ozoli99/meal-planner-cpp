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

    for (const auto& [name, entry] : data.items()) {
        Ingredient ingredient;
        ingredient.name = name;
        ingredient.kcalPerUnit = entry.value("kcal_per_unit", 0.0);
        ingredient.proteinPerUnit = entry.value("protein_per_unit", 0.0);
        ingredient.carbsPerUnit = entry.value("carbs_per_unit", 0.0);
        ingredient.fatPerUnit = entry.value("fat_per_unit", 0.0);
        ingredient.unit = entry.value("unit", "g");
        m_ingredients[name] = ingredient;
    }
}

bool IngredientDatabase::has(const std::string& name) const {
    return m_ingredients.find(name) != m_ingredients.end();
}

Ingredient IngredientDatabase::getPerUnitInfo(const std::string& name) const {
    auto it = m_ingredients.find(name);
    if (it == m_ingredients.end()) {
        throw std::runtime_error("Ingredient not found in database: " + name);
    }
    return it->second;
}