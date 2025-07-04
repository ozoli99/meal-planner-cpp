#include "core/MealPlan.h"
#include "core/NutritionUtils.h"

using namespace mealplanner::model;

// Returns macro ratios (protein, carbs, fat) as fractions of total calories
MacroRatios MealPlan::GetRatios() const {
    return NutritionUtils::calculateRatios(totalProtein, totalCarbs, totalFats, totalKcal);
}
