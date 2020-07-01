#ifndef TWOBJECTS_HPP
#define TWOBJECTS_HPP

#define GL_GLEXT_PROTOTYPES

// Cross-OS compatability
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define PI 3.14159265358979
#define RGBMAX 255.0
#define MAXCHAR 66 // characters per line
#define MAXLINE 54 // lines per page

// RGB conversion call macro
#define gColor3fRGB(x, y, z) glColor3f(x/RGBMAX, y/RGBMAX, z/RGBMAX)

// Sine and Cosine conversion macros
#define sind(x) sinf(PI/180 * (x))
#define cosd(x) cosf(PI/180 * (x))

#include <cstring>
#include <cmath>
#include <cstdio>
#include <iomanip>

// Make keyboard complete motion whether holding or not
// Based on 

// look into opengl selection mode
// associates identifier with stored objects
// selection returns an identifier
// or look into glu Un project -- returns xyz coord

class Typewriter
{
    private:
        char* pContent[MAXLINE];
        void addKey(unsigned int character, unsigned int* textures);
        void addKeySpace(unsigned int tex);
        void twBody(unsigned int* textures);
        void twpTray();
    public:
        Typewriter();
        ~Typewriter();
        void buildTypewriter(unsigned int* textures);
        void fboTypewriter();
};

void cvertex(int th, double h, unsigned int hexcolor);

// Hex conversion macro
void gColor3fHEX(unsigned int hexcolor);



#endif
