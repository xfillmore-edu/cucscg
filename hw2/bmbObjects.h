/* Individual objects for construction of bamboo stalks */

#ifndef bmbObjects
#define bmbObjects

#include <math.h>
#include <stdbool.h>

#define GL_GLEXT_PROTOTYPES
/* Cross-OS compatability */
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define pi 3.14159265358979
#define rgbmax 255.0

/* Sine and Cosine conversion macros */
#define sind(x) sin(pi/180 * (x))
#define cosd(x) cos(pi/180 * (x))

/* bamboo objects list */
/* cones, cylinders, double triangle fans, "leaves" (2x two flat faces, rounded rectangles strip) */
/* + lines for connecting leaves to stem */

/* helper function */
/* takes args: current angle pos, current height pos */
void cvertex(int th, double h, bool color);

/* cylinder */
/* for core stem segments - all vertical */
/* params: xyz centered at base, height, radius */
void cylinder(double xcen, double ycen, double zcen, double height, double radius, bool main);

/* consisting of semi-circular flat segments and rounded segments */
/* for the leaves */
/* params:  */
void leaf(double xtip, double ytip, double ztip, double length, double width, double dthx, double dthy);

/* cone */
/* for branches out to leaves */
/* params:  */
void cone(double xbase, double ybase, double zbase, double height, double radius, double dthy, double dthx);

/* lame curve / hyperellipsoid */
/* for section pieces along stem */
/* params: xyz base position, stalk radius */
void rhombohedron(double xbase, double ybase, double zbase, double radius);

#endif