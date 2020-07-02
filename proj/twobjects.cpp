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
    for (theta = 360; theta >= 0; theta -= dd)
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
    for (theta = 0; theta <= 360; theta +=dd)
    {
        cvertex(theta, 0, 0x9da2a6);
    }
    glEnd();

    glPopMatrix();

    // construct pin body below the key head
    dd = 40; // 9-sided precision
    theta = 0;
    radius = 0.2;

    glPushMatrix();
    glEnable(GL_RESCALE_NORMAL);

    glScaled(radius, 1, radius);
    
    // create cylindrical tube without a top or bottom
    glBegin(GL_QUAD_STRIP);
    for (theta = 0; theta <= 360; theta += dd)
    {
        glNormal3f(cosd(theta), 0, sind(theta));

        cvertex(theta, 0,         0x9da2a6);
        cvertex(theta, pinHeight, 0x9da2a6);
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
    int dd = 40; // 9-sided precision
    int theta = 0;
    float radius = 0.2;
    glEnable(GL_RESCALE_NORMAL);
    glPushMatrix();
    glTranslatef(-3.8, 2, -1.3);
    glScaled(radius, 1, radius);    
    // create cylindrical tube without a top or bottom
    glBegin(GL_QUAD_STRIP);
    for (theta = 0; theta <= 360; theta += dd)
    {
        glNormal3f(cosd(theta), 0, sind(theta));

        cvertex(theta, 0,         0x9da2a6);
        cvertex(theta, pinHeight, 0x9da2a6);
    }
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(6, 2, -1.3);
    glScaled(radius, 1, radius);  
    glBegin(GL_QUAD_STRIP);
    for (theta = 0; theta <= 360; theta += dd)
    {
        glNormal3f(cosd(theta), 0, sind(theta));

        cvertex(theta, 0,         0x9da2a6);
        cvertex(theta, pinHeight, 0x9da2a6);
    }
    glEnd();

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
        glVertex3f(x, 3.2, -1.8);

        glTexCoord2f(t, 1);
        glVertex3f(x, 3.2, -0.8);

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
        glVertex3f(x, 3.3, -1.8);

        glTexCoord2f(t, 1);
        glVertex3f(x, 3.2, -1.8);

        x -= 1.16;
    }
    glEnd();
    glPopMatrix();

    // rounded ends (go 180 deg)
    float rad = 0.5;
    float th = 0;
    dd = 20; // rotation precision
    glPushMatrix();
    glTranslatef(7, 3.3, -1.3); // right top round end
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
    glTranslatef(7, 3.2, -1.3); // right bottom round end
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
    glTranslatef(-4.6, 3.3, -1.3); // left top round end
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
    glTranslatef(-4.6, 3.2, -1.3); // left bottom round end
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

    // key shared coordinates
    float xl = -9.1; // x left
    float xr =  9.1; // x right
    float y0 =    0; // y base
    float yl =    2; // y lower front tier
    float ym =  4.8; // y mid front tier
    float yh =  6.8; // y high/top tier
    float yb =  5.8; // y back tier
    float z0 =    0; // z near front (0)
    float zf =  0.4; // z base front
    float z2 =   -8; // z second depth
    float z3 =  -16; // z third depth
    float zb =  -18; // z back depth
    float half1, half2, dy;

    int repx = 12; // repetition in x dir (num quads x)
    int repy = 6;  // repetition in y dir (num quads y)
    float rx = 2.0 / repx;
    float ry = 2.0 / repy;

    // body lower front face
    // glNormal3f(0, 0.4, 2); // slant forward (+y, +z)
    glNormal3f(0, 0.196, 0.981);
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
    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0.5f, 0.5f); glVertex3f(xl, ym/2.0, (z2+zf)/2.0); // center
    glTexCoord2f(1.0f, 0.5f); glVertex3f(xl, yl/2.0, zf/2.0);     // mid right
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xl, yl,     z0);     // top right
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xl, ym,     z2);     // top left
    glTexCoord2f(0.0f, 0.5f); glVertex3f(xl, ym/2.0, z2); // mid left
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xl, y0,     z2);     // lower left
    glTexCoord2f(0.5f, 0.0f); glVertex3f(xl, y0,     (zf+z2)/2.0); // mid bottom
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xl, y0,     zf);     // lower right
    glTexCoord2f(1.0f, 0.5f); glVertex3f(xl, yl/2.0, zf/2.0);     // mid right again
    glEnd();

    // body lower right face
    glNormal3f(1, 0, 0);
    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0.5f, 0.5f); glVertex3f(xr, ym/2.0, (z2-zf)/2.0); // center
    glTexCoord2f(1.0f, 0.5f); glVertex3f(xr, ym/2.0, z2);     // mid right
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xr, ym,     z2);     // top right
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xr, yl,     z0);     // top left
    glTexCoord2f(0.0f, 0.5f); glVertex3f(xr, yl/2.0, zf/2.0); // mid left
    glTexCoord2f(0.0f, 0.0f); glVertex3f(xr, y0,     zf);     // lower left
    glTexCoord2f(0.5f, 0.0f); glVertex3f(xr, y0,     z2/2.0); // mid bottom
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xr, y0,     z2);     // lower right
    glTexCoord2f(1.0f, 0.5f); glVertex3f(xr, ym/2.0, z2);     // mid right again
    glEnd();

    // body lower top
    // glNormal3f(0, 8, 2.8);
    glNormal3f(0, 0.944, 0.33);
    dy = (ym-yl) / repy;
    glBegin(GL_QUADS);
    for (int i = 0; i < repx; i++)
    {
        for (int j = 0; j < repy; j++)
        {
            float y = (dy * j) + yl;
            float z = -(y - 2) / 0.35;
            float y2 = (dy * (j+1)) + yl;
            float z2 = -(y2 - 2) / 0.35;

            glTexCoord2d(rx * (i),   ry * (j)  ); glVertex3d(xr * rx * (i)  -xr, y, z);
            glTexCoord2d(rx * (i+1), ry * (j)  ); glVertex3d(xr * rx * (i+1)-xr, y, z);
            glTexCoord2d(rx * (i+1), ry * (j+1)); glVertex3d(xr * rx * (i+1)-xr, y2, z2);
            glTexCoord2d(rx * (i),   ry * (j+1)); glVertex3d(xr * rx * (i)  -xr, y2, z2);
        }
    }
    glEnd();

    // body underside base
    glNormal3f(0, -1, 0);
    half1 = (zb - z0) / 2.0;
    glBegin(GL_QUADS);
    for (int i = 0; i < repx; i++)
    {
        for (int j = 0; j < repy; j++)
        {
            glTexCoord2d(rx * (i+1), ry * (j)  ); glVertex3d(xr * rx * (i+1)-xr, 0, (half1 * ry * (j)  ));
            glTexCoord2d(rx * (i),   ry * (j)  ); glVertex3d(xr * rx * (i)  -xr, 0, (half1 * ry * (j)  ));
            
            glTexCoord2d(rx * (i),   ry * (j+1)); glVertex3d(xr * rx * (i)  -xr, 0, (half1 * ry * (j+1)));
            glTexCoord2d(rx * (i+1), ry * (j+1)); glVertex3d(xr * rx * (i+1)-xr, 0, (half1 * ry * (j+1)));
            
        }
    }
    glEnd();

    // body upper front face
    half1 = 1;
    glNormal3f(0, 0, 1);
    glBegin(GL_QUADS);
    for (int i = 0; i < repx; i++)
    {
        for (int j = 0; j < repy; j++)
        {
            glTexCoord2d(rx * (i),   ry * (j)  ); glVertex3d(xr * rx * (i)  -xr, (half1 * ry * (j)  + ym), z2);
            glTexCoord2d(rx * (i+1), ry * (j)  ); glVertex3d(xr * rx * (i+1)-xr, (half1 * ry * (j)  + ym), z2);
            glTexCoord2d(rx * (i+1), ry * (j+1)); glVertex3d(xr * rx * (i+1)-xr, (half1 * ry * (j+1)+ ym), z2);
            glTexCoord2d(rx * (i),   ry * (j+1)); glVertex3d(xr * rx * (i)  -xr, (half1 * ry * (j+1)+ ym), z2);
        }
    }
    glEnd();

    glDisable(GL_CULL_FACE);
    // body upper left face
    glNormal3f(-1, 0, 0);
    half1 = (z3 - z2) / 2.0;
    half2 = (yh - y0) / 2.0;
    glBegin(GL_QUADS);
    for (int i = 0; i < repx; i++)
    {
        for (int j = 0; j < repy; j++)
        {
            glTexCoord2d(rx * (i),   ry * (j)  ); glVertex3d(xl, half2 * rx * (i)  , (half1 * ry * (j)  )+z2);
            glTexCoord2d(rx * (i+1), ry * (j)  ); glVertex3d(xl, half2 * rx * (i+1), (half1 * ry * (j)  )+z2);
            glTexCoord2d(rx * (i+1), ry * (j+1)); glVertex3d(xl, half2 * rx * (i+1), (half1 * ry * (j+1))+z2);
            glTexCoord2d(rx * (i),   ry * (j+1)); glVertex3d(xl, half2 * rx * (i)  , (half1 * ry * (j+1))+z2);
        }
    }
    glEnd();

    // body upper right face
    glNormal3f(1, 0, 0);
    half1 = (z3 - z2) / 2.0;
    half2 = (yh - y0) / 2.0;
    glBegin(GL_QUADS);
    for (int i = 0; i < repx; i++)
    {
        for (int j = 0; j < repy; j++)
        {
            glTexCoord2d(rx * (i+1), ry * (j)  ); glVertex3d(xr, half2 * rx * (i+1), (half1 * ry * (j)  )+z2);
            glTexCoord2d(rx * (i),   ry * (j)  ); glVertex3d(xr, half2 * rx * (i)  , (half1 * ry * (j)  )+z2);
            glTexCoord2d(rx * (i),   ry * (j+1)); glVertex3d(xr, half2 * rx * (i)  , (half1 * ry * (j+1))+z2);
            glTexCoord2d(rx * (i+1), ry * (j+1)); glVertex3d(xr, half2 * rx * (i+1), (half1 * ry * (j+1))+z2);
            
        }
    }
    glEnd();

    // body upper top left
    glNormal3f(0, 1, 0);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(xl, yh, z3);
    glTexCoord2f(1, 0); glVertex3f(xl, yh, z2);
    glTexCoord2f(1, 1); glVertex3f(-2, yh, -11);
    glTexCoord2f(0, 1); glVertex3f(-0.5, yh, z3);

    // upper top middle
    glTexCoord2f(0, 0.4); glVertex3f(-2, yh, -11);
    glTexCoord2f(1, 0); glVertex3f(xl, yh, z2);
    glTexCoord2f(1, 1); glVertex3f(xr, yh, z2);
    glTexCoord2f(0, 0.6); glVertex3f(2, yh, -11);

    // body upper top right
    glTexCoord2f(0, 0); glVertex3f(0.5, yh, z3);
    glTexCoord2f(1, 0); glVertex3f(2, yh, -11);
    glTexCoord2f(1, 1); glVertex3f(xr, yh, z2);
    glTexCoord2f(0, 1); glVertex3f(xr, yh, z3);
    glEnd();
    glEnable(GL_CULL_FACE);

    // body back
    glNormal3f(0, 0, -1);
    half1 = (yb - y0)/2.0;
    glBegin(GL_QUADS);
    for (int i = 0; i < repx; i++)
    {
        for (int j = 0; j < repy; j++)
        {
            glTexCoord2d(rx * (i+1), ry * (j)  ); glVertex3d(xr * rx * (i+1)-xr, (half1 * ry * (j)  + y0), zb);
            glTexCoord2d(rx * (i),   ry * (j)  ); glVertex3d(xr * rx * (i)  -xr, (half1 * ry * (j)  + y0), zb);
            glTexCoord2d(rx * (i),   ry * (j+1)); glVertex3d(xr * rx * (i)  -xr, (half1 * ry * (j+1)+ y0), zb);
            glTexCoord2d(rx * (i+1), ry * (j+1)); glVertex3d(xr * rx * (i+1)-xr, (half1 * ry * (j+1)+ y0), zb);
            
        }
    }
    glEnd();

    // body back top
    glNormal3f(0, 1, 0);
    half1 = (zb - z3) / 2.0;
    glBegin(GL_QUADS);
    for (int i = 0; i < repx; i++)
    {
        for (int j = 0; j < repy; j++)
        {
            glTexCoord2d(rx * (i),   ry * (j)  ); glVertex3d(xr * rx * (i)  -xr, yb, (half1 * ry * (j)  )+z3);
            glTexCoord2d(rx * (i+1), ry * (j)  ); glVertex3d(xr * rx * (i+1)-xr, yb, (half1 * ry * (j)  )+z3);
            glTexCoord2d(rx * (i+1), ry * (j+1)); glVertex3d(xr * rx * (i+1)-xr, yb, (half1 * ry * (j+1))+z3);
            glTexCoord2d(rx * (i),   ry * (j+1)); glVertex3d(xr * rx * (i)  -xr, yb, (half1 * ry * (j+1))+z3);
        }
    }
    glEnd();

    // back right face
    glNormal3f(1, 0, 0);
    half1 = (zb - z3) / 2.0;
    half2 = (yb - y0) / 2.0;
    glBegin(GL_QUADS);
    for (int i = 0; i < repx; i++)
    {
        for (int j = 0; j < repy; j++)
        {
            glTexCoord2d(rx * (i+1), ry * (j)  ); glVertex3d(xr, half2 * rx * (i+1), (half1 * ry * (j)  )+z3);
            glTexCoord2d(rx * (i),   ry * (j)  ); glVertex3d(xr, half2 * rx * (i)  , (half1 * ry * (j)  )+z3);
            glTexCoord2d(rx * (i),   ry * (j+1)); glVertex3d(xr, half2 * rx * (i)  , (half1 * ry * (j+1))+z3);
            glTexCoord2d(rx * (i+1), ry * (j+1)); glVertex3d(xr, half2 * rx * (i+1), (half1 * ry * (j+1))+z3);
            
        }
    }
    glEnd();

    // back left face
    glNormal3f(-1, 0, 0);
    half1 = (zb - z3) / 2.0;
    half2 = (yb - y0) / 2.0;
    glBegin(GL_QUADS);
    for (int i = 0; i < repx; i++)
    {
        for (int j = 0; j < repy; j++)
        {
            glTexCoord2d(rx * (i),   ry * (j)  ); glVertex3d(xl, half2 * rx * (i)  , (half1 * ry * (j)  )+z3);
            glTexCoord2d(rx * (i+1), ry * (j)  ); glVertex3d(xl, half2 * rx * (i+1), (half1 * ry * (j)  )+z3);
            glTexCoord2d(rx * (i+1), ry * (j+1)); glVertex3d(xl, half2 * rx * (i+1), (half1 * ry * (j+1))+z3);
            glTexCoord2d(rx * (i),   ry * (j+1)); glVertex3d(xl, half2 * rx * (i)  , (half1 * ry * (j+1))+z3);
        }
    }
    glEnd();

    // upper back right
    glDisable(GL_CULL_FACE);
    glNormal3f(0, 0, -1);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(xr, yh, z3);
    glTexCoord2f(1, 0); glVertex3f(xr, yb, z3);
    glTexCoord2f(1, 1); glVertex3f(0, yb, z3);
    glTexCoord2f(0, 1); glVertex3f(0.5, yh, z3);
    
    // upper back left
    glTexCoord2f(0, 0); glVertex3f(-0.5, yh, z3);
    glTexCoord2f(1, 0); glVertex3f(0, yb, z3);
    glTexCoord2f(1, 1); glVertex3f(xl, yb, z3);
    glTexCoord2f(0, 1); glVertex3f(xl, yh, z3);
    glEnd();
    glEnable(GL_CULL_FACE);

    // hammers "hidden" inside typewriter body
    // lighting effects 
    shiny[0] = {10};
    float eff[] = {0.6, 0.6, 0.6, 0.6};
    glMaterialfv(GL_FRONT, GL_SHININESS, shiny);
    glMaterialfv(GL_FRONT, GL_SPECULAR, eff);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, eff);
    // texture cover
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    // glNormal3f(0, 8, -1);
    glNormal3f(0, 0.9923, 0.124);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(xr, yb, z3);
    glTexCoord2f(1, 0); glVertex3f(xl, yb, z3);
    glTexCoord2f(1, 1); glVertex3f(xl, yh, z2);
    glTexCoord2f(0, 1); glVertex3f(xr, yh, z2);
    glEnd();

    // rails
    glDisable(GL_TEXTURE_2D);
    float sq = 0.3;
    float z1 = -16.5;
          z2 = -17.2;
    // square ends
    // gColor3fHEX(0x9da2a6);
    glColor3f(0.6, 0.6, 0.6);
    glBegin(GL_QUADS);
    glNormal3f(1, 0, 0);
    glVertex3f(xr, yb+sq, z1); // right front end
    glVertex3f(xr, yb, z1);
    glVertex3f(xr, yb, z1-sq);
    glVertex3f(xr, yb+sq, z1-sq);

    glVertex3f(xr, yb+sq, z2); // right back end
    glVertex3f(xr, yb, z2);
    glVertex3f(xr, yb, z2-sq);
    glVertex3f(xr, yb+sq, z2-sq);

    glNormal3f(-1, 0, 0);
    glVertex3f(xl, yb+sq, z2-sq); // left back end
    glVertex3f(xl, yb, z2-sq);
    glVertex3f(xl, yb, z2);
    glVertex3f(xl, yb+sq, z2);

    glVertex3f(xl, yb+sq, z1-sq); // left front end
    glVertex3f(xl, yb, z1-sq);
    glVertex3f(xl, yb, z1);
    glVertex3f(xl, yb+sq, z1);
    glEnd();
    
    // rails ~ long rods
    glBegin(GL_QUADS);
    glNormal3f(0, 0, -1);
    glVertex3f(xr, yb+sq, z2-sq); // back bar back
    glVertex3f(xr, yb,    z2-sq);
    glVertex3f(xl, yb,    z2-sq);
    glVertex3f(xl, yb+sq, z2-sq);

    glVertex3f(xr, yb+sq, z1-sq); // front bar back
    glVertex3f(xr, yb,    z1-sq);
    glVertex3f(xl, yb,    z1-sq);
    glVertex3f(xl, yb+sq, z1-sq);

    glNormal3f(0, 1, 0);
    glVertex3f(xr, yb+sq, z2); // back bar top
    glVertex3f(xr, yb+sq, z2-sq);
    glVertex3f(xl, yb+sq, z2-sq);
    glVertex3f(xl, yb+sq, z2);

    glVertex3f(xr, yb+sq, z1); // front bar top
    glVertex3f(xr, yb+sq, z1-sq);
    glVertex3f(xl, yb+sq, z1-sq);
    glVertex3f(xl, yb+sq, z1);

    glNormal3f(0, 0, 1);
    glVertex3f(xr, yb,    z2); // back bar front
    glVertex3f(xr, yb+sq, z2);
    glVertex3f(xl, yb+sq, z2);
    glVertex3f(xl, yb,    z2);

    glVertex3f(xr, yb,    z1); // front bar front
    glVertex3f(xr, yb+sq, z1);
    glVertex3f(xl, yb+sq, z1);
    glVertex3f(xl, yb,    z1);
    glEnd();

    glEnable(GL_TEXTURE_2D);
    


}

void Typewriter::twpTray(float xshift)
{
    // paper tray, carriage return, and mobile upper parts of typewriter
    // xhift argument determines the offset positioning of the carriage/tray
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
    twpTray(0);
}

Typewriter::Typewriter(){}
Typewriter::~Typewriter(){}