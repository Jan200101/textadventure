#include <ctime>

#include "rng.hpp"

RNG::RNG(unsigned int seed)
{
    if (seed)
        generator.seed(seed);
    else
    {
        seed = time(NULL);
        generator.seed(time(NULL));
    }

    printf("Seed: %u\n", seed);
}

int RNG::getInt()
{
    return distribution(generator);
}

unsigned int RNG::getUInt()
{
    return distribution(generator);
}