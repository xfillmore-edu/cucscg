#include "bmbObjects.h"

/* helper function for drawing circular polygons */
/* takes args: current angle pos, current height pos, color in hex */

void cvertex(int th, double h, unsigned int hexcolor)
{
    /* convert hex color to rgb colors */
    unsigned char red =   ((hexcolor & 0xff0000)>>4) / rgbmax;
    unsigned char green = ((hexcolor & 0x00ff00)>>2) / rgbmax;
    unsigned char blue =  (hexcolor & 0x0000ff)      / rgbmax;

    /* apply color argument to polygon vertex */
    glColor3f((double) red, (double) green, (double) blue);
    
    glVertex3d(cosd(th), h, sind(th));
}