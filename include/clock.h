#pragma once

#include <time.h>
#include <stdio.h>

clock_t startTime;
clock_t endTime;
double duration;

void startClock()
{
    startTime = clock();
}

void stopClock()
{
    endTime = clock();
    duration = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;

    printf("\ntime: %d s %d ms\n\n", (int)duration, (int)(duration * 1000) % 1000);
}