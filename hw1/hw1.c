/*
 *
 * Xuedan Fillmore
 * CSCI 4229 Computer Graphics
 * Assignment 1 Lorenz Attractor
 *
 * See README for key bindings
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

#define GL_GLEXT_PROTOTYPES

/* Cross-OS Compatability */
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/* Macros */
#define sind(x) (sin((x) * 3.1415927 / 180)) /* sine degree evaluation */
#define cosd(x) (cos((x) * 3.1415927 / 180)) /* cosine degree evaluation */

/* Global Variables */
#define MAXSTRLEN 8192
double sigma = 10; /* Prandtl number */
double b     = 2.6666; /* geometric factor */
double r     = 28;
double dt    = 0.001;
int    theta = -45;
int    phi   = 25;
double axis  = 1; /* +X, -X, +Y, -Y, +Z, -Z */


/* Error checking Function */
/* Code derived directly from ex5 */
void checkErrs (char* fn)
{
    int err = glGetError();
    if (err)
    {
        fprintf (stderr, "ERROR: %s in function <%s>.\n", gluErrorString(err), fn);
    }
}

/* Text output routine */
/* Code derived directly from ex6, ex7 */
/* variadic - #include stdarg.h */
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
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *ch++);
    }
}


/* Display scene */
/* Built based on ex5-7 and lorenz.c code */
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

    /* Draw and label X, Y, and Z axes */
    glColor3f(0.8, 0.8, 0.8); /* light grey */
    glBegin(GL_LINES);   /* connects each pair of specified vertices */
    glVertex3d(0, 0, 0); /* x begin */
    glVertex3d(1, 0, 0); /* x end   */
    glVertex3d(0, 0, 0); /* y begin */
    glVertex3d(0, 1, 0); /* y end   */
    glVertex3d(0, 0, 0); /* z begin */
    glVertex3d(0, 0, 1); /* z end   */
    glEnd();
    glRasterPos3d(1.1, 0, 0);
    gprint("X");
    glRasterPos3d(0, 1.1, 0);
    gprint("Y");
    glRasterPos3d(0, 0, 1.1);
    gprint("Z");

    /* Calculate and render lorenz values */


    /* Display current parameters in lower left corner */
    glWindowPos2i(5, 20);
    gprint("Viewing from (%d, %d) deg, Time Step dt=%.3d", theta, phi, dt);
    glWindowPos2i(5, 5);
    gprint("Lorenz Params s=%d b=%.4d r=%d", sigma, b, r);


    /* Cleanup */
    checkErrs("display");
    glFlush();
    glutSwapBuffers();
}


/* Called by GLUT when normal key is pressed */
/* Derived from ex6 */
/* BOUND KEYS
 * x         (120)   view from +X axis
 * X         (88)    view from -X axis
 * y         (121)   view from +Y axis 
 * Y         (89)    view from -Y axis
 * z         (122)   view from +Z axis
 * Z         (90)    view from -Z axis
 * s         (115)   decrease s parameter
 * S         (83)    increase s parameter
 * b         (98)    decrease b parameter
 * B         (66)    increase b parameter
 * r         (114)   decrease r parameter
 * R         (82)    increase r parameter
 * t         (116)   decrease time step
 * T         (84)    increase time step
 * e         (101)   erase modifications (reset view)
 * q or ESC  (113,27) quit program / exit display window
 */
/* key refers to the input character */
/* xpos, ypos record cursor position; not relevant here */
void keybindings(unsigned char key, int xpos, int ypos)
{
    /* exit - q or ESC */
    if (key == 27 || key == 113)
    {
        exit(0);
    }

    /* Redisplay scene */
    glutPostRedisplay();
}

/* Called by GLUT when an arrow key is pressed */
/* Directly derived from ex6 */
/* xpos, ypos record cursor position. Not relevant here */
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

/* GLUT window resized adjuster routine */
/* Directly derived from ex6 */
void winadjust(int width, int height)
{
    /* ratio width:height */
    double wh_ratio = (height > 0) ? (double)width/height : 1;
    /* dimension of orthogonal box */
    double dim = 2;

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

/* Initialize GLUT and register functions */
/* Directly derived from ex6 */
int main(int argc, char* argv[])
{
    /* Initialize GLUT, process user params */
    glutInit(&argc, argv);

    /* Display mode requests */
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    /* Start with 500x500 px window */
    glutInitWindowSize(500, 500);

    /* Create window with name */
    glutCreateWindow("Xuedan Fillmore | Assignment 1");

    /* register 'display' as scene drawing fn */
    glutDisplayFunc(display);

    /* register 'winadjust' as window resizing fn */
    glutReshapeFunc(winadjust);

    /* register key bindings for keyboard and arrows */
    glutSpecialFunc(specialkeybindings);
    glutKeyboardFunc(keybindings);

    /* Pass control to GLUT for user interaction */
    glutMainLoop();

    return 0;
}