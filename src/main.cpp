#include <cstdlib>

#include "game.hpp"

int main(int argc, char* argv[])
{
    unsigned int seed = 0;
    if (argc > 1)
        seed = std::atoi(argv[1]);

    Game gameloop(seed);
    gameloop.run();
}