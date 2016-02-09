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
			std::cerr << "coordinates are: "<<b0<<" "<<b1<<" "<<b2<<" "<<b3<<" "<<std::endl;
			std::cerr << "original point is : "<<b0*vp_ori[0]+b1*vp_ori[1]+b2*vp_ori[2]+b3*vp_ori[3]<<std::endl;
			return b0*vp_ori[0]+b1*vp_ori[1]+b2*vp_ori[2]+b3*vp_ori[3];

		}
		return Vec3f(0.0f,0.0f,0.0f);
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
			 std::cerr<<intersect_point<<std::endl;
			 playing = true;
			 play_origin_point = intersect_point;
			 break;
			}
		}

	}
}

void GameController::mouseMove(float x, float y){
	rubik->selfRotate(x,y);
}

void GameController::mouseRelease(Pos pos, bool leftb){
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
			 std::cerr<<intersect_point<<std::endl;
			 play_dest_point = intersect_point;
			 break;
			}
		}
		if(play_dest_point!= Vec3f(0.0f, 0.0f, 0.0f))
			rubik->play_rotate(play_origin_point,play_dest_point);
		playing = false;
	}
}
