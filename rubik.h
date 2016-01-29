#ifndef __RUBIK__
#define __RUBIK__

#include <iostream>
#include "Vec3.h"
#include "param.h"
#include <vector>

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

class rubik {
public:
	rubik(int sz=3);
	~rubik();

	virtual void shuffle(Level lv);
	//需要传入被点击的面
	virtual void rotate(Vec3i c, Side s, Direction dir);

	void print();
	void print2();

private:
	int size;
	//up down left right front back
	cube blocks[3*3*3];
	bool judge();


	//fix:
	// the axis of rotation, which stays immutable in the rotation
	// x 0 y 1 z 2
	//pf:
	//	the coordinate of the axis of rotation, {0,1,2}
	//dir:
	// true for clockwise
	void transform(int fix, int pf, bool dir);
	Side surfaceRotate(Side s, bool dir, int pixel);
};


#endif