#include "jsonf.h"
#include "colors.h"

void addBlueprintBegining()
{
    writeToBuffer("{\n"TAB"\"bodies\": [\n"TAB"{\n"TAB2"\"childs\": [\n"TAB2);
}

void addBlueprintEnding()
{
    removeLastCharacters(10);
    writeToBuffer("]\n"TAB"}],\n"TAB"\"version\": 4\n}");
}

void addLogicGate(int connectionAmount, int* connectionIDs, Pos* pos, const Rot rot, int partID, int mode, int colorID)
{
    if (connectionAmount > 0 && connectionIDs == NULL)
    {
        printf("could not read connection IDs - nullptr");
        exit(EXIT_FAILURE);
    }

    if (pos == NULL)
    {
        printf("could not read position - nullptr");
        exit(EXIT_FAILURE);
    }

    if (colorID < 0 || colorID >= 40)
    {
        printf("could not read color ID - out of range");
        exit(EXIT_FAILURE);
    }

    char buffer[16];

    writeToBuffer("{\n"TAB3"\"color\": \"");
    writeToBuffer(colors[colorID]);
    writeToBuffer("\",\n"TAB3"\"controller\": {\n"TAB4"\"active\": false,\n"TAB4"\"controllers\": ");

    // add connections
    if (connectionAmount > 0)
    {
        writeToBuffer("[\n"TAB4);

        for (int i = 0; i < connectionAmount; i++)
        {
            writeToBuffer("{\n"TAB5"\"id\": ");

            snprintf(buffer, sizeof(buffer), "%d", connectionIDs[i]);
            writeToBuffer(buffer);

            writeToBuffer("\n"TAB4"}");

            if (i != connectionAmount - 1) // is not the last element
            {
                writeToBuffer(",\n"TAB4);
            }
        }

        writeToBuffer("]");
    }
    else
    {
        writeToBuffer("null");
    }

    writeToBuffer(",\n"TAB4"\"id\": ");

    snprintf(buffer, sizeof(buffer), "%d", partID);
    writeToBuffer(buffer);

    writeToBuffer(",\n"TAB4"\"joints\": null,\n"TAB4"\"mode\": ");

    snprintf(buffer, sizeof(buffer), "%d", mode);
    writeToBuffer(buffer);

    writeToBuffer("\n"TAB3"},\n"TAB3"\"pos\": {\n");

    writeToBuffer(TAB4"\"x\": ");
    snprintf(buffer, sizeof(buffer), "%d", pos->x);
    writeToBuffer(buffer);
    writeToBuffer(",\n");

    writeToBuffer(TAB4"\"y\": ");
    snprintf(buffer, sizeof(buffer), "%d", pos->y);
    writeToBuffer(buffer);
    writeToBuffer(",\n");

    writeToBuffer(TAB4"\"z\": ");
    snprintf(buffer, sizeof(buffer), "%d", pos->z);
    writeToBuffer(buffer);
    writeToBuffer("\n");

    writeToBuffer(TAB3"},\n"TAB3"\"shapeId\": \"9f0f56e8-2c31-4d83-996c-d00a9b296c3f\",\n");

    writeToBuffer(TAB3"\"xaxis\": ");
    snprintf(buffer, sizeof(buffer), "%d", rot.x);
    writeToBuffer(buffer);
    writeToBuffer(",\n");

    writeToBuffer(TAB3"\"zaxis\": ");
    snprintf(buffer, sizeof(buffer), "%d", rot.z);
    writeToBuffer(buffer);
    writeToBuffer("\n");

    writeToBuffer(TAB2"},\n"TAB2);
}