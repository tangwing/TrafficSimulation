#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PI 3.1416
#define N 40

typedef struct
{
    int windowWidth;
    int windowHeight;
    float roadWidth;
    /** (Virtual length(m) of the road)/windowWidth(pixel). */
    float roadVirtualLengthFactor;
    float carWidth;
    float carLength;
    /**The total number of cars*/
    int n;
    /**Traffic light position*/
    float trafficLightPosition;
    /**Desired velocity (km/h)*/
    float v0;
    /**Time headway*/
    float T;
    /**Minimum gap*/
    float s0;
    /**Acceleration*/
    float a;
    /**Deceleration*/
    float b;
    /**L'écart moyen du temps d'arrivée.[1,5] est préférable*/
    float beta;
}Config;

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
}Car;

static Config config;
/**This should be replaced by reading config file*/
void initConfiguration(Config* c);
void initCars(Car* cars,Config c);
void drawCircle(double x, double y, double radius,bool fill);
