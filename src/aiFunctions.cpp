#include "aiFunctions.h"
#include "utilityFunctions.h"
#include <iostream>

void aiFunctions::slime (Entity &user, Entity &target, int turnCounter) {
    const int ATTACK = 0, DONOTHING = 1; int timesToAttack = 1;

    if (turnCounter % 4 == 0) { timesToAttack = utilityFunctions::random (1, 3); user.attack++; std::cout << "Slime is growing." << std::endl; }

    if ((turnCounter) % 4 < timesToAttack) {
        user.skillset [ATTACK]->use (user, target);
    } else {
        user.skillset [DONOTHING]->use (user, target);
    }

}

void aiFunctions::wisp (Entity &user, Entity &target, int turnCounter) {
    const int ATTACK = 0, HEAL = 1;

    if ((turnCounter+1) % 4 == ATTACK) {
        user.skillset [ATTACK]->use (user, target);
    } else {
        user.skillset [HEAL]->use (user, target);
    }

}

void aiFunctions::blue_slime (Entity &user, Entity &target, int turnCounter) {
    const int DONOTHING = 0, ATTACK = 1;

    if ((turnCounter+1) % 2 == DONOTHING) {
        user.skillset [DONOTHING]->use (user, target);
    } else {
        user.skillset [ATTACK]->use (user, target);
    }

}

void aiFunctions::artifact (Entity &user, Entity &target, int turnCounter) {
    const int ATTACK = 0, DEFEND = 1, GUARD_BREAK = 2;
    int offset = turnCounter / 4;

    switch (offset % 3) {
        case 0: {
            if ((turnCounter+1) % 3 != DEFEND) {
                if (target.guard > 0 && (turnCounter+1) % 2 == 0) {
                    user.skillset [GUARD_BREAK]->use (user, target);
                } else {
                   user.skillset [ATTACK]->use (user, target);
                }
            } else {
                user.skillset [DEFEND]->use (user, target);
            }
        } break;
        case 1: {
            if ((turnCounter+1) % 3 != ATTACK) {
                user.skillset [DEFEND]->use (user, target);
            } else {
                if (target.guard > 0 && (turnCounter+1) % 2 == 0) {
                    user.skillset [GUARD_BREAK]->use (user, target);
                } else {
                   user.skillset [ATTACK]->use (user, target);
                };
            }
        } break;
        case 2: {
            user.skillset [ATTACK]->use (user, target);
        } break;
    }

}

void aiFunctions::rock (Entity &user, Entity &target, int turnCounter) {
    const int DO_NOTHING = 0;

    user.skillset [DO_NOTHING]->use (user, target);
}

void aiFunctions::shieldKnight (Entity &user, Entity &target, int turnCounter) {
    const int ATTACK = 1, DEFEND = 2, DONOTHING = 0; int phase = 1;

    if (phase == 1) {
        switch ((turnCounter+1) % 3) {
            case ATTACK:
                user.skillset [ATTACK]->use (user, target);
                break;
            case DEFEND:
                user.skillset [DEFEND]->use (user, target);
                break;
            case DONOTHING:
                user.skillset [DONOTHING]->use (user, target);
                break;
        }

        if (user.health <= user.maxHealth / 2) {
            phase++; user.attack += 3;
            std::cout << "Shield Knight's shield breaks! The Shield Knight becomes enraged!" << std::endl;
        }
    } else {
        user.skillset [ATTACK]->use (user, target);
    }


}

void aiFunctions::vampire (Entity &user, Entity &target, int turnCounter) {
    const int LEECH = 0, DEFEND = 1;

    if ((turnCounter+1) % 2 == LEECH) {
        user.skillset [LEECH]->use (user, target);
    } else {
        user.skillset [DEFEND]->use (user, target);
    }

}

void aiFunctions::brute (Entity &user, Entity &target, int turnCounter) {
    const int ATTACK = 0, DEFEND = 1;

    if ((turnCounter+1) % 3 != DEFEND) {
        user.skillset [ATTACK]->use (user, target);
    } else {
        user.skillset [DEFEND]->use (user, target);
    }

    if (turnCounter % 6 == 0) { user.attack++; std::cout << "Brute becomes stronger!" << std::endl; }

}

void aiFunctions::bowman (Entity &user, Entity &target, int turnCounter) {
    const int ATTACK = 0, DEFEND = 1, ATTACK_CHANCE = 75;

    int random = utilityFunctions::random (1,100);

    if (random < ATTACK_CHANCE) {
        user.skillset [ATTACK]->use (user, target);
    } else {
        user.skillset [DEFEND]->use (user, target);
    }

}

void aiFunctions::crusader (Entity &user, Entity &target, int turnCounter) {
    const int ATTACK = 1, DEFEND = 2, RANDOM = 0, DONOTHING = 0;

    switch ((turnCounter+1) % 3) {
        case ATTACK:
            user.skillset [ATTACK]->use (user, target);
            break;
        case DEFEND:
            user.skillset [DEFEND]->use (user, target);
            break;
        case RANDOM:
            int random = utilityFunctions::random (1,100);
            if (random < 33) {
                user.skillset [ATTACK]->use (user, target);
            } else if (random < 67) {
                user.skillset [DEFEND]->use (user, target);
            } else {
                user.skillset [DONOTHING]->use (user, target);
            }
            break;
    }

}

void aiFunctions::minotaur (Entity &user, Entity &target, int turnCounter) {
    const int DONOTHING = 0, ATTACK = 1;

    if ((turnCounter+1) % 3 == DONOTHING) {
        user.skillset [DONOTHING]->use (user, target);
    } else {
        user.skillset [ATTACK]->use (user, target);
    }

}

void aiFunctions::werewolf (Entity &user, Entity &target, int turnCounter) {
    const int DONOTHING = 0, GUARD_BREAK = 1, CLEAVE = 2;

    if (turnCounter % 6 < 3) {
        if (target.guard > 0) {
            user.skillset [GUARD_BREAK]->use (user, target);
        } else {
            user.skillset [DONOTHING]->use (user, target);
        }
    } else if (turnCounter == 3) {
        user.skillset [CLEAVE]->use (user, target);
        std::cout << "Werewolf becomes stronger from lunar energy!" << std::endl;
        user.attack++;
    } else {
        user.skillset [DONOTHING]->use (user, target);
    }

}

void aiFunctions::bramble (Entity &user, Entity &target, int turnCounter) {
    const int ATTACK = 1, DAGGER = 2, MISSILES = 0;
    int phase = 1;

    if (turnCounter % 4 == 0) {
        phase++;
    }

    if (phase % 2 == 1) {
         switch ((turnCounter+1) % 3) {
            case ATTACK:
                user.skillset [ATTACK]->use (user, target);
                break;
            case DAGGER:
                user.skillset [DAGGER]->use (user, target);
                break;
            case MISSILES:
                user.skillset [MISSILES]->use (user, target);
                break;
        }

    } else {
        switch ((turnCounter+1) % 4) {
            case MISSILES:
                user.skillset [MISSILES]->use (user, target);
                break;
            default:
                user.skillset [ATTACK]->use (user, target);
                break;
        }
    }

}

void aiFunctions::wither (Entity &user, Entity &target, int turnCounter) {
    const int ATTACK = 0, LAST_RESORT = 1, DO_NOTHING = 2;

    if (user.health != 1 && turnCounter % 4 != 0) {
        user.skillset [ATTACK]->use (user, target);
    } else if (user.health != 1) {
        user.skillset [DO_NOTHING]->use (user, target);
    } else {
        user.skillset [LAST_RESORT]->use (user, target);
    }

}
