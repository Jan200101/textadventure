#ifndef ROOM_HPP
#define ROOM_HPP

#include "object.hpp"
#include "rng.hpp"

class Room
{
   private:
    unsigned int id;
    unsigned int objectcount;
    Object** objects;

    bool explored;

   public:
    Room(unsigned int id, RNG* generator);
    ~Room();

    bool hasbeenExplored();
    bool getExplored();

    unsigned int getID();
    Object** getObjects();
};

#endif