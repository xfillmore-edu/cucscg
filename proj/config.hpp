#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <cmath>
#include <cstdio>
#include <string>
#include <cstdarg>

#ifdef USEGLEW
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES

// Cross-OS compatability
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// function declarations
void checkErrs(std::string fn);
void gprint(const char* format, ...);
void fatal(const char* format, ...);
void project(double fov, double aspratio, double dimension);
unsigned int loadTexture(const char* filename);

#endif