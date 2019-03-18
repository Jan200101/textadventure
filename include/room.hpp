#ifndef ROOM_H
#define ROOM_H

#define MAXITEMS 10

#include "base/item.hpp"

class Room
{
   protected:
    // constructor
    unsigned int id;

    // randomizer
    bool exit[4]; // N; E; S; W
    bool israndom;

    Item* items[MAXITEMS];
    unsigned short itemamount;

   public:
    Room(unsigned int id = 0);

    unsigned int getID();

    bool* getExits();

    unsigned int getItemamount();

    void randomize();
};

#endif // ROOM_H