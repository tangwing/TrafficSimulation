#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#ifndef VIEWH
#define VIEWH
//#include "config.h"
#include "car.h"
//#include "shishi.h"
#define PI 3.1416
//#define N 40
//
extern Config config;
extern Car *cars;
/**The last update time*/
extern long lastUpdateTime;
extern int isTrafficLightRed;

// Config config;
// Car *cars;
///**The last update time*/
// long lastUpdateTime;
// int isTrafficLightRed;

void myDisplay(void);
/** Here update the position of cars*/
void refresh(void);
void myReshape(GLsizei w, GLsizei h);
void mouse(int button, int state, int x, int y);

void drawCircle(double x, double y, double radius, int fill);
void timer_func(int value);

#endif
