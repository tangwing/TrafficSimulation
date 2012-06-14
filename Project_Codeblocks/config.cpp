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
    c->v_begin=50;
    c->v0=500;
    c->T=1.5;
    c->s0=2/c->roadVirtualLengthFactor;/** m -> pixel */
    c->a=50;
    c->b=6;
    c->moyen=1000;
}

void initConfigurationFromFile(Config* c)
{
    FILE *f=fopen(CONFIG_FILEPATH,"r");
    char buffer[BUFFER_SIZE]="";
    int i=0;
    char line[LINE_MAXLENGTH];
    char *key,*value,*test;

    test=fgets(line,LINE_MAXLENGTH,f);
    while(test!=NULL)
    {
        if(line[0]!='#' && line[0]!='\n')
        {
            key=strtok(line,"=");
            value=strtok(NULL,"\n");
            printf("%s\t%s\n",key,value);

            if(!strcmp(key,"windowWidth"))
                c->windowWidth=atoi(value);
            else if(!stricmp(key,"windowHeight"))
                c->windowHeight=atoi(value);
            else if(!stricmp(key,"roadWidth"))
                c->roadWidth=(float)atof(value);
            else if(!stricmp(key,"carWidth"))
                c->carWidth=(float)atof(value);
            else if(!stricmp(key,"carLength"))
                c->carLength=(float)atof(value);
            else if(!stricmp(key,"carLength"))
                c->carLength=(float)atof(value);
            else if(!stricmp(key,"trafficLightPosition1"))
                c->trafficLightPosition1=(float)atof(value);
            else if(!stricmp(key,"trafficLightPosition2"))
                c->trafficLightPosition2=(float)atof(value);

            else if(!stricmp(key,"roadVirtualLengthFactor"))
                c->roadVirtualLengthFactor=(float)atof(value);
            else if(!stricmp(key,"v0"))
                c->v0=(float)atof(value);
            else if(!stricmp(key,"v_begin"))
                c->v_begin=(float)atof(value);
            else if(!stricmp(key,"T"))
                c->T=(float)atof(value);
            else if(!strcmp(key,"s0"))
                c->s0=(float)atof(value);
            else if(!strcmp(key,"a"))
                c->a=(float)atof(value);
            else if(!strcmp(key,"b"))
                c->b=(float)atof(value);
            else if(!strcmp(key,"moyen"))
                c->moyen=(float)atof(value);
        }
        test=fgets(line,LINE_MAXLENGTH,f);

    }
    c->s0=2/c->roadVirtualLengthFactor;
}

