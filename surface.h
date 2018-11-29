#ifndef SURFACE_H
#define SURFACE_H

#include <GL/glut.h>

typedef struct // Definicion de un punto del terreo
{
    GLfloat s, t; // Coordenadas de texturas
    GLfloat nx, ny, nz; // Coordenadas de la normal
    GLfloat x, hauteur, z; // posición del vértice
} PointSurface;




#endif // SURFACE_H
