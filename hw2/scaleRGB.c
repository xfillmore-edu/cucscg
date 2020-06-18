/* Convert RGB int scale to OpenGL values */

#include "config.h"

void scaleRGB(double* r, double* g, double* b)
{
    /* ensure range within 255 using uchar */
    unsigned char red   = *r;
    unsigned char green = *g;
    unsigned char blue  = *b;

    *r = red   / 255.0;
    *g = green / 255.0;
    *b = blue  / 255.0;
}