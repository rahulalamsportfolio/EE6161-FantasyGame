/**
 * @file    inventory.h
 * @brief   Holds the items a character is carrying.
 * @details Uses a vector of unique_ptr<Item> so the inventory
 *          can grow without a fixed limit (as long as the character
 *          has enough carry weight).
 *          Only one item of each category is allowed except rings,
 *          which can be many.
 * @author  Ruhul Alam
 * @date    2026-11-26
 */

#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <memory>
#include <QString>
#include "item.h"

/**
 * @class  Inventory
 * @brief  Manages the items a character carries.
 *
 * Items are stored in a vector of unique_ptr so the inventory
 * owns them. When an item is removed it is returned as a
 * unique_ptr so the caller takes over ownership.
 */
class Inventory {
public:
    Inventory();
    ~Inventory();

    /**
     * @brief  Try to add an item to the inventory.
     * @details Fails if adding the item would go over the carry weight
     *          limit, or if the character already has an item of that
     *          category (except rings). On failure the item is not added.
     * @param  newItem   The item to add (ownership passes on success).
     * @param  strength  Current max carry weight of the character.
     * @return True if the item was added, false otherwise.
     */
    bool addItem(std::unique_ptr<Item> newItem, int strength);

    /**
     * @brief  Remove the item at the given position.
     * @param  index  Position in the list (0-based).
     * @return The item (caller takes ownership). Null if bad index.
     */
    std::unique_ptr<Item> removeItem(int index);

    int         getCount()       const; /**< @brief How many items are carried. */
    int         getTotalWeight() const; /**< @brief Total weight of all items. */
    int         getTotalAtkBonus() const; /**< @brief Sum of all attack bonuses. */
    int         getTotalDefBonus() const; /**< @brief Sum of all defence bonuses. */
    int         getTotalHpBonus()  const; /**< @brief Sum of all health bonuses. */
    int         getTotalStrBonus() const; /**< @brief Sum of all strength bonuses. */

    bool hasWeapon()   const; /**< @brief True if a Weapon is already carried. */
    bool hasArmour()   const; /**< @brief True if Armour is already carried. */
    bool hasShield()   const; /**< @brief True if a Shield is already carried. */

    /**
     * @brief  Check if a category is already in the inventory.
     * @param  category  The category name to check.
     * @return True if that category is already present.
     */
    bool hasCategory(const QString& category) const;

    /**
     * @brief  Read one item (read only).
     * @param  index  Position (0-based).
     * @return Pointer to the item, or null if bad index.
     */
    const Item* getItem(int index) const;

    /**
     * @brief  Returns all items as a numbered list string.
     * @return A human-readable inventory list.
     */
    QString toDisplayString() const;

private:
    /** The list of carried items. */
    std::vector<std::unique_ptr<Item>> items_;
};

#endif // INVENTORY_H
