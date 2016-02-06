// ----------------------------------------------
// Informatique Graphique 3D & R�alit� Virtuelle.
// Travaux Pratiques
// Algorithmes de Rendu
// Copyright (C) 2015 Tamy Boubekeur
// All rights reserved.
// ----------------------------------------------

#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
//#include <GL/glut.h>
#include <GLUT/glut.h>
#include "Vec3.h"
#include "Camera.h"
#include "GameController.h"

using namespace std;

static string appTitle ("IGRV Final Projet - Rubik Cube");
static GLint window;
static unsigned int FPS = 0;
static bool fullScreen = false;

static Camera camera;
static Rubik rubik(SIMPLE,3);
static GameController game(DEFAULT_SCREENWIDTH,DEFAULT_SCREENHEIGHT);
// static Mesh mesh;

void printUsage () {
    // std::cerr << std::endl
    //   << appTitle << std::endl
 //         << "Author: Tamy Boubekeur" << std::endl << std::endl
 //         << "Usage: ./main [<file.off>]" << std::endl
 //         << "Commands:" << std::endl
 //         << "------------------" << std::endl
 //         << " ?: Print help" << std::endl
    //   << " w: Toggle wireframe mode" << std::endl
 //         << " <drag>+<left button>: rotate model" << std::endl
 //         << " <drag>+<right button>: move model" << std::endl
 //         << " <drag>+<middle button>: zoom" << std::endl
 //         << " q, <esc>: Quit" << std::endl << std::endl;
}

void init () {
    glCullFace (GL_BACK);     // Specifies the faces to cull (here the ones pointing away from the camera)
    glEnable (GL_CULL_FACE); // Enables face culling (based on the orientation defined by the CW/CCW enumeration).
    glDepthFunc (GL_LESS); // Specify the depth test for the z-buffer
    glEnable (GL_DEPTH_TEST); // Enable the z-buffer in the rasterization
    glLineWidth (2.0); // Set the width of edges in GL_LINE polygon mode
    glClearColor (0.0f, 0.0f, 0.0f, 1.0f); // Background color
    // glClearColor (1.0f, 1.0f, 1.0f, 1.0f);

    glShadeModel (GL_SMOOTH);  
    // mesh.loadOFF (modelFilename);
}

void drawScene () {
    // rubik.Render(ang_x, ang_y);
    game.Render(); 

    // glMatrixMode(GL_PROJECTION);  
    // glLoadIdentity();  
    // glOrtho(0, DEFAULT_SCREENWIDTH, 0, DEFAULT_SCREENHEIGHT, 0, DEFAULT_SCREENDEPTH);  
    // glMatrixMode(GL_MODELVIEW);  
    // glLoadIdentity();  

    // glPushMatrix();
    
    // gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    // glTranslatef(200,200,-100);
    // glRotatef(-ang, 0.0, 1.0, 0.0);  
    // glTranslatef(-50,-50,50);
    // glBegin(GL_QUADS);

    // glNormal3f(0,0,1);
    // glColor3f(1,0,0);
    // glVertex3f(100,0,0);
    // glVertex3f(100,100,0);
    // glVertex3f(0,100,0);
    // glVertex3f(0,0,0);
 
    // glNormal3f(1,0,0);
    // glColor3f(1,1,0);
    // glVertex3f(100,100,-100);
    // glVertex3f(100,100,0);
    // glVertex3f(100,0,0);
    // glVertex3f(100,0,-100);
    // glColor3f(1,1,0);
    // glVertex3f(200,0,0);
    // glVertex3f(200,100,0);
    // glVertex3f(100,100,0);
    // // glVertex3f(100,0,0);

    // glEnd();

    // glPopMatrix();
    

}

void reshape(int w, int h) {
    camera.resize (w, h);
}

void display () {
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera.apply();
    drawScene ();
    glFlush ();
    glutSwapBuffers ();
}

void key (unsigned char keyPressed, int x, int y) {
    switch (keyPressed) {
    case 'f':
        if (fullScreen) {
            // glutReshapeWindow (camera.getScreenWidth (), camera.getScreenHeight ());
            fullScreen = false;
        } else {
            glutFullScreen ();
            fullScreen = true;
        }
        break;
    case 'q':
    case 27:
        exit (0);
        break;
    case 'w':
        GLint mode[2];
        glGetIntegerv (GL_POLYGON_MODE, mode);
        glPolygonMode (GL_FRONT_AND_BACK, mode[1] ==  GL_FILL ? GL_LINE : GL_FILL);
        break;
        break;
    default:
        printUsage ();
        break;
    }
}

void mouse (int button, int state, int x, int y) {
    // camera.handleMouseClickEvent (button, state, x, y);
    if(button==GLUT_LEFT_BUTTON)  
    switch(state)  
    {  
        case GLUT_DOWN:  { 
            std::cout << "Mouse pos :" << x <<"," << 500-y << std::endl;
            Pos pos={x,y};  
            game.mouseClick(pos);
            break;  
        }
        case GLUT_UP:  
            game.mouseRelease(); 
            break;  
    }  
    if(game.isQuit()) exit(0);
    glutPostRedisplay();  
}

void motion(int x, int y){
    game.mouseMove(x,y);
}

void idle () {
    static float lastTime = glutGet ((GLenum)GLUT_ELAPSED_TIME);
    static unsigned int counter = 0;
    counter++;
    float currentTime = glutGet ((GLenum)GLUT_ELAPSED_TIME);
    if (currentTime - lastTime >= 1000.0f) {
        FPS = counter;
        counter = 0;
        static char winTitle [128];
        // unsigned int numOfTriangles = mesh.T.size ();
        // sprintf (winTitle, "Number Of Triangles: %d - FPS: %d", numOfTriangles, FPS);
        glutSetWindowTitle (winTitle);
        lastTime = currentTime;
    }
    glutPostRedisplay ();
}

int main (int argc, char ** argv) {
    if (argc > 2) {
        printUsage ();
        exit (1);
    }
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize (DEFAULT_SCREENWIDTH, DEFAULT_SCREENHEIGHT);
    window = glutCreateWindow (appTitle.c_str ());
    // init (argc == 2 ? argv[1] : DEFAULT_MESH_FILE.c_str ());
    init();
    glutIdleFunc (idle);
    glutReshapeFunc (reshape);
    glutDisplayFunc (display);
    glutKeyboardFunc (key);
    glutMouseFunc (mouse);
    glutMotionFunc (motion);
    printUsage ();
    glutMainLoop ();
    return 0;
}
