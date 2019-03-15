#ifndef ENTITY_H
#define ENTITY_H

#include <cstdint>
#include <string>

/**
 * @file entity.hpp
 * @brief header for the Entity class
 */

/**
 * abstract class for entities
 * see include/entities
 */
class Entity
{
   protected:
    std::string name;
    uint16_t health;
    uint8_t speed;
    uint16_t defense;

   public:
    std::string getName();
    void setName(std::string);

    uint16_t getHealth();
    void setHealth(uint16_t);

    uint8_t getSpeed();
    void setSpeed(uint8_t);

    uint16_t getDefense();
    void setDefense(uint16_t);
};

#endif // ENTITY_H