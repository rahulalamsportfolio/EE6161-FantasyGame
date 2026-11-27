/**
 * @file    character.h
 * @brief   Base class and race classes for all game characters.
 * @details Character is abstract because getRaceName() and
 *          getSpecialDefenceDamage() are pure virtual.
 *          Each race (Human, Elf, Dwarf, Hobbit, Orc) sets its own
 *          stats and special defence rule.
 *          Characters own an Inventory via unique_ptr.
 * @author  Ruhul Alam
 * Student ID: 21317879
 * @date    2026-11-26
 */

#ifndef CHARACTER_H
#define CHARACTER_H

#include <QString>
#include <memory>
#include "inventory.h"

/**
 * @class  Character
 * @author Ruhul Alam
 * Student ID: 21317879
 * @brief  Abstract base class for every character in the game.
 *
 * Holds stats shared by all characters: health, attack, defence,
 * and strength. Owns an Inventory.
 * You cannot create a Character directly - use one of the race
 * classes instead.
 */
class Character {
public:
    /**
     * @brief  Build a character with the given stats.
     * @param  name      The character's name.
     * @param  attack    How hard this character hits.
     * @param  defence   How well this character blocks.
     * @param  health    Starting health points.
     * @param  strength  Max weight this character can carry.
     * @param  atkNum    Top of the attack chance fraction.
     * @param  atkDen    Bottom of the attack chance fraction.
     * @param  defNum    Top of the defence chance fraction.
     * @param  defDen    Bottom of the defence chance fraction.
     */
    Character(const QString& name,
              int attack, int defence, int health, int strength,
              int atkNum, int atkDen, int defNum, int defDen);

    /** @brief Clean up the character and its inventory. */
    virtual ~Character();

    /* ---- Pure virtual - each race must implement these ---- */

    /**
     * @brief  Returns the name of this race.
     * @return Race name string (e.g. "Human").
     */
    virtual QString getRaceName() const = 0;

    /**
     * @brief  Returns damage this character takes when defence works.
     * @details Each race has a different special rule.
     *          A negative return value means the character heals.
     * @param  adjustedDamage  Attacker total attack minus defender total defence.
     * @param  isNight         True if it is night time.
     * @return Damage to take (negative = heal that amount).
     */
    virtual int getSpecialDefenceDamage(int adjustedDamage, bool isNight) const = 0;

    /* ---- Virtual getters (Orc overrides for day vs night) ---- */

    /**
     * @brief  Returns race attack value (before items).
     * @param  isNight  True during night time.
     */
    virtual int getAttack(bool isNight = false)         const;

    /**
     * @brief  Returns race defence value (before items).
     * @param  isNight  True during night time.
     */
    virtual int getDefence(bool isNight = false)        const;

    /**
     * @brief  Returns attack chance as a double between 0 and 1.
     * @param  isNight  True during night time.
     */
    virtual double getAttackChance(bool isNight = false)  const;

    /**
     * @brief  Returns defence chance as a double between 0 and 1.
     * @param  isNight  True during night time.
     */
    virtual double getDefenceChance(bool isNight = false) const;

    /* ---- Non-virtual getters and setters ---- */

    int     getHealth()    const; /**< @brief Current health. */
    int     getMaxHealth() const; /**< @brief Max health (base + ring bonuses). */
    int     getStrength()  const; /**< @brief Max carry weight (base + rings). */
    int     getGold()      const; /**< @brief Gold collected so far. */
    bool    isAlive()      const; /**< @brief True if health is above zero. */
    QString getName()      const; /**< @brief The character's name. */

    void setName(const QString& n); /**< @brief Change the character's name. */
    void addGold(int amount);       /**< @brief Add to gold total. */

    /**
     * @brief  Heal this character by the given amount.
     * @details Health will not go above getMaxHealth().
     * @param  amount  How much to heal.
     */
    void heal(int amount);

    /**
     * @brief  Reduce health by the given amount.
     * @details Health will not go below zero.
     * @param  amount  How much damage to take.
     */
    void takeDamage(int amount);

    /* ---- Total stats including items ---- */

    /**
     * @brief  Returns attack including weapon and armour modifiers.
     * @param  isNight  True during night time.
     */
    int getTotalAttack(bool isNight = false)  const;

    /**
     * @brief  Returns defence including armour and shield modifiers.
     * @param  isNight  True during night time.
     */
    int getTotalDefence(bool isNight = false) const;

    /* ---- Dice rolls ---- */

    /**
     * @brief  Roll for attack success.
     * @param  isNight  True during night time.
     * @return True if the attack roll succeeds.
     */
    bool rollAttack(bool isNight = false)  const;

    /**
     * @brief  Roll for defence success.
     * @param  isNight  True during night time.
     * @return True if the defence roll succeeds.
     */
    bool rollDefence(bool isNight = false) const;

    /* ---- Inventory access ---- */

    Inventory&       getInventory();       /**< @brief Editable inventory. */
    const Inventory& getInventory() const; /**< @brief Read-only inventory. */

protected:
    QString name_;       /**< The character's name. */
    int baseAttack_;     /**< Attack from race stats. */
    int baseDefence_;    /**< Defence from race stats. */
    int health_;         /**< Current health points. */
    int baseMaxHealth_;  /**< Starting max health (without item bonuses). */
    int baseStrength_;   /**< Base carry weight (without ring bonuses). */
    int gold_;           /**< Gold collected. */
    int atkNum_;         /**< Attack chance fraction - top number. */
    int atkDen_;         /**< Attack chance fraction - bottom number. */
    int defNum_;         /**< Defence chance fraction - top number. */
    int defDen_;         /**< Defence chance fraction - bottom number. */

    /** The items this character is carrying. */
    std::unique_ptr<Inventory> inventory_;
};

/* ================================================================== */
/* Race classes                                                         */
/* ================================================================== */

/**
 * @class  Human
 * @author Ruhul Alam
 * Student ID: 21317879
 * @brief  Human character.
 * @details Attack 30 (2/3 chance), Defence 20 (1/2 chance),
 *          Health 60, Strength 100.
 *          A successful defence causes no damage.
 */
class Human : public Character {
public:
    explicit Human(const QString& name);
    QString getRaceName() const override;
    int getSpecialDefenceDamage(int adjustedDamage, bool isNight) const override;
};

/**
 * @class  Elf
 * @author Ruhul Alam
 * Student ID: 21317879
 * @brief  Elf character.
 * @details Attack 40 (always hits), Defence 10 (1/4 chance),
 *          Health 40, Strength 70.
 *          A successful defence heals the Elf by 1.
 */
class Elf : public Character {
public:
    explicit Elf(const QString& name);
    QString getRaceName() const override;
    int getSpecialDefenceDamage(int adjustedDamage, bool isNight) const override;
};

/**
 * @class  Dwarf
 * @author Ruhul Alam
 * Student ID: 21317879
 * @brief  Dwarf character.
 * @details Attack 30 (2/3 chance), Defence 20 (2/3 chance),
 *          Health 50, Strength 130.
 *          A successful defence causes no damage.
 */
class Dwarf : public Character {
public:
    explicit Dwarf(const QString& name);
    QString getRaceName() const override;
    int getSpecialDefenceDamage(int adjustedDamage, bool isNight) const override;
};

/**
 * @class  Hobbit
 * @author Ruhul Alam
 * Student ID: 21317879
 * @brief  Hobbit character.
 * @details Attack 25 (1/3 chance), Defence 20 (2/3 chance),
 *          Health 70, Strength 85.
 *          A successful defence causes 0 to 5 random damage.
 */
class Hobbit : public Character {
public:
    explicit Hobbit(const QString& name);
    QString getRaceName() const override;
    int getSpecialDefenceDamage(int adjustedDamage, bool isNight) const override;
};

/**
 * @class  Orc
 * @author Ruhul Alam
 * Student ID: 21317879
 * @brief  Orc character. Very different stats during day and night.
 * @details Day:   Attack 25 (1/4 chance), Defence 10 (1/4 chance).
 *          Night: Attack 45 (always hits), Defence 25 (1/2 chance).
 *          Health 50, Strength 130.
 *          Daytime: successful defence causes 1/4 of adjusted damage.
 *          Night: successful defence heals by 1.
 */
class Orc : public Character {
public:
    explicit Orc(const QString& name);
    QString getRaceName()                              const override;
    int     getAttack(bool isNight = false)            const override;
    int     getDefence(bool isNight = false)           const override;
    double  getAttackChance(bool isNight = false)      const override;
    double  getDefenceChance(bool isNight = false)     const override;
    int     getSpecialDefenceDamage(int adjustedDamage, bool isNight) const override;
};

/**
 * @brief  Make a character of the given race with the given name.
 * @details Convenience factory used by the board and GUI.
 * @param  raceName  One of "Human", "Elf", "Dwarf", "Hobbit", "Orc".
 * @param  name      The character's name.
 * @return A new character on the heap (caller takes ownership).
 */
Character* makeCharacter(const QString& raceName, const QString& name);

/**
 * @brief  Make a random enemy character.
 * @details Picks a random race and a random name.
 * @return A new enemy on the heap.
 */
Character* makeRandomEnemy();

#endif // CHARACTER_H
