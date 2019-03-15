#include "abc/entity.hpp"

/**
 * @file entity.cpp
 * @brief source for the Entity class
 */

std::string Entity::getName()
{
    return this->name;
}

void Entity::setName(std::string paramName)
{
    this->name = paramName;
}

uint16_t Entity::getHealth()
{
    return this->health;
}

void Entity::setHealth(uint16_t paramHealth)
{
    this->health = paramHealth;
}

uint8_t Entity::getSpeed()
{
    return this->speed;
}

void Entity::setSpeed(uint8_t paramSpeed)
{
    this->speed = paramSpeed;
}

uint16_t Entity::getDefense()
{
    return this->defense;
}

void Entity::setDefense(uint16_t paramDefense)
{
    this->defense = paramDefense;
}
