#pragma once

#include <stdio.h>

extern FILE *file;
extern char *fileWriteBuffer;
extern int fileWriteBufferSize;
extern int fileWriteBufferLength;

void createFile(char *name);
void createBuffer();
void extendBuffer();
void writeToBuffer(char *string);
void closeFile();
void freeBuffer();