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
    c->lightDurationWhenSynchronized=5000;
    c->lightChangeDelayWhenSynchronized=-1;
    /**Parameters of the traffic*/
    /** (Virtual length(m) of the road)/windowWidth(pixel). */
    //c->roadVirtualLengthFactor=0.2;
    //c->n=50;
    //c->v0=220/3.6/c->roadVirtualLengthFactor; /** m/s -> pixel/s */
    c->v_begin=50;
    c->v0=500;
    c->T=1.5;
    c->s0=10;//c->roadVirtualLengthFactor;/** m -> pixel */
    c->a=50;
    c->b=6;
    c->moyen=1000;
}

void initConfigurationFromFile(Config* c)
{
    FILE *f=fopen(CONFIG_FILEPATH,"r");;
    char buffer[BUFFER_SIZE]="";
    int i=0;
    char line[LINE_MAXLENGTH];
    char *key,*value,*test;

    //if file doesn't exist
    if(f==NULL)
    {
        f=fopen(CONFIG_FILEPATH,"w+");
        fprintf(f,"#The first two parameters of window are used for \n#the initialisation of the window, so they should not be\n# changed during the runtime\n");
        fprintf(f,"windowWidth=1000\n");
        fprintf(f,"windowHeight=500\n");
        fprintf(f,"roadWidth=40\n");
        fprintf(f,"carWidth=15\n");
        fprintf(f,"carLength=20\n");
        fprintf(f,"#The position of traffic lights is specified by their\n#proportion to the window width\n");
        fprintf(f,"trafficLightPosition1=0.3\n");
        fprintf(f,"trafficLightPosition2=0.6\n");
        fprintf(f,"lightDurationWhenSynchronized=5000\n");
        fprintf(f,"lightChangeDelayWhenSynchronized=2000\n");
        fprintf(f,"#Parameters of the traffic\n");
        fprintf(f,"#(Virtual length(m) of the road)/windowWidth(pixel).\n");
        fprintf(f,"#This is not used:roadVirtualLengthFactor=0.2\n");
        fprintf(f,"v0=500\n");
        fprintf(f,"v_begin=50\n");
        fprintf(f,"T=1.5\n");
        fprintf(f,"s0=10\n");
        fprintf(f,"a=30\n");
        fprintf(f,"#unit:ms\n");
        fprintf(f,"b=6\n");
        fprintf(f,"moyen=2000\n");
        fflush(f);
        rewind(f);
    }

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
            else if(!stricmp(key,"lightDurationWhenSynchronized"))
                c->lightDurationWhenSynchronized=(long)atol(value);
            else if(!stricmp(key,"lightChangeDelayWhenSynchronized"))
                c->lightChangeDelayWhenSynchronized=(long)atol(value);
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
    //c->s0=c->s0/c->roadVirtualLengthFactor;
    //We try to calculate a better lightChangeDelay.(t=sqrt(2as)/a)
    if(c->lightChangeDelayWhenSynchronized==-1)
        c->lightChangeDelayWhenSynchronized=1+(long)(1000*sqrt(2*c->a*(c->trafficLightPosition2-c->trafficLightPosition1)*c->windowWidth)/c->a);
}
