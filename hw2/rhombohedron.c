#include "bmbObjects.h"

void rhombohedron(double xbase, double ybase, double zbase, double radius)
{
    radius *= 1.15; /* slightly wider than stalk itself */

    int dd = 20; /* same precision as cylinders */
    int theta = 0;
    double height = radius/10.0;

    /* save transformations */
    glPushMatrix();

    glTranslated(xbase, ybase, zbase);
    glScaled(radius, 1, radius);

    glColor3d(135.0/rgbmax, 224.0/rgbmax, 148.0/rgbmax);

    /* bottom half */
    glBegin(GL_TRIANGLE_FAN);
    glVertex3d(0, 0, 0);
    for (theta = 0; theta <= 360; theta += dd)
    {
        glVertex3d(sind(theta), height/2, cosd(theta));
    }
    glEnd();

    /* top half */
    glBegin(GL_TRIANGLE_FAN);
    glVertex3d(0, height, 0);
    for (theta = 360; theta >= 0; theta -= dd)
    {
        glVertex3d(sind(theta), height/2, cosd(theta));
    }
    glEnd();

    /* replace transformations */
    glPopMatrix();
}