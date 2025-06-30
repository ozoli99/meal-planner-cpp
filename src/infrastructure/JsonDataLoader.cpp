#include "infrastructure/JsonDataLoader.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

std::vector<Recipe> JsonDataLoader::loadRecipes(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open recipes file at " << path << "\n";
        return {};
    }

    json data;
    file >> data;

    std::vector<Recipe> recipes;
    for (const auto& r : data) {
        try {
            recipes.push_back({
                r.at("id"),
                r.at("name"),
                r.at("type"),
                r.at("kcal"),
                r.at("protein"),
                r.at("carbs"),
                r.at("fat"),
                r.at("prep_time_minutes"),
                r.at("tags").get<std::vector<std::string>>()
            });
        } catch (...) {
            std::cerr << "Warning: Skipped invalid recipe\n";
        }
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