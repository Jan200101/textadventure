#ifndef RNG_HPP
#define RNG_HPP

#include <random>

class RNG
{
   private:
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution;

   public:
    RNG(unsigned int seed = 0);

    unsigned int getUInt();
    int getInt();
};

#endif