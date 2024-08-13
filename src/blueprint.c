#include "blueprint.h"
#include "jsonf.h"
#include "transform.h"
#include "list.h"
#include "config.h"

const Rot front = { -3, 1 };
const Rot up = { 2, 1 };

int freeID;

int adressID;
int adressSize;

int outputID;
int outputSize;

int matrixID;
int matrixSize;

int zeroGate;
int oneGate;

void beginBlueprint()
{
    addBlueprintBegining();
    freeID = 0;
}

void endBlueprint()
{
    addBlueprintEnding();
}

void addAdressLine(int size)
{
    adressID = freeID;
    adressSize = size * 2;
    freeID += adressSize;

    Pos posAND = { 0, 0, 1 };
    Pos posNOR = { 0, 0, 2 };

    List connectionsAND;
    List connectionsNOR;

    for (int adressBit = 0; adressBit < size; adressBit++) // go throught each bit of the adress
    {
        initList(&connectionsAND, matrixSize);
        initList(&connectionsNOR, matrixSize);

        for (int memAdress = 0; memAdress < matrixSize / outputSize; memAdress++) // go throught each adress in mem
        {
            // decide if this adress bit should be connected to this mem adress
            int bit = memAdress & (1 << adressBit);
            if (bit == 0)
            {
                // add each gate in this adress to nor connections
                for (int i = 0; i < outputSize; i++)
                    addToList(&connectionsNOR, outputSize * memAdress + matrixID + i);
            }
            else 
            {
                // add each gate in this adress to and connections
                for (int i = 0; i < outputSize; i++)
                    addToList(&connectionsAND, outputSize * memAdress + matrixID + i);
            }
        }
        addToList(&connectionsAND, adressID + size + adressBit); // connect and gate to according nor gate

        int color = (adressBit == 0) ? 8 : 18;
        addLogicGate(connectionsAND.length, connectionsAND.arrayPtr, &posAND, front, adressID + adressBit, 0, color);
        addLogicGate(connectionsNOR.length, connectionsNOR.arrayPtr, &posNOR, front, adressID + size + adressBit, 4, color);
        
        posAND.x++;
        posNOR.x++;

        freeList(&connectionsAND);
        freeList(&connectionsNOR);
    }
}

void addOutputLine(int size)
{
    outputID = freeID;
    outputSize = size;
    freeID += outputSize;

    Pos pos = { 0, 0, 0 };

    for (int i = 0; i < size; i++)
    {
        int color = (i == 0) ? 3 : 13;
        addLogicGate(0, NULL, &pos, front, outputID + i, 1, color);

        pos.x++;
    }
}

void addMatrix(int wordAmount, int height)
{
    matrixID = freeID;
    matrixSize = outputSize * wordAmount;
    freeID += matrixSize;

    const Pos startingPos = { 0, -1, -1 };
    Pos pos;

    int connections[1];

    for (int y = 0; y < wordAmount; y++)
    {
        for (int x = 0; x < outputSize; x++)
        {
            pos.x = startingPos.x + x;
            pos.y = startingPos.y - y / height;
            pos.z = startingPos.z + y % height;

            int id = matrixID + y * outputSize + x;
            connections[0] = outputID + x;

            addLogicGate(1, &connections[0], &pos, up, id, 0, 20);
        }
    }
}

void addData()
{
    zeroGate = freeID;
    oneGate = freeID + 1;
    freeID += 2;

    List zero;
    List one;
    initList(&zero, matrixSize);
    initList(&one, matrixSize);

    addToList(&zero, oneGate);

    int byteSize = sizeof(dataArray[0]);
    int bitSize = byteSize * 8;
    if (outputSize > bitSize)
    {
        printf("data size is to small for output size");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < sizeof(dataArray) / byteSize; i++)
    {
        for (int bitIndex = 0; bitIndex < outputSize; bitIndex++)
        {
            // read each bit
            int bit = (dataArray[i] & (1 << bitIndex)) >> bitIndex;
            if (bit == 0)
            {
                addToList(&zero, matrixID + i * outputSize + bitIndex);
            }
            else
            {
                addToList(&one, matrixID + i * outputSize + bitIndex);
            }
        }
    }

    Pos zeroPos = { -1, 0, -1 };
    Pos onePos = { -1, -1, -1 };
    
    addLogicGate(zero.length, zero.arrayPtr, &zeroPos, up, zeroGate, 4, 30);
    addLogicGate(one.length, one.arrayPtr, &onePos, up, oneGate, 4, 30);
}