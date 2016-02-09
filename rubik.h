#ifndef __RUBIK__
#define __RUBIK__

#include <iostream>
#include "Vec3.h"
#include "param.h"
#include <vector>
#include <GL/glut.h>
#include "maths_funcs.h"
#include <assert.h>

using std::vector;

struct Surface{
	Side init, now;
	int idt;
	Surface(Side i=UP, Side n=UP, int idt=0) : init(i), now(n), idt(idt){}
};

struct cube{
	vector<Surface> sf;
	Vec3i pos;
};

class Rubik {
public:
	Rubik(Level lv,int sz=3);
	~Rubik();

	
	//需要传入被点击的面
	virtual void rotate(Vec3i c, Side s, Direction dir);

	void printall();
	void print2();
	void Render();

	bool isRotating() const {return rotating;}
	void startRotation(float x,float y);
	void stopRotation();
	void selfRotate(float x, float y);
	float curquat[4];
	Vec3f p[4];
	void play_rotate(Vec3f play_origin_point, Vec3f play_dest_point){
	 //std::cerr<<"doing rotation !!!"<<"origin"<<play_origin_point<<"dest"<<play_dest_point<<std::endl;
	 
	// play_origin_point = (play_origin_point-prefix)/edge_length;
	 Vec3f point_resto = (play_origin_point - prefix)/edge_length;
	 Vec3i cur_cube;
	 Direction dir;
	 cur_cube[0] = floor(point_resto[0]);
	 cur_cube[1] = floor(point_resto[1]);
	 cur_cube[2] = floor(point_resto[2]);
	 //std::cerr<<"doing rotation !!!"<<"origin"<<cur_cube<<std::endl;


	 Vec3f Direction_to_go(play_dest_point - play_origin_point);
	 //std::cerr<<"Direction is"<<Direction_to_go<<std::endl;
	 int max_site;
	 float max_product = 0;
	 for(int i=0;i<3;i++)
	 	if(fabs(Direction_to_go[i])>max_product)
	 	{
	 		max_product = fabs(Direction_to_go[i]);
	 		max_site = i+1;
	 	}
	 if(Direction_to_go[max_site-1]<0) max_site *=-1;

	 //std::cerr<<"Direction is"<<max_site<<std::endl;


	 Side cur_side;
	 if(point_resto[2] == 3)//up
	 { 	
	 	//std::cerr<<"UP SIDE"<<std::endl;
	 	cur_side = UP;
	 	cur_cube[2] = 2;
	 	switch(max_site){
			case -1:	 	dir = U; 
			//std::cerr<<"U"<<std::endl;	
					break;
			case 1:	dir = D;
			// std::cerr<<"D"<<std::endl;	
			 		break;
			case -2:		dir = L; 
			//std::cerr<<"L"<<std::endl;	

					break;
			case 2: 	dir = R; 
			//std::cerr<<"R"<<std::endl;	
					break;
			default: 	assert(-1);
		}
		
	 }
	 else if(point_resto[2] == 0)//down
	 {
	 	//std::cerr<<"DOWN SIDE"<<std::endl;
	 	cur_side = DOWN;
	 	cur_cube[2] = 0;
	 	switch(max_site){
			case 1:	dir = U; 
			//std::cerr<<"U"<<std::endl;
			break;
			case -1:	 	dir = D;
			 //std::cerr<<"D"<<std::endl;
			 break;
			case 2:		dir = L; 
			//std::cerr<<"L"<<std::endl;
			break;
			case -2: 	dir = R; 
			//std::cerr<<"R"<<std::endl;
			break;
			default: 	assert(-1);
		}
	 }
	 else if(point_resto[1] == 3)//right
	 {
	 	//std::cerr<<"RIGHT SIDE"<<std::endl;
	 	cur_side = RIGHT;
	 	cur_cube[1] = 2;
	 	switch(max_site){
			case 3:	 	dir = U; 
			//std::cerr<<"U"<<std::endl;
			break;
			case -3:	dir = D;
			// std::cerr<<"D"<<std::endl;
			 break;
			case 1:		dir = L;
			 //std::cerr<<"L"<<std::endl;
			 break;
			case -1: 	dir = R;
			 //std::cerr<<"R"<<std::endl;
			 break;
			default: 	assert(-1);
		}
	 }
	 else if(point_resto[1] == 0)//left
	 {
	 	//std::cerr<<"LEFT SIDE"<<std::endl;
	 	cur_side = LEFT;
	 	cur_cube[1] = 0;
	 	switch(max_site){
			case 3:	 	dir = U; 
			//std::cerr<<"U"<<std::endl;
			break;
			case -3:	dir = D; 
			//std::cerr<<"D"<<std::endl;
			break;
			case 1:		dir = R; 
			//std::cerr<<"R"<<std::endl;
			break;
			case -1: 	dir = L; 
			//std::cerr<<"L"<<std::endl;
			break;
			default: 	assert(-1);
		}
	 }
	 else if(point_resto[0] == 3)//front
	 {
	 	//std::cerr<<"FRONT SIDE"<<std::endl;
	 	cur_side = FRONT;
	 	cur_cube[0] = 2;
	 	switch(max_site){
			case 3:	 	dir = U; 
			//std::cerr<<"U"<<std::endl;
			break;
			case -3:	dir = D; 
			//std::cerr<<"D"<<std::endl;
			break;
			case 2:		dir = L; 
			//std::cerr<<"L"<<std::endl;
			break;
			case -2: 	dir = R; 
			//std::cerr<<"R"<<std::endl;
			break;
			default: 	assert(-1);
		}
	 }
	 else if(point_resto[0] == 0)//back
	 {
	 	//std::cerr<<"BACK SIDE"<<std::endl;
	 	cur_side = BACK;
	 	cur_cube[0] = 0;
	 	switch(max_site){
			case -3:	 	dir = U; 
			//std::cerr<<"U"<<std::endl;
			break;
			case 3:	dir = D;
			//std::cerr<<"D"<<std::endl;
			break;
			case 2:		dir = R; 
			//std::cerr<<"R"<<std::endl;
			break;
			case -2: 	dir = L; 
			//std::cerr<<"L"<<std::endl;
			break;
			default: 	assert(-1);
		}
	 }
	 else assert(-1);

	 rotate(cur_cube,cur_side,dir);
	}
private:
	int size;
	//up down left right front back

	cube blocks[3*3*3];
	bool judge();
	Vec3f prefix = Vec3f(-1.5 * edge_length,-1.5 * edge_length,-1.5 * edge_length);
	void shuffle(Level lv);
	//fix:
	// the axis of rotation, which stays immutable in the rotation
	// x 0 y 1 z 2
	//pf:
	//	the coordinate of the axis of rotation, {0,1,2}
	//dir:
	// true for clockwise
	void transform(int fix, int pf, bool dir);
	Side surfaceRotate(Side s, bool dir, int pixel);
	void colorMap(Side s, float& r,float& g, float&b);

	bool rotating;
	Vec3f lastPos;
	Vec3f curPos;
	float axis[3];
	float angle;
	void calRotation();
	//vec4 Up[4],Down[4],Left[4],Right[4],Front[4],Back[4];
	//vec4 Up[4];
	//vec4 Up_curr[4];
	//vector<Vec3f[]> Rects_init;
};


#endif
