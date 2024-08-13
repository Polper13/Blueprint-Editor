#pragma once

#include <stdlib.h>

#include "file.h"
#include "transform.h"

#define TAB "    "
#define TAB2 "        "
#define TAB3 "            "
#define TAB4 "                "
#define TAB5 "                    "

void addBlueprintBegining();
void addBlueprintEnding();

void addLogicGate(int connectionAmount, int* connectionIDs, Pos* pos, const Rot rot, int partID, int mode, int colorID);