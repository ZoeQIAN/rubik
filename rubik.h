#ifndef __RUBIK__
#define __RUBIK__

#include <iostream>
#include "Vec3.h"
#include "param.h"

struct Surface{
	Side init, now;
	//int idt;
};

struct cube{
	vector<Surface> sf;
	vec3i pos;
};

class rubik {
public:
	rubik(int sz=3);
	~rubik();

	virtual void shuffle(Level lv);
	//需要传入被点击的面
	virtual void rotate(Vec3i c, Direction dir);

private:
	int size;
	//up down left right front back
	cube blocks[3*3*3];
	bool judge();
	void transform(int fix, int p1, int p2);
	int index(int x,int y, int z);
};


#endif