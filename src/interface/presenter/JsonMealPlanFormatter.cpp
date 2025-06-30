#include "interface/presenter/JsonMealPlanFormatter.h"
#include <nlohmann/json.hpp>

std::string JsonMealPlanFormatter::format(const MealPlan& plan, bool /*verbose*/) const {
    nlohmann::json j;

    for (const auto& recipe : plan.selectedRecipes) {
        j["recipes"].push_back({
            {"name", recipe.name},
            {"kcal", recipe.kcal},
            {"protein", recipe.protein},
            {"carbs", recipe.carbs},
            {"fat", recipe.fat},
            {"prep_time_minutes", recipe.prepTimeMinutes},
            {"tags", recipe.tags}
        });
    }

    j["summary"] = {
        {"total_kcal", plan.totalKcal},
        {"total_protein", plan.totalProtein},
        {"total_carbs", plan.totalCarbs},
        {"total_fats", plan.totalFats},
        {"macro_ratios", {
            {"protein", plan.GetRatios().protein},
            {"carbs", plan.GetRatios().carbs},
            {"fat", plan.GetRatios().fat}
        }}
    };

    return j.dump(2);
}
