#include "view.h"

Config config;
CarList* cars=NULL;
/**The last update time*/
long lastUpdateTime=0;

int isTrafficLightRed=0;
//long intervalBeforeNextCar=3;
int main(int argc, char** argv)
{
    srand(time(NULL));
    initConfiguration(&config);
    config.windowWidth=glutGet(GLUT_SCREEN_WIDTH)-10;
    config.windowHeight=glutGet(GLUT_SCREEN_HEIGHT)-20;

    //init the carlist with the biggest possible size
    initCarlist(&cars,config.windowWidth/config.carLength,config);
    //printf("%d",cars->size);
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB);
    glutInitWindowSize(config.windowWidth,config.windowHeight);
    //glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Traffic Simulation");

    glClearColor(25.0/255,134.0/255,19.0/255,0.3);
    glShadeModel(GL_SMOOTH);
    glutReshapeFunc(myReshape);
    glutDisplayFunc(myDisplay);
    glutMouseFunc(mouse);

//    glutTimerFunc(3000,timer_func,5);
//    glutTimerFunc(10000,timer_func,5);

    glutMainLoop();
}
