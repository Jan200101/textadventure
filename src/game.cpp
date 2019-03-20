#include "game.hpp"

#include <iostream>
#include <iterator>
#include <sstream>

#include <cstdio>
#include <cstdlib>
#include <ctime>

Game::Game()
{
    this->generated = false;

    curroom = nullptr;

    for (int l = 0; l < LENGTH; ++l)
    {
        for (int w = 0; w < WIDTH; ++w)
        {
            rooms[l][w] = nullptr;
        }
    }

    viewpoint = 0;

    srand(time(NULL));
}

Game::~Game()
{
    std::cin.clear();
}

std::string Game::fetchinput()
{
    std::cout << PS1;
    std::cin.clear();
    getline(std::cin, lastcommand);
    return lastcommand;
}

std::vector<std::string> Game::parsecommand(std::string command)
{
    std::stringstream stream(command);

    std::istream_iterator<std::string> begin(stream);
    std::istream_iterator<std::string> end;

    std::vector<std::string> strings(begin, end);

    return strings;
}

void Game::generaterooms()
{
    for (unsigned int l = 0; l < LENGTH; ++l)
    {
        for (unsigned int w = 0; w < WIDTH; ++w)
        {
            rooms[l][w] = new Room(w + (l * WIDTH));
            rooms[l][w]->randomize();

#ifdef DEBUG
            printf("%s(%d) Room(%i, %i:%i) randomized\n", __FILE__, __LINE__, rooms[l][w]->getID(), l, w);
#endif // DEBUG
        }
    }

    this->curroom = rooms[rand() % LENGTH][rand() % WIDTH];

    this->viewpoint = rand() % 4;

    this->generated = true;
}

uint8_t Game::getViewpoint()
{
    return this->viewpoint;
}

void Game::setViewpoint(uint8_t view)
{
    while (view > 3)
    {
        view = view - (0xFF - 3);
    }
    this->viewpoint = view;
}

void Game::introduction()
{
    // reason for this and license text
    std::cout << "textadventure Copyright (C) 2019  Jan \"Sentry\" Drögehoff\n"
                 "This program comes with ABSOLUTELY NO WARRANTY;\n\n"
                 "Welcome to TEXTADVENTURE\n"
                 "a command based text adventure purely written in C++\n"
                 "this exists to show a single person what you can achieve by not just putting switch cases in switch cases\n"
                 "you know who you are\n"
              << std::endl;
}

int Game::run()
{
    generaterooms();

    std::vector<std::string> command;
    unsigned long int length;

    introduction();

    std::cout
        << "Type 'exit' to exit the game, keep in mind no progress is saved" << std::endl;

    /*
     * input;parse;interpret loop
     */
    while (true)
    {
        command = parsecommand(fetchinput());
        length = command.size();

        if (std::cin.eof())
        {
            std::cout << std::endl;
            break;
        }

        else if (command.empty())
        {
            continue;
        }

        else if (command[0][0] == '#') // comments to automate tests easily
        {
            continue;
        }

        else if (command[0] == "exit")
        {
            break;
        }

        else if (command[0] == "direction")
        {
            switch (getViewpoint())
            {
                case 0:
                    std::cout << "North" << std::endl;
                    break;
                case 1:
                    std::cout << "East" << std::endl;
                    break;
                case 2:
                    std::cout << "South" << std::endl;
                    break;
                case 3:
                    std::cout << "West" << std::endl;
                    break;
            }
        }

        else if (command[0] == "turn")
        {
            if (length > 1)
            {
                if (command[1] == "right")
                {
                    setViewpoint(getViewpoint() + 1);
                }
                else if (command[1] == "left")
                {
                    setViewpoint(getViewpoint() - 1);
                }
                else
                {
                    std::cout << "Argument is neither left or right" << std::endl;
                }
            }
            else
            {
                std::cout << "Argument missing:\nturn [left|right]" << std::endl;
            }
        }

        else if (command[0] == "face")
        {
            if (length > 1 &&
                (command[1] == "north" || command[1] == "east" ||
                 command[1] == "south" || command[1] == "west"))
            {
                if (command[1] == "north")
                {
                    setViewpoint(0);
                }
                else if (command[1] == "east")
                {
                    setViewpoint(1);
                }
                else if (command[1] == "south")
                {
                    setViewpoint(2);
                }
                else
                {
                    setViewpoint(3);
                }
            }
            else
            {
                std::cout << "Argument missing:\n face [north|east|south|west]" << std::endl;
            }
        }

        else if (command[0] == "room")
        {
            unsigned int id = this->curroom->getID();

            std::cout << id / WIDTH << " "
                      << id % WIDTH << std::endl;
        }

#ifdef DEBUG

        else if (command[0] == "go")
        {
            printf("%s(%d):TODO:implement\n", __FILE__, __LINE__);
        }

#endif // DEBUG

        else if (command[0] == "help")
        {
            std::cout << ""
                         "exit               close the game\n"
                         "direction          prints which direction you are facing\n"
                         "turn [left|right]  turns left or right\n"
                         "face [direction]   turns any direction in the sky\n"
                         "go [direction]     go any direction relative or absolute\n"
                         "room               get current room ID\n"
                         "help               show this message\n"
                      // meh "If you see this remind sentry to write a proper command interpreter instead of just lazily slapping a few if statements together just so he can focus on generation and randomization insteadl. Thanks"
                      << std::endl;
        }
        else
        {
            std::cout << "command not found: " << command[0] << std::endl;
        }

        /*
         * TODO write interpeter
         * its currently on the backburner but may be included at an later date
         */
    }

    // std::cout << std::endl; // flush stream at last
    return 0;
}