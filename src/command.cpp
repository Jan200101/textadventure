#include <algorithm>
#include <cctype>
#include <iostream>
#include <iterator>
#include <sstream>

#include "command.hpp"

Command::Command()
{
    lastcommand = Commands::invalid;
}

Commands Command::fetchinput()
{
    std::string command;
    std::cout << INPPREFIX;

    std::cin.clear();
    this->clear();

    getline(std::cin, command);

    if (std::cin.eof())
    {
        std::cout << std::endl;
        return Commands::eof;
    }

    std::transform(command.begin(), command.end(), command.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    std::stringstream stream(command);

    std::istream_iterator<std::string> begin(stream);
    std::istream_iterator<std::string> end;

    std::vector<std::string> strings(begin, end);

    if (strings.size())
    {
        if (strings[0] == "map")
        {
            lastcommand = Commands::map;
        }
        else if (strings[0] == "quit")
        {
            lastcommand = Commands::quit;
        }

        // TODO: arguments
        for (unsigned long i = 1; i < strings.size(); ++i)
        {
            if (strings[i] == "north")
            {
                lastarguments.push_back(Arguments::north);
            }
            else if (strings[i] == "south")
            {
                lastarguments.push_back(Arguments::south);
            }
            else if (strings[i] == "east")
            {
                lastarguments.push_back(Arguments::east);
            }
            else if (strings[i] == "west")
            {
                lastarguments.push_back(Arguments::west);
            }
            else
            {
                lastarguments.push_back(Arguments::invalid);
            }
        }

        return lastcommand;
    }

    return Commands::invalid;
}

Commands Command::getLastInput()
{
    return lastcommand;
}

std::vector<Arguments> Command::getLastArguments()
{
    return lastarguments;
}

void Command::clear()
{
    lastcommand = Commands::invalid;
    lastarguments.clear();
}