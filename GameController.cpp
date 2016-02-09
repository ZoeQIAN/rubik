#include "GameController.h"
#include <iostream>
#include "basicfunction.h"
#include "Ray.h"

GameController::GameController(unsigned int screenWidth, unsigned int screenHeight)
:screenHeight(screenHeight), screenWidth(screenWidth){
	//l'accueil
	float w(60);
	float h(20);

	Pos pos = {screenWidth/2, screenHeight*0.6*0.75};
	//std::cout << "button pos" << pos.x << "," << pos.y << std::endl;
	home[0] = new Button(pos,w,h,B_START,"START",true);
	level[0] = new Button(pos,w,h,B_SIMPLE,"SIMPLE",true);

	pos.y = pos.y * 2.0/3.0;
	home[1] = new Button(pos,w,h,B_SCORES,"SCORES");
	level[1] = new Button(pos,w,h,B_MEDIUM,"MEDIUM",true);

	pos.y = pos.y * 0.5;
	home[2] = new Button(pos,w,h,B_QUIT,"QUIT");
	level[2] = new Button(pos,w,h,B_HARD,"HARD",true);

	pos.x = pos.x * 1.5;
	level[3] = new Button(pos,w,h,B_QUIT,"QUIT");
	s_quit = new Button(pos,w,h,B_QUIT,"QUIT");
	g_quit = new Button(pos,w,h,B_QUIT,"QUIT");

	quit = false;
	mode = ACCUEIL;
	button_clicked = false;
	/*
	quit = false;
	mode = GAME;
	rubik = new Rubik(HARD,3);
	*/
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

		break;
		default:
		break;
	}
}

Vec3f FindOriginalIntersect(Ray& r,GLfloat m[4][4],Vec3f p[8],int a,int b,int c,int d)
{
		Vec3f vp[4];
		Vec3f vp_ori[4];
		vp_ori[0]=vp[0] = p[a];
		vp_ori[1]=vp[1] = p[b];
		vp_ori[2]=vp[2] = p[c];
		vp_ori[3]=vp[3] = p[d];
		vp[0].rotate_by_matrix(m);
		vp[1].rotate_by_matrix(m);
		vp[2].rotate_by_matrix(m);
		vp[3].rotate_by_matrix(m);
		//std::cerr << "points locations: "<< vp[0]<<vp[1]<<vp[2]<<std::endl;
		//std::cerr << "ray direction: "<< ray_wor.v[0]<<ray_wor.v[1]<<ray_wor.v[2]<<std::endl;

		if(r.rect_is_intersect_with(vp))
		{
			float b0,b1,b2,b3;
			b0=0;b1=0;b2=0;b3=0;
			r.rect_intersect_at(vp,b0,b1,b2,b3);
			//std::cerr << "coordinates are: "<<b0<<" "<<b1<<" "<<b2<<" "<<b3<<" "<<std::endl;
			//std::cerr << "original point is : "<<b0*vp_ori[0]+b1*vp_ori[1]+b2*vp_ori[2]+b3*vp_ori[3]<<std::endl;
			return b0*vp_ori[0]+b1*vp_ori[1]+b2*vp_ori[2]+b3*vp_ori[3];

		}
		return Vec3f(0.0f,0.0f,0.0f);
}

void GameController::mouseClick(Pos pos, bool leftb){
		switch(mode){
		case ACCUEIL:
		{
			unsigned int i=0;
			while(i<3 && !home[i++]->clicked(pos)){}
			if(i<3){
				home[--i]->mouseClick();
				clicked_button=i;
				button_clicked=true;
				//std::cout << "i" << i << std::endl;

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

		if(leftb)
			rubik->startRotation(pos.x,pos.y);
		else
		{
			GLfloat m[4][4];
	  		build_rotmatrix(m, rubik->curquat);

			Vec3f p[8];
			p[0] = rubik->p[0];
			p[1] = rubik->p[1];
			p[2] = rubik->p[2];
			p[3] = rubik->p[3];


			p[4] = -1.0f * p[2];
			p[5] = -1.0f * p[3];
			p[6] = -1.0f * p[0];
			p[7] = -1.0f * p[1];

			//std::cout<<p[4]<<p[5]<<p[6]<<p[7]<<std::endl;

			float x = (2.0f * pos.x) / screenWidth - 1.0f;
			float y = 1.0f - (2.0f * pos.y) / screenHeight;
			float z = 1.0f;
			float cam_x, cam_y,cam_z;
			cam_x = 0;cam_y=0;cam_z = 3;

			// normalised device space
			vec3 ray_nds = vec3 (x, y, z);
			// clip space
			vec4 ray_clip = vec4 (ray_nds.v[0], ray_nds.v[1], -1.0, 1.0);
			// eye space
			// homogenous coordinates
			float aspect = (float)screenWidth / (float)screenHeight; // aspect ratio
			mat4 proj= perspective (45.0, aspect, 0.1, 10000.0);

			float cam_heading = 0.0f; // y-rotation in degrees
			mat4 T = translate (
				identity_mat4 (), vec3 (-cam_x, -cam_y, -cam_z)
				);
			mat4 R = rotate_y_deg (identity_mat4 (), -cam_heading);
			mat4 view_mat = R * T;

			vec4 ray_eye = inverse (proj ) * ray_clip;
			//ray_eye.xyz /= ray_eye.w;
			//ray_eye.w = 1.0f;

			ray_eye = vec4 (ray_eye.v[0], ray_eye.v[1], -1.0, 0.0);
			// world space
			vec3 ray_wor = vec3 (inverse (view_mat) * ray_eye);
			// don't forget to normalise the vector at some point
			ray_wor = normalise (ray_wor);

			Ray r(Vec3f(cam_x, cam_y,cam_z), Vec3f(ray_wor.v[0],ray_wor.v[1], ray_wor.v[2]));
			Vec3f intersect_point = Vec3f(0.0f, 0.0f, 0.0f);
									//up, down, front, back, left, right
			int Verteces[6][4] = { {0 , 1, 2,  3}, { 7, 6, 5, 4}, {3, 2, 6, 7} ,{1, 0, 4, 5} ,{0, 3, 7, 4},{ 2, 1, 5, 6}};

			for(int i=0;i<6;i++){
				Vec3f point= FindOriginalIntersect(r,m,p,Verteces[i][0],Verteces[i][1],Verteces[i][2],Verteces[i][3]);
				if(point!= Vec3f(0.0f, 0.0f, 0.0f)){
				 intersect_point = point;
				 //std::cerr<<intersect_point<<std::endl;
				 playing = true;
				 play_origin_point = intersect_point;
				 break;
				}
			}

		}
		break;
		default:
		break; 
	}

}

void GameController::mouseMove(float x, float y){
	if(mode == GAME)
		rubik->selfRotate(x,y);
}

void GameController::mouseRelease(Pos pos, bool leftb){
	//if(!button_clicked) return;
	switch(mode){
		case ACCUEIL:
		if(!button_clicked) return;
		buttonAction(home[clicked_button]->getType());
		home[clicked_button]->mouseRelease();
		break;

		case NIVEAU:
		if(!button_clicked) return;
		buttonAction(level[clicked_button]->getType());
		level[clicked_button]->mouseRelease();
		break;

		case SCORES:
		if(!button_clicked) return;
		s_quit->mouseRelease();
		mode = ACCUEIL;
		break;

		case GAME:
		if(leftb)
			rubik->stopRotation();
		else if(playing == true&&!leftb){
			GLfloat m[4][4];
	  		build_rotmatrix(m, rubik->curquat);

			Vec3f p[8];
			p[0] = rubik->p[0];
			p[1] = rubik->p[1];
			p[2] = rubik->p[2];
			p[3] = rubik->p[3];


			p[4] = -1.0f * p[2];
			p[5] = -1.0f * p[3];
			p[6] = -1.0f * p[0];
			p[7] = -1.0f * p[1];

			float x = (2.0f * pos.x) / screenWidth - 1.0f;
			float y = 1.0f - (2.0f * pos.y) / screenHeight;
			float z = 1.0f;
			float cam_x, cam_y,cam_z;
			cam_x = 0;cam_y=0;cam_z = 3;

			// normalised device space
			vec3 ray_nds = vec3 (x, y, z);
			// clip space
			vec4 ray_clip = vec4 (ray_nds.v[0], ray_nds.v[1], -1.0, 1.0);
			// eye space
			// homogenous coordinates
			float aspect = (float)screenWidth / (float)screenHeight; // aspect ratio
			mat4 proj= perspective (45.0, aspect, 0.1, 10000.0);

			float cam_heading = 0.0f; // y-rotation in degrees
			mat4 T = translate (
				identity_mat4 (), vec3 (-cam_x, -cam_y, -cam_z)
				);
			mat4 R = rotate_y_deg (identity_mat4 (), -cam_heading);
			mat4 view_mat = R * T;

			vec4 ray_eye = inverse (proj ) * ray_clip;
			//ray_eye.xyz /= ray_eye.w;
			//ray_eye.w = 1.0f;

			ray_eye = vec4 (ray_eye.v[0], ray_eye.v[1], -1.0, 0.0);
			// world space
			vec3 ray_wor = vec3 (inverse (view_mat) * ray_eye);
			// don't forget to normalise the vector at some point
			ray_wor = normalise (ray_wor);

			Ray r(Vec3f(cam_x, cam_y,cam_z), Vec3f(ray_wor.v[0],ray_wor.v[1], ray_wor.v[2]));
			Vec3f intersect_point = Vec3f(0.0f, 0.0f, 0.0f);
									//up, down, front, back, left, right
			int Verteces[6][4] = { {0 , 1, 2,  3}, { 7, 6, 5, 4}, {3, 2, 6, 7} ,{1, 0, 4, 5} ,{0, 3, 7, 4},{ 2, 1, 5, 6}};
			play_dest_point = Vec3f(0.0f, 0.0f, 0.0f);
			for(int i=0;i<6;i++){
				Vec3f point= FindOriginalIntersect(r,m,p,Verteces[i][0],Verteces[i][1],Verteces[i][2],Verteces[i][3]);
				if(point!= Vec3f(0.0f, 0.0f, 0.0f)){
				 intersect_point = point;
				 //std::cerr<<intersect_point<<std::endl;
				 play_dest_point = intersect_point;
				 break;
				}
			}
			if(play_dest_point!= Vec3f(0.0f, 0.0f, 0.0f))
				rubik->play_rotate(play_origin_point,play_dest_point);
			playing = false;
		}
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