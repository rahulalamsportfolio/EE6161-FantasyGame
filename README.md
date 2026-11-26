# EE6161 Fantasy Game

**Student:** Ruhul Alam — 21317879
**Module:** EE6161 Advanced Programming
**Language:** C++14 with Qt 5/6

## What This Is

A turn-based fantasy game with a Qt GUI window.
You pick a race, choose a board size, and explore the grid.
Move around, pick up items, fight enemies, and collect gold.

## How To Build

1. Install Qt Creator (free at qt.io — Qt 5 or Qt 6 with MinGW on Windows).
2. Open `FantasyGame.pro` in Qt Creator.
3. Click the green Run button.

## How To Play

Type commands in the input box or click the buttons on the right.

| Command | What it does |
|---------|-------------|
| `n` | Move north |
| `s` | Move south |
| `e` | Move east |
| `w` | Move west |
| `p` | Pick up item on this square |
| `d` | Drop an item (use `d 2` to drop item number 2) |
| `a` | Attack the enemy on this square |
| `l` | Look at this square |
| `i` | Show inventory |
| `q` | Quit |

The board shows: `@` = you, `E` = enemy, `I` = item, `.` = empty.

## Races

| Race   | Attack | Def | HP | Carry | Attack chance | Defence chance |
|--------|--------|-----|----|-------|---------------|----------------|
| Human  | 30     | 20  | 60 | 100   | 2/3           | 1/2            |
| Elf    | 40     | 10  | 40 | 70    | 1/1           | 1/4            |
| Dwarf  | 30     | 20  | 50 | 130   | 2/3           | 2/3            |
| Hobbit | 25     | 20  | 70 | 85    | 1/3           | 2/3            |
| Orc    | 25*    | 10* | 50 | 130   | 1/4*          | 1/4*           |

*Orc stats at night: Attack 45, Defence 25, Attack chance 1/1, Defence chance 1/2.

## Day and Night

Time flips every 5 commands. At night Orcs get much stronger.

## Items

| Item           | Weight | Effect |
|----------------|--------|--------|
| Sword          | 10     | +10 attack |
| Dagger         | 5      | +5 attack |
| Plate Armour   | 40     | -5 attack, +10 defence |
| Leather Armour | 20     | +5 defence |
| Large Shield   | 30     | -5 attack, +10 defence |
| Small Shield   | 10     | +5 defence |
| Ring of Life   | 1      | +10 max health |
| Ring of Strength | 1    | +50 carry weight, -10 max health |

You can carry one weapon, one armour, one shield, and as many rings as your strength allows.

## Special Defence Abilities

Each race has a special ability when it successfully defends:

- **Human** — no extra damage, clean block.
- **Elf** — heals 1 HP on a successful block.
- **Dwarf** — no extra damage, clean block.
- **Hobbit** — deals 0 to 5 random damage back to the attacker.
- **Orc (day)** — takes only 1/4 of the adjusted damage.
- **Orc (night)** — heals 1 HP on a successful block.

## Gold

When you beat an enemy you get gold equal to their total defence value.
Try to collect as much as you can before you quit.

## Project Structure

| File | What it does |
|------|-------------|
| `character.h / .cpp` | Abstract Character base, 5 race classes, combat rolls |
| `item.h / .cpp` | Abstract Item base, 4 item types, 8 factory functions |
| `inventory.h / .cpp` | Inventory with weight limit and category checks |
| `location.h / .cpp` | One board square, holds an enemy or item |
| `board.h / .cpp` | 2D grid of locations, random enemy/item placement |
| `game.h / .cpp` | Command processor, combat, day/night cycle |
| `mainwindow.h / .cpp` | Qt GUI — setup page and game page |
| `main.cpp` | Qt application entry point |
