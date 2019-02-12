#include "Game.h"
#include "aiFunctions.h"
#include "powerFunctions.h"
#include "skillFunctions.h"
#include "utilityFunctions.h"
#include "PlayerStats.h"
#include <iostream>

Game::~Game()
{
    //dtor
}

void Game::battle (Entity &player, Entity &enemy) {
    int turnCounter = 1;

    while (player.health > 0 && enemy.health > 0) {
        std::cout << "TURN " << turnCounter << std::endl;

        for (unsigned int i = 0; i < player.powers.size (); i++) { player.powers [i]->use (player, turnCounter); }
        for (unsigned int i = 0; i < enemy.powers.size (); i++) { enemy.powers [i]->use (enemy, turnCounter); }

        displayPlayerInformation (player, enemy);

        int choice = -1; bool looping = true;

        while (looping) {
            choice = utilityFunctions::getIntegerInput ();

            if (choice >= 0 && choice < 3) { looping = false; }

        }

        player.skillset [choice]->use (player, enemy);

        if (player.focus < 0) { player.focus++; }
        if (player.evade < 0) { player.evade++; }

        enemy.guard = 0;

        if (enemy.health > 0) {

            enemy.ai (enemy, player, turnCounter);
        }

        if (enemy.focus < 0) { enemy.focus++; }
        if (enemy.evade < 0) { enemy.evade++; }
        turnCounter++; player.guard = 0;

    }

    if (player.health > 0) {

        std::cout << "You won!" << std::endl;

        replaceSkill (player, enemy.rewardSkill);
        player.gold += enemy.gold;
        player.maxHealth++; player.health++;
        player.attack = 0; player.evade = 0; player.focus = 0;

    } else {
        PlayerStats::enemiesThatKilledPlayer.push_back (enemy.name);

    }
}

void Game::displayPlayerInformation (Entity &player, Entity &enemy) {
    std::cout << player.name << " vs. " << enemy.name << std::endl;
    std::cout << "HP " << player.health << " / " << player.maxHealth << " vs. " << enemy.health << " / " << enemy.maxHealth << std::endl;
    std::cout << "ATTACK " << player.attack << " vs. " << enemy.attack << std::endl;
    std::cout << "GUARD " << player.guard << " vs. " << enemy.guard << std::endl;
    std::cout << "FOCUS " << player.focus << " vs. " << enemy.focus << std::endl;
    std::cout << "EVADE " << player.evade << " vs. " << enemy.evade << std::endl;

    displayCombatantPowers (player, enemy);

    std::cout << "\nPlayer Skills:" << std::endl;

    for (int i = 0; i < 3; i++) {
        std::cout << "[" << i << "] - " << player.skillset [i]->name << std::endl;
    }

}

void Game::displayCombatantPowers (Entity &player, Entity &enemy) {
    std::cout << "Player Powers: ";

    std::vector <std::string> powers; std::vector <int> powerStacks;

    for (unsigned int i = 0; i < player.powers.size (); i++) {

        bool isStacked = false;
        for (unsigned int j = 0; j < powers.size (); j++) {
            if (player.powers [i]->name == powers [j]) {
                powerStacks [j]++;
                isStacked = true;
            }

        }

        if (!isStacked) {
            powers.push_back (player.powers [i]->name);
            powerStacks.push_back (1);
        }

    }

    for (unsigned int i = 0; i < powers.size (); i++) {

        std::cout << powers [i];

        if (powerStacks [i] > 1) { std::cout << " (" << powerStacks [i] << ")"; }

        if (i < powers.size () - 1) { std::cout << ", "; }
    }

    powers.clear (); powerStacks.clear ();
    std::cout << "\nEnemy Powers: ";
    for (unsigned int i = 0; i < enemy.powers.size (); i++) {

        bool isStacked = false;
        for (unsigned int j = 0; j < powers.size (); j++) {
            if (enemy.powers [i]->name == powers [j]) {
                powerStacks [j]++;
                isStacked = true;
            }

        }

        if (!isStacked) {
            powers.push_back (enemy.powers [i]->name);
            powerStacks.push_back (1);
        }

    }
    for (unsigned int i = 0; i < powers.size (); i++) {

        std::cout << powers [i];

        if (powerStacks [i] > 1) { std::cout << " (" << powerStacks [i] << ")"; }

        if (i < powers.size () - 1) { std::cout << ", "; }
    }
}

void Game::initializeSkills () {
    // 0
    Skill doNothing; doNothing.name = "Do Nothing"; doNothing.use = skillFunctions::do_nothing;
    doNothing.minimumPrice = 0; doNothing.maximumPrice = 0;
    doNothing.description = "Do nothing."; gameData::gameSkills.push_back (doNothing);

    Skill attack; attack.name = "Attack"; attack.use = skillFunctions::attack;
    attack.minimumPrice = 16; attack.maximumPrice = 24;
    attack.description = "A basic attack. Deals 3 base damage."; gameData::gameSkills.push_back (attack);

    Skill dagger; dagger.name = "Dagger"; dagger.use = skillFunctions::dagger;
    dagger.minimumPrice = 36; dagger.maximumPrice = 54;
    dagger.description = "A basic attack. Deals 5 base damage."; gameData::gameSkills.push_back (dagger);

    Skill defend; defend.name = "Defend"; defend.use = skillFunctions::defend;
    defend.minimumPrice = 27; defend.maximumPrice = 44;
    defend.description = "Adds 4 guard (you can take 4 damage without losing health). Guard goes away on your next turn."; gameData::gameSkills.push_back (defend);
    // 4
    Skill leech; leech.name = "Leech"; leech.use = skillFunctions::leech;
    leech.minimumPrice = 36; leech.maximumPrice = 54;
    leech.description = "A basic attack. Deals 3 damage and heal some of the damage you inflict."; gameData::gameSkills.push_back (leech);

    Skill last_resort; last_resort.name = "Last Resort"; last_resort.use = skillFunctions::last_resort;
    last_resort.minimumPrice = 27; last_resort.maximumPrice = 44;
    last_resort.description = "Deals 50 damage if user has 1 health. Otherwise does nothing."; gameData::gameSkills.push_back (last_resort);

    Skill restore; restore.name = "Restore"; restore.use = skillFunctions::restore;
    restore.minimumPrice = 56; restore.maximumPrice = 72;
    restore.description = "Restore a fourth of your health."; gameData::gameSkills.push_back (restore);

    Skill guardBreak; guardBreak.name = "Guard Break"; guardBreak.use = skillFunctions::guard_break;
    guardBreak.minimumPrice = 36; guardBreak.maximumPrice = 54;
    guardBreak.description = "Deals damage to guarding enemies."; gameData::gameSkills.push_back (guardBreak);
    // 8
    Skill arrow; arrow.name = "Arrow"; arrow.use = skillFunctions::arrow;
    arrow.minimumPrice = 27; arrow.maximumPrice = 44;
    arrow.description = "A basic attack, can miss but user does not take damage from Thorns."; gameData::gameSkills.push_back (arrow);

    Skill shieldSwipe; shieldSwipe.name = "Shield Swipe"; shieldSwipe.use = skillFunctions::shield_swipe;
    shieldSwipe.minimumPrice = 64; shieldSwipe.maximumPrice = 80;
    shieldSwipe.description = "Gain guard and attack at the same time."; gameData::gameSkills.push_back (shieldSwipe);

    Skill tripleAttack; tripleAttack.name = "Triple Attack"; tripleAttack.use = skillFunctions::triple_attack;
    tripleAttack.minimumPrice = 64; tripleAttack.maximumPrice = 80;
    tripleAttack.description = "Attack three times."; gameData::gameSkills.push_back (tripleAttack);

    Skill offering; offering.name = "Offering"; offering.use = skillFunctions::offering;
    offering.minimumPrice = 36; offering.maximumPrice = 54;
    offering.description = "The user sacrifices some of their health but their attack increases."; gameData::gameSkills.push_back (offering);
    // 12
    Skill explode; explode.name = "Explode"; explode.use = skillFunctions::explode;
    offering.minimumPrice = 36; offering.maximumPrice = 54;
    explode.description = "An attack that does damage to the user too."; gameData::gameSkills.push_back (explode);

    Skill cleave; cleave.name = "Cleave"; cleave.use = skillFunctions::cleave;
    cleave.minimumPrice = 64; cleave.maximumPrice = 80;
    cleave.description = "A basic attack. Deals 7 base damage."; gameData::gameSkills.push_back (cleave);

    Skill missiles; missiles.name = "Missiles"; missiles.use = skillFunctions::missiles;
    missiles.minimumPrice = 90; missiles.maximumPrice = 128;
    missiles.description = "Fire off 2 to 5 missiles. The user does not take damage from Thorns."; gameData::gameSkills.push_back (missiles);

    Skill observe; observe.name = "Observe"; observe.use = skillFunctions::focus;
    observe.minimumPrice = 36; observe.maximumPrice = 54;
    observe.description = "Gain 1 Focus."; gameData::gameSkills.push_back (observe);
    // 16
    Skill shadowStrike; shadowStrike.name = "Shadow Strike"; shadowStrike.use = skillFunctions::shadow_strike;
    shadowStrike.minimumPrice = 54; shadowStrike.maximumPrice = 72;
    shadowStrike.description = "Deal 3 * Evade damage. Lose all Evade."; gameData::gameSkills.push_back (shadowStrike);

    Skill disarm; disarm.name = "Disarm"; disarm.use = skillFunctions::disarm;
    disarm.minimumPrice = 54; disarm.maximumPrice = 72;
    disarm.description = "Deal 3 damage. Target loses 1 Focus."; gameData::gameSkills.push_back (disarm);

    Skill smokebomb; smokebomb.name = "Smokebomb"; smokebomb.use = skillFunctions::evade;
    smokebomb.minimumPrice = 48; smokebomb.maximumPrice = 64;
    smokebomb.description = "Gain 1 Evade."; gameData::gameSkills.push_back (smokebomb);

    Skill mug; mug.name = "Mug"; mug.use = skillFunctions::mug;
    mug.minimumPrice = 48; mug.maximumPrice = 64;
    mug.description = "Deal 4 damage and steal some gold."; gameData::gameSkills.push_back (mug);

    // 20
    Skill splitPain; splitPain.name = "Split Pain"; splitPain.use = skillFunctions::split_pain;
    splitPain.minimumPrice = 54; splitPain.maximumPrice = 72;
    splitPain.description = "Split pain with the target (changes HP)."; gameData::gameSkills.push_back (splitPain);

    Skill wail; wail.name = "Wail"; wail.use = skillFunctions::wail;
    wail.minimumPrice = 36; wail.maximumPrice = 54;
    wail.description = "Lower the target's guard."; gameData::gameSkills.push_back (wail);
}

void Game::initializePowers () {

    Power growStrength; growStrength.name = "Grow";
    growStrength.use = powerFunctions::grow_strength;
    growStrength.description = "Gain 1 Strength every two turns."; gameData::gamePowers.push_back (growStrength);

    Power noGuard; noGuard.name = "No Guard";
    noGuard.use = powerFunctions::no_guard;
    noGuard.description = "User has -3 Guard but +3 Strength"; gameData::gamePowers.push_back (noGuard);

    Power regen; regen.name = "Regenerate";
    regen.use = powerFunctions::regenerate;
    regen.description = "Regenerate 2 health every 2 turns."; gameData::gamePowers.push_back (regen);

    Power wither; wither.name = "Wither";
    wither.use = powerFunctions::wither;
    wither.description = "Lose Strength and Guard every turn."; gameData::gamePowers.push_back (wither);

    Power metalBody; metalBody.name = "Metal Body";
    metalBody.use = powerFunctions::metal_body;
    metalBody.description = "Gain 3 Guard every turn (Guard goes away after your turn)."; gameData::gamePowers.push_back (metalBody);

    Power strengthBoost; strengthBoost.name = "Strength Boost";
    strengthBoost.use = powerFunctions::strength_boost;
    strengthBoost.description = "Gain 1 Strength."; gameData::gamePowers.push_back (strengthBoost);

    Power spike; spike.name = "Thorns";
    spike.use = powerFunctions::spike;
    spike.whenAttacked = powerFunctions::deal_spike_damage;
    spike.description = "Every time you are attacked the enemy takes 1 damage back."; gameData::gamePowers.push_back (spike);

    Power etherealHourglass; etherealHourglass.name = "Ethereal Hourglass";
    etherealHourglass.use = powerFunctions::ethereal_hourglass;
    etherealHourglass.description = "Every fifth turn, your attack becomes powerful."; gameData::gamePowers.push_back (etherealHourglass);

    Power lunarEnergy; lunarEnergy.name = "Lunar Energy";
    lunarEnergy.use = powerFunctions::lunar_energy;
    lunarEnergy.description = "A cycle where you gain Strength for three turns and return to normal for another three."; gameData::gamePowers.push_back (lunarEnergy);

    Power eagleEye; eagleEye.name = "Eagle Eye";
    eagleEye.use = powerFunctions::eagle_eye;
    eagleEye.description = "If you have less than 1 Focus, set your Focus equal to 1."; gameData::gamePowers.push_back (eagleEye);

    Power elusiveShadow; elusiveShadow.name = "Elusive Shadow";
    elusiveShadow.use = powerFunctions::elusive_shadow;
    elusiveShadow.description = "Gain 3 Evade at the start of combat but the user has halved HP."; gameData::gamePowers.push_back (elusiveShadow);

    Power counter; counter.name = "Counter";
    counter.use = powerFunctions::do_nothing;
    counter.whenAttacked = powerFunctions::counter;
    counter.description = "When the user is attacked, if the user has at least 1 Guard left, they counter-attack."; gameData::gamePowers.push_back (counter);

    Power spore; spore.name = "Spore";
    spore.use = powerFunctions::do_nothing;
    spore.whenAttacked = powerFunctions::spores;
    spore.description = "When the user is attacked, the enemy loses 2 Guard."; gameData::gamePowers.push_back (counter);
}

Entity Game::returnEntityFromName (std::string name) {
    Entity entity;

    if (name == "Slime") {
        entity.health = 27;
        entity.maxHealth = 27;
        entity.name = "Slime";

        entity.gold = utilityFunctions::random (8, 24);

        entity.skillset [0] = &gameData::gameSkills [gameData::skills::attack];
        entity.skillset [1] = &gameData::gameSkills [gameData::skills::doNothing];

        entity.rewardSkill = &gameData::gameSkills [gameData::skills::attack];

        entity.ai = aiFunctions::slime;
    }
    if (name == "Wisp") {
        entity.health = 14;
        entity.maxHealth = 14;
        entity.name = "Wisp";

        entity.gold = utilityFunctions::random (11, 17);

        entity.skillset [0] = &gameData::gameSkills [gameData::skills::restore];
        entity.skillset [1] = &gameData::gameSkills [gameData::skills::attack];

        entity.rewardSkill = &gameData::gameSkills [gameData::skills::restore];

        entity.ai = aiFunctions::wisp;
    }
    if (name == "Blue Slime") {
        entity.health = 27;
        entity.maxHealth = 27;
        entity.name = "Blue Slime";

        entity.gold = utilityFunctions::random (8, 24);

        entity.skillset [0] = &gameData::gameSkills [gameData::skills::attack];
        entity.skillset [1] = &gameData::gameSkills [gameData::skills::doNothing];

        entity.rewardSkill = &gameData::gameSkills [gameData::skills::attack];

        entity.powers.push_back (&gameData::gamePowers [gameData::powers::regen]);
        entity.ai = aiFunctions::blue_slime;
    }
    if (name == "Rock") {
        entity.health = 1;
        entity.maxHealth = 1;
        entity.name = "Rock";

        entity.gold = utilityFunctions::random (1, 3);

        entity.skillset [0] = &gameData::gameSkills [gameData::skills::doNothing];

        entity.rewardSkill = &gameData::gameSkills [gameData::skills::doNothing];

        entity.ai = aiFunctions::rock;
    }
    if (name == "Thornbush") {
        entity.health = 14;
        entity.maxHealth = 14;
        entity.name = "Thornbush";

        entity.gold = utilityFunctions::random (22, 31);

        entity.skillset [0] = &gameData::gameSkills [gameData::skills::dagger];
        entity.skillset [1] = &gameData::gameSkills [gameData::skills::attack];

        entity.rewardSkill = &gameData::gameSkills [gameData::skills::dagger];

        entity.powers.push_back (&gameData::gamePowers [gameData::powers::spike]);
        entity.ai = aiFunctions::slime;
    }
    if (name == "Shield Warrior") {
        entity.health = 11;
        entity.maxHealth = 11;
        entity.name = "Shield Warrior";

        entity.gold = utilityFunctions::random (11, 28);

        entity.skillset [0] = &gameData::gameSkills [gameData::skills::doNothing];
        entity.skillset [1] = &gameData::gameSkills [gameData::skills::attack];
        entity.skillset [2] = &gameData::gameSkills [gameData::skills::defend];

        entity.rewardSkill = &gameData::gameSkills [gameData::skills::defend];

        entity.ai = aiFunctions::shieldKnight;
    }
    if (name == "Vampire") {
        entity.health = 22;
        entity.maxHealth = 22;
        entity.name = "Vampire";

        entity.gold = utilityFunctions::random (16, 39);

        entity.skillset [0] = &gameData::gameSkills [gameData::skills::leech];
        entity.skillset [1] = &gameData::gameSkills [gameData::skills::defend];

        entity.rewardSkill = &gameData::gameSkills [gameData::skills::leech];

        entity.powers.push_back (&gameData::gamePowers [gameData::powers::etherealHourglass]);
        entity.ai = aiFunctions::vampire;
    }
    if (name == "Brute") {
        entity.health = 36;
        entity.maxHealth = 36;
        entity.name = "Brute";

        entity.gold = utilityFunctions::random (23, 32);

        entity.skillset [0] = &gameData::gameSkills [gameData::skills::attack];
        entity.skillset [1] = &gameData::gameSkills [gameData::skills::doNothing];

        entity.rewardSkill = &gameData::gameSkills [gameData::skills::attack];

        entity.powers.push_back (&gameData::gamePowers [gameData::powers::noGuard]);
        entity.ai = aiFunctions::brute;
    }
    if (name == "Hunter") {
        entity.health = 24;
        entity.maxHealth = 24;
        entity.name = "Hunter";

        entity.gold = utilityFunctions::random (16, 22);

        entity.skillset [0] = &gameData::gameSkills [gameData::skills::arrow];
        entity.skillset [1] = &gameData::gameSkills [gameData::skills::defend];

        entity.rewardSkill = &gameData::gameSkills [gameData::skills::arrow];

        entity.powers.push_back (&gameData::gamePowers [gameData::powers::eagleEye]);
        entity.ai = aiFunctions::bowman;
    }
    if (name == "Crusader") {
        entity.health = 30;
        entity.maxHealth = 30;
        entity.name = "Crusader";

        entity.gold = utilityFunctions::random (26, 38);

        entity.skillset [0] = &gameData::gameSkills [gameData::skills::shieldSwipe];
        entity.skillset [1] = &gameData::gameSkills [gameData::skills::defend];
        entity.skillset [2] = &gameData::gameSkills [gameData::skills::doNothing];

        entity.rewardSkill = &gameData::gameSkills [gameData::skills::shieldSwipe];

        entity.ai = aiFunctions::crusader;
    }
    if (name == "Minotaur") {
        entity.health = 30;
        entity.maxHealth = 30;
        entity.name = "Minotaur";

        entity.gold = utilityFunctions::random (28, 36);

        entity.skillset [0] = &gameData::gameSkills [gameData::skills::tripleAttack];
        entity.skillset [1] = &gameData::gameSkills [gameData::skills::doNothing];

        entity.rewardSkill = &gameData::gameSkills [gameData::skills::tripleAttack];

        entity.powers.push_back (&gameData::gamePowers [gameData::powers::growStrength]);
        entity.ai = aiFunctions::minotaur;
    }
    if (name == "Artifact") {
        entity.health = 10;
        entity.maxHealth = 10;
        entity.name = "Artifact";

        entity.gold = utilityFunctions::random (26, 48);

        entity.skillset [0] = &gameData::gameSkills [gameData::skills::attack];
        entity.skillset [1] = &gameData::gameSkills [gameData::skills::defend];
        entity.skillset [2] = &gameData::gameSkills [gameData::skills::guardBreak];

        entity.rewardSkill = &gameData::gameSkills [gameData::skills::defend];

        entity.powers.push_back (&gameData::gamePowers [gameData::powers::metalBody]);
        entity.ai = aiFunctions::artifact;
    }
    if (name == "Werewolf") {
        entity.health = 52;
        entity.maxHealth = 52;
        entity.name = "Werewolf";

        entity.gold = utilityFunctions::random (35, 58);

        entity.skillset [0] = &gameData::gameSkills [gameData::skills::doNothing];
        entity.skillset [1] = &gameData::gameSkills [gameData::skills::guardBreak];
        entity.skillset [2] = &gameData::gameSkills [gameData::skills::cleave];

        entity.rewardSkill = &gameData::gameSkills [gameData::skills::cleave];

        entity.powers.push_back (&gameData::gamePowers [gameData::powers::lunarEnergy]);
        entity.ai = aiFunctions::werewolf;
    }
    if (name == "Thief") {
        entity.health = 16;
        entity.maxHealth = 16;
        entity.name = "Thief";

        entity.gold = utilityFunctions::random (64, 92);

        entity.skillset [0] = &gameData::gameSkills [gameData::skills::dagger];
        entity.skillset [1] = &gameData::gameSkills [gameData::skills::smokebomb];
        entity.skillset [2] = &gameData::gameSkills [gameData::skills::mug];

        entity.rewardSkill = &gameData::gameSkills [gameData::skills::mug];

        entity.powers.push_back (&gameData::gamePowers [gameData::powers::elusiveShadow]);
        entity.ai = aiFunctions::thief;
    }
    if (name == "Shadow") {
        entity.health = 1;
        entity.maxHealth = 1;
        entity.name = "Shadow";
        entity.attack = 3;

        entity.gold = utilityFunctions::random (24, 32);

        entity.skillset [0] = &gameData::gameSkills [gameData::skills::disarm];
        entity.skillset [1] = &gameData::gameSkills [gameData::skills::smokebomb];
        entity.skillset [2] = &gameData::gameSkills [gameData::skills::shadowStrike];

        entity.rewardSkill = &gameData::gameSkills [gameData::skills::shadowStrike];

        entity.powers.push_back (&gameData::gamePowers [gameData::powers::elusiveShadow]);
        entity.ai = aiFunctions::shadow;
    }
    if (name == "Beholder") {
        entity.health = 53;
        entity.maxHealth = 53;
        entity.name = "Beholder";
        entity.attack = 3;

        entity.gold = utilityFunctions::random (24, 32);

        entity.skillset [0] = &gameData::gameSkills [gameData::skills::observe];
        entity.skillset [1] = &gameData::gameSkills [gameData::skills::attack];
        entity.skillset [2] = &gameData::gameSkills [gameData::skills::disarm];

        entity.rewardSkill = &gameData::gameSkills [gameData::skills::observe];

        entity.ai = aiFunctions::beholder;
    }
    if (name == "Tormented Spirit") {
        entity.health = 47;
        entity.maxHealth = 47;
        entity.name = "Tormented Spirit";
        entity.attack = 3;

        entity.gold = utilityFunctions::random (18, 42);

        entity.skillset [0] = &gameData::gameSkills [gameData::skills::disarm];
        entity.skillset [1] = &gameData::gameSkills [gameData::skills::splitPain];
        entity.skillset [2] = &gameData::gameSkills [gameData::skills::wail];

        entity.rewardSkill = &gameData::gameSkills [gameData::skills::splitPain];

        entity.ai = aiFunctions::spirit;
    }
    if (name == "Herbalist") {
        entity.health = 60;
        entity.maxHealth = 60;
        entity.name = "Herbalist";
        entity.attack = 3;

        entity.gold = utilityFunctions::random (50, 64);

        entity.skillset [0] = &gameData::gameSkills [gameData::skills::disarm];
        entity.skillset [1] = &gameData::gameSkills [gameData::skills::dagger];
        entity.skillset [2] = &gameData::gameSkills [gameData::skills::observe];

        entity.rewardSkill = &gameData::gameSkills [gameData::skills::observe];

        entity.powers.push_back (&gameData::gamePowers [gameData::powers::spore]);
        entity.ai = aiFunctions::herbalist;
    }
    if (name == "Bramble Fortress") {
        entity.health = 24;
        entity.maxHealth = 24;
        entity.name = "Bramble Fortress";

        entity.gold = utilityFunctions::random (46, 82);

        entity.skillset [0] = &gameData::gameSkills [gameData::skills::attack];
        entity.skillset [1] = &gameData::gameSkills [gameData::skills::dagger];
        entity.skillset [2] = &gameData::gameSkills [gameData::skills::missiles];


        entity.rewardSkill = &gameData::gameSkills [gameData::skills::attack];

        entity.powers.push_back (&gameData::gamePowers [gameData::powers::metalBody]);
        entity.powers.push_back (&gameData::gamePowers [gameData::powers::spike]);
        entity.powers.push_back (&gameData::gamePowers [gameData::powers::spike]);
        entity.ai = aiFunctions::bramble;
    }
    if (name == "Wither") {
        entity.health = 80;
        entity.maxHealth = 80;
        entity.name = "Wither";

        entity.gold = utilityFunctions::random (80, 124);

        entity.skillset [0] = &gameData::gameSkills [gameData::skills::leech];
        entity.skillset [1] = &gameData::gameSkills [gameData::skills::lastResort];
        entity.skillset [2] = &gameData::gameSkills [gameData::skills::doNothing];


        entity.rewardSkill = &gameData::gameSkills [gameData::skills::attack];

        entity.powers.push_back (&gameData::gamePowers [gameData::powers::wither]);
        entity.powers.push_back (&gameData::gamePowers [gameData::powers::noGuard]);
        entity.ai = aiFunctions::wither;
    }
    if (name == "Dragon") {
        entity.health = 77;
        entity.maxHealth = 77;
        entity.name = "Dragon";

        entity.gold = utilityFunctions::random (80, 124);

        entity.skillset [0] = &gameData::gameSkills [gameData::skills::cleave];
        entity.skillset [1] = &gameData::gameSkills [gameData::skills::guardBreak];
        entity.skillset [2] = &gameData::gameSkills [gameData::skills::wail];


        entity.rewardSkill = &gameData::gameSkills [gameData::skills::cleave];

        entity.powers.push_back (&gameData::gamePowers [gameData::powers::strengthBoost]);
        entity.powers.push_back (&gameData::gamePowers [gameData::powers::strengthBoost]);
        entity.powers.push_back (&gameData::gamePowers [gameData::powers::spike]);
        entity.ai = aiFunctions::dragon;
    }
    if (name == "Carl") {
        entity.health = 100;
        entity.maxHealth = 100;
        entity.name = "Carl";
        entity.attack = 5;

        entity.gold = utilityFunctions::random (80, 124);

        entity.skillset [0] = &gameData::gameSkills [gameData::skills::cleave];
        entity.skillset [1] = &gameData::gameSkills [gameData::skills::guardBreak];
        entity.skillset [2] = &gameData::gameSkills [gameData::skills::wail];


        entity.rewardSkill = &gameData::gameSkills [gameData::skills::cleave];

    }
    return entity;

}

void Game::replaceSkill (Entity &player, Skill *rewardSkill) {

    std::cout << "Reward Skill: " << rewardSkill->name << std::endl;
    std::cout << " -- " << rewardSkill->description << "\nChoose a skill to replace." << std::endl;

    bool looping = true; int choice = -1;

    while (looping) {
        for (int i = 0; i < 3; i++) {
            if (skillLock == true && lockedSkill == i) {
                std::cout << "[SKILL LOCKED]" << std::endl;
            } else {
                std::cout << "[" << i << "] - " << player.skillset [i]->name << std::endl;
                std::cout << " -- " << player.skillset [i]->description << std::endl;
            }

        }

        choice = utilityFunctions::getIntegerInput ();

        if (choice >= 0 && choice < 3 && ((choice != lockedSkill && skillLock == true) || skillLock == false)) { looping = false; }
    }

    player.skillset [choice] = rewardSkill; lockedSkill = choice;

}

void Game::generateMap (int seed) {
    for (int i = 0; i < 5; i++) {
        dungeon [i] = generateFloor (seed, i + 1);

    }
}

Floor Game::generateFloor (int seed, int floorNumber) {

    Floor floor (floorNumber);
    Room startingPoint; startingPoint.roomType = "start";

    floor.floorMap [0] = startingPoint;
    srand (seed);
    for (int i = 0; i < 12; i++) {


        floor.floorMap [1+i] = generateRoom (floor);

    }

    Room midBoss; midBoss.roomType = "enemy";

    switch (floorNumber) {
        case 1: {
            midBoss.entityInRoom = returnEntityFromName ("Hunter");
        } break;
        case 2: {
            midBoss.entityInRoom = returnEntityFromName ("Werewolf");
        } break;
        case 3: {
            midBoss.entityInRoom = returnEntityFromName ("Beholder");
        } break;
        default: {
           midBoss.entityInRoom = returnEntityFromName ("Blue Slime");
        } break;
    }

    floor.floorMap [13] = midBoss;
    for (int i = 0; i < 12; i++) {


        floor.floorMap [14+i] = generateRoom (floor);

    }

    Room boss; boss.roomType = "enemy";

    switch (floorNumber) {
        case 1: {
            boss.entityInRoom = returnEntityFromName ("Artifact");
        } break;
        case 2: {
            boss.entityInRoom = returnEntityFromName ("Bramble Fortress");
        } break;
        case 3: {
            boss.entityInRoom = returnEntityFromName ("Wither");
        } break;
        case 4: {
            boss.entityInRoom = returnEntityFromName ("Dragon");
        } break;
        default: {
           boss.entityInRoom = returnEntityFromName ("Blue Slime");
        } break;
    }

    floor.floorMap [26] = boss;

    int index = utilityFunctions::random (0, gameData::gamePowers.size () - 1);
    floor.powerReward = gameData::gamePowers [index];

    return floor;
}

Room Game::generateRoom (Floor &parent) {
    int random = utilityFunctions::random (1, 100); Room room;

    if (random >= 60) {
        int index = utilityFunctions::random (0, parent.enemyNames.size () - 1);

        room.entityInRoom = returnEntityFromName (parent.enemyNames [index]); room.roomType = "enemy";

    } else if (random >= 20) {
        for (int i = 0; i < 3; i++) {

            int index = utilityFunctions::random (0, parent.skillIndices.size () - 1);
            Skill skillReward; skillReward = gameData::gameSkills [parent.skillIndices [index]];
            room.skillRewards.push_back (skillReward);
            room.priceOfSkills [i] = utilityFunctions::random (gameData::gameSkills [parent.skillIndices [index]].minimumPrice, gameData::gameSkills [parent.skillIndices [index]].maximumPrice);
        }
        room.priceOfHeal = utilityFunctions::random (24, 108);
        room.roomType = "shop";
    } else if (random >= 10) {
        int index = utilityFunctions::random (0, parent.skillIndices.size () - 1);

        Skill skillReward; skillReward = gameData::gameSkills [parent.skillIndices [index]];
        room.skillRewards.push_back (skillReward);
        room.roomType = "skillreward";
    } else {
        int goldReward = utilityFunctions::random (1, 100); room.goldReward = goldReward; room.roomType = "goldreward";
    }

    return room;
}

void Game::displayRoomChoices (int roomIndex) {
    const int START = 0, MIDBOSS = 13, BOSS = 26;
    displayPaths ();
    if (roomIndex == START) {
        std::cout << "[1] " << dungeon [floor - 1].floorMap [1].roomType << std::endl;
        std::cout << "[2] " << dungeon [floor - 1].floorMap [2].roomType << std::endl;
        std::cout << "[3] " << dungeon [floor - 1].floorMap [3].roomType << std::endl;
    } else if (roomIndex >= 10 && roomIndex <= 12) {
        std::cout << "[1] Midboss" << std::endl;
    } else if (roomIndex == MIDBOSS) {
        std::cout << "[1] " << dungeon [floor - 1].floorMap [14].roomType << std::endl;
        std::cout << "[2] " << dungeon [floor - 1].floorMap [15].roomType << std::endl;
        std::cout << "[3] " << dungeon [floor - 1].floorMap [16].roomType << std::endl;
    } else if (roomIndex >= 23 && roomIndex <= 25) {
        std::cout << "[1] Floor boss" << std::endl;
    } else if (roomIndex < BOSS) {
        std::cout << "[1] " << dungeon [floor - 1].floorMap [roomIndex+3].roomType << std::endl;
    }
}

void Game::displayPaths () {

    std::cout << "Path 1: ";
    for (unsigned int i = 0; i < 4; i++) { std::cout << dungeon [floor - 1].floorMap [1 + i*3].roomType;
        if (dungeon [floor - 1].floorMap [1 + i*3].roomType == "enemy") {
            std::cout << " - " << dungeon [floor - 1].floorMap [1 + i*3].entityInRoom.name;
        }
        std::cout << ", ";
    }
    std::cout << dungeon [floor - 1].floorMap [13].roomType << ", ";
    for (unsigned int i = 0; i < 4; i++) { std::cout << dungeon [floor - 1].floorMap [14 + i*3].roomType;
        if (dungeon [floor - 1].floorMap [14 + i*3].roomType == "enemy") {
            std::cout << " - " << dungeon [floor - 1].floorMap [14 + i*3].entityInRoom.name;
        }
        std::cout << ", ";
    }
    std::cout << dungeon [floor - 1].floorMap [26].roomType << std::endl;

    std::cout << "Path 2: ";
    for (unsigned int i = 0; i < 4; i++) { std::cout << dungeon [floor - 1].floorMap [2 + i*3].roomType;
        if (dungeon [floor - 1].floorMap [2 + i*3].roomType == "enemy") {
            std::cout << " - " << dungeon [floor - 1].floorMap [2 + i*3].entityInRoom.name;
        }
        std::cout << ", ";
    }
    std::cout << dungeon [floor - 1].floorMap [13].roomType << ", ";
    for (unsigned int i = 0; i < 4; i++) { std::cout << dungeon [floor - 1].floorMap [15 + i*3].roomType;
        if (dungeon [floor - 1].floorMap [15 + i*3].roomType == "enemy") {
            std::cout << " - " << dungeon [floor - 1].floorMap [15 + i*3].entityInRoom.name;
        }
        std::cout << ", ";
    }
    std::cout << dungeon [floor - 1].floorMap [26].roomType << std::endl;

    std::cout << "Path 3: ";
    for (unsigned int i = 0; i < 4; i++) { std::cout << dungeon [floor - 1].floorMap [3 + i*3].roomType;
        if (dungeon [floor - 1].floorMap [3 + i*3].roomType == "enemy") {
            std::cout << " - " << dungeon [floor - 1].floorMap [3 + i*3].entityInRoom.name;
        }
        std::cout << ", ";
    }
    std::cout << dungeon [floor - 1].floorMap [13].roomType << ", ";
    for (unsigned int i = 0; i < 4; i++) { std::cout << dungeon [floor - 1].floorMap [16 + i*3].roomType;
        if (dungeon [floor - 1].floorMap [16 + i*3].roomType == "enemy") {
            std::cout << " - " << dungeon [floor - 1].floorMap [16 + i*3].entityInRoom.name;
        }
        std::cout << ", ";
    }
    std::cout << dungeon [floor - 1].floorMap [26].roomType << std::endl;
}

void Game::rewardPower (Entity &player) {
    int option_one, option_two, option_three;

    int index = utilityFunctions::random (0, gameData::gamePowers.size () - 1);
    option_one = index;

    index = utilityFunctions::random (0, gameData::gamePowers.size () - 1);
    option_two = index;

    index = utilityFunctions::random (0, gameData::gamePowers.size () - 1);
    option_three = index;

    std::cout << "Choose a power: \n[1] " << gameData::gamePowers [option_one].name << std::endl; std::cout << " -- " << gameData::gamePowers [option_one].description;
    std::cout << "\n[2] " << gameData::gamePowers [option_two].name << std::endl; std::cout << " -- " << gameData::gamePowers [option_two].description;
    std::cout << "\n[3] " << gameData::gamePowers [option_three].name << std::endl; std::cout << " -- " << gameData::gamePowers [option_three].description << std::endl;
    int choice = 0;

    while (choice < 1 || choice > 3) {
        choice = utilityFunctions::getIntegerInput ();
    }

    switch (choice) {
        case 1: {
            player.powers.push_back (&gameData::gamePowers [option_one]);
        } break;
        case 2: {
            player.powers.push_back (&gameData::gamePowers [option_two]);
        } break;
        case 3: {
            player.powers.push_back (&gameData::gamePowers [option_three]);
        } break;
    }
}

void Game::loop (Entity &player) {
    int roomIndex = 0;

    choosePlayerStart (player);

    while (player.health > 0) {
        std::cout << player.name << " HP " << player.health << " / " << player.maxHealth << " - " << player.gold << " G" << std::endl;
        std::cout << "FLOOR " << floor << std::endl;
        displayRoomChoices (roomIndex);

        int choice = -1;
        choice = utilityFunctions::getIntegerInput ();

        if (choice > 3 || choice <= 0) { choice = 1; }

        if (roomIndex == 0) { roomIndex = choice;
        } else if (roomIndex >= 10 && roomIndex <= 12) { roomIndex = 13;
        } else if (roomIndex >= 23 && roomIndex <= 25) { roomIndex = 26;
        } else if (roomIndex == 13) { roomIndex = choice + 13;
        } else {
            roomIndex += 3;
        }

        executeRoomLogic (player, roomIndex);

        if (roomIndex == 26 && player.health > 0) { roomIndex = 0; floor++; std::cout << "You made it to floor " << floor << "!" << std::endl; std::cin.get (); rewardPower (player); }
    }

    if (player.health <= 0) {
        std::cout << "You died..." << std::endl;
        PlayerStats::totalDamageDealt += PlayerStats::damageThisRun;
        std::cout << "You dealt " << PlayerStats::damageThisRun << " damage this run." << std::endl;
        PlayerStats::saveStatsToFile ("stats.save");
        std::cin.get ();
        std::cin.get ();

    }

}

void Game::executeRoomLogic (Entity &player, int roomIndex) {
    if (dungeon [floor - 1].floorMap [roomIndex].roomType == "enemy") {
        battle (player, dungeon [floor - 1].floorMap [roomIndex].entityInRoom);

    } else if (dungeon [floor - 1].floorMap [roomIndex].roomType == "shop") {
        shop (player, roomIndex);

    } else if (dungeon [floor - 1].floorMap [roomIndex].roomType == "skillreward") {
        std::cout << "You find an ancient text that teaches you a skill." << std::endl;
        replaceSkill (player, &dungeon [floor - 1].floorMap [roomIndex].skillRewards [0]);
    } else {
        std::cout << "You found a chest of gold!" << std::endl;
        player.gold += dungeon [floor - 1].floorMap [roomIndex].goldReward;
    }
}

void Game::shop (Entity &player, int roomIndex) {

    bool looping = true;
    while (looping) {
        std::cout << "SHOP - " << player.gold << " G" << std::endl;
        for (int i = 0; i < 3; i++) {
            std::cout << "[" << (i+1) << "] Buy Skill " << dungeon [floor - 1].floorMap [roomIndex].skillRewards [i].name << " - "
            << dungeon [floor - 1].floorMap [roomIndex].priceOfSkills [i] << std::endl;
            std::cout << " -- " << dungeon [floor - 1].floorMap [roomIndex].skillRewards [i].description << std::endl;
        }
        std::cout << "[4] Heal " << (player.maxHealth / 2) << " HP - " << dungeon [floor - 1].floorMap [roomIndex].priceOfHeal << std::endl;
        std::cout << "[5] Exit" << std::endl;
        int choice = 0; choice = utilityFunctions::getIntegerInput ();

        if (choice >= 1 && choice <= 3) {
            if (player.gold >= dungeon [floor - 1].floorMap [roomIndex].priceOfSkills [choice-1]) {
                player.gold -= dungeon [floor - 1].floorMap [roomIndex].priceOfSkills [choice-1];
                replaceSkill (player, &dungeon [floor - 1].floorMap [roomIndex].skillRewards [choice-1]);

            } else {
                std::cout << "Not enough money!" << std::endl;
            }

        }
        if (choice == 4) {
            if (player.gold >= dungeon [floor - 1].floorMap [roomIndex].priceOfHeal) {
                player.gold -= dungeon [floor - 1].floorMap [roomIndex].priceOfHeal;
                player.health += (player.maxHealth / 2); if (player.health > player.maxHealth) { player.health = player.maxHealth; }

            } else {
                std::cout << "Not enough money!" << std::endl;
            }

        }
        if (choice == 5) { looping = false; }
    }
}

void Game::choosePlayerStart (Entity &player) {
    const int NUMBER_OF_STARTING_SKILLS = 10;
    const int startingSkillIndices [NUMBER_OF_STARTING_SKILLS] = {1,2,3,4,5,7,8,15,17,18};

    int skill_options [5];

    std::cout << "CHOOSE 3 SKILLS:" << std::endl;
    for (unsigned int i = 0; i < 5; i++) {
        bool looping = true;

        while (looping) {
            skill_options [i] = startingSkillIndices [utilityFunctions::random (0, NUMBER_OF_STARTING_SKILLS-1)];

            bool isDuplicate = false;
            for (unsigned int j = 0; j < i; j++) {
                if (skill_options [i] == skill_options [j]) {
                    isDuplicate = true;
                }
            }

            if (!isDuplicate) { looping = false; }
        }

        std::cout << "[" << i << "] - " << gameData::gameSkills [skill_options [i]].name << std::endl;
        std::cout << " -- " << gameData::gameSkills [skill_options [i]].description << std::endl;
    }

    int choices [3] = {-1,-1,-1};

    for (unsigned int i = 0; i < 3; i++) {
        while (choices [i] < 0 || choices [i] >= 5) {
            choices [i] = utilityFunctions::getIntegerInput ();
        }
    }

    for (unsigned int i = 0; i < 3; i++) {
        player.skillset [i] = &gameData::gameSkills [skill_options [choices [i]]];
    }

    rewardPower (player);

}
