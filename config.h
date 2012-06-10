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
    /**Traffic light position, percentage to the window size*/
    float trafficLightPosition1;
    float trafficLightPosition2;
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
    /** Le moyen temps d'arrivée en milliseconde*/
    float moyen;
} Config;

/**This should be replaced by reading config file*/
void initConfiguration(Config* c);
#endif
