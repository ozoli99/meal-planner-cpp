// #ifndef JSON_CONVERTERS_H
// #define JSON_CONVERTERS_H

// #include <stdexcept>
// #include <optional>
// #include <unordered_map>
// #include <nlohmann/json.hpp>

// #include "IngredientDatabaseEntry.h"
// #include "Ingredient.h"
// #include "Equipment.h"
// #include "Cost.h"
// #include "Recipe.h"
// #include "UserProfile.h"
// #include "Difficulty.h"
// #include "Cuisine.h"
// #include "Quantity.h"

// namespace nlohmann {

// ////////////////////////////////////////////////////////////////////////////////
// // IngredientDatabaseEntry
// ////////////////////////////////////////////////////////////////////////////////
// template<>
// struct adl_serializer<mealplanner::model::IngredientDatabaseEntry> {
//     static void from_json(const json& j, mealplanner::model::IngredientDatabaseEntry& entry) {
//         using namespace mealplanner::model;
//         std::string name     = j.at("name").get<std::string>();
//         Unit unit            = unitFromString(j.value("unit", "unknown"));
//         Calories kcal{static_cast<int>(j.value("kcal_per_100g", 0.0) + 0.5)};
//         Grams protein{static_cast<int>(j.value("protein_per_100g", 0.0) + 0.5)};
//         Grams carbs{static_cast<int>(j.value("carbs_per_100g", 0.0) + 0.5)};
//         Grams fat{static_cast<int>(j.value("fat_per_100g", 0.0) + 0.5)};
//         std::string form     = j.value("form", "");
//         std::string category = j.value("category", "");

//         std::optional<std::string> brand = std::nullopt;
//         if (j.contains("brand") && !j["brand"].is_null() && !j["brand"].get<std::string>().empty()) {
//             brand = j["brand"].get<std::string>();
//         }

//         std::vector<std::string> tags;
//         if (j.contains("tags")) {
//             tags = j.at("tags").get<std::vector<std::string>>();
//         }

//         std::unordered_map<std::string,std::string> substitutions;
//         if (j.contains("substitutions")) {
//             substitutions = j.at("substitutions").get<std::unordered_map<std::string,std::string>>();
//         }

//         entry = IngredientDatabaseEntry{
//             std::move(name), unit, kcal, protein, carbs, fat,
//             std::move(form), std::move(category),
//             std::move(brand), std::move(tags), std::move(substitutions)
//         };
//     }

//     static void to_json(json& j, const mealplanner::model::IngredientDatabaseEntry& entry) {
//         using namespace mealplanner::model;
//         j = json{
//             {"name",             entry.GetName()},
//             {"unit",             toString(entry.GetDefaultUnit())},
//             {"kcal_per_100g",    entry.GetKcalPer100g().value},
//             {"protein_per_100g", entry.GetProteinPer100g().value},
//             {"carbs_per_100g",   entry.GetCarbsPer100g().value},
//             {"fat_per_100g",     entry.GetFatPer100g().value},
//             {"form",             entry.GetForm()},
//             {"category",         entry.GetCategory()},
//             {"brand",            entry.GetBrand() ? *entry.GetBrand() : std::string{}},
//             {"tags",             entry.GetTags()},
//             {"substitutions",    entry.GetSubstitutions()}
//         };
//     }
// };

// ////////////////////////////////////////////////////////////////////////////////
// // Quantity
// ////////////////////////////////////////////////////////////////////////////////
// template<>
// struct adl_serializer<mealplanner::model::Quantity> {
//     static void from_json(const json& j, mealplanner::model::Quantity& q) noexcept {
//         q.amount = j.value("quantity", 0.0);
//         q.unit   = j.value("unit", std::string{});
//         q.note   = j.value("note", std::string{});
//     }
//     static void to_json(json& j, const mealplanner::model::Quantity& q) {
//         j = json{
//             {"quantity", q.amount},
//             {"unit",     q.unit},
//             {"note",     q.note}
//         };
//     }
// };

// ////////////////////////////////////////////////////////////////////////////////
// // Ingredient
// ////////////////////////////////////////////////////////////////////////////////
// template<>
// struct adl_serializer<mealplanner::model::Ingredient> {
//     static void from_json(const json& j, mealplanner::model::Ingredient& ing) {
//         j.at("name").get_to(ing.name);
//         j.at("quantity").get_to(ing.quantity);
//         ing.optional = j.value("optional", false);
//     }
//     static void to_json(json& j, const mealplanner::model::Ingredient& ing) {
//         j = json{
//             {"name",     ing.name},
//             {"quantity", ing.quantity},
//             {"optional", ing.optional}
//         };
//     }
// };

// ////////////////////////////////////////////////////////////////////////////////
// // Equipment
// ////////////////////////////////////////////////////////////////////////////////
// template<>
// struct adl_serializer<mealplanner::model::Equipment> {
//     static void from_json(const json& j, mealplanner::model::Equipment& eq) {
//         j.at("name").get_to(eq.name);
//         eq.optional = j.value("optional", false);
//     }
//     static void to_json(json& j, const mealplanner::model::Equipment& eq) {
//         j = json{
//             {"name",     eq.name},
//             {"optional", eq.optional}
//         };
//     }
// };

// ////////////////////////////////////////////////////////////////////////////////
// // Cost
// ////////////////////////////////////////////////////////////////////////////////
// template<>
// struct adl_serializer<mealplanner::model::Cost> {
//     static void from_json(const json& j, mealplanner::model::Cost& c) {
//         double val            = j.value("value", 0.0);
//         std::string currency  = j.value("currency", "Unknown");
//         c = mealplanner::model::Cost{ val, mealplanner::model::currencyFromString(currency) };
//     }
//     static void to_json(json& j, const mealplanner::model::Cost& c) {
//         j = json{
//             {"value",    c.value},
//             {"currency", mealplanner::model::toString(c.currency)}
//         };
//     }
// };

// ////////////////////////////////////////////////////////////////////////////////
// // Difficulty
// ////////////////////////////////////////////////////////////////////////////////
// template<>
// struct adl_serializer<mealplanner::model::Difficulty> {
//     static void from_json(const json& j, mealplanner::model::Difficulty& d) {
//         // difficultyFromString now returns a plain Difficulty (or throws on bad input)
//         d = mealplanner::model::difficultyFromString(j.get<std::string>());
//     }
//     static void to_json(json& j, const mealplanner::model::Difficulty& d) {
//         j = static_cast<int>(d);
//     }
// };

// ////////////////////////////////////////////////////////////////////////////////
// // Cuisine
// ////////////////////////////////////////////////////////////////////////////////
// template<>
// struct adl_serializer<mealplanner::model::Cuisine> {
//     static void from_json(const json& j, mealplanner::model::Cuisine& c) {
//         // cuisineFromString returns a Cuisine (with 'Other' default)
//         c = mealplanner::model::cuisineFromString(j.get<std::string>());
//     }
//     static void to_json(json& j, const mealplanner::model::Cuisine& c) {
//         j = static_cast<int>(c);
//     }
// };

// ////////////////////////////////////////////////////////////////////////////////
// // Recipe
// ////////////////////////////////////////////////////////////////////////////////
// template<>
// struct adl_serializer<mealplanner::model::Recipe> {
//     static void from_json(const json& j, mealplanner::model::Recipe& r) {
//         using namespace mealplanner::model;
//         j.at("id").get_to(r.id);
//         j.at("name").get_to(r.name);

//         // optional description
//         if (j.contains("description"))
//             r.description = j.at("description").get<std::string>();
//         else
//             r.description = std::nullopt;

//         // times & servings
//         r.prepTime = Minutes{ j.value<int>("prep_time_minutes", 0) };
//         r.cookTime = Minutes{ j.value<int>("cook_time_minutes", 0) };
//         r.restTime = Minutes{ j.value<int>("rest_time_minutes", 0) };
//         r.servings = Servings{ j.value<int>("servings", 1) };

//         // *** HERE IS THE ONLY CHANGE: ***
//         // use .template get<...>() instead of .get<...>()
//         if (j.contains("ingredients"))
//             r.ingredients   = j.at("ingredients").template get<std::vector<Ingredient>>();
//         if (j.contains("instructions"))
//             r.instructions  = j.at("instructions").template get<std::vector<std::string>>();
//         if (j.contains("tags"))
//             r.tags          = j.at("tags").template get<std::vector<std::string>>();
//         if (j.contains("allergens"))
//             r.allergens     = j.at("allergens").template get<std::vector<std::string>>();
//         if (j.contains("equipment"))
//             r.equipment     = j.at("equipment").template get<std::vector<Equipment>>();

//         // nutrition
//         r.kcal    = Calories{ j.value<int>("kcal",    0) };
//         r.protein = Grams   { j.value<int>("protein", 0) };
//         r.carbs   = Grams   { j.value<int>("carbs",   0) };
//         r.fat     = Grams   { j.value<int>("fat",     0) };

//         // optional metadata
//         if (j.contains("cuisine"))
//             r.cuisine     = j.at("cuisine").get<Cuisine>();
//         else
//             r.cuisine     = std::nullopt;

//         if (j.contains("difficulty"))
//             r.difficulty  = j.at("difficulty").get<Difficulty>();
//         else
//             r.difficulty  = std::nullopt;

//         if (j.contains("cost"))
//             r.cost        = j.at("cost").get<Cost>();
//         else
//             r.cost        = std::nullopt;

//         r.batchFriendly     = j.value<bool>("batch-friendly",       false);
//         r.prepAheadPossible = j.value<bool>("prep_ahead_possible",  false);
//         r.expirationDays    = j.value<int>( "expiration_day",         0);

//         if (j.contains("suitable_for_goals"))
//             r.suitableForGoals = j.at("suitable_for_goals").template get<std::vector<std::string>>();
//         if (j.contains("required_skills"))
//             r.requiredSkills   = j.at("required_skills").template get<std::vector<std::string>>();

//         // source info
//         r.imageUrl  = j.contains("image_url")  ? std::make_optional(j.at("image_url").get<std::string>())  : std::nullopt;
//         r.sourceUrl = j.contains("source_url") ? std::make_optional(j.at("source_url").get<std::string>()) : std::nullopt;
//         r.author    = j.contains("author")     ? std::make_optional(j.at("author").get<std::string>())    : std::nullopt;
//     }

//     static void to_json(json& j, const mealplanner::model::Recipe& r) {
//         j = json{
//             {"id",   r.id},
//             {"name", r.name}
//         };
//     }
// };

// ////////////////////////////////////////////////////////////////////////////////
// // UserProfile
// ////////////////////////////////////////////////////////////////////////////////
// template<>
// struct adl_serializer<mealplanner::model::UserProfile> {
//     static void from_json(const json& j, mealplanner::model::UserProfile& u) {
//         using namespace mealplanner::model;
//         j.at("name").get_to(u.name);
//         u.calorieTarget = j.value<int>( "calorie_target",       2000);
//         u.mealsPerDay   = j.value<int>( "meals_per_day",         3);
//         u.snackSlots    = j.value<int>( "snack_slots",           1);
//         u.maxPrepTime   = Minutes{ j.value<int>("max_prep_time_minutes", 30) };

//         if (j.contains("dietary_restrictions"))
//             j.at("dietary_restrictions").get_to(u.dietaryRestrictions);

//         if (j.contains("macro_ratios")) {
//             auto m = j.at("macro_ratios");
//             u.macroRatios.protein = m.value<double>("protein", 0.25);
//             u.macroRatios.carbs   = m.value<double>("carbs",   0.50);
//             u.macroRatios.fat     = m.value<double>("fat",     0.25);
//         }
//     }

//     static void to_json(json& j, const mealplanner::model::UserProfile& u) {
//         j = json{
//             {"name", u.name}
//         };
//     }
// };

// } // namespace nlohmann

// #endif // JSON_CONVERTERS_H
