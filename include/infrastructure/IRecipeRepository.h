#ifndef I_RECIPE_REPOSITORY_H
#define I_RECIPE_REPOSITORY_H

#include <vector>
#include <string>
#include "core/Recipe.h"
#include "core/UserProfile.h"

class IRecipeRepository {
public:
    virtual ~IRecipeRepository() = default;
    
    virtual std::vector<Recipe> loadRecipes(const std::string& path) = 0;
    virtual UserProfile loadUserProfile(const std::string& path) = 0;
};

#endif // I_RECIPE_REPOSITORY_H