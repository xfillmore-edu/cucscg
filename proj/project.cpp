// Set OpenGL Projection
// copied from ex10/project.c, hw3

#include "config.hpp"

void project(double fov, double aspratio, double dimension, int mxpos, int mypos)
{
    // manipulate projection matrix
    glMatrixMode(GL_PROJECTION);

    // remove previous transformations
    glLoadIdentity();

    // Picking/Selection modifiers
    // http://unknownware.com/rtfm/graphics/glselection.html
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    gluPickMatrix((GLdouble)mxpos, (GLdouble)(viewport[3]-mypos), 0.2, 0.2, viewport );

    // perspective transformation
    // 0 - orthogonal
    if (fov)
    {
        gluPerspective(fov, aspratio, dimension/16, 16*dimension);
    }
    else
    {
        glOrtho(-aspratio * dimension, aspratio * dimension, -dimension, dimension, -dimension, dimension);
    }

    // back to model matrix
    glMatrixMode(GL_MODELVIEW);

    // clear transformations
    glLoadIdentity();
}