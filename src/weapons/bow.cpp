#include "weapons/bow.hpp"

#include <iostream>

Bow::Bow()
{
    this->setName("Bow");
    this->setDamage(8);
    this->setDurability(200);
    this->setCritchance(50);
    this->setCritamplifier(3);
    this->setAmmunition(20);
}

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

    this->setAmmunition(this->ammunition - 1);

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