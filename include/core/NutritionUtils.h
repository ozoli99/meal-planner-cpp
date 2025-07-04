#ifndef NUTRITION_UTILS_H
#define NUTRITION_UTILS_H

#include "Recipe.h"
#include "MealPlan.h"
#include "UserProfile.h"
#include <vector>
#include <string>

namespace NutritionUtils {
    mealplanner::model::MacroRatios calculateRatios(
        mealplanner::model::Grams protein,
        mealplanner::model::Grams carbs,
        mealplanner::model::Grams fat,
        mealplanner::model::Calories totalKcal);
    bool isRecipeCompliant(const mealplanner::model::Recipe& recipe, const std::vector<std::string>& restrictions);
    double scorePlan(const mealplanner::model::MealPlan& plan, const mealplanner::model::UserProfile& user);
}

#endif // NUTRITION_UTILS_H
