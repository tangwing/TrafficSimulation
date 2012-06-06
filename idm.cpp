#include "TS.h"

/**Here should be replaced by reading config file*/
void initConfiguration(Config* c)
{
    /**Parameters for display*/
    c->windowWidth=1000;
    c->windowHeight=500;
    c->roadWidth=40;
    c->carWidth=30;
    c->carLength=30;
    c->trafficLightPosition=c->windowWidth/2;

    /**Parameters of the traffic*/
    /** (Virtual length(m) of the road)/windowWidth(pixel). */
    c->roadVirtualLengthFactor=0.2;
    c->n=50;
    c->v0=220/3.6/c->roadVirtualLengthFactor; /** m/s -> pixel/s */
    c->T=1.5;
    c->s0=2/c->roadVirtualLengthFactor;/** m -> pixel */
    c->a=10;
    c->b=3;
}

void initCars(Car* cars,Config config)
{
    int i;
    float x=0;
    for(i=0;i<config.n;i++)
    {
        cars[i].x=x;
        cars[i].v=10;
        cars[i].a=config.a;
        x=x-config.carLength-2*config.s0;
        cars[i].lastUpdateTime=clock();
    }
}



void drawCircle(double x, double y, double radius,bool fill)
{
    double i,vx,vy;
    if (fill)
    {
        glBegin(GL_TRIANGLE_FAN);
    }
    else
    {
        glBegin(GL_LINE_STRIP);
    }

    for (i=0;i<=2*PI;i+=PI/180)
    {
        vx=x+radius * cos(i);
        vy=y+radius*sin(i);
        glVertex2d(vx,vy);
    }
    glEnd();
}

/**Calculer le temps d'attend avant l'arrivée de la voiture suivante*/
float getInterval(float moyen)
{
    srand(time(NULL));
    return -moyen*(log(rand()%1001*0.001f));
}
