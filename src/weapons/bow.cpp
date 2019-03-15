#include "weapons/bow.hpp"

#include <iostream>

/**
 * @file bow.cpp
 * @brief source for the Bow weapon
 */

/**
 * sets up various values inherited from Weapon
 */
Bow::Bow()
{
    this->setName("Bow");
    this->setDamage(8);
    this->setDurability(2000);
    this->setCritchance(75);
    this->setCritamplifier(3);
    this->setAmmunition(40);
}