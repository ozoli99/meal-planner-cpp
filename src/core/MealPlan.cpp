#include "core/MealPlan.h"
#include "core/NutritionUtils.h"

using namespace mealplanner::model;

MacroRatios MealPlan::GetRatios() const {
    return NutritionUtils::calculateRatios(totalProtein, totalCarbs, totalFats, totalKcal);
}
