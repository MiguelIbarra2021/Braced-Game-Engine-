#include "_RandomNumber.h"

_RandomNumber::_RandomNumber()
{}

_RandomNumber::~_RandomNumber()
{}

void _RandomNumber::initializeNumbers()
{
    availableNumbers.clear();

    for (int i = minimum; i < maximum; ++i)
    {
        availableNumbers.push_back(i);
    }

    allPicked = false;
}

void _RandomNumber::initializeNumbers(int min_num, int max_num)
{
    availableNumbers.clear();

    minimum = min_num;
    maximum = max_num;

    for (int i = min_num; i < max_num; ++i)
    {
        availableNumbers.push_back(i);
    }

    allPicked = false;
}

int _RandomNumber::pickNumber()
{
    int randomIndex = -1;
    srand(time(0)); // Seed random number generator

    if (availableNumbers.empty())
    {
        allPicked = true; // All numbers have been picked
        initializeNumbers();
    }

    if(!allPicked)
    {
        randomIndex = rand() % availableNumbers.size();;
        availableNumbers.erase(availableNumbers.begin() + randomIndex);
    }

    return randomIndex;
}
