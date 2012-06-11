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

typedef struct
{
    Car* carArray;
    int count;
    int size;
    int firstCar;//first car in the screen
    int lastCar;
}CarList;

//Init the carlist according to the given count, all cars are set at the beginning line
void initCarlist(CarList**cl, int size,Config c);
//When a new car enter the screen
void carIn(CarList*cl);
//When a car goes out of the screen
void carOut(CarList*cl);
/**Calculer le temps d'attend avant l'arrivée de la voiture suivante*/
long getInterval(long moyenMillisecond);
#endif
