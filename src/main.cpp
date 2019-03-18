#include "main.hpp"
#include "game.hpp"

#include <cstring>
#include <iostream>

int main(int argc, char** argv)
{
    Game game;

    if (argc > 1)
    {
        for (int i = 1; i < argc; ++i)
        {
            if (!strcmp(argv[i], "-v") ||
                !strcmp(argv[i], "--version"))
            {
                std::cout << "Version " << VERSION << std::endl;
            }
        }
    }
    else
    {
        return game.run();
    }
    return 0;
}