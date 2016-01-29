#include <iostream>
#include "rubik.h"

int main(int argc, char const *argv[])
{
	rubik rub;
	// rub.shuffle(SIMPLE);
	rub.rotate(Vec3i(2,2,2), RIGHT, L);
	rub.print();
	
	// rub.print();
	
	// rub.print();

	return 0;
}