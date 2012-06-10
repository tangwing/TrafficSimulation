#include "view.h"
//#include "config.h"
//#include "car.h"
//#include "shishi.h"


//extern Config config;
//extern Car *cars;
//*The last update time
//extern long lastUpdateTime;
//extern int isTrafficLightRed=0;
Config config;
Car *cars=NULL;
/**The last update time*/
long lastUpdateTime=0;
int isTrafficLightRed=0;

int main(int argc, char** argv)
{
    initConfiguration(&config);
    cars=(Car*)malloc(sizeof(Car)*config.n);
    initCars(cars,config);

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB);
    glutInitWindowSize( config.windowWidth,config.windowHeight);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Traffic Simulation");

    glClearColor(25.0/255,134.0/255,19.0/255,0.3);
    glShadeModel(GL_SMOOTH);
    glutReshapeFunc(myReshape);
    glutDisplayFunc(myDisplay);
    glutMouseFunc(mouse);

    glutTimerFunc(3000,timer_func,5);
    glutTimerFunc(10000,timer_func,5);

    lastUpdateTime=clock();
    glutMainLoop();

}
