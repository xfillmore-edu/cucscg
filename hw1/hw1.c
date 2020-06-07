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
#include <stdbool.h>
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
#define bool2str(bvar) (bvar ? "true" : "false") /* convert boolean true/false to string */

/* Global Variables */
#define MAXSTRLEN 8192
/* prandtl number - values for sigma (values from ScienceDirect) */
/* mercury, air, carbon disulfide, chloromethane, methanol, water, toluene, default 10, ethanol, argon, krypton */
double prandtl[11] = {0.03, 0.72, 2.36, 4.41, 6.83, 6.90, 7.26, 10.00, 18.05, 22.77, 673.68};
int    s     = 7; /* Prandtl nums array index */
/* rayleigh number - values for rho (values selected semi-randomly) */
double rayleigh[10] = {0.00, 5.00, 13.00, 14.00, 15.00, 24.74, 28.00, 99.96, 126.52, 1700};
int    r     = 6; /* index to Rayleigh nums array */
double beta  = 2.6666; /* geometric factor (constant, 8/3) */
double timesteps[] = {0.01, 0.001, 0.005, 0.0001};
int    t     = 1;
/* sets default viewing angle */
int    theta = -45;
int    phi   = 25;
bool   animate = false; /* animate point drawing for system */
int itersteps = 0;
double xcoord = 1;
double ycoord = 1;
double zcoord = 1;



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

/* function to perform animation stepping */
/* designed based on pentamollis project tutorial (YouTube) */
void timer(int filler)
{
    /* update entire display */
    double dt = timesteps[t];
    if ((itersteps < (50 / dt)) && animate)
    {
        int i = 0;
        double sigma = prandtl[s];
        double rho = rayleigh[r];
        float red[] = {1.0,1.0,1.0,0.0,0.0,0.0};
        float green[] = {0.0,0.5,1.0,1.0,1.0,0.0};
        float blue[] = {0.0,0.0,0.0,0.0,1.0,1.0};

        xcoord = ycoord = zcoord = 1;
        int imax = 50 / dt;

        glBegin(GL_LINE_STRIP);
        for (i = 0; (i < itersteps) && (itersteps < imax); i++)
        {
            double dx = sigma * (ycoord-xcoord);
            double dy = xcoord * (rho-zcoord) - ycoord;
            double dz = xcoord * ycoord - beta * zcoord;
            xcoord += dt * dx;
            ycoord += dt * dy;
            zcoord += dt * dz;

            /* Create point at calculated coordinates */
            glColor3f(red[i/1000], green[i/1000], blue[i/1000]);
            glVertex3d(xcoord, ycoord, zcoord);
        }
        glEnd();

        itersteps += 1;
        if (itersteps > (50/dt))
        {
            animate = false;
        }

        /* redisplay scene */
        glutPostRedisplay();
        /* register timer function to itself to loop at 60 fps */
        glutTimerFunc(1000.0/60.0, timer, 0);
    }
    else
    {
        animate = false;
        /* redisplay scene */
        glutPostRedisplay();
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
    int ax = 40;
    glColor3f(0.8, 0.8, 0.8); /* light grey */
    glBegin(GL_LINES);   /* connects each pair of specified vertices */
    glVertex3d(0, 0, 0);  /* x begin */
    glVertex3d(ax, 0, 0); /* x end   */
    glVertex3d(0, 0, 0);  /* y begin */
    glVertex3d(0, ax, 0); /* y end   */
    glVertex3d(0, 0, 0);  /* z begin */
    glVertex3d(0, 0, ax); /* z end   */
    glEnd();
    glRasterPos3d(ax, 0, 0);
    gprint("X");
    glRasterPos3d(0, ax, 0);
    gprint("Y");
    glRasterPos3d(0, 0, ax);
    gprint("Z");

    /* Display current parameters in lower left corner */
    double sigma = prandtl[s];
    double rho = rayleigh[r];
    double dt = timesteps[t];
    glWindowPos2i(5, 35);
    gprint("Animation on: %s", bool2str(animate));
    glWindowPos2i(5, 20);
    gprint("Viewing from (%d, %d) deg, Time Step dt=%.3f", theta, phi, dt);
    glWindowPos2i(5, 5);
    gprint("Lorenz Params s=%.2f b=%.4f r=%.2f, Initial condition (x,y,z)=(1,1,1)", sigma, beta, rho);

    /* Calculate and render lorenz values */
    /* Derived from PrinMath lorenz.c and Qt example lorenz.cpp */   
    if (!animate)
    {
        int i = 0;
        float red[] = {1.0,1.0,1.0,0.0,0.0,0.0};
        float green[] = {0.0,0.5,1.0,1.0,1.0,0.0};
        float blue[] = {0.0,0.0,0.0,0.0,1.0,1.0};

        xcoord = ycoord = zcoord = 1;

        glBegin(GL_LINE_STRIP);
        int imax = 50/dt; /* calculate number of steps for 50 time units */
        for (i = 0; i < imax; i++)
        {
            double dx = sigma * (ycoord-xcoord);
            double dy = xcoord * (rho-zcoord) - ycoord;
            double dz = xcoord * ycoord - beta * zcoord;
            xcoord += dt * dx;
            ycoord += dt * dy;
            zcoord += dt * dz;

            /* Create point at calculated coordinates */
            glColor3f(red[i/1000], green[i/1000], blue[i/1000]);
            glVertex3d(xcoord, ycoord, zcoord);
        }
        glEnd();
    }
    else
    {
        timer(itersteps);
    }

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
 * r         (114)   decrease r parameter
 * R         (82)    increase r parameter
 * t         (116)   decrease time step
 * T         (84)    increase time step
 * e         (101)   erase modifications (reset view)
 * a         (97)    toggle animation on/off
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
    /* view from +X axis - x */
    else if (key == 120)
    {
        theta = 90;
        phi   = 0;
    }
    /* view from -X axis - X */
    else if (key == 88)
    {
        theta = -90;
        phi   = 0;
    }
    /* view from +Y axis - y */
    else if (key == 121)
    {
        theta = 0;
        phi   = 90;
    }
    /* view from -Y axis - Y */
    else if (key == 89)
    {
        theta = 0;
        phi   = -90;
    }
    /* view from +Z axis - z */
    else if (key == 122)
    {
        theta = 0;
        phi   = 0;
    }
    /* view from -Z axis - Z */
    else if (key == 90)
    {
        theta = 180;
        phi   = 0;
    }
    /* reset to default/startup view and params - e */
    else if (key == 101)
    {
        theta = -45;
        phi   = 25;
        s = 7;
        r = 6;
        t = 1;
        animate = false;
    }
    /* decrease s parameter - s */
    else if (key == 115)
    {
        s -= 1;
        if (s < 0)
        {
            s = 10;
        }
    }
    /* increase s parameter - S */
    else if (key == 83)
    {
        s += 1;
        s %= 11;
    }
    /* decrease r parameter - r */
    else if (key == 114)
    {
        r -= 1;
        if (r < 0)
        {
            r = 9;
        }
    }
    /* increase r parameter - R */
    else if (key == 82)
    {
        r += 1;
        r %= 10;
    }
    /* increase time step - T */
    else if (key == 84)
    {
        t -= 1;
        if (t < 0)
        {
            t = 3;
        }
    }
    /* decrease time step - t */
    else if (key == 116)
    {
        t += 1;
        t %= 4;
    }
    /* toggle animation - a */
    else if (key == 97)
    {
        animate = !animate;
        if (animate)
        {
            itersteps = 0;
            glutTimerFunc(500, timer, 0);
        }
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

    /* register 'reshape' as window resizing fn */
    glutReshapeFunc(reshape);

    /* register key bindings for keyboard and arrows */
    glutSpecialFunc(specialkeybindings);
    glutKeyboardFunc(keybindings);

    /* Pass control to GLUT for user interaction */
    glutMainLoop();

    return 0;
}