#include "interface/presenter/MealPlanPresenter.h"
#include "interface/presenter/TextMealPlanFormatter.h"
#include "interface/presenter/JsonMealPlanFormatter.h"
#include <iostream>
#include <fstream>

namespace {
    std::unique_ptr<IMealPlanFormatter> createFormatter(const std::string& format) {
        if (format == "json") return std::make_unique<JsonMealPlanFormatter>();
        return std::make_unique<TextMealPlanFormatter>();
    }
}

void MealPlanPresenter::printToConsole(const MealPlan& plan, const std::string& format, bool verbose) {
    auto formatter = createFormatter(format);
    std::cout << formatter->format(plan, verbose) << "\n";
}

void MealPlanPresenter::exportToFile(const MealPlan& plan, const std::string& path, const std::string& format, bool verbose) {
    auto formatter = createFormatter(format);
    std::ofstream out(path);
    if (!out) {
        std::cerr << "❌ Could not write to file: " << path << "\n";
        return;
    }
    out << formatter->format(plan, verbose);
}
