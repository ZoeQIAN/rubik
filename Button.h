#ifndef __BUTTON__
#define __BUTTON__
#include "param.h"
#include <GLUT/glut.h>
#include <iostream>
enum Type {B_START, B_SCORES, B_QUIT, B_SIMPLE=10, B_MEDIUM=20, B_HARD=30};

struct Pos{float x,y;};
typedef struct Pos Pos;

class Button{  
public:
	Button(Pos pos, float w, float h, Type t): pos(pos), width(w), height(h), type(t) {}
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
  
    bool m_bPressed; 
    Type type;
};

#endif