#include "main.hpp"
#include "weapons/bow.hpp"
#include "weapons/sword.hpp"

#include <iostream>

int main()
{
    Bow* knife = new Bow;
    while (knife->attack(true))
    {
        //std::cout << knife->getDurability() << '\n';
    }
}