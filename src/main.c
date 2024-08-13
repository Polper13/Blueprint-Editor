#include <stdio.h>        

#include "clock.h"
#include "generator.h"

int main(int argc, char *argv[])
{
    startClock();

    generateROM();
    
    stopClock();
}