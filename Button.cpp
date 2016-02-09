#include "Button.h"
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
//from https://nccastaff.bournemouth.ac.uk/jmacey/RobTheBloke/www/opengl_programming.html#2
void Font(void *font,unsigned char *text,int x,int y)
{
    glRasterPos2i(x, y);

    while( *text != '\0' )
    {
        glutBitmapCharacter( font, *text );
        ++text;
    }
}

void Button::Render()  
{  
    if(!active) return;

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    unsigned char label[20];
    strcpy( (char*) label, this->label );

    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();  
    glOrtho(0, DEFAULT_SCREENWIDTH, 0, DEFAULT_SCREENHEIGHT, -1, 1);  
    //glOrtho(0,DEFAULT_SCREENWIDTH,DEFAULT_SCREENHEIGHT,0,-1,1);
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();  

    glPushMatrix();  
    {  
        /*
        //initialize the position, considering its size
        glTranslatef(pos.x+width/2, pos.y+height/2, -20.0);        //-2.0只是为了按钮可见  
        if( m_bPressed )  
        {  
            glScalef(0.9, 0.9, 1.0);  
        }  
        //the center of the cubez
        glScalef (width, height, 5.0); 
        glColor3f (1.0, 1.0, 1.0);         
        glutSolidCube(1.0); 
        */
         if (m_bPressed) 
            glColor3f(0.7f,0.7f,0.8f);
        else 
            glColor3f(0.6f,0.6f,0.6f);

        glBegin(GL_QUADS);
            glVertex2i( pos.x     , pos.y      );
            glVertex2i( pos.x     , pos.y+height );
            glVertex2i( pos.x+width, pos.y+height );
            glVertex2i( pos.x+width, pos.y      );
        glEnd();

        glLineWidth(3);

        glColor3f(0.8f,0.8f,0.8f);
        glBegin(GL_LINE_STRIP);
            glVertex2i( pos.x+width, pos.y      );
            glVertex2i( pos.x     , pos.y      );
            glVertex2i( pos.x     , pos.y+height );
        glEnd();

        glColor3f(0.4f,0.4f,0.4f);
        glBegin(GL_LINE_STRIP);
            glVertex2i( pos.x     , pos.y+height );
            glVertex2i( pos.x+width, pos.y+height );
            glVertex2i( pos.x+width, pos.y      );
        glEnd();

        glLineWidth(1);

        //text content
        int fontx;
        int fonty;
        fontx = pos.x + (width - glutBitmapLength(GLUT_BITMAP_HELVETICA_10, label)) / 2 ;
        fonty = pos.y + (height+1)/2;

        if(m_bPressed)
        {
            glColor3f(0,0,0);
            Font(GLUT_BITMAP_HELVETICA_10,label,fontx,fonty);
            fontx--;
            fonty--;
        }

        glColor3f(1,1,1);
        Font(GLUT_BITMAP_HELVETICA_10,label,fontx,fonty);

    }  
    glPopMatrix();
}  

bool Button::clicked(Pos p){
    p.y = DEFAULT_SCREENHEIGHT-p.y;
    bool ans;
    if(p.x > pos.x && p.x < pos.x+width &&  p.y > pos.y && p.y < pos.y+height){
        ans=true;
        //std::cout << "clicked:" << pos.x << "," << pos.y << std::endl;
    }
    else ans=false;
    return ans;
}

void Button::mouseClick()  
{  
    m_bPressed = true;        
}  

void Button::mouseRelease()  
{  
    m_bPressed = false;  
}  