#include "bmbObjects.h"

void cylinder(double xcen, double ycen, double zcen, double height, double radius, unsigned int hexcolor)
{
    int dd    = 30; /* change in degrees ~ visual precision */
    int theta = 0;  /* current angle pos */

    /* lighting effects */
    float shiny[] = {30};
    float whtsp[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT, GL_SHININESS, shiny);
    glMaterialfv(GL_FRONT, GL_SPECULAR, whtsp);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, whtsp);
    glEnable(GL_RESCALE_NORMAL);

    /* save transformations */
    glPushMatrix();

    /* final transformation for cylinder */
    glTranslated(xcen, ycen, zcen);
    glScaled(radius, 1, radius);

    /* cylinder main body */
    glBegin(GL_QUAD_STRIP);
    for (theta = 0; theta <= 360; theta += dd)
    {
        glNormal3f(cosd(theta), 0, sind(theta));
        glTexCoord3d(cosd(theta), 0,      sind(theta)); cvertex(theta, 0,      hexcolor);
        glTexCoord3d(cosd(theta), height, sind(theta)); cvertex(theta, height, hexcolor);
    }
    glEnd();

    /* cylinder cap */
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, 1, 0);
    // glColor3f(205.0/rgbmax, 227.0/rgbmax, 157.0/rgbmax);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3d(0, height, 0);
    for (theta = 0; theta <= 360; theta += dd)
    {
        cvertex(theta, height, hexcolor);
    }
    glEnd();

    /* cylinder base */
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, -1, 0);
    // glColor3f(205.0/rgbmax, 227.0/rgbmax, 157.0/rgbmax);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3d(0, 0, 0);
    for (theta = 360; theta >= 0; theta -=dd)
    {
        cvertex(theta, 0, hexcolor);
    }
    glEnd();


    /* replace transformations */
    glPopMatrix();
}