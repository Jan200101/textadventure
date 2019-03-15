#include "entities/player.hpp"

/**
 * @file player.cpp
 * @brief source for the Player entity
 */

/**
 * sets up various values inherited from Entity
 */
Player::Player()
{
    this->setName("Player");
    this->setHealth(500);
    this->setSpeed(20);
    this->setDefense(2);
}