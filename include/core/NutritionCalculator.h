#ifndef NUTRITION_CALCULATOR_H
#define NUTRITION_CALCULATOR_H

#include "core/Recipe.h"
#include "core/MealPlan.h"
#include "core/IngredientDatabase.h"

class NutritionCalculator {
public:
    explicit NutritionCalculator(const IngredientDatabase& ingredientDatabase);

    mealplanner::model::Recipe enrichRecipeWithNutrition(const mealplanner::model::Recipe& recipe) const;
    mealplanner::model::MealPlan computeMealPlanNutrition(const mealplanner::model::MealPlan& plan) const;

private:
    const IngredientDatabase& m_ingredientDatabase;
};

#endif // NUTRITION_CALCULATOR_H