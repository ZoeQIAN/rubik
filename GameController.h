#ifndef __GAMECONTROLLER__
#define __GAMECONTROLLER__

#include "Button.h"
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
	void mouseClick(Pos pos);
	void mouseRelease();
	void mouseMove(float x, float y);
	bool isQuit() const{return quit;}

private:
	enum Mode{ACCUEIL, NIVEAU, SCORES, GAME} mode;

	//For the welcome page
	// Button* a_start, a_score, a_quit;
	Button* home[3];

	//For choosing the game level
	// Button* c_simple, c_medium, c_hard, c_back;
	Button* level[4];

	//For the scores page
	Button* s_quit;

	//For the game page
	Button* g_quit;

	//The address of the score files
	string score_file;
	void listScore();
	void buttonAction(Type type);
	//The game will be constructed when the difficulty is chosen
	Rubik *rubik;
	bool quit;
	int clicked_button;
	bool button_clicked;
};

#endif
