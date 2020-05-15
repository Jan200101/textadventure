#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <string>

class Object
{
   private:
    std::string name;

   public:
    Object();

    std::string getName();
};

#endif