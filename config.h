//#pragma once
#ifndef CONFIGH
#define CONFIGH
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
} Config;

/**This should be replaced by reading config file*/
void initConfiguration(Config* c);
#endif
