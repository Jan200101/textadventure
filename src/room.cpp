#include "room.hpp"

#include <cstdlib>

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

void Room::randomize()
{
    Item* pool[] = {nullptr}; // TODO fill pool

    const unsigned short poolsize = 1;

    for (short i = 0; i < 4; ++i)
    {
        exit[i] = (bool)(rand() % 2);
    }

    // item randomizatin per room

    this->itemamount = (rand() % 3) + (rand() % 2);

    for (int i = 0; i < this->itemamount; ++i)
    {
        items[i] = pool[rand() % poolsize];
    }

    this->israndom = true;
}