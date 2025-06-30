#ifndef JSON_DATA_LOADER_H
#define JSON_DATA_LOADER_H

#include <vector>
#include <string>
#include "core/Recipe.h"
#include "core/UserProfile.h"
#include "IRecipeRepository.h"

class JsonDataLoader : public IRecipeRepository {
public:
    std::vector<Recipe> loadRecipes(const std::string& path) override;
    UserProfile loadUserProfile(const std::string& path) override;
};

#endif // JSON_DATA_LOADER_H