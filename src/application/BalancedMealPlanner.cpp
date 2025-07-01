#include "application/BalancedMealPlanner.h"
#include "core/NutritionUtils.h"

MealPlan BalancedMealPlanner::generateMealPlan(const std::vector<Recipe>& recipes, const UserProfile& user) {
    MealPlan bestPlan;
    double bestScore = -1e9;

    const int maxCombinations = 1 << recipes.size();
    for (int mask = 1; mask < maxCombinations; ++mask) {
        MealPlan candidate;
        for (size_t i = 0; i < recipes.size(); ++i) {
            if (!(mask & (1 << i))) {
                continue;
            }
            
            const auto& r = recipes[i];
            if (r.prepTimeMinutes > user.maxPrepTimeMinutes) {
                continue;
            }
            if (!NutritionUtils::isRecipeCompliant(r, user.dietaryRestrictions)) {
                continue;
            }
            
            candidate.selectedRecipes.push_back(r);
            candidate.totalKcal += r.kcal;
            candidate.totalProtein += r.protein;
            candidate.totalCarbs += r.carbs;
            candidate.totalFats += r.fat;
        }
        if (candidate.selectedRecipes.empty()) {
            continue;
        }

        double score = NutritionUtils::scorePlan(candidate, user);
        if (score > bestScore) {
            bestScore = score;
            bestPlan = candidate;
        }
    }

    return bestPlan;
}
