#ifndef INGREDIENT_DATABASE_H
#define INGREDIENT_DATABASE_H

#include <unordered_map>
#include <string>
#include <vector>

/**
 * @brief Stores metadata and nutrition info per 100g/ml/unit for each known ingredient.
 */
struct IngredientDatabaseEntry {
    std::string name;              ///< Name of the ingredient (e.g., "oats").
    std::string defaultUnit = "g"; ///< Unit of measurement (e.g., "g", "ml", "tbsp").

    // Nutritional values per 100g/ml/unit
    double kcalPer100g = 0.0;    ///< Calories per unit.
    double proteinPer100g = 0.0; ///< Protein content per unit (grams).
    double carbsPer100g = 0.0;   ///< Carbohydrates per unit (grams).
    double fatPer100g = 0.0;     ///< Fat content per unit (grams).

    // Additional metadata
    std::string form;              ///< Physical form (e.g., "chopped", "frozen").
    std::string category;          ///< Category or food group (e.g., "dairy", "grain").
    std::string brand;             ///< Optional brand name.
    std::vector<std::string> tags; ///< Tags such as "organic", "gluten_free".

    std::unordered_map<std::string, std::string> substitutions; ///< Suggested replacements (e.g., "milk" -> "soy milk").
};

class IngredientDatabase {
public:
    void loadFromFile(const std::string& path);
    bool has(const std::string& name) const;
    IngredientDatabaseEntry getPerUnitInfo(const std::string& name) const;

private:
    std::unordered_map<std::string, IngredientDatabaseEntry> m_ingredients;
};

#endif // INGREDIENT_DATABASE_H