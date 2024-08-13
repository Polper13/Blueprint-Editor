#pragma once

#include <stdio.h>

extern FILE *file;
extern char *fileWriteBuffer;
extern int fileWriteBufferSize;
extern int fileWriteBufferLength;

void createFile(char *name);
void createBuffer();

void extendBuffer();
void removeLastCharacters(int amount);

void writeToBuffer(char *string);
void writeBufferToFile();

void clearBuffer();
void closeFile();
void freeBuffer();