#include "GameController.h"
#include <iostream>

GameController::GameController(unsigned int screenWidth, unsigned int screenHeight){
	//l'accueil
	float w(60);
	float h(20);

	quit = false;
	mode = GAME;
	rubik = new Rubik(HARD,3); 	
}

GameController::~GameController(){
}

void GameController::Render(){
		rubik->Render();
}

void GameController::mouseClick(Pos pos, bool leftb){
	if(leftb)
		rubik->startRotation(pos.x,pos.y);
	else
	{

	}
}

void GameController::mouseMove(float x, float y){
	rubik->selfRotate(x,y);
}

void GameController::mouseRelease( bool leftb){
	if(leftb)
		rubik->stopRotation();
	else{

	}
}
