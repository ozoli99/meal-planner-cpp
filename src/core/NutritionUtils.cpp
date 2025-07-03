#include "core/NutritionUtils.h"
#include "core/MealPlan.h"
#include "core/UserProfile.h"
#include <algorithm>

using namespace mealplanner::model;

MacroRatios NutritionUtils::calculateRatios(int protein, int carbs, int fat, int totalKcal) {
    if (totalKcal == 0) {
        return {};
    }

    return {
        (protein * 4.0) / totalKcal,
        (carbs * 4.0) / totalKcal,
        (fat * 9.0) / totalKcal
    };
}

bool NutritionUtils::isRecipeCompliant(const Recipe& recipe, const std::vector<std::string>& restrictions) {
    for (const auto& restriction : restrictions) {
        if (std::find(recipe.tags.begin(), recipe.tags.end(), restriction) == recipe.tags.end()) {
            return false;
        }
    }
    return true;
}

double NutritionUtils::scorePlan(const MealPlan& plan, const UserProfile& user) {
    if (plan.totalKcal == 0) {
        return 0.0;
    }

    MacroRatios actual = plan.GetRatios();
    MacroRatios target = user.macroRatios;

    double proteinDiff = std::abs(actual.protein - target.protein);
    double carbsDiff = std::abs(actual.carbs - target.carbs);
    double fatDiff = std::abs(actual.fat - target.fat);

    double macroPenalty = proteinDiff + carbsDiff + fatDiff;

    double kcalPenalty = std::abs(plan.totalKcal - user.calorieTarget) / user.calorieTarget;

    return -(macroPenalty * 0.7 + kcalPenalty * 0.3);
}