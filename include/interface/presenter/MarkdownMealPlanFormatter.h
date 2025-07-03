#ifndef MARKDOWN_MEAL_PLAN_FORMATTER_H
#define MARKDOWN_MEAL_PLAN_FORMATTER_H

#include "IMealPlanFormatter.h"

class MarkdownMealPlanFormatter : public IMealPlanFormatter {
public:
    std::string format(const mealplanner::model::MealPlan& plan, bool verbose = false) const override;
};

#endif // MARKDOWN_MEAL_PLAN_FORMATTER_H
