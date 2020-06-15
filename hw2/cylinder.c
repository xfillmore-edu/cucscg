#include "bmbObjects.h"

float red   = 47.0  / 256.0;
float green = 161.0 / 256.0;
float blue  = 64.0  / 256.0;

/* helper function for gl quad strip vertices */
/* takes args: current angle pos, current height pos */
void cvertex(int th, double h)
{
    glColor3f(red, green, blue);
    glVertex3d(cosd(th), h, sind(th));
}

void cylinder(double xcen, double ycen, double zcen, double height, double radius)
{
    int dd    = 20; /* change in degrees ~ visual precision */
    int theta = 0;  /* current angle pos */

    /* save transformations */
    glPushMatrix();

    /* final transformation for cylinder */
    glTranslated(xcen, ycen, zcen);
    glScaled(radius, 1, radius);

    /* cylinder main body */
    glBegin(GL_QUAD_STRIP);
    for (theta = 0; theta <= 360; theta += dd)
    {
        cvertex(theta, 0);
        cvertex(theta, height);
    }
    glEnd();

    /* cylinder cap */
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(red, green, blue);
    cvertex(0, height);
    for (theta = 0; theta <= 360; theta += dd)
    {
        cvertex(theta, height);
    }
    glEnd();

    /* cylinder base */
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(red, green, blue);
    cvertex(0, 0);
    for (theta = 360; theta >= 0; theta -=dd)
    {
        cvertex(theta, 0);
    }
    glEnd();


    /* replace transformations */
    glPopMatrix();
}