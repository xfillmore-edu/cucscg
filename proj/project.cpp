// Set OpenGL Projection
// copied from ex10/project.c, hw3

#include "config.hpp"

void project(double fov, double aspratio, double dimension)
{
    // manipulate projection matrix
    glMatrixMode(GL_PROJECTION);

    // remove previous transformations
    glLoadIdentity();

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