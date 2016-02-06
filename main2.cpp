#include <cstdio>  
#include <cstdlib>  
#include <GLUT/glut.h>  
#include <cmath>  
#include <ctime>  
#include "GameController.h"
//////////////////////////////////////////////////  
//global  

  
static GameController game(DEFAULT_SCREENWIDTH,DEFAULT_SCREENHEIGHT);
  
void init(void)   
{  
    glClearColor (0.0, 0.0, 0.0, 0.0);  
    glShadeModel (GL_SMOOTH);  
  
}  
  
void display(void)  
{  
    glClear (GL_COLOR_BUFFER_BIT);  

  
    game.Render(); 
    // glBegin(GL_QUADS);
    // glColor3f(1,0,0);
    // glVertex3f(0,0,0);
    // glVertex3f(1,0,0);
    // glVertex3f(0,1,0);
    // glVertex3f(1,1,0);
    // glColor3f(0,1,0);
    // glVertex3f(0,1,0);
    // glVertex3f(1,1,0);
    // glVertex3f(0,1,1);
    // glVertex3f(1,1,1);
    
   /* modeling transformation */   

    glFlush();  
    glutSwapBuffers();  
}  
  
void reshape (int w, int h)  
{  
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);   
    glMatrixMode (GL_PROJECTION);  
    glLoadIdentity ();  
    gluPerspective(60,1.0,1.5,20);  
    glMatrixMode (GL_MODELVIEW);  
}  
  
void keyboard(unsigned char key, int x, int y)  
{  
    switch (key) {  
case 27:  
    exit(0);  
    break;  
    }  
}  
  
void mouse(int button, int state, int x, int y)  
{  
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
  
int main(int argc, char** argv)  
{  
    glutInit(&argc, argv);  
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);  
    glutInitWindowSize (DEFAULT_SCREENWIDTH, DEFAULT_SCREENHEIGHT);   
    glutInitWindowPosition (100, 100);  
    glutCreateWindow (argv[0]);  
    init ();  
    glutDisplayFunc(display);   
    glutReshapeFunc(reshape);  
    glutKeyboardFunc(keyboard);  
    glutMouseFunc( mouse );  
    glutMainLoop();  
    return 0;  
}  
