#include "twobjects.hpp"

// helper conversion macro for hex id color to RGB
// same color conversion code as in cvertex
void gColor3fHEX(unsigned int hexcolor)
{
    unsigned char red = ((hexcolor>>4) & 0x0000ff) / RGBMAX;
    unsigned char gre = ((hexcolor>>2) & 0x0000ff) / RGBMAX;
    unsigned char blu = ( hexcolor     & 0x0000ff) / RGBMAX;

    glColor3f((float)red, (float)gre, (float)blu);
}

// fboTypewriter helper function for building each key
void fboKey(float rad, unsigned int id)
{ // only key head, not pin 
    // build parameters
    int dd = 20;
    int th = 0;
    float keyHeight = 0.1;
    float pinHeight = 1.2;
    float keyTop = keyHeight + pinHeight;

    glPushMatrix();
    glScalef(rad, 1, rad);

    gColor3fHEX(id);

    // key top
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, keyTop, 0);
    for (th = 0; th <= 360; th++)
    {
        cvertex(th, keyTop, id);
    }
    glEnd();

    // key bottom
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, pinHeight, 0);
    for (th = 360; th >= 0; th-= dd)
    {
        cvertex(th, pinHeight, id);
    }
    glEnd();

    // key rim
    glBegin(GL_QUAD_STRIP);
    for (th = 0; th <= 360; th += dd)
    {
        cvertex(th, keyTop, id);
        cvertex(th, pinHeight, id);
    }
    glEnd();

    glPopMatrix();
}

// fboTypewriter helper function for drawing space bar
void fboSpace(unsigned int id)
{ // broken down from twobjects addKeySpace()
    glPushMatrix();

    // color id: 0x000021
    gColor3fHEX(id);

    float xleft = -4.6;
    float xright = 7;
    float ytop = 3.3;
    float ybtm = 3.2;
    float zfront = -0.8;
    float zback = -1.8;

    glBegin(GL_QUAD_STRIP); // 4 sides of rectangular prism
    
    glVertex3f(xleft,  ytop, zback);
    glVertex3f(xright, ytop, zback);

    glVertex3f(xleft,  ytop, zfront);
    glVertex3f(xright, ytop, zfront);

    glVertex3f(xleft,  ybtm, zfront);
    glVertex3f(xright, ybtm, zfront);

    glVertex3f(xleft,  ybtm, zback);
    glVertex3f(xright, ybtm, zback);

    glVertex3f(xleft,  ytop, zback);
    glVertex3f(xright, ytop, zback);

    glEnd();

    float zcen = -1.3;
    int th = 0;
    int dd = 20;

    // right rounded end
    glPushMatrix();
    glTranslatef(xright, 0, zcen);
    glRotatef(90, 0, 1, 0);
    glScalef(0.5, 1, 0.5);
    glBegin(GL_TRIANGLE_FAN); // top
    glVertex3f(0, ytop, 0);
    for (th = 0; th <= 180; th+=dd)
    {
        cvertex(th, ytop, id);
    }
    glEnd();
    glBegin(GL_TRIANGLE_FAN); // bottom
    glVertex3f(0, ybtm, 0);
    for (th = 180; th >= 0; th-=dd)
    {
        cvertex(th, ybtm, id);
    }
    glEnd();
    glBegin(GL_QUAD_STRIP); // rim
    for (th = 0; th <= 180; th += dd)
    {
        cvertex(th, ytop, id);
        cvertex(th, ybtm, id);
    }
    glEnd();
    glPopMatrix();

    // left rounded end
    glPushMatrix();
    glTranslatef(xleft, 0, zcen);
    glRotatef(-90, 0, 1, 0);
    glScalef(0.5, 1, 0.5);
    glBegin(GL_TRIANGLE_FAN); // top
    glVertex3f(0, ytop, 0);
    for (th = 0; th <= 180; th+=dd)
    {
        cvertex(th, ytop, id);
    }
    glEnd();
    glBegin(GL_TRIANGLE_FAN); // bottom
    glVertex3f(0, ybtm, 0);
    for (th = 180; th >= 0; th-=dd)
    {
        cvertex(th, ybtm, id);
    }
    glEnd();
    glBegin(GL_QUAD_STRIP); // rim
    for (th = 0; th <= 180; th += dd)
    {
        cvertex(th, ytop, id);
        cvertex(th, ybtm, id);
    }
    glEnd();
    glPopMatrix();


    glPopMatrix();
}

// fboTypewriter helperfunction for placing each key
void fboPlace(unsigned int id)
{
    // x y z pos copied from main addKey fn

    // defined row positions
    const float r1y = 2.5; // zxcvbnm
    const float r1z = -3.1;
    const float r2y = 3.0; // asdfghjkl
    const float r2z = -4.9;
    const float r3y = 3.5; // qwertyuiop
    const float r3z = -6.7;

    glPushMatrix();

    switch(id)
    {
        case 0x000001: // a
            glTranslatef(-5.9, r2y, r2z);
            fboKey(0.5, id);
            break;
        case 0x000002: // b
            glTranslatef(0.4, r1y, r1z);
            fboKey(0.5, id);
            break;
        case 0x000003: // c
            glTranslatef(-2.4, r1y, r1z);
            fboKey(0.5, id);
            break;
        case 0x000004: // d
            glTranslatef(-3.1, r2y, r2z);
            fboKey(0.5, id);
            break;
        case 0x000005: // e
            glTranslatef(-3.8, r3y, r3z);
            fboKey(0.5, id);
            break;
        case 0x000006: // f
            glTranslatef(-1.7, r2y, r2z);
            fboKey(0.5, id);
            break;
        case 0x000007: // g
            glTranslatef(-0.3, r2y, r2z);
            fboKey(0.5, id);
            break;
        case 0x000008: // h
            glTranslatef(1.1, r2y, r2z);
            fboKey(0.5, id);
            break;
        case 0x000009: // i
            glTranslatef(3.2, r3y, r3z);
            fboKey(0.5, id);
            break;
        case 0x00000a: // j
            glTranslatef(2.5, r2y, r2z);
            fboKey(0.5, id);
            break;
        case 0x00000b: // k
            glTranslatef(3.9, r2y, r2z);
            fboKey(0.5, id);
            break;
        case 0x00000c: // l
            glTranslatef(5.3, r2y, r2z);
            fboKey(0.5, id);
            break;
        case 0x00000d: // m
            glTranslatef(3.2, r1y, r1z);
            fboKey(0.5, id);
            break;
        case 0x00000e: // n
            glTranslatef(1.8, r1y, r1z);
            fboKey(0.5, id);
            break;
        case 0x00000f: // o
            glTranslatef(4.6, r3y, r3z);
            fboKey(0.5, id);
            break;
        case 0x000010: // p
            glTranslatef(6, r3y, r3z);
            fboKey(0.5, id);
            break;
        case 0x000011: // q
            glTranslatef(-6.6, r3y, r3z);
            fboKey(0.5, id);
            break;
        case 0x000012: // r
            glTranslatef(-2.4, r3y, r3z);
            fboKey(0.5, id);
            break;
        case 0x000013: // s
            glTranslatef(-4.5, r2y, r2z);
            fboKey(0.5, id);
            break;
        case 0x000014: // t
            glTranslatef(-1, r3y, r3z);
            fboKey(0.5, id);
            break;
        case 0x000015: // u
            glTranslatef(1.8, r3y, r3z);
            fboKey(0.5, id);
            break;
        case 0x000016: // v
            glTranslatef(-1, r1y, r1z);
            fboKey(0.5, id);
            break;
        case 0x000017: // w
            glTranslatef(-5.2, r3y, r3z);
            fboKey(0.5, id);
            break;
        case 0x000018: // x
            glTranslatef(-3.8, r1y, r1z);
            fboKey(0.5, id);
            break;
        case 0x000019: // y
            glTranslatef(0.4, r3y, r3z);
            fboKey(0.5, id);
            break;
        case 0x00001a: // z
            glTranslatef(-5.2, r1y, r1z);
            fboKey(0.5, id);
            break;
        case 0x00001b: // ?
            glTranslatef(6.7, r2y, r2z);
            fboKey(0.5, id);
            break;
        case 0x00001c: // ,
            glTranslatef(4.6, r1y, r1z);
            fboKey(0.5, id);
            break;
        case 0x00001d: // .
            glTranslatef(6, r1y, r1z);
            fboKey(0.5, id);
            break;
        case 0x00001e: // -
            glTranslatef(7.4, r1y, r1z);
            fboKey(0.5, id);
            break;
        case 0x00001f: // CAP
            glTranslatef(-6.8, r1y, -2.2);
            fboKey(0.7, id);
            break;
        case 0x000020: // FIG
            glTranslatef(-7.5, r2y, -4.4);
            fboKey(0.7, id);
            break;
        case 0x000021: // SPACE
            fboSpace(0x000021);
            
    }


    glPopMatrix();
}

void Typewriter::fboTypewriter()
{
    // ensure no lighting or textures
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    // render relevant keys in frame buffer for detection
    unsigned int pickColor; // increment through blues

    for (pickColor = 0x000001; pickColor <= 0x000021; pickColor++)
    {
        fboPlace(pickColor);
    }
}