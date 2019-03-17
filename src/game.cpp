#include "game.hpp"

#include <iostream>
#include <iterator>
#include <sstream>

Game::Game() {}

std::vector<std::string> Game::fetchinput()
{
    std::string input;

    getline(std::cin, input);

    std::stringstream ss(input);

    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;

    std::vector<std::string> vstrings(begin, end);

    this->lastcommand = input;

    return vstrings;
}

int Game::run()
{
    std::cout << fetchinput().size();

    return 0;
}