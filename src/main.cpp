#include "main.hpp"
#include "weapons/bow.hpp"
#include "weapons/sword.hpp"

#include <iostream>

int main()
{
    Sword* sword = new Sword;
    while (sword->attack(true))
    {
    }

    Bow* knife = new Bow;
    while (knife->attack(true))
    {
        //std::cout << knife->getDurability() << '\n';
    }
}