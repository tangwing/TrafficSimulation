#include "view.h"
#define MAX_CAR_NUMBER 50 //max car number on the screen

Config config;
CarList* cars=NULL;
/**The last update time*/
long lastUpdateTime=0;

int isTrafficLight1Red=0;
int isTrafficLight2Red=0;
int isLightSynchronized=0;

int main(int argc, char** argv)
{

    srand(time(NULL));
    //initConfiguration(&config);
    initConfigurationFromFile(&config);
    printf("width=%d;height=%d\n",glutGet(GLUT_SCREEN_WIDTH),glutGet(GLUT_SCREEN_HEIGHT));
    //init the carlist with the biggest possible size
    initCarlist(&cars,MAX_CAR_NUMBER,config);
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB);
    glutInitWindowSize(config.windowWidth,config.windowHeight);
    glutInitWindowPosition(0,0);

    glutCreateWindow("Traffic Simulation");
    glClearColor(25.0/255,134.0/255,19.0/255,0.3);
    glShadeModel(GL_SMOOTH);
    glutReshapeFunc(myReshape);
    glutDisplayFunc(myDisplay);
    glutKeyboardFunc(keyDown);
    //Create right-click menu
    glutCreateMenu(menuFonc);
    glutAddMenuEntry("Start",MENU_START);
    glutAddMenuEntry("Renew configuration",MENU_RENEW);
    glutAddMenuEntry("Synchronize the traffic lights",MENU_SYNC);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
}
