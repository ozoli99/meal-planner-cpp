#include "core/NutritionUtils.h"
#include <algorithm>

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

Recipe NutritionUtils::computeNutritionFromIngredients(const Recipe& recipe) {
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
