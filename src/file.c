#include <stdlib.h>
#include <string.h>

#include "file.h"

const int startingBufferSize = 32 * 16384;

FILE *file;
char *fileWriteBuffer;
int fileWriteBufferSize;
int fileWriteBufferLength;

void createFile(char *name)
{
    file = fopen("blueprint.json", "w");

    if (file == NULL)
    {
        printf("could not create file");
        exit(EXIT_FAILURE);
    }
}

void createBuffer()
{
    fileWriteBuffer = (char*)malloc(startingBufferSize * sizeof(char));
    if (fileWriteBuffer == NULL)
    {
        printf("could not allocate buffer");
        exit(EXIT_FAILURE);
    }

    fileWriteBufferSize = startingBufferSize;
    fileWriteBufferLength = 0;
}

void extendBuffer()
{
    printf("trying to extend to %d bytes\n", fileWriteBufferSize * 2);

    char *ptr = (char*)malloc(fileWriteBufferSize * 2);
    if (ptr == NULL)
    {
        printf("could not extend buffer");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < fileWriteBufferLength; i++)
    {
        ptr[i] = fileWriteBuffer[i];
    }

    free(fileWriteBuffer);
    fileWriteBufferSize *= 2;
    fileWriteBuffer = ptr;
}

void writeToBuffer(char *string)
{
    int stringLength = strlen(string);
    printf("string length: %d\n", stringLength);

    while (fileWriteBufferSize - fileWriteBufferLength < stringLength)
    {
        extendBuffer();
    }

    for (int i = 0; i < stringLength; i++)
    {
        fileWriteBuffer[fileWriteBufferLength + i] = string[i];
    }

    fileWriteBufferLength += stringLength;
    fileWriteBuffer[stringLength] = '\0';
}

void closeFile()
{
    fclose(file);
}

void freeBuffer()
{
    free(fileWriteBuffer);
}