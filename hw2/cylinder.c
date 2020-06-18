#include "bmbObjects.h"

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
    glColor3f(205.0/rgbmax, 227.0/rgbmax, 157.0/rgbmax);
    cvertex(0, height);
    for (theta = 0; theta <= 360; theta += dd)
    {
        cvertex(theta, height);
    }
    glEnd();

    /* cylinder base */
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(205.0/rgbmax, 227.0/rgbmax, 157.0/rgbmax);
    cvertex(0, 0);
    for (theta = 360; theta >= 0; theta -=dd)
    {
        cvertex(theta, 0);
    }
    glEnd();


    /* replace transformations */
    glPopMatrix();
}