#include "bmbObjects.h"

/* helper function */
/* takes args: current angle pos, current height pos */
void cvertex(int th, double h, bool color)
{
    if (color) /* stalk main green */
    {
        glColor3f(47.0  / rgbmax, 161.0 / rgbmax, 64.0  / rgbmax);
    }
    else /* stalk section light green */
    {
        glColor3f(135.0/rgbmax, 224.0/rgbmax, 148.0/rgbmax);
    }
    
    glVertex3d(cosd(th), h, sind(th));
}