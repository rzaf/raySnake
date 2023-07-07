#ifndef TIMER_H
#define TIMER_H

#include <inttypes.h>


typedef struct 
{
    uint32_t startTime; 
    uint32_t lastPausedTime; // its not zero when timer is paused
    uint32_t totalPausedTime;
} Timer;

// #define InitTimer(X) Timer X = {0,0,0}

int IsPaused (const Timer* timer);
int IsRunning(const Timer* timer);

void        TimerStart  (Timer* timer       );
void        TimerPause  (Timer* timer       );
void        TimerResume (Timer* timer       );
uint32_t    TimerStop   (Timer* timer       );
uint32_t    TimerGet    (const Timer* timer );  // return in millisecond
float       TimerGetS   (const Timer* timer );  // return in seconds

#endif //TIMER_H