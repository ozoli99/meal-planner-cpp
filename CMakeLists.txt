cmake_minimum_required(VERSION 3.16)
project(MealPlanner VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Use vcpkg-installed libraries
find_package(nlohmann_json CONFIG REQUIRED)
find_package(CLI11 CONFIG REQUIRED)

# App source files
add_executable(mealplanner
    src/interface/cli/main.cpp
    src/interface/cli/MealPlannerCLI.cpp
    src/interface/presenter/MealPlanPresenter.cpp
    src/interface/presenter/TextMealPlanFormatter.cpp
    src/interface/presenter/JsonMealPlanFormatter.cpp
    src/interface/presenter/MarkdownMealPlanFormatter.cpp
    src/application/BalancedMealPlanner.cpp
    src/infrastructure/JsonDataLoader.cpp
    src/core/NutritionUtils.cpp
    src/core/MealPlan.cpp
)

target_include_directories(mealplanner PRIVATE
    include
    include/core
    include/application
    include/infrastructure
    include/interface/cli
)

# Link libraries from vcpkg
target_link_libraries(mealplanner
    PRIVATE nlohmann_json::nlohmann_json
    PRIVATE CLI11::CLI11
)
