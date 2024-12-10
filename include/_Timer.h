#ifndef _TIMER_H
#define _TIMER_H

#include "_Common.h"

class _Timer
{
    public:
        _Timer();
        virtual ~_Timer();

        // added this
        void initTimer(); // init start Timer
        void start();
        void stop();
        void reset();
        double getElapsedTime() const;

        clock_t startTime;

        // added this
        clock_t endTime;
        bool running;

    protected:

    private:
};

#endif // _TIMER_H
