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
            if (!strcmp(argv[i], "-h") ||
                !strcmp(argv[i], "--help"))
            {
                std::cout << argv[0]
                          << " [-h] [-v]\n\n"
                             "Arguments:\n"
                             " -h, --help      display this message\n"
                             " -v, --version   show the program version\n"
                          << std::flush;
                return 0;
            }
            else if (!strcmp(argv[i], "-v") ||
                     !strcmp(argv[i], "--version"))
            {
                std::cout << "Version " << VERSION << std::endl;
                return 0;
            }
            else
            {
                std::cout << "Unknown flag " << argv[i] << std::endl;
                return 0;
            }
        }
    }
    else
    {
        return game.run();
    }
    return 0;
}