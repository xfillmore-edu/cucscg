/*
 *
 * Xuedan Fillmore
 * CSCI 4229 Computer Graphics
 * Assignment 2 3d scene
 *
 * See README for key bindings
 *
 */

#include "bmbObjects.h"
#include "config.h"

/* global variables */
int alpha    = 0;  /* view angle longitude */
int beta     = 0;  /* view angle latitude */
int viewmode = 0;  /* viewing mode (use p to switch) */
int objmode  = 1;  /* which object(s) to view */
int fov      = 0; /* field of view, perspective */
double aspr  = 1;  /* aspect ratio */
double dim   = 40; /* dimension - world size */
double Ex, Ey, Ez;

/* * * * * * * * * * * * * * * * * * *
 *        S H A P E S
 * * * * * * * * * * * * * * * * * * */

/* some parts reused from hw1 */
void display()
{
    /* Clear current image */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /* Reset prior transformations */
    glLoadIdentity();

    /* copied from ex9 */
    /* http://www.opengl-tutorial.org/beginners-tutorials/tutorial-6-keyboard-and-mouse/ */
    if (viewmode) /* set view for perspective projection */
    {
        Ex = -2 * dim * sind(alpha) * cosd(beta);
        Ey =  2 * dim               * sind(beta);
        Ez =  2 * dim * cosd(alpha) * cosd(beta);
        gluLookAt(Ex, Ey, Ez, 0, 0, 0, 0, cosd(beta), 0);
    }
    else /* set view for orthogonal projection */
    {
        glRotatef(beta,1,0,0);
        glRotatef(alpha,0,1,0);
    }

    /* Allow z-buffer */
    glEnable(GL_DEPTH_TEST);

    /* TEMPORARY - to show relative positioning of objects */
    /* Draw and label X, Y, and Z axes */
    int ax = 20;
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

    glWindowPos2i(5, 20);
    gprint("Viewing Angle: (%d, %d)", alpha, beta);
    glWindowPos2i(5, 5);
    gprint("View Mode: %s (FOV %d)", viewmode?"Perspective":"Orthographic", fov);

    /* switch between viewing objects */
    switch (objmode)
    {
        case 1: /* bamboo stalk */
            cylinder(1, 10 + 4/10, 1, 10, 4);
            rhombohedron(1, 10, 1, 4);
            cylinder(1, 0, 1, 10, 4);
            break;
        case 2: /* cylinder */
            cylinder (0, 0, 0, 5, 1);
            break;
        case 3: /* cone */
            cone(-2.5, -2.5, -2.5, 5, 1, 135, 45);
            break;
        case 4: /* rhombohedron */
            rhombohedron(0, 1, 0, 2);
            break;
        /* case 5 ~ leaf, case 6 ~ forest */
    }
    
    
    

    /* Cleanup */
    checkErrs("display");
    glutSwapBuffers();
}

/* called by GLUT when a standard key is pressed */
/* KEYBINDINGS
 * q or ESC (27, 113) quit/close program
 * p        (112)     switch between projection modes
 * 1-4      (49-52)   switch between viewable objects
 * wasd     (119, 97, 115, 100) 
 * f/F      (70,102)  increase/decrease fov
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 */
/* key refers to the input character */
/* xpos and ypos record mouse position at key input */
void keybindings(unsigned char key, int xpos, int ypos)
{
    /* exit - q or ESC */
    if (key == 27 || key == 113)
    {
        exit(0);
    }
    /* switch between orthogonal, perspective, and 1st person projections */
    else if (key == 112)
    {
        viewmode++;
        viewmode %= 3;
        if (viewmode)
        { /* reset fov */
            fov = 60;
        }
        else
        { /* reset fov to 0 bc doesn't matter */
            fov = 0;
        }
    }
    else if ((key > 48) || (key < 53))
    {
        switch(key)
        {
            case 49: /* (1) single bamboo stalk */
                objmode = 1;
                break;
            case 50: /* (2) cylinder */
                objmode = 2;
                break;
            case 51: /* (3) rhombohedron */
                objmode = 3;
                break;
            case 52: /* (4) cone */
                objmode = 4;
                break;
            
            /* for future use probably */
            // case 53: /* (5) leaf */
            //     objmode = 5;
            //     break;
            // case 54: /* (6) single bamboo stalk */
            //     objmode = 6;
            //     break;

        }
    }
    else if (key == 119 || key == 97 || key == 115 || key == 100)
    {
        switch (key)
        {
            case 119: /* w - move forward */
                break;
            case 97: /* a - move laterally left */
                break;
            case 115: /* s - move laterally right */
                break;
            case 100: /* d - move backwards */
                break;
        }
    }
    else if (key == 70)
    { /* upper case F */
        fov++;
    }
    else if (key == 102)
    { /* lower case f */
        fov--;
    }
    else if (key == 43)
    { /* plus key */
        dim++;
    }
    else if (key == 45)
    { /* minus key */
        dim--;
    }

    /* update projection/redisplay scene */
    project(fov, aspr, dim);
    glutPostRedisplay();
}

/* arrow functionalities different based on projection mode */
void specialkeybindings(int key, int xpos, int ypos)
{
    switch(key)
    { /* azimuth ~ longitude / elevation ~ latitude */
        case GLUT_KEY_RIGHT:
            alpha += 5;      /* increase longitudinal view 5 deg */
            break;
        case GLUT_KEY_LEFT:
            alpha -= 5;      /* decrease longitudinal view 5 deg */
            break;
        case GLUT_KEY_UP:
            beta += 5;       /* increase latitudinal view 5 deg */
            if ((viewmode==2) && (beta > 55)) beta = 55;
            break;
        case GLUT_KEY_DOWN:
            beta -= 5;       /* decrease latitudinal view 5 deg */
            if ((viewmode==2) && (beta < 0)) beta = 0;
            break;
    }

    /* Maintain angle between 0 and 360 deg */
    alpha %= 360;
    beta  %= 360;

    /* update projection */
    project(fov, aspr, dim);
    /* redisplay scene */
    glutPostRedisplay();
}

/* window resize adjustment */
/* copied directly from hw1 */
/* needs adjustment for different projection types */
void reshape(int width, int height)
{
    /* ratio width:height */
    aspr = (height > 0) ? (double)width/height : 1;

    /* set viewport to entire window */
    glViewport(0, 0, width, height);

    /* update projection */
    project(fov, aspr, dim);
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

    /* Start with 700x500 px window */
    glutInitWindowSize(700, 500);

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