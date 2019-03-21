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

    /*
     * 0 None
	 */
    uint8_t type;

   public:
    Item();

    std::string getName();
    void setName(std::string);

    std::string getFlavortext();
    void setFlavortext(std::string);

    uint8_t getType();
    void setType(uint8_t);
};

#endif // ITEM_H