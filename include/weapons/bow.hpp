#ifndef BOW_H
#define BOW_H

#include "base/weapon.hpp"

#include <cstdint>

/**
 * @file bow.hpp
 * @brief header for the Bow weapon
 *
 * inhertits from RangedWeapon
 */

/**
 * creates interfaces for ranged weapons
 */
class Bow : public RangedWeapon
{
   public:
    Bow();
};

#endif // BOW_H