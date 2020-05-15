#ifndef GAME_HPP
#define GAME_HPP

// size of each area
#define WIDTH 10
#define LENGTH 10
#define MINROOMS 10
#define MAXROOMS 15

#include <map>
#include <string>
#include <vector>

#include "command.hpp"
#include "rng.hpp"
#include "room.hpp"

class Game
{
   private:
    // current area the player is in
    // every time the player leaves one area they go to the next
    unsigned int area;

    Room* curroom;
    Room* exitroom;
    Room* rooms[WIDTH][LENGTH];
    bool generated;

    Command parser;
    RNG generator;

   public:
    Game(unsigned int& seed);
    ~Game();

    void printrooms();

    void cleanuprooms();
    void generate();

    int run();
};

#endif