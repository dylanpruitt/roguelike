#include "statusFunctions.h"

void statusFunctions::poison (Entity &user, int turnsLeft) {
    user.health -= 1;
    turnsLeft--;
}
