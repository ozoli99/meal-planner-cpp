#ifndef DATA_VALIDATION_H
#define DATA_VALIDATION_H

#include "core/UserProfile.h"
#include "core/Recipe.h"
#include <string>
#include <vector>

namespace mealplanner::util {
    inline std::vector<std::string> validateUserProfile(const model::UserProfile& user) {
        std::vector<std::string> errors;
        if (user.name.empty()) errors.push_back("User name is empty");
        if (user.calorieTarget <= 0) errors.push_back("Calorie target must be > 0");
        if (user.mealsPerDay <= 0) errors.push_back("Meals per day must be > 0");
        if (user.maxPrepTime.count() < 0) errors.push_back("Max prep time must be >= 0");
        // Add more checks as needed
        return errors;
    }

    inline std::vector<std::string> validateRecipe(const model::Recipe& recipe) {
        std::vector<std::string> errors;
        if (recipe.id.empty()) errors.push_back("Recipe id is empty");
        if (recipe.name.empty()) errors.push_back("Recipe name is empty");
        if (recipe.servings <= 0) errors.push_back("Recipe servings must be > 0");
        if (recipe.kcal < 0) errors.push_back("Calories (kcal) must be >= 0");
        if (recipe.protein < 0) errors.push_back("Protein must be >= 0");
        if (recipe.carbs < 0) errors.push_back("Carbs must be >= 0");
        if (recipe.fat < 0) errors.push_back("Fat must be >= 0");
        // Add more checks as needed
        return errors;
    }
}

#endif // DATA_VALIDATION_H
