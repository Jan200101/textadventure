#ifndef BOW_H
#define BOW_H

#include "weapon.hpp"

#include <cstdlib>

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