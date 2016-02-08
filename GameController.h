#ifndef __GAMECONTROLLER__
#define __GAMECONTROLLER__

#include "param.h"
#include "rubik.h"
#include <string>
#include <iostream>
#include <GL/glut.h>

using std::string;

class GameController{
public:
	GameController(unsigned int screenWidth, unsigned int screenHeight);
	~GameController();

	void Render();
	void mouseClick(Pos pos, bool leftb);
	void mouseRelease(Pos pos,bool leftb);
	void mouseMove(float x, float y);
	bool isQuit() const{return quit;}

private:
	enum Mode{ACCUEIL, NIVEAU, SCORES, GAME} mode;
	unsigned int screenWidth, screenHeight;
	//The game will be constructed when the difficulty is chosen
	Rubik *rubik;
	bool quit;	
	bool playing;
	Vec3f play_origin_point, play_dest_point;
};

#endif
