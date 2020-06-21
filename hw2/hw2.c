/*
 *
 * Xuedan Fillmore
 * CSCI 4229 Computer Graphics
 * Assignment 2 3d scene
 *
 * See README for key bindings
 *
 * With help from
 * http://www.lighthouse3d.com/tutorials/glut-tutorial/keyboard-example-moving-around-the-world/
 */

#include "bmbObjects.h"
#include "config.h"

/* global variables */
int alpha    = 0;  /* view angle longitude */
int beta     = 10;  /* view angle latitude */
int viewmode = 0;  /* viewing mode (use p to switch) */
int objmode  = 1;  /* which object(s) to view */
int fov      = 0; /* field of view, perspective */
double aspr  = 1;  /* aspect ratio */
double dim   = 40; /* dimension - world size */
double camx  = 15;
double camy  = 5;
double camz  = 15; /* eye pos */
double dirx  = 0;
double diry  = 6;
double dirz  = 0; /* facing pos */
float movspeed = 0.4;

char* vmode()
{
    if      (viewmode == 0) return "Orthogonal";
    else if (viewmode == 1) return "Perspective";
    else if (viewmode == 2) return "1st Person";
    return "";
}
char* omode()
{
    if      (objmode == 1) return "Bamboo Stalk";
    else if (objmode == 2) return "Cylinder";
    else if (objmode == 3) return "Cone";
    else if (objmode == 4) return "Rhombohedron";
    else if (objmode == 5) return "Leaf";
    return "";
}

/* some parts reused from hw1 */
void display()
{
    /* Clear current image */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /* Reset prior transformations */
    glLoadIdentity();

    /* copied from ex9 */
    /* http://www.opengl-tutorial.org/beginners-tutorials/tutorial-6-keyboard-and-mouse/ */
    if (viewmode == 1) /* set view for perspective projection */
    {
        camx = -2 * dim * sind(alpha) * cosd(beta);
        camy =  2 * dim               * sind(beta);
        camz =  2 * dim * cosd(alpha) * cosd(beta);

        /* gluLookAt args:
         * eye x, eye y, eye z (cam pos)
         * ref x, ref y, ref z (reference viewing point)
         * up x, up y, up z (dir of up vec)
         */
        gluLookAt(camx, camy, camz, 0, 0, 0, 0, cosd(beta), 0);
    }
    else if (viewmode == 2)
    {
        // camx = dim * cosd(alpha) * sind(beta);
        // camy = dim * sind(alpha) * sind(beta);
        // camz = dim * cosd(beta);
        dirx = sind(alpha);
        // diry = 5*cosd(beta);
        dirz = -cosd(alpha);

        gluLookAt(camx, camy, camz, dirx, diry, dirz, 0, cosd(beta), 0);

    }
    else /* set view for orthogonal projection */
    {
        glRotatef(beta,1,0,0);
        glRotatef(alpha,0,1,0);
    }

    /* Allow z-buffer */
    glEnable(GL_DEPTH_TEST);

    glColor3f(0.8, 0.8, 0.8);
    if (viewmode == 2)
    {
        glWindowPos2i(5, 35);
        gprint("Eye position: (%.1f, %.1f, %.1f)", camx, camy, camz);
    }
    glWindowPos2i(5, 20);
    gprint("Viewing Angle: (%d, %d)", alpha, beta);
    glWindowPos2i(5, 5);
    // gprint("View Mode: %s (FOV %d)", viewmode?"Perspective":"Orthographic", fov);
    gprint("View Mode: %s  Object: %s  FOV: %d", vmode(), omode(), fov);

    /* switch between viewing objects */
    double height = 6.0;
    double radius = 2.0;
    double dr = radius * 1.2;
    double dh = height/8.0;
    switch (objmode)
    {
        case 1: /* bamboo stalk built from top to bottom */
            /* Draw Floor */
            glColor3f(122.0/rgbmax, 88.0/rgbmax, 40.0/rgbmax); /* brown */
            glBegin(GL_QUADS);
            glVertex3d(-40, 0, -40);
            glVertex3d( 40, 0, -40);
            glVertex3d( 40, 0,  40);
            glVertex3d(-40, 0,  40);
            glEnd();

            cylinder(0, 3*height+3*dh, 0, height, radius, 1);
            cylinder(0, 3*height+2*dh, 0, dh,     dr,     0);
            cylinder(0, 2*height+2*dh, 0, height, radius, 1);
            cylinder(0, 2*height+dh,   0, dh,     dr,     0);
            cylinder(0, height+dh,     0, height, radius, 1);
            cylinder(0, height,        0, dh,     dr,     0);
            cylinder(0, 0,             0, height, radius, 1);

            break;
        case 2: /* cylinder */
            cylinder (0, 0, 0, 15, 5, 1);
            break;
        case 3: /* cone */
            cone(-2.5, -2.5, -2.5, 15, 5, 135, 45);
            break;
        case 4: /* rhombohedron */
            rhombohedron(0, 4, 0, 10);
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
    { /* p */
        viewmode++;
        viewmode %= 3;
        if (viewmode)
        { /* reset fov */
            fov = 60;
            camx = 15;
            camy = 5;
            camz = 15;
        }
        else
        { /* reset fov to 0 bc doesn't matter */
            fov = 0;
        }
    }
    else if ((viewmode == 2) && (key == 119 || key == 97 || key == 115 || key == 100))
    {
        switch (key)
        { /* need cross products for a, s / lateral movement? */
            case 119: /* w - move forward */
                camx += dirx * movspeed;
                camz += dirz * movspeed;
                break;
            case 97: /* a - move laterally left */
                camx -= dirx * movspeed;
                camz += dirz * movspeed;
                break;
            case 115: /* s - move backwards */
                camx -= dirx * movspeed;
                camz -= dirz * movspeed;
                break;
            case 100: /* d - move laterally right */
                camx += dirx * movspeed;
                camz -= dirz * movspeed;
                break;
        }
    }
    else if ((viewmode != 0) && (key == 70))
    { /* upper case F */
        fov++;
    }
    else if ((viewmode != 0) && (key == 102))
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
            dirx = 3 * abs(sind(alpha)); /* circulates back around..... no bueno */
            dirz = 3 * -abs(cosd(alpha));
            break;
        case GLUT_KEY_LEFT:
            alpha -= 5;      /* decrease longitudinal view 5 deg */
            dirx = -3 * abs(sind(alpha));
            dirz = -3 * -abs(cosd(alpha));
            break;
        case GLUT_KEY_UP:
            beta += 5;       /* increase latitudinal view 5 deg */
            diry += 3;
            if ((viewmode==2) && (diry > 80 || beta > 80))
            {
                diry = 80;
                beta = 80;
            }
            break;
        case GLUT_KEY_DOWN:
            beta -= 5;       /* decrease latitudinal view 5 deg */
            diry -= 3;
            if ((viewmode==2) && (diry < -10 || beta < -70))
            {
                diry = -10;
                beta = -70;
            }
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