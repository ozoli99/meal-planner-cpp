#include "infrastructure/JsonDataLoader.h"
#include "core/NutritionUtils.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

JsonDataLoader::JsonDataLoader(const IngredientDatabase& ingredientDb)
    : m_ingredientDb(ingredientDb) {}

std::vector<Recipe> JsonDataLoader::loadRecipes(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        throw std::runtime_error("Cannot open recipes file: " + path);
    }

    json data;
    file >> data;

    std::vector<Recipe> recipes;
    for (const auto& r : data) {
        Recipe recipe;
        recipe.id = r.at("id");
        recipe.name = r.at("name");
        recipe.type = r.at("type");
        recipe.prepTimeMinutes = r.at("prep_time_minutes");
        recipe.tags = r.at("tags").get<std::vector<std::string>>();
            
        for (const auto& ingr : r.value("ingredients", std::vector<json>{})) {
            Ingredient ingredient;
            ingredient.name = ingr.at("name").get<std::string>();
            ingredient.quantity = ingr.at("quantity").get<double>();
            ingredient.unit = ingr.at("unit").get<std::string>();

            if (ingr.contains("kcal_per_unit")) {
                ingredient.kcalPerUnit = ingr.value("kcal_per_unit", 0.0);
                ingredient.proteinPerUnit = ingr.value("protein_per_unit", 0.0);
                ingredient.carbsPerUnit = ingr.value("carbs_per_unit", 0.0);
                ingredient.fatPerUnit = ingr.value("fat_per_unit", 0.0);
            } else if (m_ingredientDb.has(ingredient.name)) {
                const auto& base = m_ingredientDb.getPerUnitInfo(ingredient.name);
                ingredient.kcalPerUnit = base.kcalPerUnit;
                ingredient.proteinPerUnit = base.proteinPerUnit;
                ingredient.carbsPerUnit = base.carbsPerUnit;
                ingredient.fatPerUnit = base.fatPerUnit;
            }

            recipe.ingredients.push_back(ingredient);
        }
        recipes.push_back(recipe);
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

    UserProfile profile;
    profile.name = data.at("name");
    profile.calorieTarget = data.value("calorie_target", 2000);
    profile.mealsPerDay = data.value("meals_per_day", 3);
    profile.snackSlots = data.value("snack_slots", 1);
    profile.maxPrepTimeMinutes = data.value("max_prep_time_minutes", 30);
    profile.dietaryRestrictions = data.at("dietary_restrictions").get<std::vector<std::string>>();

    MacroRatios ratios;
    ratios.protein = data["macro_ratios"].value("protein", 0.25);
    ratios.carbs = data["macro_ratios"].value("carbs", 0.5);
    ratios.fat = data["macro_ratios"].value("fat", 0.25);
    profile.macroRatios = ratios;

    return profile;
}