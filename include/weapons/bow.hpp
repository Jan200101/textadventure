#ifndef BOW_H
#define BOW_H

#include "weapon.hpp"

#include <cstdint>

/**
 * @file bow.hpp
 * @brief header for the Bow weapon
 *
 * inhertits from Weapon
 */

/**
 * creates interfaces for ranged weapons
 * may get moved into a dedicated rangedweapon header
 */
class Bow : public Weapon
{
   protected:
    uint16_t ammunition;

   public:
    Bow();

    uint16_t attack(bool msgoutput = false);

    uint16_t getAmmunition();
    void setAmmunition(uint16_t);
};

#endif // BOW_H