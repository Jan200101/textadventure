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

void Game::generaterooms(bool verbose)
{
    for (unsigned int l = 0; l < LENGTH; ++l)
    {
        for (unsigned int w = 0; w < WIDTH; ++w)
        {
            rooms[l][w] = new Room(w + (l * WIDTH));
            rooms[l][w]->randomize();
            if (verbose)
            {
                printf("Room(%i, %i:%i) randomized\n", rooms[l][w]->getID(), l, w);
            }
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
        view = view - 3;
    }
    this->viewpoint = view;
}

void Game::introduction()
{
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
    generaterooms(false);

    std::vector<std::string> command;

    introduction();

    std::cout
        << "Type 'exit' to exit the game, keep in mind no progress is saved" << std::endl;

    while (true)
    {
        command = parsecommand(fetchinput());

        if (std::cin.eof())
        {
            std::cout << std::endl;
            break;
        }

        else if (command.empty())
        {
            continue;
        }

        else if (command[0] == "exit")
        {
            break;
        }

        else if (command[0] == "room")
        {
            std::cout << (int)this->curroom->getID() % WIDTH << " "
                      << (int)this->curroom->getID() / WIDTH << std::endl;
        }

        else if (command[0] == "help")
        {
            std::cout << "help   show this message\n"
                         "room   get current room ID"
                         "exit   close the game\n\n"
                         "If you see this remind sentry to write a proper command interpreter instead of just lazily slapping a few if statements together just so he can focus on generation and randomization insteadl. Thanks"
                      << std::endl;
        }
        else
        {
            std::cout << "command not found: " << command[0] << std::endl;
        }

        // TODO write interpeter
    }

    std::cout << std::endl; // flush stream at last
    return 0;
}