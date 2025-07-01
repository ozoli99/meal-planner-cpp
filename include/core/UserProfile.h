#ifndef USER_PROFILE_H
#define USER_PROFILE_H

#include <vector>
#include <string>
#include "MealPlan.h"
#include "MacroRatios.h"

struct UserProfile {
    std::string name;
    int calorieTarget = 2000;
    int mealsPerDay = 3;
    int snackSlots = 1;
    int maxPrepTimeMinutes = 30;
    MacroRatios macroRatios;
    std::vector<std::string> dietaryRestrictions;
};

#endif // USER_PROFILE_H