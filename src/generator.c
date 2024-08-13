#include "generator.h"
#include "file.h"
#include "blueprint.h"
#include "config.h"

void generateROM()
{
    createBuffer();
    createFile("blueprint.json");

    beginBlueprint();

    addOutputLine(wordBitCount);
    addMatrix(wordCount, stackHeight);
    addAdressLine(adressBitCount);
    addData();

    endBlueprint();

    writeBufferToFile();
    freeBuffer();
    closeFile();
}