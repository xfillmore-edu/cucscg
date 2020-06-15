/* OpenGL text output routine */

#include "config.h"
/* #include stdarg.h */

#define MAXSTRLEN 8192
#define BITFONT GLUT_BITMAP_HELVETICA_12

void gprint(const char* format, ...)
{
    char buffer[MAXSTRLEN];
    char* ch = buffer;
    va_list args;

    /* convert parameters to char string */
    va_start(args, format);
    vsnprintf(buffer, MAXSTRLEN, format, args);
    va_end(args);

    /* Disp chars one by one at current raster pos */
    while (*ch)
    {
        glutBitmapCharacter(BITFONT, *ch++);
    }
}