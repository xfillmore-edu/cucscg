#include "twobjects.hpp"

float pinHeight = 1.2;
unsigned int white = 0xffffff;

// texture binding code written with help from
// https://stackoverflow.com/a/26536836

// helper function for drawing circular polygons
// takes args: current angle pos, current height pos, color in hex
// declared in header but not part of typewriter class
void cvertex(int th, double h, unsigned int hexcolor)
{
    // convert hex color to rgb colors
    unsigned char red   = ((hexcolor>>4) & 0x0000ff) / RGBMAX;
    unsigned char green = ((hexcolor>>2) & 0x0000ff) / RGBMAX;
    unsigned char blue  = ( hexcolor     & 0x0000ff) / RGBMAX;

    // apply color argument to polygon vertex
    glColor3f((float) red, (float) green, (float) blue);
    
    // place vertex
    glVertex3d(cosd(th), h, sind(th));
}

// helper construction function
// top of key body
void keyFace(bool type)
{
    // type argument refers to large or small key
    // true - std small key ~ false - large key

    int dd    = 20; // change in degrees ~ visual precision
    int theta = 0;  // current angle pos
    float radius;
    float keyHeight = 0.1;

    if (type) radius = 0.5; // qwerty and punctuation
    else radius = 0.7; // fig and cap

    // lighting effects 
    float shiny[] = {30};
    float whtsp[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT, GL_SHININESS, shiny);
    glMaterialfv(GL_FRONT, GL_SPECULAR, whtsp);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, whtsp);

    // save transformations 
    glPushMatrix();

    // final transformation for cylinder 
    glTranslatef(0, pinHeight, 0);
    glScalef(radius, 1, radius); // y is set at keyHeight

    // key top face (cylinder cap)
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, 1, 0);
    glColor3f(1.0, 1.0, 1.0);
    glTexCoord2f(0.5f, 0.5f);
    glVertex3f(0, keyHeight, 0);
    for (theta = 0; theta <= 360; theta += dd)
    {
        glNormal3f(0, 1, 0);
        glTexCoord2f(0.5f * sind(theta+90) + 0.5f, 0.5f * cosd(theta+90) + 0.5f);
        cvertex(theta, keyHeight, white);
    }
    glEnd();

    // replace transformations 
    glPopMatrix();
}

// helper construction function
// side and bottom of circular key body
void keyBody(bool type)
{
    // rim and bottom of key
    float theta = 0;
    float dd    = 20;
    float radius;
    float keyHeight = 0.1;

    if (type) radius = 0.5; // qwerty and punctuation
    else radius = 0.7; // fig and cap

    // lighting effects 
    float shiny[] = {60};
    float whtsp[] = {1.0, 1.0, 1.0, 0.6};
    glMaterialfv(GL_FRONT, GL_SHININESS, shiny);
    glMaterialfv(GL_FRONT, GL_SPECULAR, whtsp);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, whtsp);
    glEnable(GL_RESCALE_NORMAL);

    glPushMatrix();

    glTranslatef(0, pinHeight, 0);
    glScalef(radius, 1, radius);

    // key rim (cylinder side)
    glBegin(GL_QUAD_STRIP);
    for (theta = 0; theta <= 360; theta += dd)
    {
        float ang = theta / 360.0;
        glNormal3f(cosd(theta), 0, sind(theta));

        glTexCoord2f(ang, 0);
        cvertex(theta, 0, white);

        glTexCoord2f(ang, 1.0);
        cvertex(theta, keyHeight, white);
    }
    glEnd();

    // key bottom (cylinder base)
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, -1, 0); // set normal facing down
    gColor3fRGB(157.0, 162.0, 166.0); // light grey, dropper color from rim metallic grey
    glVertex3d(0, 0, 0); // base center
    for (theta = 360; theta >= 0; theta -=dd)
    {
        cvertex(theta, 0, 0x9da2a6);
    }
    glEnd();

    glPopMatrix();
}

// helper construction function
// supporting key rods
void keyRod()
{
    // construct pin body below the key head
    int dd = 60; // 6-sided precision
    int th = 0;
    int rad = 0.2;

    glPushMatrix();
    glEnable(GL_RESCALE_NORMAL);

    glScaled(rad, 1, rad);
    
    // create cylindrical tube without a top or bottom
    glBegin(GL_QUAD_STRIP);
    glColor3f(1.0, 1.0, 1.0);
    for (th = 0; th <= 360; th += dd)
    {
        gColor3fRGB(157.0, 162.0, 166.0);
        glNormal3f(cosd(th), 0, sind(th));

        glVertex3f(cosd(th), pinHeight, sind(th));
        glVertex3f(cosd(th), 0, sind(th));
    }
    glEnd();

    glPopMatrix();
}


void Typewriter::addKey(unsigned int character, unsigned int* textures)
{ // see README for character arguments
    // Select and bind texture for key
    // Specify coordinates for key    

    glPushMatrix();

    unsigned int ktex; // hold texture for the current key
    unsigned int mtex = textures[0]; // textures[0] is metallic texture

    // defined row positions
    const float r1y = 2.5; // zxcvbnm
    const float r1z = -3.1;
    const float r2y = 3.0; // asdfghjkl
    const float r2z = -4.9;
    const float r3y = 3.5; // qwertyuiop
    const float r3z = -6.7;
    
    switch (character)
    {
        // pull texture
        // set transformations for key position
        // build key
        // add to selection/name map

        case 97:  // a and at
            ktex = textures[15];

            // position individual key
            glTranslatef(-5.9, r2y, r2z);

            // build key
            glBindTexture(GL_TEXTURE_2D, ktex);
            keyFace(1);
            glBindTexture(GL_TEXTURE_2D, mtex);
            keyBody(1);
            keyRod();

            break;
        case 98:  // b and double quote
            ktex = textures[30];
            
            // position individual key
            glTranslatef(0.4, r1y, r1z);

            // build key
            glBindTexture(GL_TEXTURE_2D, ktex);
            keyFace(1);
            glBindTexture(GL_TEXTURE_2D, mtex);
            keyBody(1);
            keyRod();

            break;
        case 99:  // c and tilde
            ktex = textures[28];
            
            // position individual key
            glTranslatef(-2.4, r1y, r1z);

            // build key
            glBindTexture(GL_TEXTURE_2D, ktex);
            keyFace(1);
            glBindTexture(GL_TEXTURE_2D, mtex);
            keyBody(1);
            keyRod();

            break;
        case 100: // d and percent
            ktex = textures[17];
            
            // position individual key
            glTranslatef(-3.1, r2y, r2z);

            // build key
            glBindTexture(GL_TEXTURE_2D, ktex);
            keyFace(1);
            glBindTexture(GL_TEXTURE_2D, mtex);
            keyBody(1);
            keyRod();

            break;
        case 101: // e and 3
            ktex = textures[7];
            
            // position individual key
            glTranslatef(-3.8, r3y, r3z);

            // build key
            glBindTexture(GL_TEXTURE_2D, ktex);
            keyFace(1);
            glBindTexture(GL_TEXTURE_2D, mtex);
            keyBody(1);
            keyRod();

            break;
        case 102: // f and ampersand
            ktex = textures[18];
            
            // position individual key
            glTranslatef(-1.7, r2y, r2z);

            // build key
            glBindTexture(GL_TEXTURE_2D, ktex);
            keyFace(1);
            glBindTexture(GL_TEXTURE_2D, mtex);
            keyBody(1);
            keyRod();

            break;
        case 103: // g and underscore
            ktex = textures[19];
            
            // position individual key
            glTranslatef(-0.3, r2y, r2z);

            // build key
            glBindTexture(GL_TEXTURE_2D, ktex);
            keyFace(1);
            glBindTexture(GL_TEXTURE_2D, mtex);
            keyBody(1);
            keyRod();

            break;
        case 104: // h and asterisk
            ktex = textures[21];
            
            // position individual key
            glTranslatef(1.1, r2y, r2z);

            // build key
            glBindTexture(GL_TEXTURE_2D, ktex);
            keyFace(1);
            glBindTexture(GL_TEXTURE_2D, mtex);
            keyBody(1);
            keyRod();

            break;
        case 105: // i and 8
            ktex = textures[12];
            
            // position individual key
            glTranslatef(3.2, r3y, r3z);

            // build key
            glBindTexture(GL_TEXTURE_2D, ktex);
            keyFace(1);
            glBindTexture(GL_TEXTURE_2D, mtex);
            keyBody(1);
            keyRod();

            break;
        case 106: // j and forward slash
            ktex = textures[22];
            
            // position individual key
            glTranslatef(2.5, r2y, r2z);

            // build key
            glBindTexture(GL_TEXTURE_2D, ktex);
            keyFace(1);
            glBindTexture(GL_TEXTURE_2D, mtex);
            keyBody(1);
            keyRod();

            break;
        case 107: // k and equals
            ktex = textures[23];
            
            // position individual key
            glTranslatef(3.9, r2y, r2z);

            // build key
            glBindTexture(GL_TEXTURE_2D, ktex);
            keyFace(1);
            glBindTexture(GL_TEXTURE_2D, mtex);
            keyBody(1);
            keyRod();

            break;
        case 108: // l and pound
            ktex = textures[24];
            
            // position individual key
            glTranslatef(5.3, r2y, r2z);

            // build key
            glBindTexture(GL_TEXTURE_2D, ktex);
            keyFace(1);
            glBindTexture(GL_TEXTURE_2D, mtex);
            keyBody(1);
            keyRod();

            break;
        case 109: // m and semicolon
            ktex = textures[32];
            
            // position individual key
            glTranslatef(3.2, r1y, r1z);

            // build key
            glBindTexture(GL_TEXTURE_2D, ktex);
            keyFace(1);
            glBindTexture(GL_TEXTURE_2D, mtex);
            keyBody(1);
            keyRod();

            break;
        case 110: // n and colon
            ktex = textures[31];
            
            // position individual key
            glTranslatef(1.8, r1y, r1z);

            // build key
            glBindTexture(GL_TEXTURE_2D, ktex);
            keyFace(1);
            glBindTexture(GL_TEXTURE_2D, mtex);
            keyBody(1);
            keyRod();

            break;
        case 111: // o and 9
            ktex = textures[13];
            
            // position individual key
            glTranslatef(4.6, r3y, r3z);

            // build key
            glBindTexture(GL_TEXTURE_2D, ktex);
            keyFace(1);
            glBindTexture(GL_TEXTURE_2D, mtex);
            keyBody(1);
            keyRod();

            break;
        case 112: // p and 0
            ktex = textures[14];
            
            // position individual key
            glTranslatef(6, r3y, r3z);

            // build key
            glBindTexture(GL_TEXTURE_2D, ktex);
            keyFace(1);
            glBindTexture(GL_TEXTURE_2D, mtex);
            keyBody(1);
            keyRod();

            break;
        case 113: // q and 1
            ktex = textures[5];
            
            // position individual key
            glTranslatef(-6.6, r3y, r3z);

            // build key
            glBindTexture(GL_TEXTURE_2D, ktex);
            keyFace(1);
            glBindTexture(GL_TEXTURE_2D, mtex);
            keyBody(1);
            keyRod();

            break;
        case 114: // r and 4
            ktex = textures[8];
            
            // position individual key
            glTranslatef(-2.4, r3y, r3z);

            // build key
            glBindTexture(GL_TEXTURE_2D, ktex);
            keyFace(1);
            glBindTexture(GL_TEXTURE_2D, mtex);
            keyBody(1);
            keyRod();

            break;
        case 115: // s and dollar
            ktex = textures[16];
            
            // position individual key
            glTranslatef(-4.5, r2y, r2z);

            // build key
            glBindTexture(GL_TEXTURE_2D, ktex);
            keyFace(1);
            glBindTexture(GL_TEXTURE_2D, mtex);
            keyBody(1);
            keyRod();

            break;
        case 116: // t and 5
            ktex = textures[9];
            
            // position individual key
            glTranslatef(-1, r3y, r3z);

            // build key
            glBindTexture(GL_TEXTURE_2D, ktex);
            keyFace(1);
            glBindTexture(GL_TEXTURE_2D, mtex);
            keyBody(1);
            keyRod();

            break;
        case 117: // u and 7
            ktex = textures[11];
            
            // position individual key
            glTranslatef(1.8, r3y, r3z);

            // build key
            glBindTexture(GL_TEXTURE_2D, ktex);
            keyFace(1);
            glBindTexture(GL_TEXTURE_2D, mtex);
            keyBody(1);
            keyRod();

            break;
        case 118: // v and single quote
            ktex = textures[29];
            
            // position individual key
            glTranslatef(-1, r1y, r1z);

            // build key
            glBindTexture(GL_TEXTURE_2D, ktex);
            keyFace(1);
            glBindTexture(GL_TEXTURE_2D, mtex);
            keyBody(1);
            keyRod();

            break;
        case 119: // w and 2
            ktex = textures[6];
            
            // position individual key
            glTranslatef(-5.2, r3y, r3z);

            // build key
            glBindTexture(GL_TEXTURE_2D, ktex);
            keyFace(1);
            glBindTexture(GL_TEXTURE_2D, mtex);
            keyBody(1);
            keyRod();

            break;
        case 120: // x and close parenthesis
            ktex = textures[27];
            
            // position individual key
            glTranslatef(-3.8, r1y, r1z);

            // build key
            glBindTexture(GL_TEXTURE_2D, ktex);
            keyFace(1);
            glBindTexture(GL_TEXTURE_2D, mtex);
            keyBody(1);
            keyRod();

            break;
        case 121: // y and 6
            ktex = textures[10];
            
            // position individual key
            glTranslatef(0.4, r3y, r3z);

            // build key
            glBindTexture(GL_TEXTURE_2D, ktex);
            keyFace(1);
            glBindTexture(GL_TEXTURE_2D, mtex);
            keyBody(1);
            keyRod();

            break;
        case 122: // z and open parenthesis
            ktex = textures[26];
            
            // position individual key
            glTranslatef(-5.2, r1y, r1z);

            // build key
            glBindTexture(GL_TEXTURE_2D, ktex);
            keyFace(1);
            glBindTexture(GL_TEXTURE_2D, mtex);
            keyBody(1);
            keyRod();

            break;
        case 128: // cap
            ktex = textures[3];
            
            // position individual key
            glTranslatef(-6.8, r1y, -2.2);

            // build key
            glBindTexture(GL_TEXTURE_2D, ktex);
            keyFace(0);
            glBindTexture(GL_TEXTURE_2D, mtex);
            keyBody(0);
            keyRod();

            break;
        case 129: // fig
            ktex = textures[4];
            
            // position individual key
            glTranslatef(-7.5, r2y, -4.4);

            // build key
            glBindTexture(GL_TEXTURE_2D, ktex);
            keyFace(0);
            glBindTexture(GL_TEXTURE_2D, mtex);
            keyBody(0);
            keyRod();

            break;
        case 45:  // minus and plus
            ktex = textures[35];
            
            // position individual key
            glTranslatef(7.4, r1y, r1z);

            // build key
            glBindTexture(GL_TEXTURE_2D, ktex);
            keyFace(1);
            glBindTexture(GL_TEXTURE_2D, mtex);
            keyBody(1);
            keyRod();

            break;
        case 46:  // period and right angle bracket
            ktex = textures[34];
            
            // position individual key
            glTranslatef(6, r1y, r1z);

            // build key
            glBindTexture(GL_TEXTURE_2D, ktex);
            keyFace(1);
            glBindTexture(GL_TEXTURE_2D, mtex);
            keyBody(1);
            keyRod();

            break;
        case 44:  // comma and left angle bracket
            ktex = textures[33];
            
            // position individual key
            glTranslatef(4.6, r1y, r1z);

            // build key
            glBindTexture(GL_TEXTURE_2D, ktex);
            keyFace(1);
            glBindTexture(GL_TEXTURE_2D, mtex);
            keyBody(1);
            keyRod();

            break;
        case 63: // question mark and back slash
            ktex = textures[25];
            
            // position individual key
            glTranslatef(6.7, r2y, r2z);

            // build key
            glBindTexture(GL_TEXTURE_2D, ktex);
            keyFace(1);
            glBindTexture(GL_TEXTURE_2D, mtex);
            keyBody(1);
            keyRod();

            break;
    }

    glPopMatrix();
}

void Typewriter::addKeySpace(unsigned int tex)
{
    // lighting effects 
    float shiny[] = {60};
    float whtsp[] = {1.0, 1.0, 1.0, 0.6};
    glMaterialfv(GL_FRONT, GL_SHININESS, shiny);
    glMaterialfv(GL_FRONT, GL_SPECULAR, whtsp);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, whtsp);

    // two rods
    glPushMatrix();
    glTranslatef(-3.8, 2, -1.3);
    keyRod();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(6, 2, -1.3);
    keyRod();
    glPopMatrix();

    // rectangular prism body
    glPushMatrix();
    glTranslatef(2.2, 0, 0);
    glBindTexture(GL_TEXTURE_2D, tex);
    // rectangles across to increase lightable vertices
    float x = -6.8; // min x to +5.8 max x
    float t;
    glBegin(GL_QUAD_STRIP);
    glNormal3f(0, 1, 0); // top
    for (int i = 0; i <= 10; i++)
    {
        t = i/10.0;

        glTexCoord2f(t, 1);
        glVertex3f(x, 3.3, -1.8);

        glTexCoord2f(t, 0);
        glVertex3f(x, 3.3, -0.8);

        x += 1.16;
    }
    glEnd();
    x = 4.8;
    glBegin(GL_QUAD_STRIP);
    glNormal3f(0, -1, 0); // bottom
    for (int i = 10; i >= 0; i--)
    {
        t = 1 - (i/10.0);
        
        glTexCoord2f(t, 0);
        glVertex3f(x, 3.2, -0.8);

        glTexCoord2f(t, 1);
        glVertex3f(x, 3.2, -1.8);

        x -= 1.16;
    }
    glEnd();
    x = -6.8;
    glBegin(GL_QUAD_STRIP);
    glNormal3f(0, 0, 1); // front side
    for (int i = 0; i <= 10; i++)
    {
        t = i/10.0;
        
        glTexCoord2f(t, 1);
        glVertex3f(x, 3.3, -0.8);

        glTexCoord2f(t, 0);
        glVertex3f(x, 3.2, -0.8);

        x += 1.16;
    }
    glEnd();
    x = 4.8;
    glBegin(GL_QUAD_STRIP);
    glNormal3f(0, 0, -1); // back side
    for (int i = 10; i >= 0; i--)
    {
        t = 1- (i/10.0);
        
        glTexCoord2f(t, 0);
        glVertex3f(x, 3.2, -1.8);

        glTexCoord2f(t, 1);
        glVertex3f(x, 3.3, -1.8);

        x -= 1.16;
    }
    glEnd();
    glPopMatrix();

    // rounded ends (go 180 deg)
    float rad = 0.5;
    float th = 0;
    float dd = 20; // rotation precision
    glPushMatrix();
    glTranslatef(7, 3.3, -1.3); // right top round end
    glRotatef(90, 0, 1, 0);
    glScalef(rad, 1, rad);
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, 1, 0);
    glColor3f(1.0, 1.0, 1.0);
    glTexCoord2f(0.5f, 0.5f);
    glVertex3f(0, 0, 0);
    for (th = 0; th <= 180; th += dd)
    {
        glNormal3f(0, 1, 0);
        glTexCoord2f(0.5f * sind(th) + 0.5f, 0.5f * cosd(th) + 0.5f);
        cvertex(th, 0, white);
    }
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(7, 3.2, -1.3); // right bottom round end
    glRotatef(90, 0, 1, 0);
    glScalef(rad, 1, rad);
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, 1, 0);
    glColor3f(1.0, 1.0, 1.0);
    glTexCoord2f(0.5f, 0.5f);
    glVertex3f(0, 0, 0);
    for (th = 180; th >= 0; th -= dd)
    {
        glNormal3f(0, 1, 0);
        glTexCoord2f(0.5f * sind(th) + 0.5f, 0.5f * cosd(th) + 0.5f);
        cvertex(th, 0, white);
    }
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-4.6, 3.3, -1.3); // left top round end
    glRotatef(-90, 0, 1, 0);
    glScalef(rad, 1, rad);
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, 1, 0);
    glColor3f(1.0, 1.0, 1.0);
    glTexCoord2f(0.5f, 0.5f);
    glVertex3f(0, 0, 0);
    for (th = 0; th <= 180; th += dd)
    {
        glNormal3f(0, 1, 0);
        glTexCoord2f(0.5f * sind(th) + 0.5f, 0.5f * cosd(th) + 0.5f);
        cvertex(th, 0, white);
    }
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-4.6, 3.2, -1.3); // left bottom round end
    glRotatef(-90, 0, 1, 0);
    glScalef(rad, 1, rad);
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, 1, 0);
    glColor3f(1.0, 1.0, 1.0);
    glTexCoord2f(0.5f, 0.5f);
    glVertex3f(0, 0, 0);
    for (th = 180; th >= 0; th -= dd)
    {
        glNormal3f(0, 1, 0);
        glTexCoord2f(0.5f * sind(th) + 0.5f, 0.5f * cosd(th) + 0.5f);
        cvertex(th, 0, white);
    }
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(7, 3.2, -1.3); // right round rim
    glRotatef(90, 0, 1, 0);
    glScalef(0.5, 1, 0.5);
    glBegin(GL_QUAD_STRIP);
    for (th = 0; th <= 180; th += dd)
    {
        glNormal3f(cosd(th), 0, sind(th));
        float ang = th / 180.0;

        glTexCoord2f(ang, 0);
        cvertex(th, 0, white);

        glTexCoord2f(ang, 1.0);
        cvertex(th, 0.1, white);
    }
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-4.6, 3.2, -1.3); // left round rim
    glRotatef(-90, 0, 1, 0);
    glScalef(0.5, 1, 0.5);
    glBegin(GL_QUAD_STRIP);
    for (th = 0; th <= 180; th += dd)
    {
        glNormal3f(cosd(th), 0, sind(th));
        float ang = th / 180.0;

        glTexCoord2f(ang, 0);
        cvertex(th, 0, white);

        glTexCoord2f(ang, 1.0);
        cvertex(th, 0.1, white);
    }
    glEnd();
    glPopMatrix();

}

void Typewriter::twBody(unsigned int* textures)
{
    // main lower body of typewriter, including hammers

    unsigned int ptex = textures[1]; // plastic body texture

    // lighting effects 
    float shiny[] = {30};
    float whtsp[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT, GL_SHININESS, shiny);
    glMaterialfv(GL_FRONT, GL_SPECULAR, whtsp);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, whtsp);

    // bind plastic texture for all faces
    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, ptex);

    // body lower front face
    glNormal3f(0, 0.4, 2); // slant forward (+y, +z)
    glBegin(GL_QUAD_STRIP);
    // build lower strip of quads
    float xpos = -9.1;
    for (int j = 0; j <= 14; j++)
    {
        float t = j / 14.0;
        glTexCoord2f(t, 0.5);
        glVertex3f(xpos, 1, 0.2);

        glTexCoord2f(t, 0);
        glVertex3f(xpos, 0, 0.4);
        xpos += 1.3;
    }
    glEnd();
    glBegin(GL_QUAD_STRIP);
    // build upper strip of quads
    xpos = -9.1;
    for (int j = 0; j <= 14; j++)
    {
        float t = j / 14.0;
        glTexCoord2f(t, 1);
        glVertex3f(xpos, 2, 0.0);

        glTexCoord2f(t, 0.5);
        glVertex3f(xpos, 1, 0.2);
        xpos += 1.3;
    }
    glEnd();

    // body lower left face
    glNormal3f(-1, 0, 0);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-9.1, 0, -8);
    glTexCoord2f(1, 0);
    glVertex3f(-9.1, 0, 0.4);
    glTexCoord2f(1, 1);
    glVertex3f(-9.1, 2, 0);
    glTexCoord2f(0, 1);
    glVertex3f(-9.1, 4.8, -8);
    glEnd();

    // body lower right face
    glNormal3f(1, 0, 0);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(9.1, 0, 0.4);
    glTexCoord2f(1, 0);
    glVertex3f(9.1, 0, -8);
    glTexCoord2f(1, 1);
    glVertex3f(9.1, 4.8, -8);
    glTexCoord2f(0, 1);
    glVertex3f(9.1, 2, 0);
    glEnd();

    // body lower top
    glNormal3f(0, 8, 2.8);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-9.1, 2, 0);
    glTexCoord2f(1, 0);
    glVertex3f(9.1, 2, 0);
    glTexCoord2f(1, 1);
    glVertex3f(9.1, 4.8,-8);
    glTexCoord2f(0, 1);
    glVertex3f(-9.1, 4.8, -8);
    glEnd();

    // body underside base
    glNormal3f(0, -1, 0);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-9.1, 0, -16);
    glTexCoord2f(1, 0);
    glVertex3f(9.1, 0, -16);
    glTexCoord2f(1, 1);
    glVertex3f(9.1, 0, 0.4);
    glTexCoord2f(0, 1);
    glVertex3f(-9.1, 0, 0.4);
    glEnd();

    // body upper front face
    glNormal3f(0, 0, 1);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-9.1, 4.8, -8);
    glTexCoord2f(1, 0);
    glVertex3f(9.1, 4.8, -8);
    glTexCoord2f(1, 1);
    glVertex3f(9.1, 6.8, -8);
    glTexCoord2f(0, 1);
    glVertex3f(-9.1, 6.8, -8);
    glEnd();

    // body upper left face
    glNormal3f(-1, 0, 0);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-9.1, 0, -16);
    glTexCoord2f(1, 0);
    glVertex3f(-9.1, 0, -8);
    glTexCoord2f(1, 1);
    glVertex3f(-9.1, 6.8, -8);
    glTexCoord2f(0, 1);
    glVertex3f(-9.1, 6.8, -16);
    glEnd();

    // body upper right face
    glNormal3f(1, 0, 0);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(9.1, 0, -8);
    glTexCoord2f(1, 0);
    glVertex3f(9.1, 0, -16);
    glTexCoord2f(1, 1);
    glVertex3f(9.1, 6.8, -16);
    glTexCoord2f(0, 1);
    glVertex3f(9.1, 6.8, -8);
    glEnd();

    // // body upper top left
    // glNormal3f(0, 1, 0);
    // glBegin(GL_QUADS);
    // glTexCoord2f(0, 0);
    // glVertex3f();
    // glTexCoord2f(1, 0);
    // glVertex3f();
    // glTexCoord2f(1, 1);
    // glVertex3f();
    // glTexCoord2f(0, 1);
    // glVertex3f();
    // glEnd();

    // // body upper top right
    // glNormal3f(0, 1, 0);
    // glBegin(GL_QUADS);
    // glTexCoord2f(0, 0);
    // glVertex3f();
    // glTexCoord2f(1, 0);
    // glVertex3f();
    // glTexCoord2f(1, 1);
    // glVertex3f();
    // glTexCoord2f(0, 1);
    // glVertex3f();
    // glEnd();

    // body back
    glNormal3f(0, 0, -1);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(9.1, 0, -16);
    glTexCoord2f(1, 0);
    glVertex3f(-9.1, 0, -16);
    glTexCoord2f(1, 1);
    glVertex3f(-9.1, 6.8, -16);
    glTexCoord2f(0, 1);
    glVertex3f(9.1, 6.8, -16);
    glEnd();


}

void Typewriter::twpTray()
{
    // paper tray, carriage return, and upper parts of typewriter
}

void Typewriter::buildTypewriter(unsigned int* textures)
{
    // add each key
    for (int k = 97; k <= 122; k++)
    { // a through z keys
        addKey(k, textures);
    }
    // remaining punctuation and control keys
    addKey(44, textures);
    addKey(45, textures);
    addKey(46, textures);
    addKey(63, textures);
    addKey(128, textures);
    addKey(129, textures);

    glPushName(33);
    addKeySpace(textures[0]);
    glPopName(); // to stop objects that are part of this name

    // build typewriter body around keys
    twBody(textures);

    // build paper tray
    twpTray();
}

Typewriter::Typewriter(){}
Typewriter::~Typewriter(){}