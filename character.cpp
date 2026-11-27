/**
 * @file    character.cpp
 * @brief   Character base class and all race implementations.
 * @author  Ruhul Alam
 * Student ID: 21317879
 * @date    2026-11-26
 */

#include "character.h"
#include <cstdlib>

/* ================================================================== */
/* Character - base class                                               */
/* ================================================================== */

/**
 * @brief  Build a character with the given stats.
 */
Character::Character(const QString& name,
                     int attack, int defence, int health, int strength,
                     int atkNum, int atkDen, int defNum, int defDen)
    : name_(name), baseAttack_(attack), baseDefence_(defence),
      health_(health), baseMaxHealth_(health), baseStrength_(strength),
      gold_(0), atkNum_(atkNum), atkDen_(atkDen),
      defNum_(defNum), defDen_(defDen),
      inventory_(new Inventory())
{
}

/** @brief Clean up the character and its inventory. */
Character::~Character() {}

/* ---- Virtual getters ---- */

/** @brief Returns race attack (before items). */
int Character::getAttack(bool /*isNight*/) const { return baseAttack_; }

/** @brief Returns race defence (before items). */
int Character::getDefence(bool /*isNight*/) const { return baseDefence_; }

/** @brief Returns attack chance as a double. */
double Character::getAttackChance(bool /*isNight*/) const
{
    return static_cast<double>(atkNum_) / static_cast<double>(atkDen_);
}

/** @brief Returns defence chance as a double. */
double Character::getDefenceChance(bool /*isNight*/) const
{
    return static_cast<double>(defNum_) / static_cast<double>(defDen_);
}

/* ---- Non-virtual getters and setters ---- */

/** @brief Returns the current health. */
int Character::getHealth() const { return health_; }

/**
 * @brief  Returns the max health (base + ring bonuses).
 * @return Base health plus any ring of life bonuses.
 */
int Character::getMaxHealth() const
{
    return baseMaxHealth_ + inventory_->getTotalHpBonus();
}

/**
 * @brief  Returns the current max carry weight (base + ring bonuses).
 */
int Character::getStrength() const
{
    return baseStrength_ + inventory_->getTotalStrBonus();
}

/** @brief Returns gold collected. */
int Character::getGold() const { return gold_; }

/** @brief True if health is above zero. */
bool Character::isAlive() const { return health_ > 0; }

/** @brief Returns the character's name. */
QString Character::getName() const { return name_; }

/** @brief Change the character's name. */
void Character::setName(const QString& n) { name_ = n; }

/** @brief Add gold to the total. */
void Character::addGold(int amount)
{
    if (amount > 0) gold_ += amount;
}

/**
 * @brief  Heal by the given amount. Health stops at getMaxHealth().
 */
void Character::heal(int amount)
{
    if (amount <= 0) return;
    health_ += amount;
    int maxHp = getMaxHealth();
    if (health_ > maxHp) health_ = maxHp;
}

/**
 * @brief  Take damage. Health stops at zero.
 */
void Character::takeDamage(int amount)
{
    if (amount <= 0) return;
    health_ -= amount;
    if (health_ < 0) health_ = 0;
}

/* ---- Total stats including items ---- */

/**
 * @brief  Returns total attack including weapon and armour modifiers.
 */
int Character::getTotalAttack(bool isNight) const
{
    int total = getAttack(isNight) + inventory_->getTotalAtkBonus();
    /* Attack cannot go below 0. */
    return (total < 0) ? 0 : total;
}

/**
 * @brief  Returns total defence including armour and shield modifiers.
 */
int Character::getTotalDefence(bool isNight) const
{
    int total = getDefence(isNight) + inventory_->getTotalDefBonus();
    return (total < 0) ? 0 : total;
}

/* ---- Dice rolls ---- */

/**
 * @brief  Roll for attack success.
 * @details Uses rand() to pick a number between 1 and atkDen_.
 *          If that number is <= atkNum_ the attack works.
 * @return True if the attack roll succeeds.
 */
bool Character::rollAttack(bool isNight) const
{
    double chance = getAttackChance(isNight);
    /* chance of 1.0 means always hits. */
    if (chance >= 1.0) return true;
    if (chance <= 0.0) return false;
    /* Roll 1 to 100 and check against percentage. */
    int roll = (rand() % 100) + 1;
    return roll <= static_cast<int>(chance * 100.0);
}

/**
 * @brief  Roll for defence success.
 * @return True if the defence roll succeeds.
 */
bool Character::rollDefence(bool isNight) const
{
    double chance = getDefenceChance(isNight);
    if (chance >= 1.0) return true;
    if (chance <= 0.0) return false;
    int roll = (rand() % 100) + 1;
    return roll <= static_cast<int>(chance * 100.0);
}

/* ---- Inventory access ---- */

/** @brief Returns the editable inventory. */
Inventory& Character::getInventory() { return *inventory_; }

/** @brief Returns the read-only inventory. */
const Inventory& Character::getInventory() const { return *inventory_; }

/* ================================================================== */
/* Human                                                                */
/* ================================================================== */

/** @brief Build a Human: A30 2/3, D20 1/2, H60, S100. */
Human::Human(const QString& name)
    : Character(name, 30, 20, 60, 100, 2, 3, 1, 2)
{
}

/** @brief Returns "Human". */
QString Human::getRaceName() const { return "Human"; }

/**
 * @brief  A successful Human defence causes no damage.
 * @return Always 0.
 */
int Human::getSpecialDefenceDamage(int /*adjustedDamage*/, bool /*isNight*/) const
{
    return 0;
}

/* ================================================================== */
/* Elf                                                                  */
/* ================================================================== */

/** @brief Build an Elf: A40 1/1, D10 1/4, H40, S70. */
Elf::Elf(const QString& name)
    : Character(name, 40, 10, 40, 70, 1, 1, 1, 4)
{
}

/** @brief Returns "Elf". */
QString Elf::getRaceName() const { return "Elf"; }

/**
 * @brief  A successful Elf defence heals the Elf by 1.
 * @return -1 (negative means heal 1).
 */
int Elf::getSpecialDefenceDamage(int /*adjustedDamage*/, bool /*isNight*/) const
{
    return -1;
}

/* ================================================================== */
/* Dwarf                                                                */
/* ================================================================== */

/** @brief Build a Dwarf: A30 2/3, D20 2/3, H50, S130. */
Dwarf::Dwarf(const QString& name)
    : Character(name, 30, 20, 50, 130, 2, 3, 2, 3)
{
}

/** @brief Returns "Dwarf". */
QString Dwarf::getRaceName() const { return "Dwarf"; }

/**
 * @brief  A successful Dwarf defence causes no damage.
 * @return Always 0.
 */
int Dwarf::getSpecialDefenceDamage(int /*adjustedDamage*/, bool /*isNight*/) const
{
    return 0;
}

/* ================================================================== */
/* Hobbit                                                               */
/* ================================================================== */

/** @brief Build a Hobbit: A25 1/3, D20 2/3, H70, S85. */
Hobbit::Hobbit(const QString& name)
    : Character(name, 25, 20, 70, 85, 1, 3, 2, 3)
{
}

/** @brief Returns "Hobbit". */
QString Hobbit::getRaceName() const { return "Hobbit"; }

/**
 * @brief  A successful Hobbit defence causes 0 to 5 random damage.
 * @return A random number from 0 to 5.
 */
int Hobbit::getSpecialDefenceDamage(int /*adjustedDamage*/, bool /*isNight*/) const
{
    return rand() % 6; /* 0, 1, 2, 3, 4, or 5 */
}

/* ================================================================== */
/* Orc                                                                  */
/* ================================================================== */

/**
 * @brief  Build an Orc. Base stats are the daytime ones.
 *         Night stats are handled in the override methods.
 */
Orc::Orc(const QString& name)
    : Character(name, 25, 10, 50, 130, 1, 4, 1, 4)
{
}

/** @brief Returns "Orc". */
QString Orc::getRaceName() const { return "Orc"; }

/** @brief Orc attack: 25 during day, 45 at night. */
int Orc::getAttack(bool isNight) const
{
    return isNight ? 45 : 25;
}

/** @brief Orc defence: 10 during day, 25 at night. */
int Orc::getDefence(bool isNight) const
{
    return isNight ? 25 : 10;
}

/** @brief Orc attack chance: 1/4 during day, 1/1 at night. */
double Orc::getAttackChance(bool isNight) const
{
    return isNight ? 1.0 : (1.0 / 4.0);
}

/** @brief Orc defence chance: 1/4 during day, 1/2 at night. */
double Orc::getDefenceChance(bool isNight) const
{
    return isNight ? (1.0 / 2.0) : (1.0 / 4.0);
}

/**
 * @brief  Orc special defence.
 * @details During day: 1/4 of adjusted damage.
 *          At night: heals by 1 (returns -1).
 */
int Orc::getSpecialDefenceDamage(int adjustedDamage, bool isNight) const
{
    if (isNight) {
        return -1; /* Heal 1 at night. */
    }
    /* During day: take 1/4 of the adjusted damage. At least 0. */
    int dmg = adjustedDamage / 4;
    return (dmg < 0) ? 0 : dmg;
}

/* ================================================================== */
/* Factory functions                                                    */
/* ================================================================== */

/**
 * @brief  Make a character of the given race with the given name.
 * @param  raceName  One of "Human", "Elf", "Dwarf", "Hobbit", "Orc".
 * @param  name      The character's name.
 * @return A new character on the heap (caller takes ownership).
 */
Character* makeCharacter(const QString& raceName, const QString& name)
{
    if (raceName == "Elf")    return new Elf(name);
    if (raceName == "Dwarf")  return new Dwarf(name);
    if (raceName == "Hobbit") return new Hobbit(name);
    if (raceName == "Orc")    return new Orc(name);
    /* Default to Human if unknown race given. */
    return new Human(name);
}

/**
 * @brief  Make a random enemy.
 * @details Picks one of the 5 races at random, and picks a name
 *          from a fixed list.
 * @return A new enemy on the heap.
 */
Character* makeRandomEnemy()
{
    /* A pool of enemy names to pick from. */
    static const char* names[] = {
        "Gargoyle", "Grimtooth", "Stoneclaw", "Shadowmere",
        "Ironhide", "Redcap", "Blackthorn", "Frostbane",
        "Skulker", "Nightcrawler", "Rotfang", "Swiftblade"
    };
    static const int nameCount = 12;

    /* Pick a random name and race. */
    const QString name = names[rand() % nameCount];
    switch (rand() % 5) {
        case 0: return new Human(name);
        case 1: return new Elf(name);
        case 2: return new Dwarf(name);
        case 3: return new Hobbit(name);
        default: return new Orc(name);
    }
}
