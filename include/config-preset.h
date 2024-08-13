#pragma once

#define NONE 0b0000000000000000 // 16 bits

static const int wordBitCount = 8;
static const int wordCount = 16;
static const int stackHeight = 1;
static const int adressBitCount = 4;

// 32 bit data (update type for bigger size)
static const int dataArray[] =
{
    NONE, NONE, NONE, NONE, //00
    NONE, NONE, NONE, NONE, //01
    NONE, NONE, NONE, NONE, //02
    NONE, NONE, NONE, NONE, //03
};

// update and compile blueprint.c and generator.c for this to have an effect (sadly)
// --TODO create better config file