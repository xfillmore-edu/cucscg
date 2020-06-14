/* Set OpenGL Projection */
/* Copied directly from ex10/project.c */



/* REWRITE FOR SELF */



#include <config.h>

void project(double fov, double aspratio, double dimension)
{
    /* manipulate projection matrix */
    glMatrixMode(GL_PROJECTION);

    /* remove previous transformations */
    glLoadIdentity();

    /* perspective transformation */
    /* 0 - orthogonal */
    if (fov)
    {
        gluePerspective(fov, aspratio, dimension/16, 16*dimension);
    }
    else
    {
        glOrtho(-aspratio * dimension, aspratio * dimension, -dimension, dimension, -dimension, dimension);
    }

    /* back to model matrix */
    glMatrixMode(GL_MODELVIEW);

    /* clear transformations */
    glLoadIdentity();
}