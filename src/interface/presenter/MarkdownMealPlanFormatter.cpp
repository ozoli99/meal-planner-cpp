#include "../../include/interface/presenter/MarkdownMealPlanFormatter.h"
#include <sstream>

std::string MarkdownMealPlanFormatter::format(const MealPlan& plan, bool verbose) const {
    std::ostringstream out;

    out << "## 🥗 Meal Plan (Markdown Export)\n\n";

    for (const auto& recipe : plan.selectedRecipes) {
        out << "### 🍽️ " << recipe.name << "\n";
        out << "- **Kcal:** " << recipe.kcal << "\n";
        out << "- **Macros:** P: " << recipe.protein << "g, C: " << recipe.carbs << "g, F: " << recipe.fat << "g\n";
        if (verbose) {
            out << "- **Prep Time:** " << recipe.prepTimeMinutes << " min\n";
        }
        if (!recipe.tags.empty()) {
            out << "- **Tags:** ";
            for (size_t i = 0; i < recipe.tags.size(); ++i) {
                out << "`" << recipe.tags[i] << "`";
                if (i != recipe.tags.size() - 1) out << ", ";
            }
            out << "\n";
        }
        out << "\n";
    }

    out << "---\n\n";
    out << "**Total:** " << plan.totalKcal << " kcal | "
        << "P: " << plan.totalProtein << "g | "
        << "C: " << plan.totalCarbs << "g | "
        << "F: " << plan.totalFats << "g\n";

    MacroRatios ratios = plan.GetRatios();
    out << "**Macros:** P" << static_cast<int>(ratios.protein * 100) << "% "
        << "C" << static_cast<int>(ratios.carbs * 100) << "% "
        << "F" << static_cast<int>(ratios.fat * 100) << "%\n";

    return out.str();
}
