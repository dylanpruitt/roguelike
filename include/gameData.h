#ifndef GAMEDATA_H
#define GAMEDATA_H

namespace gameData
{
    enum skills { doNothing = 0, attack, dagger, defend, leech, lastResort,
            restore, guardBreak, arrow, shieldSwipe, tripleAttack,
            offering, explode, cleave, missiles, observe, shadowStrike,
            disarm, smokebomb, mug, splitPain, wail };
    enum powers { growStrength = 0, noGuard, regen, wither, metalBody,
            strengthBoost, spike, etherealHourglass, lunarEnergy,
            eagleEye, elusiveShadow, counter, spore };
};

#endif // GAMEDATA_H
