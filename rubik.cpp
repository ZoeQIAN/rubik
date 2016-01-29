#include "rubik.h"

rubik::rubik(int sz){

	for (int i = 0; i < 3; ++i)
		for (int j=0; j<3; ++j)
			for(int k=0; k<3; ++k){
				int p = k+j*3+i*3;
				blocks[p].pos = Vec3i(k,j,i);
				switch(i){
					case 0: blocks[p].sf.push_back({Surface::DOWN,Surface::DOWN});
					break;
					case 2: blocks[p].sf.push_back({Surface::UP,Surface::UP});
					break;
					default:
					break;
				}
				switch(j){
					case 0: blocks[p].sf.push_back({Surface::LEFT,Surface::LEFT});
					break;
					case 2: blocks[p].sf.push_back({Surface::RIGHT,Surface::RIGHT});
					break;
					default:
					break;
				}
				switch(k){
					case 0: blocks[p].sf.push_back({Surface::BACK,Surface::BACK});
					break;
					case 2: blocks[p].sf.push_back({Surface::FRONT,Surface::FRONT});
					break;
					default:
					break;
				}
			}
}

void rubik::shuffle(Level lv){
	 srand(time(NULL));
	 for (int i = 0; i < lv; ++i)
	 {
	 	int l,m,n;
	 	do{
	 		l=rand()%6;
	 		m=rand()%size;
	 		n=rand()%size;
	 	}while(l==1 && m==1 && n==1);
	 	rotate(vec3i(l,m,n),rand()%4);
	 }
}

void transform(int fix, int p1, int p2);
void rubik::rotate(Vec3i c, Direction dir){
	switch(dir){
		case UP:
		case DOWN:
			
	}
}

void transform(int fix,int pf, bool dir){
	int left = (dir?fix+1:fix-1)%3;
	int right = (dir?fix-1:fix+1)%3;

	for(int i=0; i<blocks.size(); i++){
		if(blocks[i].pos.p[fix] == pf){
			int vl = blocks[i].pos.p[left];
			int vr = blocks[i].pos.p[right];
			blocks[i].pos.p[left] = vr;
			blocks[i].pos.p[riht] = -vl+2;
			for(int j=0; j<blocks[i].sf.size(); j++){
				blocks[i].sf[j] = surfaceRotate(blocks[i].sf[j],dir,fix);
			}
		}
	}

}

Side surfaceRotate(Side s, bool dir, int pixel){
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
}

bool judge(){
	for(int i=0; i<blocks.size(); i++){
		for(int j=0; j<blocks[i].sf.size(); j++){
			if(blocks[i].sf[j].init != blocks[i].sf[j].now)
				return false;
		}
	}
	return true;
}