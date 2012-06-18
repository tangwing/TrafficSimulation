#include "car.h"
/**Init the carlist according to the given count,
 **all cars are set at the beginning line*/
void initCarlist(CarList**cl, int size,Config c)
{
    int i;
    float x=0;

    if(*cl==NULL)
        *cl=(CarList*)malloc(sizeof(CarList));
    (*cl)->carArray=(Car*)malloc(sizeof(Car)*size);
    (*cl)->firstCar=-1;
    (*cl)->lastCar=-1;
    (*cl)->count=0;
    (*cl)->size=size;

    for(i=0; i<size; i++)
    {
        (*cl)->carArray[i].x=x;
        (*cl)->carArray[i].v=c.v_begin;
        (*cl)->carArray[i].a=c.a;
    }
}

/**When a new car enter the screen*/
void carIn(CarList*cl, Config c)
{
    if(cl->count==0 )
    {
        cl->firstCar=0;
        cl->lastCar=0;
        cl->count=1;

    }
    else
    {
         cl->lastCar=(cl->lastCar+1)%cl->size;
         cl->count++;
    }
    cl->carArray[cl->lastCar].a=c.a;
    cl->carArray[cl->lastCar].x=0.0;
    cl->carArray[cl->lastCar].v=c.v_begin;
    return;
}
/**When a car goes out of the screen*/
void carOut(CarList*cl)
{
    if(cl->count==0)return;
    if(cl->count==1)
    {
        cl->firstCar=-1;
        cl->lastCar=-1;
        cl->count=0;
    }
    else
    {
        cl->firstCar=(cl->firstCar+1)%cl->size;
        cl->count--;
    }

}

/**Calculer le temps d'attend avant l'arrivée de la voiture suivante*/
long getInterval(long moyen, long T)
{
    return (long)(-moyen*(log(rand()%1001*0.001f)))%(long)moyen+T;
    //return moyen*(rand()%1001*0.001f);
}
