/*
 *
 * Xuedan Fillmore
 * CSCI 4229 Computer Graphics
 * Assignment 2 3d scene
 *
 * See README for key bindings
 *
 */

#include <config.h>
#include <bmbObjects.h>

/* global variables */
int theta    = 0;
int phi      = 0;
int viewmode = 0;

/* some parts reused from hw1 */
void display()
{
    /* Clear current image */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /* Reset prior transformations */
    glLoadIdentity();
    /* Set view angle */
    glRotated(phi,   1, 0, 0);
    glRotated(theta, 0, 1, 0);
    /* Allow z-buffer */
    glEnable(GL_DEPTH_TEST);

    // CODE BODY HERE
    /* use rand()%maxsize + minsize

    /* Cleanup */
    checkErrs("display");
    glutSwapBuffers();
}

void keybindings()
{
    //
}

/* arrow functionalities different based on projection mode */
void specialkeybindings(int key, int xpos, int ypos)
{
    switch(key)
    { /* azimuth ~ longitude / elevation ~ latitude */
        case GLUT_KEY_RIGHT:
            theta += 5;      /* increase longitudinal view 5 deg */
            break;
        case GLUT_KEY_LEFT:
            theta -= 5;      /* decrease longitudinal view 5 deg */
            break;
        case GLUT_KEY_UP:
            phi += 5;        /* increase latitudinal view 5 deg */
            break;
        case GLUT_KEY_DOWN:
            phi -= 5;        /* decrease latitudinal view 5 deg */
            break;
    }

    /* Maintain angle between 0 and 360 deg */
    theta %= 360;
    phi   %= 360;

    /* redisplay scene */
    glutPostRedisplay();
}

/* window resize adjustment */
/* copied directly from hw1 */
/* needs adjustment for different projection types */
void reshape(int width, int height)
{
    /* ratio width:height */
    double wh_ratio = (height > 0) ? (double)width/height : 1;
    /* dimension of orthogonal box */
    double dim = 50;

    /* set viewport to entire window */
    glViewport(0, 0, width, height);

    /* to manipulate projection matrix */
    glMatrixMode(GL_PROJECTION);

    /* Remove prev transformations */
    glLoadIdentity();

    /* Adjust projection box for new win aspect ratio */
    glOrtho(-dim * wh_ratio, dim * wh_ratio, -dim, dim, -dim, dim);

    /* Switch to manipulating model matrix */
    glMatrixMode(GL_MODELVIEW);

    /* Remove prev transformations */
    glLoadIdentity();
}

/* initialize glut and register functions */
/* copied directly from hw1 */
int main(int argc, char* argv[])
{
    srand((unsigned)time(NULL));

    /* Initialize GLUT, process user params */
    glutInit(&argc, argv);

    /* Display mode requests */
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    /* Start with 500x500 px window */
    glutInitWindowSize(500, 700);

    /* Create window with name */
    glutCreateWindow("Xuedan Fillmore | Assignment 2");

    /* register 'display' as scene drawing fn */
    glutDisplayFunc(display);

    /* register 'reshape' as window resizing fn */
    glutReshapeFunc(reshape);

    /* register key bindings for keyboard and arrows */
    glutSpecialFunc(specialkeybindings);
    glutKeyboardFunc(keybindings);

    /* Pass control to GLUT for user interaction */
    glutMainLoop();

    return 0;
}