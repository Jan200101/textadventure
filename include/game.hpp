#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>

class Game
{
   private:
    std::string lastcommand;

   public:
    Game();

    std::vector<std::string> fetchinput();
    int run();
};

#endif // GAME_H