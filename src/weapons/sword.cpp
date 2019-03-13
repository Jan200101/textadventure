#include "weapons/sword.hpp"

/**
 * @file sword.cpp
 * @brief source for the Sword weapon
 */

/**
 * sets up various values inherited from Weapon
 */
Sword::Sword()
{
    this->setName("Sword");
    this->setDamage(10);
    this->setDurability(2750);
    this->setCritchance(30);
    this->setCritamplifier(2);
}