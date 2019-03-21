#include "base/item.hpp"

/**
 * @file item.cpp
 * @brief Source file for the abstracted Item class
 */

Item::Item()
{
    type = 0;
}

Item::Item(std::string paramName, std::string paramText, uint8_t paramType)
{
    name = paramName;
    flavortext = paramText;
    type = paramType;
}

std::string Item::getName()
{
    return this->name;
}

std::string Item::getFlavortext()
{
    return this->flavortext;
}

uint8_t Item::getType()
{
    return this->type;
}