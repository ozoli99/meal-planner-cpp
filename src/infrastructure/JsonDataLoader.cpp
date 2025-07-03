#include "infrastructure/JsonDataLoader.h"

#include <nlohmann/json.hpp>
#include <fstream>
#include <stdexcept>

#include "core/Recipe.h"
#include "core/Ingredient.h"
#include "core/Equipment.h"
#include "core/Cost.h"
#include "core/NutritionUtils.h"
#include "core/NutritionCalculator.h"
#include "core/JsonConverters.h"

using json = nlohmann::json;
using namespace mealplanner::model;
using namespace mealplanner::infrastructure;

JsonDataLoader::JsonDataLoader(const IngredientDatabase& ingredientDatabase)
    : m_ingredientDatabase(ingredientDatabase) {}
    
std::vector<Recipe> JsonDataLoader::loadRecipes(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open recipes file: " + path);
    }
    
    json data;
    file >> data;
    
    std::vector<Recipe> recipes;
    recipes.reserve(data.size());
    for (const auto& entry : data) {
        recipes.push_back(entry.get<Recipe>());
    }
    
    return recipes;
}
    
UserProfile JsonDataLoader::loadUserProfile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Cannot open user file: " + path);
    }
    
    json data;
    file >> data;
    
    return data.get<UserProfile>();
}