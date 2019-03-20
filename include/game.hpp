#ifndef GAME_H
#define GAME_H

#include "room.hpp"

#include <string>
#include <vector>

// SIZE OF MAP IN ROOMS
#define WIDTH 5
#define LENGTH 5

#define PS1 "> "

#define VERSION "0.5.0"

class Game
{
   protected:
    std::string lastcommand;

    bool generated;
    Room* curroom;
    Room* rooms[LENGTH][WIDTH];

    /* 
     * Direction player is facing
     * 0 North
     * 1 East
     * 2 South
     * 3 West
     */
    uint8_t viewpoint;

   public:
    Game();
    ~Game();

    std::string fetchinput();
    std::vector<std::string> parsecommand(std::string);

    void generaterooms();

    uint8_t getViewpoint();
    void setViewpoint(uint8_t);

    void introduction();

    int run();
};

/*
 * Exit direction
 *   Viewpoint
 *     Direction
 * 0 0 0
 * 0 1 3
 * 0 2 2
 * 0 3 1
 *
 * 1 0 1
 * 1 1 0
 * 1 2 3
 * 1 3 2
 *
 * 2 0 2
 * 2 1 1
 * 2 2 0
 * 2 3 3
 *
 * 3 0 3
 * 3 1 2
 * 3 2 1
 * 3 3 0
 */
#endif // GAME_H