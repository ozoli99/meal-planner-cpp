#include "core/NutritionCalculator.h"

Recipe NutritionCalculator::enrichRecipeWithNutrition(const Recipe& recipe) {
    Recipe copy = recipe;
    copy.kcal = 0;
    copy.protein = 0;
    copy.carbs = 0;
    copy.fat = 0;

    for (const auto& ingredient : recipe.ingredients) {
        copy.kcal += ingredient.kcalPerUnit * ingredient.quantity;
        copy.protein += ingredient.proteinPerUnit * ingredient.quantity;
        copy.carbs += ingredient.carbsPerUnit * ingredient.quantity;
        copy.fat += ingredient.fatPerUnit * ingredient.quantity;
    }

    return copy;
}

MealPlan NutritionCalculator::computeMealPlanNutrition(const MealPlan& plan) {
    MealPlan enriched = plan;
    enriched.totalKcal = 0;
    enriched.totalProtein = 0;
    enriched.totalCarbs = 0;
    enriched.totalFats = 0;

    for (const auto& recipe : plan.selectedRecipes) {
        auto r = enrichRecipeWithNutrition(recipe);
        enriched.totalKcal += r.kcal;
        enriched.totalProtein += r.protein;
        enriched.totalCarbs += r.carbs;
        enriched.totalFats += r.fat;
    }

    return enriched;
}