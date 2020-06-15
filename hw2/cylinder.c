#include <bmbObjects.h>

/* helper function for gl quad strip vertices */
/* takes args: current angle pos, current height pos */
void cvertex(int th, double h)
{
    double red   = 47  / 256;
    double green = 161 / 256;
    double blue  = 64  / 256;
    glColor3f(red, green, blue);
    glVertex3d(sind(th), h, cosd(th));
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
    cvertex(0, height);
    for (theta = 0; theta <= 360; theta += dd)
    {
        cvertex(theta, height);
    }
    glEnd();

    /* cylinder base */
    glBegin(GL_TRIANGLE_FAN);
    cvertex(0,0);
    for (theta = 360; theta >= 0; theta -=dd)
    {
        cvertex(theta, 0);
    }
    glEnd();


    /* replace transformations */
    glPopMatrix();
}