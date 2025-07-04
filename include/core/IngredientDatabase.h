#ifndef INGREDIENT_DATABASE_H
#define INGREDIENT_DATABASE_H

#include "IngredientDatabaseEntry.h"

namespace mealplanner::model {
    /**
     * @brief Ingredient database for lookup and management.
     * @details Provides loading, lookup, and safe access to ingredient metadata.
     */
    class IngredientDatabase {
    public:
        /**
         * @brief Load ingredient data from a file.
         * @param path Path to the data file (e.g., JSON).
         */
        void loadFromFile(const std::string& path);
    
        /**
         * @brief Check if an ingredient exists in the database.
         * @param name Ingredient name.
         * @return True if found, false otherwise.
         */
        bool has(const std::string& name) const;
    
        /**
         * @brief Get ingredient info by name.
         * @param name Ingredient name.
         * @return Optional entry if found, std::nullopt otherwise.
         */
        std::optional<IngredientDatabaseEntry> getPerUnitInfo(const std::string& name) const;
    
    private:
        std::unordered_map<std::string, IngredientDatabaseEntry> m_ingredients;
    };
} // namespace mealplanner::model

#endif // INGREDIENT_DATABASE_H