#include "core/MealPlan.h"
#include "core/NutritionUtils.h"

MacroRatios MealPlan::GetRatios() const {
    return NutritionUtils::calculateRatios(totalProtein, totalCarbs, totalFats, totalKcal);
}
