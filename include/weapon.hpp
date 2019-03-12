#ifndef WEAPON_H
#define WEAPON_H

#include <cstdlib>
#include <string>

class Weapon
{
   private:
    std::string name;
    uint16_t damage;
    uint16_t durability;
    uint8_t critchance;
    uint8_t critamplifier;

   public:
    std::string getName();
    void setName(std::string);

    uint16_t getDamage();
    void setDamage(uint16_t);

    uint8_t getCritchance();
    void setCritchange(uint8_t);

    uint8_t getCritamplifier();
    void setCritamplifier(uint8_t);
};

#endif // WEAPON_H