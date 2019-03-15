#include "main.hpp"

#include "weapons/bow.hpp"

#include <iostream>

int main()
{
    RangedWeapon* knife = new Bow;
    while (knife->attack(true))
    {
        //std::cout << knife->getDurability() << '\n';
    }
}