#include <stdio.h>        

#include "file.h"

int main(int argc, char *argv[])
{
    createBuffer();
    writeToBuffer("hello");
    writeToBuffer(" world");

    printf("%s", fileWriteBuffer);
}