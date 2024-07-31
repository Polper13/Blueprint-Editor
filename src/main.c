#include <stdio.h>        

#include "clock.h"
#include "file.h"
#include "jsonf.h"

int main(int argc, char *argv[])
{
    startClock();

    createBuffer();
    createFile("blueprint.json");

    addBlueprintBegining();

    int connections[] = { 0 };
    int connections2[] = { 0, 1 };
    Pos pos1 = { 0, 0, 0 };
    Pos pos2 = { 0, 1, 0 };
    Pos pos3 = { 1, 0, 0 };
    Rot rot = { 2, 1 };

    addLogicGate(0, NULL, &pos1, &rot, 0, 0, 30);
    addPointSymbol();
    addLogicGate(1, &connections[0], &pos2, &rot, 1, 3, 30);
    addPointSymbol();
    addLogicGate(2, &connections2[0], &pos3, &rot, 2, 0, 20);

    addBlueprintEnding();

    writeBufferToFile();

    freeBuffer();
    closeFile();
    
    stopClock();
}