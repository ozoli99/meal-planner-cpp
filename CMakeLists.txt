cmake_minimum_required(VERSION 3.16)
project(MealPlanner VERSION 0.1 LANGUAGES CXX)

#-------------------------------------------------------------------------------
# Global policies, standards & warnings
#-------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# treat warnings as errors, but use MSVC‐friendly flags when using MSVC
if (MSVC)
    # /W4 = “level 4” warnings, /WX = warnings-as-errors
    add_compile_options(/W4 /WX)
else()
    # GCC / Clang flags
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

#-------------------------------------------------------------------------------
# Find external dependencies
#-------------------------------------------------------------------------------
find_package(nlohmann_json CONFIG REQUIRED) # JSON serialization
find_package(CLI11 CONFIG REQUIRED)         # CLI parsing

#-------------------------------------------------------------------------------
# Model library (header-only + JsonConverters)
#-------------------------------------------------------------------------------
add_library(mealplanner-model INTERFACE)
target_include_directories(mealplanner-model
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include # finds model/*.h and JsonConverters.h
)

#-------------------------------------------------------------------------------
# Core library (nutrition, mealplan, database)
#-------------------------------------------------------------------------------
add_library(mealplanner-core
    src/core/NutritionUtils.cpp
    src/core/MealPlan.cpp
    src/core/NutritionCalculator.cpp
    src/core/IngredientDatabase.cpp
)
target_link_libraries(mealplanner-core
    PUBLIC
        mealplanner-model               # needs the model types
        nlohmann_json::nlohmann_json
)
target_include_directories(mealplanner-core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

#-------------------------------------------------------------------------------
# Infra library (JsonDataLoader + IRecipeRepository)
#-------------------------------------------------------------------------------
add_library(mealplanner-infra
    src/infrastructure/JsonDataLoader.cpp
)
target_include_directories(mealplanner-infra
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(mealplanner-infra
    PUBLIC
        mealplanner-core
        mealplanner-model
        nlohmann_json::nlohmann_json    # from_json/to_json are ADL hooks
)

#-------------------------------------------------------------------------------
# Application library
#-------------------------------------------------------------------------------
add_library(mealplanner-app
    src/application/BalancedMealPlanner.cpp
)
target_include_directories(mealplanner-app
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(mealplanner-app
    PUBLIC
        mealplanner-core
)

#-------------------------------------------------------------------------------
# CLI executable
#-------------------------------------------------------------------------------
add_executable(mealplanner
    src/interface/cli/main.cpp
    src/interface/cli/MealPlannerCLI.cpp
    src/interface/presenter/MealPlanPresenter.cpp
    src/interface/presenter/TextMealPlanFormatter.cpp
    src/interface/presenter/JsonMealPlanFormatter.cpp
    src/interface/presenter/MarkdownMealPlanFormatter.cpp
)
target_include_directories(mealplanner
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(mealplanner
    PRIVATE
        mealplanner-app     # brings in BalancedMealPlanner + core
        mealplanner-infra   # brings in JsonDataLoader + model + core + nlohmann_json
        CLI11::CLI11
)

#-------------------------------------------------------------------------------
# Installation rules
#-------------------------------------------------------------------------------
install(TARGETS mealplanner
    RUNTIME DESTINATION bin
)
