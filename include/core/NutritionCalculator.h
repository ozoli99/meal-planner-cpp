#ifndef NUTRITION_CALCULATOR_H
#define NUTRITION_CALCULATOR_H

#include "core/Recipe.h"
#include "core/MealPlan.h"

class NutritionCalculator {
public:
    // Computes and fills kcal, protein, carbs, fat fields based on ingredients
    static Recipe enrichRecipeWithNutrition(const Recipe& recipe);
    // Sums total macros for all selected recipes
    static MealPlan computeMealPlanNutrition(const MealPlan& plan);
};

#endif // NUTRITION_CALCULATOR_H