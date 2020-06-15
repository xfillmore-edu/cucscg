#include "bmbObjects.h"

void cvertex(int th, double h)
{
    float red   = 47  / 256;
    float green = 161 / 256;
    float blue  = 64  / 256;
    glColor3f(red, green, blue);
    glVertex3d(cosd(th), h, sind(th));
}

/* need to create a rotation matrix...? */
void cone(double xbase, double ybase, double zbase, double height, double radius, double ox, double oy, double oz)
{
    /* use triangle fan with triangle fan base */
    int theta = 0;
    int dd = 20;
    
    /* save transformations */
    glPushMatrix();

    glTranslated(xbase, ybase, zbase);
    /* rotate(amount, unit axis/combo) */
    glRotated(ox, ox, oy, oz);
    glRotated(ox, ox, oy, oz);
    glScaled(radius, height, radius);

    /* main cone body/top */
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(47/256, 161/256, 64/256);
    glVertex3d(0, 1, 0);
    for (theta = 0; theta <= 360; theta += dd)
    {
        cvertex(theta, 0);
    }
    glEnd();

    /* cone base */
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(47/256, 161/256, 64/256);
    glVertex3d(0, 0, 0);
    for (theta = 360; theta >= 0; theta -= dd)
    {
        cvertex(theta, 0);
    }
    glEnd();

    /* restore transformations */
    glPopMatrix();
}