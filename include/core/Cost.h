#ifndef COST_H
#define COST_H

#include <string>
#include <stdexcept>
#include <functional>

namespace mealplanner::model {
    enum class Currency {
        USD,
        EUR,
        GBP,
        Unknown
    };
    inline std::string toString(Currency currency) {
        switch (currency) {
            case Currency::USD: return "USD";
            case Currency::EUR: return "EUR";
            case Currency::GBP: return "GBP";
            default: return "Unknown";
        }
    }
    inline Currency currencyFromString(const std::string& str) {
        if (str == "USD") return Currency::USD;
        if (str == "EUR") return Currency::EUR;
        if (str == "GBP") return Currency::GBP;
        return Currency::Unknown;
    }

    /**
     * @brief Monetary cost with explicit currency code.
     * @details Immutable, type-safe representation of a monetary value and its currency.
     */
    struct Cost {
        double value = 0.0;                    ///< Numeric cost
        Currency currency = Currency::Unknown; ///< ISO currency, e.g. USD, EUR

        Cost(double value_, Currency currency_)
            : value(value_)
            , currency(currency_) {
            if (value < 0.0) {
                throw std::invalid_argument("Cost value must be >= 0");
            }
        }

        /// Equality: only equal if both value and currency match
        bool operator==(const Cost& other) const {
            return value == other.value && currency == other.currency;
        }
        /// Less-than: only valid for same currency
        bool operator<(const Cost& other) const {
            if (currency != other.currency) throw std::logic_error("Cannot compare costs with different currencies");
            return value < other.value;
        }
        /// Formatted output, e.g. "$12.34 USD" or "12.34 €"
        std::string toString() const {
            char buf[32];
            snprintf(buf, sizeof(buf), "%.2f", value);
            std::string symbol;
            switch (currency) {
                case Currency::USD: symbol = "$"; break;
                case Currency::EUR: symbol = "€"; break;
                case Currency::GBP: symbol = "£"; break;
                default: symbol = ""; break;
            }
            // Place symbol before or after value depending on currency
            if (currency == Currency::EUR) {
                return std::string(buf) + " " + symbol;
            } else if (currency == Currency::Unknown) {
                return std::string(buf) + " " + mealplanner::model::toString(currency);
            } else {
                return symbol + std::string(buf);
            }
        }

        /// Addition for same currency
        Cost operator+(const Cost& other) const {
            if (currency != other.currency) throw std::logic_error("Cannot add costs with different currencies");
            return Cost(value + other.value, currency);
        }

        /// Subtraction for same currency
        Cost operator-(const Cost& other) const {
            if (currency != other.currency) throw std::logic_error("Cannot subtract costs with different currencies");
            return Cost(value - other.value, currency);
        }
    };

    /**
     * @brief Convert a Cost to another currency using an exchange rate.
     * @param original The original cost.
     * @param target The target currency.
     * @param exchangeRate The rate to multiply the original value by (target per source).
     * @return A new Cost in the target currency.
     * @throws std::invalid_argument if exchangeRate <= 0 or source and target are the same.
     */
    inline Cost convertTo(const Cost& original, Currency target, double exchangeRate) {
        if (exchangeRate <= 0.0) throw std::invalid_argument("Exchange rate must be > 0");
        if (original.currency == target) throw std::invalid_argument("Source and target currency are the same");
        return Cost(original.value * exchangeRate, target);
    }
} // namespace mealplanner::model

namespace std {
    template<>
    struct hash<mealplanner::model::Currency> {
        std::size_t operator()(const mealplanner::model::Currency& currency) const noexcept {
            return std::hash<int>()(static_cast<int>(currency));
        }
    };
    template<>
    struct hash<mealplanner::model::Cost> {
        std::size_t operator()(const mealplanner::model::Cost& cost) const noexcept {
            std::size_t h1 = std::hash<double>()(cost.value);
            std::size_t h2 = std::hash<mealplanner::model::Currency>()(cost.currency);
            return h1 ^ (h2 << 1);
        }
    };
} // namespace std

#endif // COST_H