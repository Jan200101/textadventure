#include "base/item.hpp"

/**
 * @file item.cpp
 * @brief Source file for the abstracted Item class
 */

Item::Item()
{
    type = 0;
}

std::string Item::getName()
{
    return this->name;
}

void Item::setName(std::string paramName)
{
    this->name = paramName;
}

std::string Item::getFlavortext()
{
    return this->flavortext;
}

void Item::setFlavortext(std::string paramText)
{
    this->flavortext = paramText;
}

uint8_t Item::getType()
{
    return this->type;
}

void Item::setType(uint8_t paramType)
{
    this->type = paramType;
}