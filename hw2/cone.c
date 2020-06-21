#include "bmbObjects.h"

/* need to create a rotation matrix...? */
void cone(double xbase, double ybase, double zbase, double height, double radius, double dthy, double dthx)
{
    /* use triangle fan with triangle fan base */
    int theta = 0;
    int dd = 20;
    
    /* save transformations */
    glPushMatrix();

    glTranslated(xbase, ybase, zbase);
    /* rotate(amount, unit axis/combo) */
    glRotated(dthy, 0, 1, 0); /* rotate around y axis 2nd */
    glRotated(dthx, 1, 0, 0); /* rotate around x axis 1st */
    glScaled(radius, height, radius);

    /* main cone body/top */
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(205.0/rgbmax, 227.0/rgbmax, 157.0/rgbmax);
    glVertex3d(0, 1, 0);
    for (theta = 0; theta <= 360; theta += dd)
    {
        cvertex(theta, 0, 1);
    }
    glEnd();

    /* cone base */
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(205.0/rgbmax, 227.0/rgbmax, 157.0/rgbmax);
    glVertex3d(0, 0, 0);
    for (theta = 360; theta >= 0; theta -= dd)
    {
        cvertex(theta, 0, 1);
    }
    glEnd();

    /* restore transformations */
    glPopMatrix();
}