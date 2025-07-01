#include "application/BalancedMealPlanner.h"
#include "core/NutritionUtils.h"

MealPlan BalancedMealPlanner::generateMealPlan(const std::vector<Recipe>& recipes, const UserProfile& user) {
    MealPlan plan;

    for (const auto& recipe : recipes) {
        if (recipe.prepTimeMinutes > user.maxPrepTimeMinutes) {
            continue;
        }

        if (!NutritionUtils::isRecipeCompliant(recipe, user.dietaryRestrictions)) {
            continue;
        }

        if (plan.totalKcal + recipe.kcal > user.calorieTarget * 1.1) {
            continue;
        }

        plan.selectedRecipes.push_back(recipe);
        plan.totalKcal += recipe.kcal;
        plan.totalProtein += recipe.protein;
        plan.totalCarbs += recipe.carbs;
        plan.totalFats += recipe.fat;
    }

    return plan;
}
