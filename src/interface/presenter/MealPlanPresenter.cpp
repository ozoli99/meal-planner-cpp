#include "interface/presenter/MealPlanPresenter.h"
#include "interface/presenter/TextMealPlanFormatter.h"
#include "interface/presenter/JsonMealPlanFormatter.h"
#include "interface/presenter/MarkdownMealPlanFormatter.h"
#include <iostream>
#include <fstream>

void MealPlanPresenter::PrintToConsole(const MealPlan& plan, const std::string& format, bool verbose) {
    auto formatter = createFormatter(format);
    if (!formatter) {
        std::cerr << "❌ Unknown format: " << format << "\n";
        return;
    }
    std::cout << formatter->format(plan, verbose) << "\n";
}

void MealPlanPresenter::ExportToFile(const MealPlan& plan, const std::string& path, const std::string& format, bool verbose) {
    auto formatter = createFormatter(format);
    if (!formatter) {
        std::cerr << "❌ Unknown format: " << format << "\n";
        return;
    }

    std::ofstream out(path);
    if (!out) {
        std::cerr << "❌ Could not write to file: " << path << "\n";
        return;
    }
    out << formatter->format(plan, verbose);
}

std::unique_ptr<IMealPlanFormatter> MealPlanPresenter::createFormatter(const std::string& format) {
    if (format == "text") {
        return std::make_unique<TextMealPlanFormatter>();
    } else if (format == "json") {
        return std::make_unique<JsonMealPlanFormatter>();
    } else if (format == "markdown") {
        return std::make_unique<MarkdownMealPlanFormatter>();
    }
    return nullptr;
}