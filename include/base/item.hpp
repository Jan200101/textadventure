#ifndef ITEM_H
#define ITEM_H

#include <cstdint>
#include <string>

/**
 * @file item.cpp
 * @brief Header file for the abstracted Item class
 */

/**
 * @brief abstracted Item class
 *
 * class designed to simplify item creation and randomization
 */
class Item
{
   protected:
    std::string name;
    std::string flavortext;
    uint8_t type;

   public:
    Item();
    Item(std::string, std::string, uint8_t);

    std::string getName();

    std::string getFlavortext();

    uint8_t getType();

    enum Types
    {
        None
    };
};

#endif // ITEM_H