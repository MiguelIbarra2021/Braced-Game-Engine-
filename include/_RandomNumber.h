#ifndef _RANDOMNUMBER_H
#define _RANDOMNUMBER_H

#include "_Common.h"

using namespace std;

class _RandomNumber
{
    public:
        _RandomNumber();
        virtual ~_RandomNumber();

        vector<int> availableNumbers; // Holds numbers that can still be picked
        bool allPicked = false; // Flag to indicate if all numbers have been picked
        int minimum, maximum;

        void initializeNumbers();
        void initializeNumbers(int, int);
        int pickNumber();
};

#endif // _RANDOMNUMBER_H
