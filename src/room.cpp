#include "room.hpp"
#include "items/bush.hpp"

#include <cstdlib>

/**
 * @file room.cpp
 * @brief Source file for rooms
 */

/**
 * sets the idea,
 * randomized flag,
 * closes all exits for randomization,
 * sets all possible to null,
 * sets item amount to 0
 */
Room::Room(unsigned int id)
{
    this->id = id;
    this->israndom = false;

    for (short e = 0; e < 4; ++e)
    {
        exit[e] = false;
    }

    for (unsigned short i = 0; i < MAXITEMS; ++i)
    {
        items[i] = nullptr;
    }

    this->itemamount = 0;
}

unsigned int Room::getID()
{
    return this->id;
}

bool* Room::getExits()
{
    return this->exit;
}

unsigned int Room::getItemamount()
{
    return this->itemamount;
}

Item** Room::getItems()
{
    return this->items;
}

/**
 * randomizes exits and items
 * item amount is randomized aswell
 */
void Room::randomize()
{
    this->itemamount = 0;

    Item* pool[] = {
        (new Bush),
    }; // TODO fill pool

    const unsigned short poolsize = 1;

    for (short i = 0; i < 4; ++i)
    {
        exit[i] = (bool)(rand() % 2);
    }

    // item randomizatin per room

    unsigned short amount = 0;

    for (unsigned short i = 0; i < MAXITEMSPAWNS; ++i)
    {
        amount += (rand() % 2);
    }

    Item* obj;

    for (unsigned short i = 0; i < amount; ++i)
    {
        obj = pool[rand() % poolsize];
        if (obj != nullptr)
        {
            items[i] = obj;
            ++this->itemamount;
        }
    }

    this->israndom = true;
}