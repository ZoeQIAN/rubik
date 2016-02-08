#include "GameController.h"
#include <iostream>
#include "basicfunction.h"
#include "Ray.h"

GameController::GameController(unsigned int screenWidth, unsigned int screenHeight)
:screenHeight(screenHeight), screenWidth(screenWidth){
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
		//float quat[4];
		//for(int i=0;i<4;i++)
		//	quat[i] = rubik->curquat[i];
		GLfloat m[4][4]; 
  		build_rotmatrix(m, rubik->curquat);

		Vec3f p[8];
		p[0] = rubik->p[0];
		p[1] = rubik->p[1];
		p[2] = rubik->p[2];
		p[3] = rubik->p[3];

		p[0].rotate_by_matrix(m);
		p[1].rotate_by_matrix(m);
		p[2].rotate_by_matrix(m);
		p[3].rotate_by_matrix(m);

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
		Vec3f vp[4];
		Vec3f intersect_point;
		//===UP
		vp[0] = p[0];
		vp[1] = p[1];
		vp[2] = p[2];
		vp[3] = p[3];
		std::cerr << "points locations: "<< vp[0]<<vp[1]<<vp[2]<<std::endl;
		std::cerr << "ray direction: "<< ray_wor.v[0]<<ray_wor.v[1]<<ray_wor.v[2]<<std::endl;
		//std::cerr<<"camera position: "<<cam_x<<cam_y<<cam_z<<std::endl;
		if(r.is_intersect_with(vp[0],vp[1],vp[3]))
		{
			intersect_point = r.intersect_at(vp[0],vp[1],vp[3]);
			std::cerr << "is intersect with UP!"<<intersect_point<<std::endl;
		}
		else if(r.is_intersect_with(vp[1],vp[2],vp[3]))
		{
			intersect_point = r.intersect_at(vp[1],vp[2],vp[3]);
			std::cerr << "is intersect with UP!"<<intersect_point<<std::endl;
		}


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
