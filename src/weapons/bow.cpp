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
    this->setDurability(200);
    this->setCritchance(50);
    this->setCritamplifier(2);
    this->setAmmunition(40);
}

/**
 * implements checks for ammunition then fallsback onto Weapon::attack
 */
uint16_t Bow::attack(bool msgoutput)
{
    if (this->ammunition <= 0)
    {
        if (msgoutput)
        {
            std::cout << "No arrows left" << std::endl;
        }
        return 0;
    }

    this->setAmmunition(this->getAmmunition() - 1);

    return Weapon::attack(msgoutput);
}

uint16_t Bow::getAmmunition()
{
    return this->ammunition;
}

void Bow::setAmmunition(uint16_t paramAmmo)
{
    this->ammunition = paramAmmo;
}