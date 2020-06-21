#ifndef config
#define config


/* C libraries */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>

#ifdef USEGLEW
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES

/* Cross-OS compatability */
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define pi 3.14159265358979

/* Sine and Cosine conversion macros */
#define sind(x) sin(pi/180 * (x))
#define cosd(x) cos(pi/180 * (x))

/* convert boolean true/false to string */
#define bool2str(bvar) (bvar ? "true" : "false")

/* function declarations */
void checkErrs(char* fn);
void gprint(const char* format, ...);
void fatal(const char* format, ...);
void project(double fov, double aspratio, double dimension);
unsigned int loadTexture(const char* filename);

#endif /* config.h */