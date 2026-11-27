/**
 * @file    inventory.cpp
 * @brief   Inventory class implementation.
 * @author  Ruhul Alam
 * Student ID: 21317879
 * @date    2026-11-26
 */

#include "inventory.h"
#include <algorithm>

/* ================================================================== */
/* Constructor and destructor                                           */
/* ================================================================== */

/** @brief Build an empty inventory. */
Inventory::Inventory() {}

/** @brief Clean up the inventory and all its items. */
Inventory::~Inventory() {}

/* ================================================================== */
/* Add and remove items                                                 */
/* ================================================================== */

/**
 * @brief  Try to add an item to the inventory.
 * @details Fails if the total weight goes over the strength limit,
 *          or if the character already has an item of the same category
 *          (except rings). If it fails the item is not added and the
 *          caller keeps ownership.
 * @param  newItem   The item to add.
 * @param  strength  The character's current max carry weight.
 * @return True if the item was added, false otherwise.
 */
bool Inventory::addItem(std::unique_ptr<Item> newItem, int strength)
{
    if (!newItem) return false;

    /* Check the weight limit. */
    if (getTotalWeight() + newItem->getWeight() > strength) {
        return false;
    }

    /* Only one of each category except rings. */
    if (newItem->getCategory() != "Ring") {
        if (hasCategory(newItem->getCategory())) {
            return false;
        }
    }

    /* Add the item. The vector takes ownership. */
    items_.push_back(std::move(newItem));
    return true;
}

/**
 * @brief  Remove the item at the given position.
 * @param  index  Position in the list (0-based).
 * @return The removed item (caller takes ownership). Null if bad index.
 */
std::unique_ptr<Item> Inventory::removeItem(int index)
{
    if (index < 0 || index >= static_cast<int>(items_.size())) {
        return nullptr;
    }

    /* Move the item out of the vector, then erase the now-empty slot. */
    std::unique_ptr<Item> removed = std::move(items_[index]);
    items_.erase(items_.begin() + index);
    return removed;
}

/* ================================================================== */
/* Getters                                                              */
/* ================================================================== */

/** @brief Returns how many items are in the inventory. */
int Inventory::getCount() const
{
    return static_cast<int>(items_.size());
}

/** @brief Returns one item by position (read only). */
const Item* Inventory::getItem(int index) const
{
    if (index < 0 || index >= static_cast<int>(items_.size())) {
        return nullptr;
    }
    return items_[index].get();
}

/** @brief Returns the total weight of all items. */
int Inventory::getTotalWeight() const
{
    int total = 0;
    for (const auto& item : items_) {
        total += item->getWeight();
    }
    return total;
}

/** @brief Returns the sum of all attack bonuses. */
int Inventory::getTotalAtkBonus() const
{
    int total = 0;
    for (const auto& item : items_) {
        total += item->getAtkBonus();
    }
    return total;
}

/** @brief Returns the sum of all defence bonuses. */
int Inventory::getTotalDefBonus() const
{
    int total = 0;
    for (const auto& item : items_) {
        total += item->getDefBonus();
    }
    return total;
}

/** @brief Returns the sum of all health bonuses. */
int Inventory::getTotalHpBonus() const
{
    int total = 0;
    for (const auto& item : items_) {
        total += item->getHpBonus();
    }
    return total;
}

/** @brief Returns the sum of all strength bonuses. */
int Inventory::getTotalStrBonus() const
{
    int total = 0;
    for (const auto& item : items_) {
        total += item->getStrBonus();
    }
    return total;
}

/** @brief True if a Weapon is already in the inventory. */
bool Inventory::hasWeapon() const { return hasCategory("Weapon"); }

/** @brief True if Armour is already in the inventory. */
bool Inventory::hasArmour() const { return hasCategory("Armour"); }

/** @brief True if a Shield is already in the inventory. */
bool Inventory::hasShield() const { return hasCategory("Shield"); }

/* ================================================================== */
/* Display                                                              */
/* ================================================================== */

/**
 * @brief  Returns all items as a numbered list string.
 * @return A human-readable inventory list, or a message if empty.
 */
QString Inventory::toDisplayString() const
{
    if (items_.empty()) {
        return "  (nothing)";
    }
    QString s;
    for (int i = 0; i < static_cast<int>(items_.size()); ++i) {
        s += "  " + QString::number(i + 1) + ". " +
             items_[i]->toDisplayString() + "\n";
    }
    return s;
}

/* ================================================================== */
/* Private helpers                                                      */
/* ================================================================== */

/**
 * @brief  Check if a category is already in the inventory.
 * @param  category  The category name to look for.
 * @return True if found.
 */
bool Inventory::hasCategory(const QString& category) const
{
    for (const auto& item : items_) {
        if (item->getCategory() == category) {
            return true;
        }
    }
    return false;
}
