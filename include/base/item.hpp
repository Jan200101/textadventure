#ifndef ITEM_H
#define ITEM_H

#include <cstdint>
#include <string>

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