#ifndef JSON_DATA_LOADER_H
#define JSON_DATA_LOADER_H

#include <vector>
#include <string>
#include <unordered_map>
#include "core/Recipe.h"
#include "core/UserProfile.h"
#include "core/IngredientDatabase.h"
#include "IRecipeRepository.h"

class JsonDataLoader : public IRecipeRepository {
public:
    JsonDataLoader(const IngredientDatabase& ingredientDb);

    std::vector<Recipe> loadRecipes(const std::string& path) override;
    UserProfile loadUserProfile(const std::string& path) override;

private:
    const IngredientDatabase& m_ingredientDb;
};

#endif // JSON_DATA_LOADER_H