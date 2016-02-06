#include "GameController.h"
#include <iostream>

GameController::GameController(unsigned int screenWidth, unsigned int screenHeight){
	//l'accueil
	float w(60);
	float h(20);

	Pos pos = {screenWidth/2, screenHeight*0.6*0.75};
	std::cout << "button pos" << pos.x << "," << pos.y << std::endl;
	home[0] = new Button(pos,w,h,B_START);
	level[0] = new Button(pos,w,h,B_SIMPLE);

	pos.y = pos.y * 2.0/3.0;
	home[1] = new Button(pos,w,h,B_SCORES);
	level[1] = new Button(pos,w,h,B_MEDIUM);

	pos.y = pos.y * 0.5;
	home[2] = new Button(pos,w,h,B_QUIT);
	level[2] = new Button(pos,w,h,B_HARD);

	pos.x = pos.x * 1.5;
	level[3] = new Button(pos,w,h,B_QUIT);
	s_quit = new Button(pos,w,h,B_QUIT);
	g_quit = new Button(pos,w,h,B_QUIT);

	quit = false;
	mode = ACCUEIL;
	button_clicked = false;
}

GameController::~GameController(){
	for(int i=0; i<3; i++)
		delete home[i];
	for(int i=0; i<4; i++)
		delete level[i];
	delete s_quit;
	delete g_quit;
}

void GameController::Render(){

	switch(mode){
		case ACCUEIL:
		for(int i=0; i<3; i++)
			home[i]->Render();
		break;
		case NIVEAU:
		for(int i=0; i<4; i++){
			level[i]->Render();
		}
		break;
		case SCORES:
		listScore();
		break;
		case GAME:
		rubik->Render();
		// std::cerr << "Game part not implemented" << std::endl;
		break;
		default:
		break;
	}
}

void GameController::mouseClick(Pos pos){
	switch(mode){
		case ACCUEIL:
		{
			unsigned int i=0;
			while(i<3 && !home[i++]->clicked(pos)){}
			if(i<3){
				home[--i]->mouseClick();
				clicked_button=i;
				button_clicked=true;
				std::cout << "i" << i << std::endl;

			} 
			else button_clicked=false;
		}
		std::cout << "ACCUEIL" << std::endl;
		break;
		case NIVEAU:
		{	
			int i=0;
			while(!level[i++]->clicked(pos)){}
			if(i<4){
				level[--i]->mouseClick();
				clicked_button=i;	
				button_clicked=true;			
			}
			else button_clicked=false;
		}		
		std::cout << "NIVEAU" << std::endl;
		break;
		case SCORES:
		if(s_quit->clicked(pos)){
			s_quit->mouseClick();
			button_clicked=true;
		}
		else
			button_clicked=false;
		std::cout << "SCORES" << std::endl;
		break;
		case GAME:
		if(g_quit->clicked(pos)){
			button_clicked=true;
			g_quit->mouseClick();
			break;
		}
		else
			button_clicked=false;
		rubik->startRotation(pos.x,pos.y);
		break;
		default:
		break; 
	}

}

void GameController::mouseMove(float x, float y){
	rubik->selfRotate(x,y);
}

void GameController::mouseRelease(){
	if(!button_clicked) return;
	switch(mode){
		case ACCUEIL:
		buttonAction(home[clicked_button]->getType());
		home[clicked_button]->mouseRelease();
		break;
		case NIVEAU:
		buttonAction(level[clicked_button]->getType());
		level[clicked_button]->mouseRelease();
		break;
		case SCORES:
		s_quit->mouseRelease();
		mode = ACCUEIL;
		break;
		case GAME:
		if(button_clicked)
			g_quit->mouseRelease();
		else
			rubik->stopRotation();
		mode = ACCUEIL;
		break;
		default:
		break; 
	}
}

void GameController::buttonAction(Type type){
	switch(mode){
		case ACCUEIL:
		switch(type){
			case B_START:
			mode = NIVEAU;
			std::cout << "START" << std::endl;
			break;
			case B_SCORES:
			mode = SCORES;
			std::cout <<"SCORES" << std::endl;
			break;
			case B_QUIT:
			quit = true;
			std::cout << "QUIT" << std::endl;
			break;
			default:
			break;
		}
		break;

		case NIVEAU:
		if(type==B_QUIT){
			mode = ACCUEIL;
			break;
		}
		Level lv=(Level)type;
		//construct corresponding rubik
		rubik = new Rubik(lv,3);
		mode = GAME;
		break;
	}
}

void GameController::listScore(){}