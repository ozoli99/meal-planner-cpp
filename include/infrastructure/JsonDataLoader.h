#ifndef JSON_DATA_LOADER_H
#define JSON_DATA_LOADER_H

#include <vector>
#include <string>
#include "core/Recipe.h"
#include "core/UserProfile.h"
#include "core/IngredientDatabase.h"
#include "IRecipeRepository.h"

namespace mealplanner::infrastructure {
    class JsonDataLoader : public IRecipeRepository {
    public:
        explicit JsonDataLoader(const model::IngredientDatabase& ingredientDatabase);
    
        std::vector<model::Recipe> loadRecipes(const std::string& path) override;
        model::UserProfile loadUserProfile(const std::string& path) override;
    
    private:
        const model::IngredientDatabase& m_ingredientDatabase;
    };
}

#endif // JSON_DATA_LOADER_H