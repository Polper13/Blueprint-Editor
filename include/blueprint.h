#pragma once

extern int freeID;

extern int adressID;
extern int adressSize;

extern int outputID;
extern int outputSize;

extern int matrixID;
extern int matrixSize;

extern int zeroGate;
extern int oneGate;

void beginBlueprint();
void endBlueprint();

void addAdressLine(int size);
void addOutputLine(int size);
void addMatrix(int wordAmount, int height);
void addData();