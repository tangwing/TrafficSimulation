#include "car.h"

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
        (*cl)->carArray[i].v=10;
        (*cl)->carArray[i].a=c.a;
        //x=x-c.carLength-2*c.s0;
        //carlist[i].lastUpdateTime=clock();
    }
}

//int addIndex(CarList*cl,int i)
//{
//    return (i+1)%cl->size;
//}
//
//int Index(CarList*cl,int i)
//{
//    return (i+1)%cl->size;
//}
void carIn(CarList*cl)
{
    if(cl->count==0 )
    {
        cl->firstCar=0;
        cl->lastCar=0;
        cl->count=1;
        return;
    }
    else
    {
         cl->lastCar=(cl->lastCar+1)%cl->size;
         cl->count++;
    }

}

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


/**Calculer le temps d'attend avant l'arriv�e de la voiture suivante*/
long getInterval(long moyen)
{
    return -moyen*(log(rand()%1001*0.001f));
}


