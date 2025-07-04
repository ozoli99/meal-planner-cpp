#ifndef INGREDIENT_DATABASE_ENTRY_H
#define INGREDIENT_DATABASE_ENTRY_H

#include <string>
#include <vector>
#include <unordered_map>
#include <optional>
#include <stdexcept>
#include <ostream>

#include "core/Unit.h"
#include "core/NutritionUnits.h"

namespace mealplanner::model {
    /**
     * @brief Immutable, type-safe representation of an ingredient's database entry.
     * @details Uses strong types for nutrition and optional fields for brand. Provides validation and hash support.
     */
    /**
     * @brief Represents a single entry in the ingredient database, including nutrition and metadata.
     *
     * All fields are immutable and validated on construction.
     */
    class [[nodiscard]] IngredientDatabaseEntry {
    public:
        /**
         * @brief Construct a new IngredientDatabaseEntry with validation.
         * @param name Name of the ingredient (required, non-empty)
         * @param defaultUnit Unit of measurement (required, non-empty)
         * @param kcalPer100g Calories per 100g (>=0)
         * @param proteinPer100g Protein per 100g (>=0)
         * @param carbsPer100g Carbs per 100g (>=0)
         * @param fatPer100g Fat per 100g (>=0)
         * @param form Physical form (optional)
         * @param category Food group/category (optional)
         * @param brand Brand name (optional)
         * @param tags Tags (optional)
         * @param substitutions Substitutions (optional)
         * @throws std::invalid_argument if required fields are missing or invalid
         */
        IngredientDatabaseEntry(std::string name, Unit defaultUnit, Calories kcalPer100g, Grams proteinPer100g, Grams carbsPer100g, Grams fatPer100g, std::string form = {}, std::string category = {}, std::optional<std::string> brand = std::nullopt, std::vector<std::string> tags = {}, std::unordered_map<std::string, std::string> substitutions = {})
            : m_name(std::move(name))
            , m_defaultUnit(defaultUnit)
            , m_kcalPer100g(kcalPer100g)
            , m_proteinPer100g(proteinPer100g)
            , m_carbsPer100g(carbsPer100g)
            , m_fatPer100g(fatPer100g)
            , m_form(std::move(form))
            , m_category(std::move(category))
            , m_brand(std::move(brand))
            , m_tags(std::move(tags))
            , m_substitutions(std::move(substitutions)) {
            validate();
        }
    
        const std::string& GetName() const { return m_name; }
        Unit GetDefaultUnit() const { return m_defaultUnit; }
        Calories GetKcalPer100g() const { return m_kcalPer100g; }
        Grams GetProteinPer100g() const { return m_proteinPer100g; }
        Grams GetCarbsPer100g() const { return m_carbsPer100g; }
        Grams GetFatPer100g() const { return m_fatPer100g; }
        const std::string& GetForm() const { return m_form; }
        const std::string& GetCategory() const { return m_category; }
        const std::optional<std::string>& GetBrand() const { return m_brand; }
        const std::vector<std::string>& GetTags() const { return m_tags; }
        const std::unordered_map<std::string, std::string>& GetSubstitutions() const { return m_substitutions; }
    
        /**
         * @brief Print a human-readable summary of the entry.
         */
        friend std::ostream& operator<<(std::ostream& os, const IngredientDatabaseEntry& entry) {
            os << "Ingredient: " << entry.m_name << " [" << toString(entry.m_defaultUnit) << "]\n"
               << "  kcal/100g: " << entry.m_kcalPer100g << ", protein: " << entry.m_proteinPer100g
               << ", carbs: " << entry.m_carbsPer100g << ", fat: " << entry.m_fatPer100g << "\n"
               << "  form: " << entry.m_form << ", category: " << entry.m_category;
            if (entry.m_brand) {
                os << ", brand: " << *entry.m_brand;
            }
            if (!entry.m_tags.empty()) {
                os << ", tags: ";
                for (const auto& tag : entry.m_tags) {
                    os << tag << ", ";
                }
            }
            if (!entry.m_substitutions.empty()) {
                os << "\n  substitutions: ";
                for (const auto& [from, to] : entry.m_substitutions) {
                    os << from << "->" << to << ", ";
                }
            }
            return os;
        }
    
        /**
         * @brief Equality comparison operator.
         */
        bool operator==(const IngredientDatabaseEntry& other) const {
            return m_name == other.m_name && m_defaultUnit == other.m_defaultUnit &&
                m_kcalPer100g == other.m_kcalPer100g && m_proteinPer100g == other.m_proteinPer100g &&
                m_carbsPer100g == other.m_carbsPer100g && m_fatPer100g == other.m_fatPer100g &&
                m_form == other.m_form && m_category == other.m_category && m_brand == other.m_brand &&
                m_tags == other.m_tags && m_substitutions == other.m_substitutions;
        }
    
    private:
        /**
         * @brief Validate the entry fields. Throws if invalid.
         */
        void validate() const {
            if (m_name.empty()) {
                throw std::invalid_argument("Ingredient name cannot be empty");
            }
            if (m_defaultUnit == Unit::Unknown) {
                throw std::invalid_argument("Default unit cannot be unknown");
            }
            if (m_kcalPer100g.value < 0.0 || m_proteinPer100g.value < 0.0 || m_carbsPer100g.value < 0.0 || m_fatPer100g.value < 0.0) {
                throw std::invalid_argument("Nutrition values must be >= 0");
            }
        }
    
        std::string m_name;
        Unit m_defaultUnit;
        Calories m_kcalPer100g;
        Grams m_proteinPer100g;
        Grams m_carbsPer100g;
        Grams m_fatPer100g;
        std::string m_form;
        std::string m_category;
        std::optional<std::string> m_brand;
        std::vector<std::string> m_tags;
        std::unordered_map<std::string, std::string> m_substitutions;
    };
} // namespace mealplanner::model

namespace std {
    template<>
    struct hash<mealplanner::model::IngredientDatabaseEntry> {
        std::size_t operator()(const mealplanner::model::IngredientDatabaseEntry& entry) const {
            std::size_t h1 = std::hash<std::string>{}(entry.GetName());
            std::size_t h2 = std::hash<int>{}(static_cast<int>(entry.GetDefaultUnit()));
            std::size_t h3 = std::hash<double>{}(entry.GetKcalPer100g().value);
            std::size_t h4 = std::hash<double>{}(entry.GetProteinPer100g().value);
            std::size_t h5 = std::hash<double>{}(entry.GetCarbsPer100g().value);
            std::size_t h6 = std::hash<double>{}(entry.GetFatPer100g().value);
            std::size_t h7 = std::hash<std::string>{}(entry.GetForm());
            std::size_t h8 = std::hash<std::string>{}(entry.GetCategory());
            std::size_t h9 = entry.GetBrand() ? std::hash<std::string>{}(*entry.GetBrand()) : 0;
            return h1 ^ h2 ^ h3 ^ h4 ^ h5 ^ h6 ^ h7 ^ h8 ^ h9;
        }
    };
} // namespace std

#endif // INGREDIENT_DATABASE_ENTRY_H
