#pragma once
#include "Engine.h"
#include <sstream>
#include <iostream>

//The timer starting time
    Uint32 start = 0;
//The timer current time
    Uint32 cur = 0;

    bool run = true;

bool Timer(float dur)
{

    if(run)
    {
        //Start the timer
        start = SDL_GetTicks();
        print("Start:" << start)
        //Start the timer
    }

    cur = SDL_GetTicks();
    print("Cur:" << cur);

    unsigned time = cur - time;
     print("Timer:" << time);

    if (time == dur)
    {
        start = 0;
        cur = 0;
        run = false;
        return true;
    }
    else 
    {
        run = true;
        return false;
    }
    run = true;
    time = cur;
}