#include "core/NutritionCalculator.h"

using namespace mealplanner::model;

NutritionCalculator::NutritionCalculator(const IngredientDatabase& ingredientDatabase)
    : m_ingredientDatabase(ingredientDatabase) {}

Recipe NutritionCalculator::enrichRecipeWithNutrition(const Recipe& recipe) const {
    Recipe copy = recipe;
    copy.kcal = Calories(0);
    copy.protein = Grams{0};
    copy.carbs = Grams{0};
    copy.fat = Grams{0};

    for (const auto& ingredient : recipe.ingredients) {
        auto opt = m_ingredientDatabase.getPerUnitInfo(ingredient.name);
        if (!opt) {
            continue;
        }

        const auto& databaseEntry = *opt;
        
        double amount = ingredient.quantity.amount;
        double multiplier = amount / 100.0;

        int kcalDelta = static_cast<int>(databaseEntry.GetKcalPer100g().value * multiplier + 0.5);
        int proteinDelta = static_cast<int>(databaseEntry.GetProteinPer100g().value * multiplier + 0.5);
        int carbsDelta = static_cast<int>(databaseEntry.GetCarbsPer100g().value * multiplier + 0.5);
        int fatDelta = static_cast<int>(databaseEntry.GetFatPer100g().value * multiplier + 0.5);

        copy.kcal += Calories{kcalDelta};
        copy.protein += Grams{proteinDelta};
        copy.carbs += Grams{carbsDelta};
        copy.fat += Grams{fatDelta};
    }

    return copy;
}

MealPlan NutritionCalculator::computeMealPlanNutrition(const MealPlan& plan) const {
    MealPlan enriched = plan;
    enriched.totalKcal = Calories{0};
    enriched.totalProtein = Grams{0};
    enriched.totalCarbs = Grams{0};
    enriched.totalFats = Grams{0};

    for (const auto& recipe : plan.selectedRecipes) {
        auto r = enrichRecipeWithNutrition(recipe);
        enriched.totalKcal += r.kcal;
        enriched.totalProtein += r.protein;
        enriched.totalCarbs += r.carbs;
        enriched.totalFats += r.fat;
    }

    return enriched;
}