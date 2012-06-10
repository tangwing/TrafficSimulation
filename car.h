#include "config.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifndef CARH
#define CARH
typedef struct
{
    /**The postion of the current car (pixel)*/
    float x;
    /**The current velocity (pixel)*/
    float v;
    /**The current acceleration*/
    float a;
    /**The last update time*/
    long lastUpdateTime;
} Car;

void initCars(Car* cars,Config c);
#endif
