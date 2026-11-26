/**
 * @file    item.h
 * @brief   Base class and all item types for the game.
 * @details An Item can be picked up and carried by a character.
 *          Items change attack, defence, health, or strength.
 *          Item is abstract so you cannot create one directly.
 *          Each type (Weapon, Armour, Shield, Ring) has its own category.
 *          A character can carry one of each category except rings.
 * @author  Ruhul Alam
 * @date    2026-11-26
 */

#ifndef ITEM_H
#define ITEM_H

#include <QString>

/**
 * @class  Item
 * @brief  Abstract base class for all items in the game.
 *
 * Every item has a name, weight, and stat bonuses.
 * getCategory() is pure virtual - each item type must say
 * what category it belongs to.
 */
class Item {
public:
    /**
     * @brief  Build an item.
     * @param  name      What the item is called.
     * @param  weight    How heavy the item is.
     * @param  atkBonus  How much it changes attack (can be negative).
     * @param  defBonus  How much it adds to defence.
     * @param  hpBonus   How much it adds to max health (can be negative).
     * @param  strBonus  How much it adds to max carry weight.
     */
    Item(const QString& name, int weight, int atkBonus, int defBonus,
         int hpBonus = 0, int strBonus = 0);

    /** @brief Clean up the item. */
    virtual ~Item();

    /**
     * @brief  Returns the category of this item.
     * @details Each type returns its own string: "Weapon", "Armour",
     *          "Shield", or "Ring".
     * @return The category name.
     */
    virtual QString getCategory() const = 0;

    QString getName()    const; /**< @brief The item's name. */
    int     getWeight()  const; /**< @brief How heavy it is. */
    int     getAtkBonus() const; /**< @brief Attack change (can be negative). */
    int     getDefBonus() const; /**< @brief Defence bonus. */
    int     getHpBonus()  const; /**< @brief Health bonus (can be negative). */
    int     getStrBonus() const; /**< @brief Strength bonus. */

    /**
     * @brief  Returns item info as one line of text.
     * @return Name, weight, and bonuses as a string.
     */
    QString toDisplayString() const;

protected:
    QString name_;
    int     weight_;
    int     atkBonus_;
    int     defBonus_;
    int     hpBonus_;
    int     strBonus_;
};

/* ------------------------------------------------------------------ */

/**
 * @class  Weapon
 * @brief  A weapon (Sword or Dagger). Adds attack.
 * @details Only one weapon may be carried at a time.
 */
class Weapon : public Item {
public:
    Weapon(const QString& name, int weight, int atkBonus);
    QString getCategory() const override;
};

/**
 * @class  Armour
 * @brief  Armour (Plate or Leather). Adds defence, may reduce attack.
 * @details Only one armour may be carried at a time.
 */
class Armour : public Item {
public:
    Armour(const QString& name, int weight, int atkBonus, int defBonus);
    QString getCategory() const override;
};

/**
 * @class  Shield
 * @brief  A shield (Large or Small). Adds defence, may reduce attack.
 * @details Only one shield may be carried at a time.
 */
class Shield : public Item {
public:
    Shield(const QString& name, int weight, int atkBonus, int defBonus);
    QString getCategory() const override;
};

/**
 * @class  Ring
 * @brief  A ring (Ring of Life or Ring of Strength).
 * @details A character can carry many rings as long as there is
 *          enough carry weight.
 */
class Ring : public Item {
public:
    Ring(const QString& name, int weight, int hpBonus, int strBonus);
    QString getCategory() const override;
};

/* ------------------------------------------------------------------ */
/* Factory functions - each one makes a named item.                    */
/* ------------------------------------------------------------------ */

/** @brief Make a Sword (Weapon, weight 10, +10 attack). */
Item* makeSword();

/** @brief Make a Dagger (Weapon, weight 5, +5 attack). */
Item* makeDagger();

/** @brief Make Plate Armour (Armour, weight 40, -5 attack, +10 defence). */
Item* makePlateArmour();

/** @brief Make Leather Armour (Armour, weight 20, +5 defence). */
Item* makeLeatherArmour();

/** @brief Make a Large Shield (Shield, weight 30, -5 attack, +10 defence). */
Item* makeLargeShield();

/** @brief Make a Small Shield (Shield, weight 10, +5 defence). */
Item* makeSmallShield();

/** @brief Make a Ring of Life (Ring, weight 1, +10 health). */
Item* makeRingOfLife();

/** @brief Make a Ring of Strength (Ring, weight 1, +50 strength, -10 health). */
Item* makeRingOfStrength();

/**
 * @brief  Make a random item.
 * @details Used to place items on the board at the start of the game.
 * @return A new item picked at random.
 */
Item* makeRandomItem();

#endif // ITEM_H
