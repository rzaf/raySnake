#include "timer.h"

// #include <time.h>
#include <sys/time.h>

#define NULL (void*)0



static uint32_t currentTimeMillis() {
  struct timeval time;
  gettimeofday(&time, NULL);
  uint32_t s1 = (uint32_t)(time.tv_sec) * 1000;
  uint32_t s2 = (time.tv_usec / 1000);
  return s1 + s2;
}

int IsPaused(const Timer* timer)
{
    if(timer->lastPausedTime == 0)
        return 0;
    return 1;
}

int IsRunning(const Timer* timer)
{
    return !IsPaused(timer);
}

void TimerStart(Timer* timer)
{
    timer->startTime = currentTimeMillis();
    timer->lastPausedTime = 0;
    timer->totalPausedTime = 0;
};

uint32_t TimerGet(const Timer* timer)
{
    if(!IsPaused(timer)) {
        return currentTimeMillis() - timer->startTime - timer->totalPausedTime;
    }
    return timer->lastPausedTime - timer->startTime - timer->totalPausedTime;
}

float TimerGetS (const Timer* timer )
{
    uint32_t r = TimerGet(timer);
    return r/1000.0f;
}

void TimerPause(Timer* timer)
{
    if(IsPaused(timer)) 
        return;     
    timer->lastPausedTime = currentTimeMillis();    
}


void TimerResume(Timer* timer)
{
    if(!IsPaused(timer)) 
        return;
    timer->totalPausedTime =  currentTimeMillis() - timer->lastPausedTime;
    timer->lastPausedTime = 0;
}

uint32_t TimerStop(Timer* timer)
{
    uint32_t r  = TimerGet(timer);
    timer->lastPausedTime  = 0;
    timer->startTime       = 0;
    timer->totalPausedTime = 0;
    return r;
};
