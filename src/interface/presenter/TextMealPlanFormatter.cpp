#include "interface/presenter/TextMealPlanFormatter.h"
#include <sstream>

std::string TextMealPlanFormatter::format(const MealPlan& plan, bool verbose) const {
    std::ostringstream oss;
    oss << "\n📅 Meal Plan\n" << std::string(40, '─') << "\n";

    for (const auto& recipe : plan.selectedRecipes) {
        oss << "🍽️  " << recipe.name << " (" << recipe.kcal << " kcal)"
            << " | P: " << recipe.protein << "g"
            << " C: " << recipe.carbs << "g"
            << " F: " << recipe.fat << "g";
        if (verbose) {
            oss << " | ⏱️ " << recipe.prepTimeMinutes << " min";
        }
        oss << "\n";
    }

    oss << std::string(40, '─') << "\n";
    oss << "Total: " << plan.totalKcal << " kcal | "
        << "Protein: " << plan.totalProtein << "g | "
        << "Carbs: " << plan.totalCarbs << "g | "
        << "Fat: " << plan.totalFats << "g\n";

    MacroRatios ratios = plan.GetRatios();
    oss << "Macros: P" << static_cast<int>(ratios.protein * 100) << "% "
        << "C" << static_cast<int>(ratios.carbs * 100) << "% "
        << "F" << static_cast<int>(ratios.fat * 100) << "%\n";

    return oss.str();
}