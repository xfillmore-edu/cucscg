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
 * KEYSITE https://thepentamollisproject.blogspot.com/2018/02/setting-up-first-person-camera-in.html
 */


#include "config.h"
#include "bmbObjects.h"

/* global variables */
int theta = 0; /* azimuth (left/right) angle */
int phi   = 0; /* elevation (up/down) angle */
unsigned int textures[2]; /* array holding texture references */
unsigned int curtex = 0; /* current texture */
int dim  = 30; /* dimension / world size */
int aspr = 1; /* aspect ratio (viewport/window) */
int fov  = 60; /* field of view */
double camx = 0; /* x eye pos (perspective) */
double camy = 5; /* constant view height (perspective) */
double camz = 10; /* z eye pos (perspective) */
bool viewmode = 1; /* 1st person perspective ~ orthographic */
int ambient   = 10; /* percent ambient intensity */
int diffuse   = 50; /* percent diffuse intensity */
int specular  = 0; /* percent specular (reflective spot) intensity */
int shininess = 0; /* pow2 shininess */
int emission  = 100; /* percent emission intensity */
int lposy     = 5; /* height of light source */
int lposxz    = 0; /* radial position of light */

/* create the scene's source of "sunlight" */
/* derived from ex13.c */
void lightsrc(double xposl, double yposl, double zposl)
{
    float emis[] = {0.0, 0.0, 0.01 * emission, 1.0};
    float ylwcorrection[] = {1.0, 1.0, 0.0, 1.0};

    /* save current transformations */
    glPushMatrix();
    /*  Offset, scale and rotate */
    glTranslated(xposl, yposl, zposl);
    glScaled(0.1, 0.1, 0.1);
    //  White ball
    glColor3f(1,1,1);
    glMaterialfv(GL_FRONT,GL_SPECULAR, ylwcorrection);
    glMaterialfv(GL_FRONT,GL_EMISSION, emis);
    
    /* the polygon (tetrahedron) itself */
    /* coordinates assumed from https://en.wikipedia.org/wiki/Tetrahedron */
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3d( 0.9428,       0, -0.3333);
    glVertex3d(-0.4714,  0.8165, -0.3333);
    glVertex3d(-0.4714, -0.8165, -0.3333); /* 3rd vertex close 1st side */
    glVertex3d(      0,       0,       1); /* 4th vertex close 2nd side */
    glVertex3d(-0.4714,  0.8165, -0.3333); /* repeat 2nd vertex to close 3rd side */
    glVertex3d(-0.4714, -0.8165, -0.3333); /* repeat 3rd vertex to close 4th side */
    glEnd();

    /* replace transofrmations */
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
    glColor3f(0.8, 0.8, 0.8); /* make text light grey */
    if (viewmode)
    {
        /* set current view */
        /* derived from walkthrough at KEYSITE */
        glRotatef(-phi,   1, 0, 0);
        glRotatef(-theta, 0, 1, 0);
        glTranslatef(-camx, -camy, -camz);

        glWindowPos2i(5, 5);
        gprint("1st Person Perspective Projection (FOV %d)", fov);
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
    /*  Translate intensity to rgba color vectors */
    float Ambient[]  = {0.01*ambient,  0.01*ambient,  0.01*ambient,  1.0};
    float Diffuse[]  = {0.01*diffuse,  0.01*diffuse,  0.01*diffuse,  1.0};
    float Specular[] = {0.01*specular, 0.01*specular, 0.01*specular, 1.0};
    //  Light position
    float lightposition[] = {dim * cosd(lposxz) /3, lposy, dim * sind(lposxz) /3, 1.0};
    /* draw source object for the light */
    lightsrc(lightposition[0], lightposition[1], lightposition[2]);
    /*  Tell OpenGL to normalize normal vectors */
    glEnable(GL_NORMALIZE);
    /* Enable lighting */
    glEnable(GL_LIGHTING);
    /* set ambient and diffuse color materials */
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    /* Enable light 0 */
    glEnable(GL_LIGHT0);
    /* Set ambient, diffuse, specular components and position of light 0 */
    glLightfv(GL_LIGHT0, GL_AMBIENT,  Ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  Diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, Specular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightposition);

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

    /* bamboo stalk ~ more sections for more vertices */
    double height = 1;
    double radius = 0.5;
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    cylinder(0, 5*height, 0, height, radius, 0xffffff);
    cylinder(0, 4*height, 0, height, radius, 0xffffff);
    cylinder(0, 3*height, 0, height, radius, 0xffffff);
    cylinder(0, 2*height, 0, height, radius, 0xffffff);
    cylinder(0,   height, 0, height, radius, 0xffffff);
    cylinder(0, 0,        0, height, radius, 0xffffff);

    checkErrs("display::objects");

    /* disable individual aspects of scene */
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);

    checkErrs("display");
    glFlush();
    project(fov, aspr, dim);
    glutSwapBuffers();
}

/* called by GLUT when a standard key is pressed */
/* KEYBINDINGS
 * q or ESC (27, 113) quit/close program
 * r        (114)     reset view in the current mode
 * wasd     (119, 97, 115, 100)  change lateral position
 * ijkl     (105, 106, 107, 108) change angular perspective
 * f/F      (102, 70) decrease/increase field of view
 * +/-      (43, 45)  increase/decrease dimension
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
            camx = 0;
            camy = 5;
            camz = 10;
        }
        else
        {
            fov = 0;
            theta = -5;
            phi = 20;
        }
    }
    else if (key == 114) /* r - reset scene */
    {
        if (viewmode)
        {
            fov = 60;
            dim = 30;
            phi = 0;
            theta = 0;
        }
        else
        {
            fov = 0;
            theta = -5;
            phi = 20;
            dim = 30;
        }
    }
    else if (viewmode && (key == 119 || key == 97 || key == 115 || key == 100))
    { /* w, a, s, d lateral movement of camera/eye */
        /* derived from tutorial at KEYSITE (Pentamollis Project) */
        float movspeed = 2.0;
        switch (key)
        {
            case 119: /* w - lateral forward */
                camx += cosd(theta+90) / movspeed;
                camz -= sind(theta+90) / movspeed;
                break;
            case 115: /* s - lateral backward */
                camx += cosd(theta+270) / movspeed;
                camz -= sind(theta+270) / movspeed;
                break;
            case 97:  /* a - lateral left */
                camx += cosd(theta+180) / movspeed;
                camz -= sind(theta+180) / movspeed;
                break;
            case 100: /* d - lateral right */
                camx += cosd(theta) / movspeed;
                camz -= sind(theta) / movspeed;
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
                if (phi > 70) phi = 70;
                break;
            case 107: /* k - angular down */
                phi -= 2.5;
                if (phi < -60) phi = -60;
                break;
            case 106: /* j - angular left */
                theta += 2.5;
                break;
            case 108: /* l - angular right */
                theta -= 2.5;
                break;
        }
    }
    else if (viewmode && (key == 102 || key == 70))
    { /* f/F increase/decrease field of view */
        if (key == 102)
        {
            fov -= 2;
        }
        else
        {
            fov += 2;
        }

        /* maintain reasonable fov range */
        if (fov < 45) fov = 46;
        if (fov > 81) fov = 80;
    }
    else if (!viewmode && (key == 43 || key == 45))
    { /* +/- increase/decrease dimension/zoom */
        if (key == 43)
        { /* plus key */
            dim += 2;
        }
        else
        { /* minus key */
            dim -= 2;
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

/* run this function when no key presses are happening */
/* copied from ex13.c */
void idle()
{
    /* elapsed time, seconds */
    double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
    lposxz = fmod(90*t, 360.0);

    /* redisplay scene (light is moving) */
    glutPostRedisplay();
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

    /* idle function */
    glutIdleFunc(idle);

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