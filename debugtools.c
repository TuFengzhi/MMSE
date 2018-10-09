//
// Created by Tu Fengzhi on 2018/9/30.
//

#include "debugtools.h"

void PrintFloatArray(float *Arr, int Length)
{
    DEBUG("---------------------------\n");
    for (int i = 0; i < Length; i++)
    {
        DEBUG("%4f ", Arr[i]);
    }
    DEBUG("\n---------------------------\n");
}

void PrintIntArray(int *Arr, int Length)
{
    DEBUG("---------------------------\n");
    for (int i = 0; i < Length; i++)
    {
        DEBUG("%d ", Arr[i]);
    }
    DEBUG("\n---------------------------\n");
}

void PrintComplexFloatArray(float complex *Arr, int Length)
{
    DEBUG("---------------------------\n");
    for (int i = 0; i < Length; i++)
    {
        DEBUG("%f%+fi ", creal(Arr[i]), cimag(Arr[i]));
    }
    DEBUG("\n---------------------------\n");
}
