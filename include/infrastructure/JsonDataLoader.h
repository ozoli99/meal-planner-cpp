#ifndef JSON_DATA_LOADER_H
#define JSON_DATA_LOADER_H

#include <vector>
#include <string>
#include <unordered_map>
#include "core/Recipe.h"
#include "core/UserProfile.h"
#include "IRecipeRepository.h"

class JsonDataLoader : public IRecipeRepository {
public:
    std::vector<Recipe> loadRecipes(const std::string& path) override;
    UserProfile loadUserProfile(const std::string& path) override;

private:
    std::unordered_map<std::string, Ingredient> loadIngredientDatabase(const std::string& path);
    
    std::unordered_map<std::string, Ingredient> m_ingredients;
};

#endif // JSON_DATA_LOADER_H