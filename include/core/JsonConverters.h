#ifndef JSON_CONVERTERS_H
#define JSON_CONVERTERS_H

#include <stdexcept>
#include <optional>
#include <nlohmann/json.hpp>

#include "Ingredient.h"
#include "Equipment.h"
#include "Cost.h"
#include "Recipe.h"
#include "UserProfile.h"
#include "Difficulty.h"
#include "Cuisine.h"
#include "Quantity.h"

namespace nlohmann {
    template<>
    struct adl_serializer<mealplanner::model::Quantity> {
        static void from_json(const json& j, mealplanner::model::Quantity& quantity) noexcept {
            quantity.amount = j.value("quantity", 0.0);
            quantity.unit = j.value("unit", std::string{});
            quantity.note = j.value("note", std::string{});
        }
        static void to_json(json& j, const mealplanner::model::Quantity& quantity) {
            j = json{
                {"quantity", quantity.amount},
                {"unit", quantity.unit},
                {"note", quantity.note}
            };
        }
    };

    template<>
    struct adl_serializer<mealplanner::model::Ingredient> {
        static void from_json(const json& j, mealplanner::model::Ingredient& ingredient) {
            j.at("name").get_to(ingredient.name);
            j.at("quantity").get_to(ingredient.quantity);
            ingredient.optional = j.value("optional", false);
        }
        static void to_json(json& j, const mealplanner::model::Ingredient& ingredient) {
            j = json{
                {"name", ingredient.name},
                {"quantity", ingredient.quantity},
                {"optional", ingredient.optional}
            };
        }
    };

    template<>
    struct adl_serializer<mealplanner::model::Equipment> {
        static void from_json(const json& j, mealplanner::model::Equipment& equipment) {
            j.at("name").get_to(equipment.name);
            equipment.optional = j.value("optional", false);
        }
        static void to_json(json& j, const mealplanner::model::Equipment& equipment) {
            j = json{
                {"name", equipment.name},
                {"optional", equipment.optional}
            };
        }
    };

    template<>
    struct adl_serializer<mealplanner::model::Cost> {
        static void from_json(const json& j, mealplanner::model::Cost& cost) {
            cost.value = j.value("value", 0.0);
            cost.currency = j.value("currency", std::string{});
        }
        static void to_json(json& j, const mealplanner::model::Cost& cost) {
            j = json{
                {"value", cost.value},
                {"currency", cost.currency}
            };
        }
    };

    template<>
    struct adl_serializer<mealplanner::model::Difficulty> {
        static void from_json(const json& j, mealplanner::model::Difficulty& difficulty) {
            auto opt = mealplanner::model::difficultyFromString(j.get<std::string>());
            if (!opt) {
                throw std::runtime_error("Invalid difficulty");
            }
            difficulty = *opt;
        }
        static void to_json(json& j, const mealplanner::model::Difficulty& difficulty) {
            j = static_cast<int>(difficulty);
        }
    };

    template<>
    struct adl_serializer<mealplanner::model::Cuisine> {
        static void from_json(const json& j, mealplanner::model::Cuisine& cuisine) {
            cuisine = mealplanner::model::cuisineFromString(j.get<std::string>()).value_or(mealplanner::model::Cuisine::Other);
        }
        static void to_json(json& j, const mealplanner::model::Cuisine& cost) {
            j = static_cast<int>(cost);
        }
    };

    template<>
    struct adl_serializer<mealplanner::model::Recipe> {
        static void from_json(const json& j, mealplanner::model::Recipe& recipe) {
            using namespace mealplanner::model;
    
            j.at("id").get_to(recipe.id);
            j.at("name").get_to(recipe.name);

            if (j.contains("description")) {
                recipe.description = j.at("description").get<std::string>();
            } else {
                recipe.description = std::nullopt;
            }
    
            recipe.prepTime = Minutes{ j.value("prep_time_minutes", 0) };
            recipe.cookTime = Minutes{ j.value("cook_time_minutes", 0) };
            recipe.restTime = Minutes{ j.value("rest_time_minutes", 0) };
            recipe.servings = j.value("servings", 1);
    
            if (j.contains("ingredients")) {
                j.at("ingredients").get_to(recipe.ingredients);
            }
            if (j.contains("instructions")) {
                j.at("instructions").get_to(recipe.instructions);
            }
            if (j.contains("tags")) {
                j.at("tags").get_to(recipe.tags);
            }
            if (j.contains("allergens")) {
                j.at("allergens").get_to(recipe.allergens);
            }
            if (j.contains("equipment")) {
                j.at("equipment").get_to(recipe.equipment);
            }
    
            recipe.kcal = j.value("kcal", 0);
            recipe.protein = j.value("protein", 0);
            recipe.carbs = j.value("carbs", 0);
            recipe.fat = j.value("fat", 0);
    
            if (j.contains("cuisine")) {
                recipe.cuisine = j.at("cuisine").get<Cuisine>();
            } else {
                recipe.cuisine = std::nullopt;
            }

            if (j.contains("difficulty")) {
                recipe.difficulty = j.at("difficulty").get<Difficulty>();
            } else {
                recipe.difficulty = std::nullopt;
            }

            if (j.contains("cost")) {
                recipe.cost = j.at("cost").get<Cost>();
            } else {
                recipe.cost = std::nullopt;
            }
    
            recipe.batchFriendly = j.value("batch-friendly", false);
            recipe.prepAheadPossible = j.value("prep_ahead_possible", false);
            recipe.expirationDays = j.value("expiration_day", 0);
    
            if (j.contains("suitable_for_goals")) {
                j.at("suitable_for_goals").get_to(recipe.suitableForGoals);
            }
            if (j.contains("required_skills")) {
                j.at("required_skills").get_to(recipe.requiredSkills);
            }
    
            if (j.contains("image_url")) {
                recipe.imageUrl = j.at("image_url").get<std::string>();
            } else {
                recipe.imageUrl = std::nullopt;
            }

            if (j.contains("source_url")) {
                recipe.sourceUrl = j.at("source_url").get<std::string>();
            } else {
                recipe.sourceUrl = std::nullopt;
            }

            if (j.contains("author")) {
                recipe.author = j.at("author").get<std::string>();
            } else {
                recipe.author = std::nullopt;
            }
        }
        static void to_json(json& j, const mealplanner::model::Recipe& recipe) {
            j = json{
                {"id", recipe.id},
                {"name", recipe.name}
            };
        }
    };

    template<>
    struct adl_serializer<mealplanner::model::UserProfile> {
        static void from_json(const json& j, mealplanner::model::UserProfile& user) {
            using namespace mealplanner::model;
    
            j.at("name").get_to(user.name);
            user.calorieTarget = j.value("calorie_target", 2000);
            user.mealsPerDay = j.value("meals_per_day", 3);
            user.snackSlots = j.value("snack_slots", 1);
            user.maxPrepTime = Minutes{ j.value("max_prep_time_minutes", 30) };
    
            if (j.contains("dietary_restrictions")) {
                j.at("dietary_restrictions").get_to(user.dietaryRestrictions);
            }
    
            if (j.contains("macro_ratios")) {
                auto m = j.at("macro_ratios");
                user.macroRatios.protein = m.value("protein", 0.25);
                user.macroRatios.carbs = m.value("carbs", 0.50);
                user.macroRatios.fat = m.value("fat", 0.25);
            }
        }
        static void to_json(json& j, const mealplanner::model::UserProfile& user) {
            j = json{
                {"name", user.name}
            };
        }
    };
} // namespace nlohmann

#endif // JSON_CONVERTERS_H