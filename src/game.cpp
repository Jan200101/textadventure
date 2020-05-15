#include <cinttypes>
#include <cstdio>

#include "game.hpp"

Game::Game(unsigned int& seed) : generator(seed)
{
    area = 0;

    curroom = nullptr;
    for (int x = 0; x < WIDTH; ++x)
        for (int y = 0; y < LENGTH; ++y)
        {
            rooms[x][y] = nullptr;
        }

    generated = false;
}

Game::~Game()
{
    cleanuprooms();
}

void Game::printrooms()
{
    int vertpos = 0;

    printf("  ");

    for (int y = 0; y < WIDTH; ++y)
    {
        printf("%i ", y);
    }
    printf("\n");

    for (int y = 0; y < WIDTH; ++y)
    {
        bool verticalprint = false;
        for (int x = 0; x < LENGTH; ++x)
        {
            if (!verticalprint)
            {
                printf("%i ", vertpos);
                verticalprint = true;
            }
            if (rooms[x][y] == nullptr
// TODO remove
#ifndef DEBUG
                || !rooms[x][y]->getExplored()
#endif
            )
            {
                printf("  ");
            }
            else if (rooms[x][y] == curroom)
            {
                printf("S ");
            }
            else if (rooms[x][y] == exitroom)
            {
                printf("E ");
            }
            else
            {
                printf("R ");
            }
        }
        ++vertpos;
        printf("\n");
    }
}

void Game::cleanuprooms()
{
    curroom = nullptr;
    exitroom = nullptr;

    for (int x = 0; x < WIDTH; ++x)
        for (int y = 0; y < LENGTH; ++y)
        {
            if (rooms[x][y] != nullptr)
                delete rooms[x][y];
            rooms[x][y] = nullptr;
        }
}

void Game::generate()
{
    int x = generator.getUInt() % LENGTH;
    int y = generator.getUInt() % WIDTH;
    int roomcount = MINROOMS + (generator.getUInt() % (MAXROOMS - MINROOMS));

    uint8_t lastid = 0;

    while (x >= WIDTH)
    {
        x -= WIDTH;
        ++y;
    }

    rooms[x][y] = new Room(lastid++, &generator);
    curroom = rooms[x][y];

    for (; lastid < roomcount;)
    {
        switch (generator.getUInt() % 4)
        {
            case 0:
                if (--x < 0)
                    ++x;
                break;

            case 1:
                if (--y < 0)
                    ++y;
                break;

            case 2:
                if (++x >= WIDTH)
                    --x;
                break;

            case 3:
                if (++y >= LENGTH)
                    --y;
                break;

            default:
                break;
        }
        if (rooms[x][y] == nullptr)
        {
            rooms[x][y] = new Room(lastid++, &generator);

            if (lastid == roomcount)
                exitroom = rooms[x][y];
        }
    }

    generated = true;
}

int Game::run()
{
    Commands command;
    bool exit = false;

    // generate rooms for this layer
    generate();

    curroom->hasbeenExplored();

    while (true)
    {
        command = parser.fetchinput();

        switch (command)
        {
            case Commands::move:
                if (!parser.getLastArguments().size())
                    break;

                switch (parser.getLastArguments()[0])
                {
                    case Arguments::north:
                    case Arguments::south:
                    case Arguments::east:
                    case Arguments::west:
                    case Arguments::invalid:
                    default:
                        break;
                }
                break;

            case Commands::use:
                // TODO
                break;

            case Commands::attack:
                // TODO
                break;

            case Commands::map:
                printrooms();
                break;

            case Commands::eof:
            case Commands::quit:
                exit = true;
                break;

            case Commands::invalid:
                break;
        }

        if (exit) break;
    }

    return 0;
}