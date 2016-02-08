#ifndef __RUBIK__
#define __RUBIK__

#include <iostream>
#include "Vec3.h"
#include "param.h"
#include <vector>
#include <GL/glut.h>
#include "maths_funcs.h"

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
private:
	int size;
	//up down left right front back

	cube blocks[3*3*3];
	bool judge();

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
