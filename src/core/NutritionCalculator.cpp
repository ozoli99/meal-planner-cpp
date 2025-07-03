#include "core/NutritionCalculator.h"

using namespace mealplanner::model;

NutritionCalculator::NutritionCalculator(const IngredientDatabase& ingredientDatabase)
    : m_ingredientDatabase(ingredientDatabase) {}

Recipe NutritionCalculator::enrichRecipeWithNutrition(const Recipe& recipe) const {
    Recipe copy = recipe;
    copy.kcal = 0;
    copy.protein = 0;
    copy.carbs = 0;
    copy.fat = 0;

    for (const auto& ingredient : recipe.ingredients) {
        if (!m_ingredientDatabase.has(ingredient.name)) {
            continue;
        }

        const auto& databaseEntry = m_ingredientDatabase.getPerUnitInfo(ingredient.name);
        
        double amount = ingredient.quantity.amount;
        double multiplier = amount / 100.0;

        copy.kcal += static_cast<int>(databaseEntry.kcalPer100g * multiplier + 0.5);
        copy.protein += static_cast<int>(databaseEntry.proteinPer100g * multiplier + 0.5);
        copy.carbs += static_cast<int>(databaseEntry.carbsPer100g * multiplier + 0.5);
        copy.fat += static_cast<int>(databaseEntry.fatPer100g * multiplier + 0.5);
    }

    return copy;
}

MealPlan NutritionCalculator::computeMealPlanNutrition(const MealPlan& plan) const {
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