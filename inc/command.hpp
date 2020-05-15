#ifndef COMMAND_HPP
#define COMMAND_HPP

// prefix used for command input
#define INPPREFIX ">"

#include <string>
#include <vector>

enum class Commands
{
    move,
    use,
    attack,
    map,
    eof, // like quit?
    quit,
    invalid,
};

enum class Arguments
{
    north,
    south,
    west,
    east,
    invalid
};

class Command
{
   private:
    Commands lastcommand;
    std::vector<Arguments> lastarguments;

   public:
    Command();

    Commands fetchinput();

    Commands getLastInput();
    std::vector<Arguments> getLastArguments();

    void clear();
};

#endif