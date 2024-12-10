#include "_Timer.h"

_Timer::_Timer()
{
    //ctor
    // initialize this with init method
    //startTime = clock();

    // added these
    running = false;
    startTime = 0;
    endTime = 0;
}

_Timer::~_Timer()
{
    //dtor
}

void _Timer::initTimer() {
    start(); // Start the timer
}

void _Timer::start() {
    if (!running) {
        running = true;
        startTime = clock();
    }
}

void _Timer::stop() {
    if (running) {
        endTime = clock();
        running = false;
    }
}

void _Timer::reset() {
    running = false;
    startTime = 0;
    endTime = 0;
}

double _Timer::getElapsedTime() const {
    if (running) {
        return (clock() - startTime) / (double) CLOCKS_PER_SEC;
    } else {
        return (endTime - startTime) / (double) CLOCKS_PER_SEC;
    }
}

/* original
_Timer::_Timer()
{
    //ctor
    startTime = clock();
}

_Timer::~_Timer()
{
    //dtor
}
*/
