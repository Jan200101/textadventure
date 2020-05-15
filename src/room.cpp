#define OBJECTLIMIT 10

#include "room.hpp"

// TODO remove
#include <cstdlib>

Room::Room(unsigned int id, RNG* generator)
{
    this->id = id;

    objectcount = generator->getUInt() % OBJECTLIMIT;

    objects = new Object*[objectcount];

    for (unsigned int i = 0; i < objectcount; ++i)
    {
        objects[i] = new Object;
    }

    explored = false;
}

Room::~Room()
{
    delete[] objects;
}

bool Room::hasbeenExplored()
{
    if (explored)
        return 1;

    explored = true;
    return 0;
}
bool Room::getExplored()
{
    return explored;
}

unsigned int Room::getID()
{
    return id;
}

Object** Room::getObjects()
{
    return objects;
}