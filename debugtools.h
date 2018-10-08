//
// Created by tufen on 2018/9/30.
//

#ifndef MMSE_DEBUGTOOLS_H
#define MMSE_DEBUGTOOLS_H

#include <stdio.h>
#include <complex.h>

#ifdef __DEBUG__
#define ERROR_INFO(format, ...) printf("File: "__FILE__              \
                                       ", Line: %05d: " format "/n", \
                                       __LINE__, ##__VA_ARGS__)
#define DEBUG(...) printf(__VA_ARGS__)
#else
#define ERROR_INFO(format, ...)
#define DEBUG(...)
#endif

void PrintFloatArray(float *Arr, int Length);
void PrintIntArray(int *Arr, int Length);
void PrintComplexFloatArray(float complex *Arr, int Length);

#endif //MMSE_DEBUGTOOLS_H
