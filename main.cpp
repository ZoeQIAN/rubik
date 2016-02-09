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
#include <GL/glut.h>
#include "Vec3.h"
#include "Camera.h"
#include "GameController.h"
#include "Texture.h"

using namespace std;

static string appTitle ("IGRV Final Projet - Rubik Cube");
static GLint window;
static unsigned int FPS = 0;
static bool fullScreen = false;

static Camera camera;
static Rubik rubik(SIMPLE,3);
static GameController game(DEFAULT_SCREENWIDTH,DEFAULT_SCREENHEIGHT);
// static Mesh mesh;

GLint texture;
Texture *t1;

GLfloat LightAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //环境光参数，半亮白色
GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //漫射光参数，
GLfloat LightSpecular[] = { 0.5f, 0.5f, 0.5f, 1.0f }; //漫射光参数，
GLfloat LightPosition1[] = { 0.0f, 0.0f, 100.0f, -1.0f }; //光源位置
GLfloat LightPosition2[] = { 10.0f, 10.0f, 590.0f, -1.0f }; //光源位置
GLfloat LightPosition3[] = { 5423.0f, -5340.0f, 1200.0f, -1.0f }; //光源位置

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
/*
void initLighting () {
    GLfloat light_position1[4] = {52, 16, 50, 0};
    GLfloat light_position2[4] = {26, 48, 50, 0};
    GLfloat light_position3[4] = {-16, 52, 50, 0};
    GLfloat direction1[3] = {-52,-16,-50};
    GLfloat direction2[3] = {-26,-48,-50};
    GLfloat direction3[3] = {16,-52,-50};
    GLfloat color1[4] = {1,0, 0, 1};
    GLfloat color2[4] = {0, 1, 0, 1};
    GLfloat color3[4] = {0, 0, 1, 1};
    GLfloat ambient[4] = {0.1f, 0.1f, 0.1f, 0.5f};
    glLightfv (GL_LIGHT1, GL_POSITION, light_position1);
    glLightfv (GL_LIGHT1, GL_SPOT_DIRECTION, direction1);
    glLightfv (GL_LIGHT1, GL_DIFFUSE, color1);
    glLightfv (GL_LIGHT1, GL_SPECULAR, color1);
    glLightfv (GL_LIGHT2, GL_POSITION, light_position2);
    glLightfv (GL_LIGHT2, GL_SPOT_DIRECTION, direction2);
    glLightfv (GL_LIGHT2, GL_DIFFUSE, color2);
    glLightfv (GL_LIGHT2, GL_SPECULAR, color2);
    glLightfv (GL_LIGHT3, GL_POSITION, light_position3);
    glLightfv (GL_LIGHT3, GL_SPOT_DIRECTION, direction3);
    glLightfv (GL_LIGHT3, GL_DIFFUSE, color3);
    glLightModelfv (GL_LIGHT_MODEL_AMBIENT, ambient);
    glEnable (GL_LIGHT1);
    glEnable (GL_LIGHT2);
    glEnable (GL_LIGHT3);
    glDisable (GL_LIGHT0);
    glEnable (GL_LIGHTING);
}

void initMaterial () {
    GLfloat material_color[4] = {1,1,1,1.0f};
    GLfloat material_specular[4] = {0.85,0.85,0.85,1.0};
    GLfloat material_ambient[4] = {0.0,0.0,0.0,0.0};
    glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, material_specular);
    glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE, material_color);
    glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient);
    glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 128.0f);
}
*/
void init () {
    glCullFace (GL_BACK);     // Specifies the faces to cull (here the ones pointing away from the camera)
    glEnable (GL_CULL_FACE); // Enables face culling (based on the orientation defined by the CW/CCW enumeration).
    glDepthFunc (GL_LESS); // Specify the depth test for the z-buffer
    glEnable (GL_DEPTH_TEST); // Enable the z-buffer in the rasterization
    glLineWidth (2.0); // Set the width of edges in GL_LINE polygon mode
    glClearColor (0.0f, 0.0f, 0.0f, 1.0f); // Background color
    // glClearColor (1.0f, 1.0f, 1.0f, 1.0f);

    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient); //设置环境光
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse); //设置漫射光
    glLightfv(GL_LIGHT1, GL_POSITION, LightPosition1); //设置光源位置
    glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular);
    
    glLightfv(GL_LIGHT2, GL_AMBIENT, LightAmbient); //设置环境光
    glLightfv(GL_LIGHT2, GL_DIFFUSE, LightDiffuse); //设置漫射光
    glLightfv(GL_LIGHT2, GL_POSITION, LightPosition2); //设置光源位置
    glLightfv(GL_LIGHT2, GL_SPECULAR, LightSpecular);
    
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHTING);

    GLfloat a[] = { 0.1, 0.1, 0.1, 1.0 };
    glColor4f(1.0, 1.0, 1.0, 1.0);
   
    glEnable(GL_TEXTURE_2D); // Activation de la texturation 2D
    
    GLfloat white[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 80.0f);
    
    glColorMaterial(GL_FRONT, GL_AMBIENT);
    glEnable(GL_COLOR_MATERIAL);
    
    glShadeModel (GL_SMOOTH);
    // mesh.loadOFF (modelFilename);

    t1=new Texture();
    t1->readImage("wood1.ppm");
    t1->createTexture(1);  

    camera.resize (DEFAULT_SCREENWIDTH, DEFAULT_SCREENHEIGHT);
    // mesh.loadOFF (modelFilename);
}

void drawScene () {
    if(game.isGameMode())
    {
        /*
        glMatrixMode(GL_PROJECTION);  
        glLoadIdentity();  
        glOrtho(0, DEFAULT_SCREENWIDTH, 0, DEFAULT_SCREENHEIGHT, 0, DEFAULT_SCREENDEPTH);  
        glMatrixMode(GL_MODELVIEW);  
        glLoadIdentity();  

        glPushMatrix();  
        glBindTexture(GL_TEXTURE_2D, 1);
        glBegin(GL_QUADS);
        glColor3f(155,55,85);
        glNormal3f(0,0,1);
        glTexCoord2f(1.0f,1.0f);
        glVertex3f(150,150,-100);
        glTexCoord2f(0.0f,1.0f);
        glVertex3f(-150,150,-100);
        glTexCoord2f(0.0f,0.0f);
        glVertex3f(-150,-150,-100);
        glTexCoord2f(1.0f,0.0f);
        glVertex3f(150,-150,-100);
        glEnd();

        glPopMatrix();
        */

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, 1);
        glBegin(GL_QUADS);
        glColor3f(155,55,85);
        glNormal3f(0,0,1);
        float k = 0.1;
        glTexCoord2f(1.0f,1.0f);
        glVertex3f(25*k,5*k,-2);
        glTexCoord2f(0.0f,1.0f);
        glVertex3f(-5*k,5*k,-2);
        glTexCoord2f(0.0f,0.0f);
        glVertex3f(-15*k,-10*k,0.1);
        glTexCoord2f(1.0f,0.0f);
        glVertex3f(10*k,-10*k,0.1);
        glEnd();
        glPopMatrix();


        camera.resize (DEFAULT_SCREENWIDTH, DEFAULT_SCREENHEIGHT);
    }

    game.Render(); 
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
    Pos pos={float(x),float(y)}; 
    if(button==GLUT_LEFT_BUTTON)  
    {
    switch(state)  
    {  
        case GLUT_DOWN:  { 
            //std::cout << "Mouse pos :" << x <<"," << 500-y << std::endl
            game.mouseClick(pos, true);
            break;  
        }
        case GLUT_UP:  
            game.mouseRelease(pos,true); 
            //float cam_x, cam_y,cam_z;
            //camera.getPos(cam_x, cam_y,cam_z);
            //std::cerr<<"camera position: "<<cam_x<<cam_y<<cam_z<<endl;
            break;  
    }  
    }
    else if(button == GLUT_RIGHT_BUTTON)
    {
    switch(state)
    {
        case GLUT_DOWN:  { 
            game.mouseClick(pos, false);
            break;  
        }
        case GLUT_UP:  
            game.mouseRelease( pos,false); 
            break;  
    }
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
