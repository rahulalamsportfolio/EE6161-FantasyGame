/**
 * @file    item.cpp
 * @brief   Item class and all item type implementations.
 * @author  Ruhul Alam
 * Student ID: 21317879
 * @date    2026-11-26
 */

#include "item.h"
#include <cstdlib>

/* ================================================================== */
/* Item - base class                                                    */
/* ================================================================== */

/**
 * @brief  Build an item with the given stats.
 * @param  name      The item name.
 * @param  weight    How heavy it is.
 * @param  atkBonus  Attack change (can be negative).
 * @param  defBonus  Defence bonus.
 * @param  hpBonus   Health bonus (can be negative).
 * @param  strBonus  Strength bonus.
 */
Item::Item(const QString& name, int weight, int atkBonus, int defBonus,
           int hpBonus, int strBonus)
    : name_(name), weight_(weight), atkBonus_(atkBonus),
      defBonus_(defBonus), hpBonus_(hpBonus), strBonus_(strBonus)
{
}

/** @brief Clean up the item. */
Item::~Item() {}

/** @brief Returns the item's name. */
QString Item::getName() const { return name_; }

/** @brief Returns how heavy the item is. */
int Item::getWeight() const { return weight_; }

/** @brief Returns the attack bonus (can be negative). */
int Item::getAtkBonus() const { return atkBonus_; }

/** @brief Returns the defence bonus. */
int Item::getDefBonus() const { return defBonus_; }

/** @brief Returns the health bonus (can be negative). */
int Item::getHpBonus() const { return hpBonus_; }

/** @brief Returns the strength bonus. */
int Item::getStrBonus() const { return strBonus_; }

/**
 * @brief  Returns item info as one line of text.
 * @return Name, category, weight, and bonuses as a string.
 */
QString Item::toDisplayString() const
{
    QString s = name_ + " [" + getCategory() + "] wt:" + QString::number(weight_);
    if (atkBonus_ != 0) s += " atk" + QString::number(atkBonus_);
    if (defBonus_ != 0) s += " def+" + QString::number(defBonus_);
    if (hpBonus_  != 0) s += " hp"  + QString::number(hpBonus_);
    if (strBonus_ != 0) s += " str+" + QString::number(strBonus_);
    return s;
}

/* ================================================================== */
/* Weapon                                                               */
/* ================================================================== */

/**
 * @brief  Build a Weapon.
 * @param  name      The weapon name.
 * @param  weight    How heavy it is.
 * @param  atkBonus  Attack bonus (always positive for weapons).
 */
Weapon::Weapon(const QString& name, int weight, int atkBonus)
    : Item(name, weight, atkBonus, 0, 0, 0)
{
}

/** @brief Returns "Weapon". */
QString Weapon::getCategory() const { return "Weapon"; }

/* ================================================================== */
/* Armour                                                               */
/* ================================================================== */

/**
 * @brief  Build an Armour item.
 * @param  name      The armour name.
 * @param  weight    How heavy it is.
 * @param  atkBonus  Attack change (negative means attack goes down).
 * @param  defBonus  Defence bonus.
 */
Armour::Armour(const QString& name, int weight, int atkBonus, int defBonus)
    : Item(name, weight, atkBonus, defBonus, 0, 0)
{
}

/** @brief Returns "Armour". */
QString Armour::getCategory() const { return "Armour"; }

/* ================================================================== */
/* Shield                                                               */
/* ================================================================== */

/**
 * @brief  Build a Shield item.
 * @param  name      The shield name.
 * @param  weight    How heavy it is.
 * @param  atkBonus  Attack change (negative means attack goes down).
 * @param  defBonus  Defence bonus.
 */
Shield::Shield(const QString& name, int weight, int atkBonus, int defBonus)
    : Item(name, weight, atkBonus, defBonus, 0, 0)
{
}

/** @brief Returns "Shield". */
QString Shield::getCategory() const { return "Shield"; }

/* ================================================================== */
/* Ring                                                                 */
/* ================================================================== */

/**
 * @brief  Build a Ring item.
 * @param  name      The ring name.
 * @param  weight    How heavy it is (always 1).
 * @param  hpBonus   Health bonus (can be negative).
 * @param  strBonus  Strength bonus.
 */
Ring::Ring(const QString& name, int weight, int hpBonus, int strBonus)
    : Item(name, weight, 0, 0, hpBonus, strBonus)
{
}

/** @brief Returns "Ring". */
QString Ring::getCategory() const { return "Ring"; }

/* ================================================================== */
/* Factory functions                                                    */
/* ================================================================== */

/** @brief Make a Sword (Weapon, weight 10, +10 attack). */
Item* makeSword() { return new Weapon("Sword", 10, 10); }

/** @brief Make a Dagger (Weapon, weight 5, +5 attack). */
Item* makeDagger() { return new Weapon("Dagger", 5, 5); }

/** @brief Make Plate Armour (Armour, weight 40, -5 attack, +10 defence). */
Item* makePlateArmour()   { return new Armour("Plate Armour",  40,  -5,  10); }

/** @brief Make Leather Armour (Armour, weight 20, +5 defence). */
Item* makeLeatherArmour() { return new Armour("Leather Armour",20,   0,   5); }

/** @brief Make a Large Shield (Shield, weight 30, -5 attack, +10 defence). */
Item* makeLargeShield()   { return new Shield("Large Shield",  30,  -5,  10); }

/** @brief Make a Small Shield (Shield, weight 10, +5 defence). */
Item* makeSmallShield()   { return new Shield("Small Shield",  10,   0,   5); }

/** @brief Make a Ring of Life (Ring, weight 1, +10 health). */
Item* makeRingOfLife()    { return new Ring("Ring of Life",     1,  10,   0); }

/** @brief Make a Ring of Strength (Ring, weight 1, +50 strength, -10 health). */
Item* makeRingOfStrength(){ return new Ring("Ring of Strength", 1, -10,  50); }

/**
 * @brief  Make a random item.
 * @details Picks one of the 8 items at random.
 * @return A new item on the heap.
 */
Item* makeRandomItem()
{
    /* Pick a number 0-7 and return that item. */
    switch (rand() % 8) {
        case 0: return makeSword();
        case 1: return makeDagger();
        case 2: return makePlateArmour();
        case 3: return makeLeatherArmour();
        case 4: return makeLargeShield();
        case 5: return makeSmallShield();
        case 6: return makeRingOfLife();
        default: return makeRingOfStrength();
    }
}
