#include "Button.h"

void Button::Render()  
{  
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();  
    glOrtho(0, DEFAULT_SCREENWIDTH, 0, DEFAULT_SCREENHEIGHT, 0, DEFAULT_SCREENDEPTH);  
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();  

    glPushMatrix();  
    {  
        //initialize the position, considering its size
        glTranslatef(pos.x+width/2, pos.y+height/2, -20.0);        //-2.0只是为了按钮可见  
        if( m_bPressed )  
        {  
            glScalef(0.9, 0.9, 1.0);  
        }  
        //the center of the cube
        glScalef (width, height, 5.0); 
        glColor3f (1.0, 1.0, 1.0);         
        glutSolidCube(1.0);  
    }  
    glPopMatrix();
}  

bool Button::clicked(Pos p){
    p.y = DEFAULT_SCREENHEIGHT-p.y;
    bool ans;
    if(p.x > pos.x && p.x < pos.x+width &&  p.y > pos.y && p.y < pos.y+height){
        ans=true;
        std::cout << "clicked:" << pos.x << "," << pos.y << std::endl;
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