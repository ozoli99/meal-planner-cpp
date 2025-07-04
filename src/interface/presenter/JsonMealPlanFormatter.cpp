#include "interface/presenter/JsonMealPlanFormatter.h"
#include <nlohmann/json.hpp>

using namespace mealplanner::model;

std::string JsonMealPlanFormatter::format(const MealPlan& plan, bool /*verbose*/) const {
    nlohmann::json j;

    j["recipes"] = nlohmann::json::array();
    for (const auto& recipe : plan.selectedRecipes) {
        nlohmann::json rec;
        rec["name"] = recipe.name;
        rec["kcal"] = recipe.kcal.value;
        rec["protein"] = recipe.protein.value;
        rec["carbs"] = recipe.carbs.value;
        rec["fat"] = recipe.fat.value;
        rec["prep_time_minutes"] = recipe.prepTime.count();
        rec["tags"] = recipe.tags;
        j["recipes"].push_back(std::move(rec));
    }

    nlohmann::json summary;
    summary["total_kcal"]     = plan.totalKcal.value;
    summary["total_protein"]  = plan.totalProtein.value;
    summary["total_carbs"]    = plan.totalCarbs.value;
    summary["total_fats"]     = plan.totalFats.value;
    summary["macro_ratios"] = {
        {"protein", plan.GetRatios().protein},
        {"carbs",   plan.GetRatios().carbs},
        {"fat",     plan.GetRatios().fat}
    };
    j["summary"] = std::move(summary);

    return j.dump(2);
}
