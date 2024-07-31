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
    file = fopen(name, "w");

    if (file == NULL)
    {
        printf("could not create file\n");
        exit(EXIT_FAILURE);
    }
}

void createBuffer()
{
    fileWriteBuffer = (char*)malloc(startingBufferSize * sizeof(char));
    if (fileWriteBuffer == NULL)
    {
        printf("could not allocate buffer\n");
        exit(EXIT_FAILURE);
    }

    fileWriteBufferSize = startingBufferSize;
    fileWriteBufferLength = 0;
}

void extendBuffer()
{
    printf("extending to %d bytes\n", fileWriteBufferSize * 2);

    char *ptr = (char*)malloc(fileWriteBufferSize * 2);
    if (ptr == NULL)
    {
        printf("could not extend buffer\n");
        exit(EXIT_FAILURE);
    }

    if (fileWriteBuffer == NULL)
    {
        printf("could not copy contents to new buffer - old buffer didnt exist");
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
    if (string == NULL)
    {
        printf("could not write to buffer - string was null");
        exit(EXIT_FAILURE);
    }

    int stringLength = strlen(string);

    while (fileWriteBufferSize - fileWriteBufferLength < stringLength)
    {
        extendBuffer();
    }

    for (int i = 0; i < stringLength; i++)
    {
        fileWriteBuffer[fileWriteBufferLength + i] = string[i];
    }

    fileWriteBufferLength += stringLength;
    fileWriteBuffer[fileWriteBufferLength] = '\0';
}

void writeBufferToFile()
{
    if (fileWriteBuffer == NULL)
    {
        printf("could not write to file - buffer didnt exist");
        exit(EXIT_FAILURE);
    }

    if (file == NULL)
    {
        printf("could not write to file - file didnt exist");
        exit(EXIT_FAILURE);
    }

    size_t length = strlen(fileWriteBuffer);
    size_t written = fwrite(fileWriteBuffer, sizeof(char), length, file);

    if (written < length)
    {
        printf("error while writing buffer to file\n");
        exit(EXIT_FAILURE);
    }
}

void clearBuffer()
{
    fileWriteBufferLength = 0;
}

void closeFile()
{
    fclose(file);
}

void freeBuffer()
{
    free(fileWriteBuffer);
}