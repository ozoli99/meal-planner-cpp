#include "core/MealPlan.h"

MacroRatios MealPlan::GetRatios() const {
    return NutritionUtils::calculateRatios(totalProtein, totalCarbs, totalFats, totalKcal);
}
