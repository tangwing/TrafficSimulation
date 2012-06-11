#include "config.h"

/**Here should be replaced by reading config file*/
void initConfiguration(Config* c)
{
    /**Parameters for display*/
    c->windowWidth=1000;
    c->windowHeight=500;
    c->roadWidth=40;
    c->carWidth=30;
    c->carLength=15;
    c->trafficLightPosition1=0.3;
    c->trafficLightPosition2=0.6;

    /**Parameters of the traffic*/
    /** (Virtual length(m) of the road)/windowWidth(pixel). */
    c->roadVirtualLengthFactor=0.2;
    //c->n=50;
    //c->v0=220/3.6/c->roadVirtualLengthFactor; /** m/s -> pixel/s */
    c->v0=500;
    c->T=1.5;
    c->s0=2/c->roadVirtualLengthFactor;/** m -> pixel */
    c->a=50;
    c->b=6;
    c->moyen=1000;
}


