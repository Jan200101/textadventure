#include "entities/goblin.hpp"

/**
 * @file goblin.cpp
 * @brief source for Goblin entity
 */

/**
 * sets up various values inherited from Entity
 */
Goblin::Goblin()
{
    this->setName("Goblin");
    this->setHealth(300);
    this->setSpeed(25);
    this->setDefense(0);
}