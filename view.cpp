#include "view.h"
long intervalBeforeNextCar;
long lastCarEnterTime;
void myDisplay(void)
{
    int i,index,n,first;
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    //draw the road (by two lines)
    glLineWidth(3.0);
    glBegin(GL_LINES);
    glVertex2f( -config.windowWidth/2.0, -config.roadWidth/2.0);
    glVertex2f( config.windowWidth/2.0, -config.roadWidth/2.0);
    glVertex2f( -config.windowWidth/2.0, config.roadWidth/2.0);
    glVertex2f( config.windowWidth/2.0, config.roadWidth/2.0);
    glEnd();
    //draw the two traffic lights
    if(isTrafficLightRed==1)
    {
        //red light
        glColor3f(1,0,0);
    }
    else
    {
        glColor3f(0,1,0);
    }
    glBegin(GL_LINE_LOOP);
    drawCircle(config.trafficLightPosition1*config.windowWidth-config.windowWidth/2.0,config.roadWidth,10,1);
    drawCircle(config.trafficLightPosition2*config.windowWidth-config.windowWidth/2.0,config.roadWidth,10,1);
    glEnd();
    //Draw cars
    glColor3f(1.0,1.0,1.0);
    if(cars->count>0)
    {
        printf("count:%d;",cars->count);
        first=cars->firstCar;
        n=cars->count;//Function carOut will change the value of count
        for(index=0; index<n; index++)
        {
            i=(first+index)%cars->size;
            if(cars->carArray[i].x-config.carLength<=config.windowWidth)
            {
                glRectf(-config.windowWidth/2.0+cars->carArray[i].x-config.carLength,
                        config.carWidth/2.0,
                        -config.windowWidth/2.0+cars->carArray[i].x,
                        -config.carWidth/2.0);
                //printf("%d-point:%f\t",i,-config.windowWidth/2.0+cars->carArray[i].x);
                printf("%d:%f;%f;%f;%f;%f;\n",i,cars->carArray[i].x,
                        -config.windowWidth/2.0+cars->carArray[i].x-config.carLength,
                        config.carWidth/2.0,
                        -config.windowWidth/2.0+cars->carArray[i].x,
                        -config.carWidth/2.0);
            }
            else
            {
                carOut(cars);
            }

        }
        printf("\n");

    }

    glPopMatrix();
    glutSwapBuffers();
    //lastUpdateTime=clock();
}

/** Here update the position of cars*/
void refresh(void)
{
    int i,index,n,first;
    float deltaT,deltaV,sStar,deltaS,tmp,a1,a2;
    long currentTime=clock();

    if(cars->firstCar==-1)
        return;
    deltaT=(currentTime-lastUpdateTime)/1000.0;

    /**Update positions and velocities
    (based on the acceleration of the last time)*/
    first=cars->firstCar;
    n=cars->count;
    for(index=0; index<n; index++)
    {
        i=(first+index)%cars->size;
        tmp=(cars->carArray[i].v+cars->carArray[i].a*deltaT/2)*deltaT;
        if(tmp>0)
            cars->carArray[i].x+=tmp;
        cars->carArray[i].v+= cars->carArray[i].a*deltaT;
        if(cars->carArray[i].v<0)
            cars->carArray[i].v=0;
        if(cars->carArray[i].x-config.carLength>config.windowWidth)
        {
            carOut(cars);
        }
    }

    /**Update acceleration*/
    n=cars->count;
    for(index=0; index<n; index++)
    {

        i=(cars->lastCar-index)%cars->size;
        if(i==cars->firstCar)break;

        deltaS=cars->carArray[(i-1)%cars->size].x-cars->carArray[i].x-config.carLength;
        //printf("%d->%d__Deltas=%f\n",i,(i-1)%cars->size,deltaS);
        deltaV=cars->carArray[i].v-cars->carArray[(i-1)%cars->size].v;
        sStar=config.s0+cars->carArray[i].v*config.T+(cars->carArray[i].v*deltaV/(2*sqrt(config.a*config.b)));
        a1= config.a*(1-pow(cars->carArray[i].v/config.v0,4)-pow(sStar/deltaS,2));
        /**Juge whether the traffic light is valide for current car.
         The driver take the red light as the car in front.*/
        if(isTrafficLightRed==1 && cars->carArray[i].x<config.trafficLightPosition1*config.windowWidth)
        {
            deltaS=config.trafficLightPosition1*config.windowWidth-cars->carArray[i].x;
            deltaV=cars->carArray[i].v;
            sStar=config.s0+cars->carArray[i].v*config.T+(cars->carArray[i].v*deltaV/(2*sqrt(config.a*config.b)));
            a2= config.a*(1-pow(cars->carArray[i].v/config.v0,4)-pow(sStar/deltaS,2));

            if(a1>a2)
                cars->carArray[i].a=a2;
            else
                cars->carArray[i].a=a1;
        }
        else
        {
            cars->carArray[i].a=a1;
        }

    }
    //i==cars->firstCar
    if(i==cars->firstCar)
    {
        a1= config.a*(1-pow(cars->carArray[cars->firstCar].v/config.v0,4));
        if(isTrafficLightRed==1 && cars->carArray[cars->firstCar].x<config.trafficLightPosition1*config.windowWidth)
        {
            deltaS=config.trafficLightPosition1*config.windowWidth-cars->carArray[cars->firstCar].x;
            deltaV=cars->carArray[cars->firstCar].v;
            sStar=config.s0+cars->carArray[cars->firstCar].v*config.T+(cars->carArray[cars->firstCar].v*deltaV/(2*sqrt(config.a*config.b)));
            a2= config.a*(1-pow(cars->carArray[cars->firstCar].v/config.v0,4)-pow(sStar/deltaS,2));
            if(a1>a2)
                cars->carArray[cars->firstCar].a=a2;
            else
                cars->carArray[cars->firstCar].a=a1;
        }
        else
        {
            cars->carArray[cars->firstCar].a=a1;
        }
    }


    printf("currentTime=%ld;lastCarEnterTime=%ld;interval=%ld;carindex=%d;x=%f;\n",currentTime,lastCarEnterTime,intervalBeforeNextCar,cars->lastCar,cars->carArray[cars->lastCar].x);
    //Add a new car if necessary (!Only when there is place!)
    if(currentTime-lastCarEnterTime>=intervalBeforeNextCar&&
       cars->count>0&&
       (cars->carArray[cars->lastCar].x-config.carLength-config.s0>0))
    {
        carIn(cars);
        printf("first=%d;carindex=%d;x=%f;\n",cars->firstCar,cars->lastCar,cars->carArray[cars->lastCar].x);
        lastCarEnterTime=clock();
        intervalBeforeNextCar=getInterval(config.moyen);

    }
    lastUpdateTime=currentTime;

    glutPostRedisplay();
}

void myReshape(GLsizei w, GLsizei h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-config.windowWidth/2.0,config.windowWidth/2.0,-config.windowHeight/2.0,config.windowHeight/2.0,-1,1);
//    if(w<=h)
//        gluOrtho2D(-1.0,1.5,-1.5,1.5*(GLfloat)h/(GLfloat)w);
//    else
//        gluOrtho2D(-1.0,1.5*(GLfloat)w/(GLfloat)h,-1.5,1.5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
//    gluOrtho2D(-1.5,0.0,-1.5,1.5);
}

void mouse(int button, int state, int x, int y)
{
    switch(button)
    {
    case GLUT_LEFT_BUTTON:
        if(state==GLUT_UP)
        {
            //For the first time
            if(cars->count==0)
            {
                carIn(cars);
                lastCarEnterTime=clock();
                lastUpdateTime=lastCarEnterTime;
                intervalBeforeNextCar=getInterval(config.moyen);
            }
            glutIdleFunc(refresh);
        }

        break;
    case GLUT_MIDDLE_BUTTON:
        if(state==GLUT_UP)
        {
            initConfigurationFromFile(&config);
            //glutIdleFunc(NULL);
            //printf("x=%f;a=%f;v=%f;\n",cars[0].x,cars[0].a,cars[0].v);
        }

        break;
    case GLUT_RIGHT_BUTTON:
        if(state==GLUT_UP)
        {
            if(isTrafficLightRed==0)
                isTrafficLightRed=1;
            else
                isTrafficLightRed=0;
            glutPostRedisplay();
        }
    default:
        break;
    }
}


void drawCircle(double x, double y, double radius,int fill)
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

    for (i=0; i<=2*PI; i+=PI/180)
    {
        vx=x+radius * cos(i);
        vy=y+radius*sin(i);
        glVertex2d(vx,vy);
    }
    glEnd();
}

void timer_func(int value)
{
    if(value>0)
    {
        value --;
        printf("I'm a timer !");
    }
}
