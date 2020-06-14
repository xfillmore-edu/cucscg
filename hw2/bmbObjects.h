/* Individual objects for construction of bamboo stalks */

#ifndef bmbObjects
#define bmbObjects

/* bamboo objects list */
/* cones, cylinders, double triangle fans, "leaves" (2x two flat faces, rounded rectangles strip) */
/* + lines for connecting leaves to stem */

/* cylinder */
/* for core stem segments */
void cylinder(double xcen, double ycen, double zcen, double height, double radius, int axis);

/* consisting of semi-circular flat segments and rounded segments */
/* for the leaves */
/* params:  */
void leaf();

/* cone */
/* for branches out to leaves */
void cone();

/* lame curve / hyperellipsoid */
/* for section pieces along stem */
void rhombohedron();

#endif