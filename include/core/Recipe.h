#ifndef RECIPE_H
#define RECIPE_H

#include <vector>
#include <string>
#include <optional>
#include <stdexcept>

#include "NutritionUnits.h"
#include "Ingredient.h"
#include "Equipment.h"
#include "Cost.h"
#include "Time.h"
#include "MacroRatios.h"
#include "Difficulty.h"
#include "Cuisine.h"

namespace mealplanner::model {
    /**
     * @brief Represents a complete recipe with ingredients, instructions, nutrition, and metadata.
     */
    struct Recipe {
        // Identity & classification
        std::string id;   ///< Unique identifier (e.g., "r1").
        std::string name; ///< Human-readable name (e.g., "Oatmeal with Berries").
        std::optional<std::string> description;
    
        // Time & yield
        Minutes prepTime = Minutes{0}; ///< Preparation time (excluding cooking).
        Minutes cookTime = Minutes{0}; ///< Cooking time.
        Minutes restTime = Minutes{0}; ///< Optional rest time (e.g., for dough).
        Servings servings = Servings{1}; ///< Number of servings the recipe yields.
    
        // Recipe content
        std::vector<Ingredient> ingredients; ///< List of ingredients with amounts and macros.
        std::vector<std::string> instructions;            ///< Cooking/preparation steps.
        
        // Metadata
        std::vector<std::string> tags;      ///< General-purpose tags (e.g., "vegetarian", "quick").
        std::vector<std::string> allergens; ///< Known allergens (e.g., "nuts", "gluten").
        std::vector<Equipment> equipment;   ///< Required equipment (e.g., "blender", "oven").
    
        // Nutritional info (per serving)
        Calories kcal = Calories{0}; ///< Per-serving calories.
        Grams protein = Grams{0};    ///< Per-serving protein in grams.
        Grams carbs = Grams{0};      ///< Per-serving carbohydrates in grams.
        Grams fat = Grams{0};        ///< Per-serving fat in grams.
    
        // Advanced filtering & info
        std::optional<Cuisine> cuisine;            ///< Cuisine origin (e.g., "Italian", "Japanese").
        std::optional<Difficulty> difficulty;      ///< Difficulty level (e.g., "easy", "intermediate").
        std::optional<Cost> cost;                  ///< Approximate cost in user-defined currency.
        bool batchFriendly = false;                ///< Indicates if it's good for meal prepping.
        bool prepAheadPossible = false;            ///< Indicates if it can be prepared in advance.
        int expirationDays = 0;                    ///< How many days it can be stored (e.g., 3 days in fridge).
        std::vector<std::string> suitableForGoals; ///< Tags like "weight_loss", "bulking", "maintenance".
        std::vector<std::string> requiredSkills;   ///< Skills needed (e.g., "chopping", "baking").
    
        // Source info
        std::optional<std::string> imageUrl;  ///< Optional image URL or relative path.
        std::optional<std::string> sourceUrl; ///< Original source (e.g., blog or cookbook URL).
        std::optional<std::string> author;    ///< Creator or source of the recipe.
    
        Recipe(std::string id_, std::string name_, Servings servings_)
            : id(std::move(id_)), name(std::move(name_)), servings(servings_) {
            if (id.empty() || name.empty()) {
                throw std::invalid_argument("Recipe requires non-empty id & name");
            }
        }
        Recipe() = default;

        /**
         * @brief Calculates total time required (prep + cook + rest).
         */
        Minutes totalTime() const {
            return prepTime + cookTime + restTime;
        }
    };
}

#endif // RECIPE_H