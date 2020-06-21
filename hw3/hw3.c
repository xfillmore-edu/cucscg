/*
 *
 * Xuedan Fillmore
 * CSCI 4229 Computer Graphics
 * Assignment 3 lighting & texture
 *
 * See README for key bindings
 *
 * https://github.com/mattearly/TheOnlyEscapeIsESC/blob/master/code/camera.h
 * https://www.tomdalling.com/blog/modern-opengl/04-cameras-vectors-and-input/
 */


#include "config.h"
#include "bmbObjects.h"

/* global variables */
int theta = -45; /* azimuth (left/right) angle */
int phi = 0; /* elevation (up/down) angle */
unsigned int textures[2]; /* array holding texture references */
unsigned int curtex = 0; /* current texture */
int dim = 30; /* dimension / world size */
int aspr = 1; /* aspect ratio (viewport/window) */
int fov = 60; /* field of view */
/* eye/camera position starting coordinates (perspective mode) */
double camx, camy, camz;
// double camx = 10;
// double camy = 5;
// double camz = 10;
/* facing direction coordinates (perspective mode) */
int dirx = 0;
int diry = 15; /* take the sind of this angle */
int dirz = 0;
bool viewmode = 1; /* 1st person perspective ~ orthographic */
int ambient = 10; /* percent ambient intensity */
int diffuse = 50; /* percent diffuse intensity */
int specular = 0; /* percent specular (reflective spot) intensity */
int shininess = 0; /* pow2 shininess */
int emission = 0; /* percent emission intensity */
int lposy = 15; /* height of light source */
int lposxz = 0; /* radial position of light */

void lightsrc()
{
    int th, ph;
    float emis[] = {0.0, 0.0, 0.01 * emission, 1.0};

    /* save current transformations */
    glPushMatrix();
    /*  Offset, scale and rotate */
    glTranslated(x,y,z);
    glScaled(0.3, 0.3, 0.3);
    //  White ball
    glColor3f(1,1,1);
    glMaterialf(GL_FRONT,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
    glMaterialfv(GL_FRONT,GL_EMISSION,emis);
    
    /* the polygon itself */
    glBegin(GL_TRIANGLE_STRIP);
    
    glEnd();

    //  Undo transofrmations
    glPopMatrix();
}

/* display function called by GLUT */
void display()
{
    /* Clear current image */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /* Reset prior transformations */
    glLoadIdentity();
    /* Allow z-buffer */
    glEnable(GL_DEPTH_TEST);

    /* View mode specific settings and text panel */
    glColor3f(0.8, 0.8, 0.8); /* make text white */
    if (viewmode)
    {
        camx = (dim/2); //* sind(theta) * cosd(phi);
        // camy = (dim/2); //* sind(phi);
        camy = 15;
        camz = (dim/2); //* cosd(theta) * cosd(phi);

        dirx = cosd(theta) * cosd(phi);
        diry = sind(phi);
        dirz = sind(theta) * cos(phi);

        /* cross product */
        double upx = camy * dirz - camz * diry;
        double upy = camz * dirx - camx * dirz;
        double upz = camx * diry - camy * dirx;
        /* normalize each */
        /* written with help from https://stackoverflow.com/a/28490779 */
        double uplen = sqrt(upx*upx + upy*upy + upz*upz);
        upx /= uplen;
        upy /= uplen;
        upz /= uplen;

        /* set current view */
        gluLookAt(camx, camy, camz, dirx, diry, dirz, 0, cosd(phi), 0);

        /* display viewing settings */
        glWindowPos2i(5, 35);
        gprint("Current eye position: (%.1f, %.1f, %.1f)", camx, camy, camz);
        glWindowPos2i(5, 20);
        gprint("Looking at: (%.1f, %.1f, %.1f)", dirx, diry, dirz);
        glWindowPos2i(5, 5);
        gprint("1st Person Perspective Projection (FOV %.1f)", fov);
    }
    else
    {
        /* set current view */
        glRotatef(phi,   1, 0, 0);
        glRotatef(theta, 0, 1, 0);

        /* display viewing settings */
        glWindowPos2i(5, 20);
        gprint("Viewing Angle: (%d, %d)", theta, phi);
        glWindowPos2i(5, 5);
        gprint("Orthographic Projection");
    }
    checkErrs("display::setup");

    /* set light in scene */
    /* derived from ex13.c */
    //  Translate intensity to color vectors
    float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
    float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
    float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
    //  Light position
    float Position[]  = {distance*Cos(lposxz), lposy, distance*Sin(lposxz),1.0};
    //  Draw light position as ball (still no lighting here)
    glColor3f(1,1,1);
    lightsrc(Position[0],Position[1],Position[2] , 0.1);
    //  OpenGL should normalize normal vectors
    glEnable(GL_NORMALIZE);
    //  Enable lighting
    glEnable(GL_LIGHTING);
    //  Location of viewer for specular calculations
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,local);
    //  glColor sets ambient and diffuse color materials
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    //  Enable light 0
    glEnable(GL_LIGHT0);
    //  Set ambient, diffuse, specular components and position of light 0
    glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
    glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
    glLightfv(GL_LIGHT0,GL_POSITION,Position);

    checkErrs("display::lighting");

    /* enable texture application */
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    /* DRAW FLOOR */
    double qrep = 2.0 / 16; /* repeated quad vertices for lighting */
    int maxgrid = 40;
    glColor3f(1.0, 1.0, 1.0);
    glNormal3f(0, 1, 0); /* straight up */
    /* select ground texture */
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glBegin(GL_QUADS);
    /* build matrix of quads */
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            glTexCoord2d(qrep * (i),   qrep * (j)  ); glVertex3d(maxgrid * qrep * (i)  -maxgrid, 0, maxgrid * qrep * (j)  -maxgrid);
            glTexCoord2d(qrep * (i+1), qrep * (j)  ); glVertex3d(maxgrid * qrep * (i+1)-maxgrid, 0, maxgrid * qrep * (j)  -maxgrid);
            glTexCoord2d(qrep * (i+1), qrep * (j+1)); glVertex3d(maxgrid * qrep * (i+1)-maxgrid, 0, maxgrid * qrep * (j+1)-maxgrid);
            glTexCoord2d(qrep * (i),   qrep * (j+1)); glVertex3d(maxgrid * qrep * (i)  -maxgrid, 0, maxgrid * qrep * (j+1)-maxgrid);
        }
    }
    glEnd();
    checkErrs("display::floor");
    /* END OF FLOOR */

    double height = 20;
    double radius = 0.5;
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    cylinder(0, 0, 0, height, radius, 0xffffff);

    glDisable(GL_TEXTURE_2D);

    checkErrs("display");
    glFlush();
    glutSwapBuffers();
}

/* called by GLUT when a standard key is pressed */
/* KEYBINDINGS
 * q or ESC (27, 113) quit/close program
 * 0        (0)       reset view in the current mode
 * wasd
 * ijkl
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
    else if (key == 112) /* p - switch projection mode */
    {
        viewmode = !viewmode;
        if (viewmode)
        {
            fov = 60;
            dim = 30;
            camx = 10;
            camy = 15;
            camz = 10;
            dirx = 0;
            diry = 15;
            dirz = 0;
        }
        else
        {
            fov = 0;
            theta = -5;
            phi = 20;
        }
    }
    else if (key == 0)
    {
        if (viewmode)
        {
            fov = 60;
            dim = 30;

        }
        else
        {
            fov = 0;
            theta = -5;
            phi = 20;
        }
    }
    else if (viewmode && (key == 119 || key == 97 || key == 115 || key == 100))
    { /* w, a, s, d lateral movement of camera/eye */
        switch (key)
        {
            case 119: /* w - lateral forward */
                break;
            case 115: /* s - lateral backward */
                break;
            case 97:  /* a - lateral left */
                break;
            case 100: /* d - lateral right */
                break;
        }
    }
    /* "rotate" view by actually translating the entire scene? */
    else if (viewmode && (key >= 105 && key <= 108))
    { /* i, j, k, l angular rotation of view */
        switch (key)
        {
            case 105: /* i - angular up */
                phi += 2.5;
                break;
            case 107: /* k - angular down */
                phi -= 2.5;
                break;
            case 106: /* j - angular left */
                break;
            case 108: /* l - angular right */
                break;
        }
    }

    /* tell glut to redisplay after key press */
    project(fov, aspr, dim);
    glutPostRedisplay();
}

void specialkeybindings(int key, int xpos, int ypos)
{
    if (!viewmode)
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
    }
    

    /* update projection */
    project(fov, aspr, dim);
    /* redisplay scene */
    glutPostRedisplay();
}

void reshape(int width, int height)
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
    glutInitWindowSize(500, 500);

    /* Create window with name */
    glutCreateWindow("Xuedan Fillmore | Assignment 3");

    /* register 'display' as scene drawing fn */
    glutDisplayFunc(display);

    /* register 'reshape' as window resizing fn */
    glutReshapeFunc(reshape);

    /* register key bindings for keyboard and arrows */
    glutSpecialFunc(specialkeybindings);
    glutKeyboardFunc(keybindings);

    /* load texture files to be used */
    textures[0] = loadTexture("bmbstalk2.bmp");
    textures[1] = loadTexture("texground.bmp");

    /* check for initialization/texture loading errors */
    checkErrs("main");

    /* Pass control to GLUT for user interaction */
    glutMainLoop();

    return 0;
}