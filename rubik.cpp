#include "rubik.h"

rubik::rubik(int sz){

	for (int i = 0; i < 3; ++i)
		for (int j=0; j<3; ++j)
			for(int k=0; k<3; ++k){
				int p = k+j*3+i*3*3;
				blocks[p].pos = Vec3i(k,j,i);
				switch(i){
					case 0: blocks[p].sf.push_back(Surface(DOWN,DOWN,1));
					break;
					case 2: blocks[p].sf.push_back(Surface(UP,UP,2));
					break;
					default:
					break;
				}
				switch(j){
					case 0: blocks[p].sf.push_back(Surface(LEFT,LEFT,3));
					break;
					case 2: blocks[p].sf.push_back(Surface(RIGHT,RIGHT,4));
					break;
					default:
					break;
				}
				switch(k){
					case 0: blocks[p].sf.push_back(Surface(BACK,BACK,5));
					break;
					case 2: blocks[p].sf.push_back(Surface(FRONT,FRONT,6));
					break;
					default:
					break;
				}
			}
}

rubik::~rubik(){}

void rubik::shuffle(Level lv){
	 srand(time(NULL));
	 for (int i = 0; i < lv; ++i)
	 {
	 	// int l,m,n;
	 	// do{
	 	// 	l=rand()%6;
	 	// 	m=rand()%size;
	 	// 	n=rand()%size;
	 	// }while(l==1 && m==1 && n==1);
	 	// rotate(Vec3i(l,m,n),rand()%4);
	 	int l=rand()%3;
	 	int m=rand()%3;
	 	int n=rand()%2;
	 	// std::cout << l << " " << m << " " << n << std::endl;
	 	transform(l, m, n==1?true:false);
	 }
}

void rubik::rotate(Vec3i c, Side s, Direction dir){
	switch(s){
		case UP:
		case DOWN:
		switch(dir){
			case U:	transform(1, c[1], true); break;
			case D:	transform(1, c[1], false); break;
			case L:	transform(0, c[0], false); break;
			case R: transform(0, c[0], true); break;
			default: break;
		}
		break;

		case FRONT:
		case BACK:
		switch(dir){
			case U:	transform(1, c[1], true); break;
			case D:	transform(1, c[1], false); break;
			case L:	transform(2, c[2], false); break;
			case R: transform(2, c[2], true); break;
			default: break;
		}
		break;

		case LEFT:
		case RIGHT:
		switch(dir){
			case U:	transform(0, c[0], false); break;
			case D:	transform(0, c[0], true); break;
			case L:	transform(2, c[2], true); break;
			case R: transform(2, c[2], false); break;
			default: break;
		}
		break;

		default:
		break;
			
	}
}

void rubik::transform(int fix,int pf, bool dir){
	int left = (dir?fix+1:fix-1)%3;
	int right = (dir?fix-1:fix+1)%3;
	if(left==-1) left=2;
	if(right==-1) right=2;
	// std::cout << left << " " << right << std::endl;
	// std::cout << std::endl;
	for(int i=0; i<3*3*3; i++){
		if(blocks[i].pos[fix] == pf){
			int vl = blocks[i].pos[left];
			int vr = blocks[i].pos[right];
			blocks[i].pos[left] = vr;
			blocks[i].pos[right] = -vl+2;
			for(int j=0; j<blocks[i].sf.size(); j++){
				blocks[i].sf[j].now = surfaceRotate(blocks[i].sf[j].now,dir,fix);
			}
		}
	}

}

Side rubik::surfaceRotate(Side s, bool dir, int pixel){
	switch(s){
		case UP:
		case DOWN:
		if(pixel == 2) return s;
		break;
		case LEFT:
		case RIGHT:
		if(pixel == 1) return s;
		break;
		case FRONT:
		case BACK:
		if(pixel == 0) return s;
		break;
		default:
		break;
	}

	switch(pixel){
		case 0:
		switch(s){
			case UP: return dir?RIGHT:LEFT;
			break;
			case RIGHT: return dir?DOWN:UP;
			break;
			case DOWN: return dir?LEFT:RIGHT;
			break;
			case LEFT: return dir?UP:DOWN;
			break;
			default:
			break;
		}

		case 1:
		switch(s){
			case DOWN: return dir?FRONT:BACK;
			break;
			case BACK: return dir?DOWN:UP;
			break;
			case UP: return dir?BACK:FRONT;
			break;
			case FRONT: return dir?UP:DOWN;
			break;
			default:
			break;
		}
		break;

		case 2:
		switch(s){
			case BACK: return dir?RIGHT:LEFT;
			break;
			case LEFT: return dir?BACK:FRONT;
			break;
			case FRONT: return dir?LEFT:RIGHT;
			break;
			case RIGHT: return dir?FRONT:BACK;
			break;
			default:
			break;
		}
		break;

	}
	//return UP;
}

bool rubik::judge(){
	for(int i=0; i<3*3*3; i++){
		for(int j=0; j<blocks[i].sf.size(); j++){
			if(blocks[i].sf[j].init != blocks[i].sf[j].now)
				return false;
		}
	}
	return true;
}

void rubik::print2(){
		for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			for(int k=0; k<3; k++){
				int p = k+j*3+i*3*3;
				std::cout << blocks[p].pos << ":";
				for(int m=0; m<blocks[p].sf.size(); m++){
					std::cout << blocks[p].sf[m].now << " ";
				}
				std::cout << std::endl;
			}
		}
	}

}
void rubik::print(){

	int up[3][3];
	int down[3][3];
	int left[3][3];
	int right[3][3];
	int front[3][3];
	int back[3][3];

	// vector<int> up;
	// vector<int> down;
	// vector<int> left;
	// vector<int> right;
	// vector<int> front;
	// vector<int> back;
	for(int i=0; i<3*3*3; i++){
		for(int j=0; j<blocks[i].sf.size(); j++){
			Surface s = blocks[i].sf[j];
			cube c = blocks[i];
			switch(s.now){
				case UP:
				up[c.pos[0]][c.pos[1]] = s.idt; break; 
				case DOWN:
				down[c.pos[0]][c.pos[1]] = s.idt; break;

				case LEFT:
				left[c.pos[0]][c.pos[2]] = s.idt; break;
				case RIGHT:
				right[c.pos[0]][c.pos[2]] = s.idt; break;

				case FRONT:
				front[c.pos[1]][c.pos[2]] = s.idt; break;
				case BACK:
				back[c.pos[1]][c.pos[2]] = s.idt; break;

				default: break;
			}
		}
	}

	std::cout << "UP"	<< std::endl;
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			std::cout << up[j][i] << "\t";
		}
		std::cout << std::endl;
	}

	std::cout << "DOWN"	<< std::endl;
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			std::cout << down[j][i] << "\t";
		}
		std::cout << std::endl;
	}


	std::cout << "LEFT"	<< std::endl;
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			std::cout << left[j][i] << "\t";
		}
		std::cout << std::endl;
	}


	std::cout << "RIGHT"	<< std::endl;
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			std::cout << right[j][i] << "\t";
		}
		std::cout << std::endl;
	}

	std::cout << "FRONT"	<< std::endl;
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			std::cout << front[j][i] << "\t";
		}
		std::cout << std::endl;
	}

	std::cout << "BACK"	<< std::endl;
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			std::cout << back[j][i] << "\t";
		}
		std::cout << std::endl;
	}

}