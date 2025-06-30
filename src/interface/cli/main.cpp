#include <stdexcept>
#include <CLI/CLI.hpp>
#include "MealPlannerCLI.h"
#include "infrastructure/JsonDataLoader.h"
#include "application/BalancedMealPlanner.h"
#ifdef _WIN32
#include <windows.h>
#endif

int main(int argc, char** argv) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    CLI::App app{"🍽️ Meal Planner CLI"};
    
    std::string userPath;
    std::string recipePath;
    std::string outputPath;
    std::string planType = "balanced";
    std::string format = "text";
    bool verbose = false;
    
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--format" && i + 1 < argc) {
            format = argv[++i];
        }
    }

    app.add_option("-u,--user", userPath, "Path to user profile JSON")->required();
    app.add_option("-r,--recipes", recipePath, "Path to recipes JSON")->required();
    app.add_option("-p,--plan", planType, "Meal plan type (default: balanced)");
    app.add_option("-f,--format", format, "Output format: text or json")->check(CLI::IsMember({"text", "json"}));
    app.add_flag("-v,--verbose", verbose, "Enable detailed output");
    app.add_option("-o,--output", outputPath, "Optional output file path");

    CLI11_PARSE(app, argc, argv);

    JsonDataLoader loader;
    BalancedMealPlanner planner;
    MealPlannerCLI cli(loader, planner);
    cli.run(userPath, recipePath, planType, verbose, outputPath, format);

    return 0;
}