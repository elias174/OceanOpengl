#include <iostream>
#include <GL/glut.h>
#include "wave.h"


using namespace std;

#define RED 0
#define GREEN 0
#define BLUE 0
#define ALPHA 1

#define ECHAP 27

Ocean *o_object = NULL;

GLfloat rotacionX = 0.0f;
GLfloat rotacionY = 0.0f;

GLvoid callback_special(int key, int x, int y)
{
        switch (key)
        {
        case GLUT_KEY_UP:
                rotacionX -= 3.0f;
                glutPostRedisplay();
                break;

        case GLUT_KEY_DOWN:
                rotacionX += 3.0f;
                glutPostRedisplay();
                break;

        case GLUT_KEY_LEFT:
            rotacionY -= 3.0f;
                glutPostRedisplay();
                break;

        case GLUT_KEY_RIGHT:
                rotacionY += 3.0f;
                glutPostRedisplay();
                break;
        }
}

GLvoid initGL()
{
    GLfloat position[] = { 0.0f, 5.0f, 10.0f, 0.0 };

    //enable light : try without it
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glEnable(GL_LIGHTING);
    //light 0 "on": try without it
    glEnable(GL_LIGHT0);

    //shading model : try GL_FLAT
    glShadeModel(GL_SMOOTH);

    glEnable(GL_DEPTH_TEST);

    //enable material : try without it
    //glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    //glEnable(GL_COLOR_MATERIAL);

    glClearColor(255, 255, 255, 255);
}


float t = 0.0;
GLvoid window_display()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60,800.0/600.0, 0.1, 10000);
    //glOrtho(-25.0f, 25.0f, -25.0f, 25.0f, -25.0f, 25.0f);
    //glFrustum(-25.0, 25.0, -25.0, 25.0, -25.0, 20.0);
    //gluLookAt()
    glTranslatef(-50,-30,-150);
    /*dibujar aqui*/
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    o_object->display();
    o_object->update_heights(t);
    t += 0.007;

    glutSwapBuffers();

    glFlush();
}

GLvoid window_reshape(GLsizei width, GLsizei height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(-25.0f, 25.0f, -25.0f, 25.0f, -25.0f, 25.0f);
    gluPerspective(60,800.0/600.0, 0.1, 10000);
    glMatrixMode(GL_MODELVIEW);
}



void init_scene()
{

}

GLvoid window_key(unsigned char key, int x, int y)
{
    switch (key) {
    case ECHAP:
        exit(1);
        break;

    default:
        printf("La touche %d non active.\n", key);
        break;
    }
}


//function called on each frame
GLvoid window_idle()
{


    glutPostRedisplay();
}



int main(int argc, char **argv)
{
    o_object = new Ocean(100,100,1,1);
    o_object->create_list_vertex();
    o_object->create_index_list();
    o_object->load_waves("spectrum.txt");


    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);


    glutInitWindowSize(800, 800);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("TP 2 : Transformaciones");


    initGL();

    glutDisplayFunc(&window_display);

    glutReshapeFunc(&window_reshape);

    glutKeyboardFunc(&window_key);
    glutSpecialFunc(&callback_special);

    //function called on each frame
    glutIdleFunc(&window_idle);

    glutMainLoop();
    return 0;
}

//int main(int argc, char **argv)
//{
//    Ocean o(,15,1,1);
//    o.load_waves("spectrum.txt");
//    return 0;
//}
