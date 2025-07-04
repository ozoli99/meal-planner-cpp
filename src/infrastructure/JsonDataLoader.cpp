// JsonDataLoader.cpp

#include "infrastructure/JsonDataLoader.h"

#include <nlohmann/json.hpp>
#include <fstream>
#include <stdexcept>

#include "core/Recipe.h"
#include "core/Ingredient.h"
#include "core/Equipment.h"
#include "core/Cost.h"
#include "core/NutritionUtils.h"

using json = nlohmann::json;
using namespace mealplanner::model;
using namespace mealplanner::infrastructure;

JsonDataLoader::JsonDataLoader(const IngredientDatabase& ingredientDatabase)
  : m_ingredientDatabase(ingredientDatabase)
{}

std::vector<Recipe> JsonDataLoader::loadRecipes(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open recipes file: " + path);
    }

    json data;
    file >> data;

    std::vector<Recipe> recipes;
    recipes.reserve(data.size());

    for (auto& j : data) {
        // Start with default Recipe
        Recipe recipe;

        // --- identity ---
        recipe.id   = j.at("id").get<std::string>();
        recipe.name = j.at("name").get<std::string>();

        if (j.contains("description")) {
            recipe.description = j["description"].get<std::string>();
        }

        // --- times & servings ---
        recipe.prepTime = Minutes{ j.value("prep_time_minutes", 0) };
        recipe.cookTime = Minutes{ j.value("cook_time_minutes", 0) };
        recipe.restTime = Minutes{ j.value("rest_time_minutes", 0) };
        recipe.servings = Servings{ j.value("servings", 1) };

        // --- ingredients ---
        if (j.contains("ingredients")) {
            for (auto& ji : j["ingredients"]) {
                // extract quantity first
                double amt = ji["quantity"].value("quantity", 0.0);
                std::string unit = ji["quantity"].value("unit", "");
                std::string note = ji["quantity"].value("note", "");
                Quantity qty{amt, unit, note};

                std::string name = ji.at("name").get<std::string>();
                bool optional    = ji.value("optional", false);

                recipe.ingredients.emplace_back(
                    std::move(name),
                    std::move(qty),
                    optional
                );
            }
        }

        // --- instructions, tags, allergens ---
        if (j.contains("instructions")) {
            for (auto& s : j["instructions"])
                recipe.instructions.push_back(s.get<std::string>());
        }
        if (j.contains("tags")) {
            for (auto& s : j["tags"])
                recipe.tags.push_back(s.get<std::string>());
        }
        if (j.contains("allergens")) {
            for (auto& s : j["allergens"])
                recipe.allergens.push_back(s.get<std::string>());
        }

        // --- equipment ---
        if (j.contains("equipment")) {
            for (auto& je : j["equipment"]) {
                std::string name = je.at("name").get<std::string>();
                bool optional    = je.value("optional", false);
                recipe.equipment.emplace_back(std::move(name), optional);
            }
        }

        // --- nutrition per serving ---
        recipe.kcal    = Calories{ j.value("kcal",    0) };
        recipe.protein = Grams   { j.value("protein", 0) };
        recipe.carbs   = Grams   { j.value("carbs",   0) };
        recipe.fat     = Grams   { j.value("fat",     0) };

        // --- optional metadata ---
        if (j.contains("cuisine")) {
            recipe.cuisine = cuisineFromString(j["cuisine"].get<std::string>());
        }
        if (j.contains("difficulty")) {
            recipe.difficulty = difficultyFromString(j["difficulty"].get<std::string>());
        }
        if (j.contains("cost")) {
            auto& jc = j["cost"];
            double  val = jc.value("value", 0.0);
            std::string cur = jc.value("currency", "");
            recipe.cost = Cost{val, currencyFromString(cur)};
        }

        recipe.batchFriendly     = j.value("batch-friendly",      false);
        recipe.prepAheadPossible = j.value("prep_ahead_possible", false);
        recipe.expirationDays    = j.value("expiration_day",      0);

        if (j.contains("suitable_for_goals")) {
            for (const auto& s : j["suitable_for_goals"])
                recipe.suitableForGoals.push_back(s.get<std::string>());
        }
        if (j.contains("required_skills")) {
            for (auto& s : j["required_skills"])
                recipe.requiredSkills.push_back(s.get<std::string>());
        }

        // --- source info ---
        if (j.contains("image_url"))  recipe.imageUrl  = j["image_url"].get<std::string>();
        if (j.contains("source_url")) recipe.sourceUrl = j["source_url"].get<std::string>();
        if (j.contains("author"))     recipe.author    = j["author"].get<std::string>();

        recipes.push_back(std::move(recipe));
    }

    return recipes;
}

UserProfile JsonDataLoader::loadUserProfile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open user profile file: " + path);
    }

    json j;
    file >> j;

    // **Ensure this is NOT declared const**, so we can mutate its fields
    UserProfile user{
        j.at("name").get<std::string>(),
        j.value("calorie_target",        2000),
        j.value("meals_per_day",            3),
        j.value("snack_slots",              1),
        Minutes{ j.value("max_prep_time_minutes", 30) }
    };

    if (j.contains("dietary_restrictions")) {
        for (auto& dr : j["dietary_restrictions"])
            user.dietaryRestrictions.push_back(dr.get<std::string>());
    }

    if (j.contains("macro_ratios")) {
        auto& m = j["macro_ratios"];
        user.macroRatios.protein = m.value("protein", 0.25);
        user.macroRatios.carbs   = m.value("carbs",   0.50);
        user.macroRatios.fat     = m.value("fat",     0.25);
    }

    return user;
}
