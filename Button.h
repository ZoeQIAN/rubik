#ifndef __BUTTON__
#define __BUTTON__
#include "param.h"
#include <GL/glut.h>
#include <iostream>
#include <string>
using namespace std;

enum Type {B_START, B_SCORES, B_QUIT, B_SIMPLE=10, B_MEDIUM=20, B_HARD=30};


class Button{  
public:
	Button(Pos pos, float w, float h, Type t, char* label, bool active = false): pos(pos), width(w), height(h), type(t),label(label),active(active) {}
	~Button() {}

	Pos getPos() const {return pos;}
	Type getType() const {return type;}
	

	void Render();
	bool clicked(Pos pos);
	void mouseClick();
	void mouseRelease();

private:
    Pos pos;	//position
    float width,height; //size
  	
    bool m_bPressed=false; 
    bool highlighted=false;// if mouse is over the control, highlight it
    char* label; //the text of the button
    bool active;//delete the buttons out of function
    Type type;
};

#endif