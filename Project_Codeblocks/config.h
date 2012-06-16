#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#ifndef CONFIGH
#define CONFIGH
#define CONFIG_FILEPATH "C:\\TS_setting.ini"
#define BUFFER_SIZE 5000
#define LINE_MAXLENGTH 1000
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
    //int n;
    /**Traffic light position, percentage to the window size*/
    float trafficLightPosition1;
    float trafficLightPosition2;
    long lightDurationWhenSynchronized;
    //The value -1 means intelligent
    long lightChangeDelayWhenSynchronized;
    /**Desired velocity (km/h)*/
    float v0;
    /**The velocity in the beginning*/
    float v_begin;
    /**Time headway*/
    float T;
    /**Minimum gap*/
    float s0;
    /**Acceleration*/
    float a;
    /**Deceleration*/
    float b;
    /** Le moyen temps d'arrivée en milliseconde*/
    float moyen;
} Config;

/**This should be replaced by reading config file*/
void initConfiguration(Config* c);
void initConfigurationFromFile(Config* c);
#endif
