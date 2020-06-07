Xuedan Fillmore
CSCI 4229 Computer Graphics
05 June 2020

Assignment 1 | Lorenz Attractor

PURPOSE
  To gain an understanding of basics of creating OpenGL scenes.
  To explore properties of the Lorenz Attractor.
  To practice implementing user interaction with OpenGL.

COMPILE
  Compile and display using
  $ make
  $ hw1

LOCAL CONFIG
  Windows OS 10 with mounted Ubuntu terminal
  Start Xming
  $ export DISPLAY=:0.0
  $ ./hw1

KEY BINDINGS
  x         view from +X axis
  X         view from -X axis
  y         view from +Y axis 
  Y         view from -Y axis
  z         view from +Z axis
  Z         view from -Z axis
  s         decrease s parameter
  S         increase s parameter
  r         decrease r parameter
  R         increase r parameter
  t         decrease time step
  T         increase time step
  e         erase modifications (reset view)
  q or ESC  Exit display window

UPDATING PARAMETERS
  The key bindings specify that the sigma (s), rho (r), and dt (t) parameters
  can be changed to modify the system.
  Available values for each is stored an array.
  For sigma, the values correspond to actual fluids.
  For rho, most values are randomly selected with the exception of a select few
    that are determined to be critical values. For very large values of rho,
    the specified dimension is insufficient to accomodate the entire graph.
  For dt, time steps are limited to 0.01, 0.001, 0.005, and 0.0001 (which is displayed as 0.000)
  The default values for each of these, as well as the initial display angle,
    can be quickly set using e (erase all modifications).

Time spent
~ 8 hours, 30 minutes
[Status: Minimum Requirements met]