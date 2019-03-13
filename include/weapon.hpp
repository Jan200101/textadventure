#ifndef WEAPON_H
#define WEAPON_H

#include <cstdint>
#include <string>

/**
 * @file weapon.hpp
 * @brief header for the Weapon class
 */

/**
 * abstract class for weapons
 * see include/weapons
 */
class Weapon
{
   protected:
    std::string name;
    uint16_t damage;
    uint16_t durability;
    uint8_t critchance;
    uint8_t critamplifier;

   public:
    Weapon();

    std::string getName();
    void setName(std::string);

    uint16_t getDamage();
    void setDamage(uint16_t);

    uint16_t getDurability();
    void setDurability(uint16_t);

    uint8_t getCritchance();
    void setCritchance(uint8_t);

    uint8_t getCritamplifier();
    void setCritamplifier(uint8_t);

    uint16_t attack(bool msgoutput = false);
};

#endif // WEAPON_H