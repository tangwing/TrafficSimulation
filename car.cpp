#include "car.h"


void initCars(Car* carlist,Config c)
{
    int i;
    float x=0;
    for(i=0; i<c.n; i++)
    {
        carlist[i].x=x;
        carlist[i].v=10;
        carlist[i].a=c.a;
        x=x-c.carLength-2*c.s0;
        carlist[i].lastUpdateTime=clock();
    }
}

/**Calculer le temps d'attend avant l'arrivée de la voiture suivante*/
float getInterval(float moyen)
{
    srand(time(NULL));
    return -moyen*(log(rand()%1001*0.001f));
}



