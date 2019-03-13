#include "weapon.hpp"

#include <stdlib.h>
#include <ctime>
#include <iostream>

/**
 * @file weapon.hpp
 * @brief Source for the Weapon class
 */

/**
 * constructor sets random salt to the current time
 * randomness is used in Weapon::attack
 */
Weapon::Weapon()
{
    srand(time(NULL));
}

std::string Weapon::getName()
{
    return this->name;
}

void Weapon::setName(std::string paramName)
{
    this->name = paramName;
}

uint16_t Weapon::getDamage()
{
    return this->damage;
}

void Weapon::setDamage(uint16_t paramDamage)
{
    this->damage = paramDamage;
}

uint16_t Weapon::getDurability()
{
    return this->durability;
}

void Weapon::setDurability(uint16_t paramDur)
{
    this->durability = paramDur;
}

uint8_t Weapon::getCritchance()
{
    return this->critchance;
}

void Weapon::setCritchance(uint8_t paramChance)
{
    this->critchance = paramChance;
}

uint8_t Weapon::getCritamplifier()
{
    return this->critamplifier;
}

void Weapon::setCritamplifier(uint8_t paramAmp)
{
    this->critamplifier = paramAmp;
}

/**
 * @param msgoutput declares if the function should output text to the stdout or not
 * @returns damage delt (multiplied by critamplifier)
 *
 * checks if the weapon has any durability left,
 * decreases the durability by 1,
 * calculates if a crit happens or not (Salt set in Weapon::Weapon)
 */
uint16_t Weapon::attack(bool msgoutput)
{
    if (durability <= 0)
    {
        if (msgoutput)
        {
            std::cout << "Your weapon broke" << std::endl;
        }
        return 0;
    }

    this->setDurability(this->getDurability() - 1);

    if ((rand() % 255) + 1 < this->critchance)
    {
        if (msgoutput)
        {
            std::cout << "CRIT" << '\n'
                      << '-' << this->damage * this->critamplifier << std::endl;
        }
        return this->damage * this->critamplifier;
    }
    else
    {
        if (msgoutput)
        {
            std::cout << '-' << this->damage << std::endl;
        }
        return this->damage;
    }
}
