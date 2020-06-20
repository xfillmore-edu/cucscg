/*
 *
 * Xuedan Fillmore
 * CSCI 4229 Computer Graphics
 * Assignment 3 lighting & texture
 *
 * See README for key bindings
 *
 */


#include "config.h"
#include "bmbObjects.h"

/* global variables */
int theta = 0;
int phi = 20;

unsigned int textures[];
unsigned int curtex = 0; /* current texture */

/* display function called by GLUT */
void display()
{
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, textures[curtex]);
}

/* called by GLUT when a standard key is pressed */
/* KEYBINDINGS
 * q or ESC (27, 113) quit/close program
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
}

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
            phi += 5;       /* increase latitudinal view 5 deg */
            break;
        case GLUT_KEY_DOWN:
            phi -= 5;       /* decrease latitudinal view 5 deg */
            break;
    }

    /* Maintain angle between 0 and 360 deg */
    theta %= 360;
    phi  %= 360;

    /* update projection */
    // project(fov, aspr, dim);
    /* redisplay scene */
    glutPostRedisplay();
}

void reshape()
{
    /* ratio width:height */
    aspr = (height > 0) ? (double)width/height : 1;

    /* set viewport to entire window */
    glViewport(0, 0, width, height);

    /* update projection */
    project(0, aspr, dim);
}

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

    /* load texture files to be used */
    textures[0] = loadTexture("bmbstalk1.bmp");

    /* check for initialization/texture loading errors */
    checkErrs("main");

    /* Pass control to GLUT for user interaction */
    glutMainLoop();

    return 0;
}