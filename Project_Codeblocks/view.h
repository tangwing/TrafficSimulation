#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#ifndef VIEWH
#define VIEWH

#include "car.h"

#define PI 3.1416
#define MENU_START 1
#define MENU_RENEW 2
#define MENU_SYNC 3

extern Config config;
extern CarList *cars;
/**The last update time*/
extern long lastUpdateTime;
extern int isTrafficLight1Red;
extern int isTrafficLight2Red;
extern int isLightSynchronized;

/**The call back function for OpenGL for drawing*/
void myDisplay(void);
/** Here update the position of cars, called by GL at idle time*/
void refresh(void);
/**Called by GL when the window is reshaped*/
void myReshape(GLsizei w, GLsizei h);
/**Draw a circle as traffic light.*/
void drawCircle(double x, double y, double radius, int fill);
void switchLight(int value);
/**Bound with mouse right button as a menu fonction*/
void menuFonc(int value);
/**Fonction dealing with key action*/
void keyDown(unsigned char,int,int);
#endif
