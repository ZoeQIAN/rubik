#include "rubik.h"
#include "basicfunction.h"
#include <cstdio>
#include <cstdlib>
//#define gen_cur_rect(cur_rect,i,j,rect) cur_rect = float(1 - i*1.0/sum - j*1.0/sum)*rect[1] + float(i*1.0/sum)* rect[0] + float(j*1.0/sum)*rect[2]
void trackball(int x, int y, Vec3f& v);

void Paintrect(Vec3f* rect, GLfloat m[4][4], Vec3f prefix,float r,float g,float b, Vec3f normal){

	normal.rotate_by_matrix(m);
    glNormal3f(normal.p[0],normal.p[1],normal.p[2]);
	glBindTexture(GL_TEXTURE_2D, 0);

	float line_width = 0.05;
	glBegin(GL_QUADS);
	glColor3f(r,g,b);
	for(int i=0; i<4; i++)
	{
		rect[i] +=prefix;
		rect[i].rotate_by_matrix(m);
		glVertex3f(rect[i].p[0],rect[i].p[1],rect[i].p[2]);
	}


	glEnd();


    glLineWidth(3);

    glColor3f(0.3f,0.3f,0.3f);
    glBegin(GL_LINE_STRIP);
    glVertex3f(rect[0].p[0],rect[0].p[1],rect[0].p[2]);
    glVertex3f(rect[1].p[0],rect[1].p[1],rect[1].p[2]);
    glVertex3f(rect[2].p[0],rect[2].p[1],rect[2].p[2]);
    glVertex3f(rect[3].p[0],rect[3].p[1],rect[3].p[2]);
    glVertex3f(rect[0].p[0],rect[0].p[1],rect[0].p[2]);
    glEnd();
}

Rubik::Rubik(Level lv,int sz){/*
	Up[0] = v[0];
	Up[1] = v[1];
	Up[2] = v[2];
	Up[3] = v[3];
	Down[0] = v[7];
	Down[1] = v[6];
	Down[2] = v[5];
	Down[3] = v[4];

	Front[0] = v[3];
	Front[1] = v[2];
	Front[2] = v[6];
	Front[3] = v[7];

	Back[0] = v[1];
	Back[1] = v[0];
	Back[2] = v[4];
	Back[3] = v[5];

	Left[0] = v[0];
	Left[1] = v[3];
	Left[2] = v[7];
	Left[3] = v[4];


	Right[0] = v[2];
	Right[1] = v[1];
	Right[2] = v[5];
	Right[3] = v[6];
*/

	p[0] = Vec3f(1.5*edge_length, -1.5*edge_length, 1.5*edge_length);
	p[1] = Vec3f(1.5*edge_length, 1.5*edge_length, 1.5*edge_length);
	p[2] = Vec3f(-1.5*edge_length, 1.5*edge_length, 1.5*edge_length);
	p[3] = Vec3f(-1.5*edge_length, -1.5*edge_length, 1.5*edge_length);

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
	shuffle(lv);
	std::cout << "Selected level is: " << lv << std::endl;
	angle=0;
	trackball(0,0,curPos);
	trackball(0,0,lastPos);
	//std::cout << curPos << std::endl;
	//std::cout << lastPos << std::endl;
	calRotation();
	//std::cout << axis[0] << "," << axis[1] << ","<< axis[2] << "," << angle<< std::endl;
	axis_to_quat(axis,angle,curquat);
	std::printf("curquat = %f %f %f %f\n", curquat[0], curquat[1], curquat[2], curquat[3]);
}

Rubik::~Rubik(){}

void trackball(int x, int y, Vec3f& v) {
    float d, a;
    // 将x， y投影到在width，height内的半球中心
    v[0] = (2.0F * x - DEFAULT_SCREENWIDTH) / DEFAULT_SCREENWIDTH;
    v[1] = (DEFAULT_SCREENHEIGHT - 2.0F * y) / DEFAULT_SCREENHEIGHT;
    d = sqrt(v[0] * v[0] + v[1] * v[1]);
    v[2] = cos((M_PI / 2.0F) * ((d < 1.0F) ? d : 1.0F));
    a = 1.0F / sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    v[0] *= a;
    v[1] *= a;
    v[2] *= a;
}

void Rubik::startRotation(float x, float y){
	rotating=true;
	trackball(x,y,lastPos);
	//std::cout << "Start:" << lastPos << std::endl;
}
void Rubik::stopRotation(){
	rotating=false;

}

void Rubik::selfRotate(float x, float y) {
	if(!rotating) return;

	trackball(x,y,curPos);
	calRotation();

 	lastPos = curPos;

    float quat[4];
    axis_to_quat(axis,angle,quat);

    add_quats(quat,curquat,curquat);

}

void Rubik::calRotation(){
	float dx, dy, dz;
    dx = curPos[0] - lastPos[0];
    dy = curPos[1] - lastPos[1];
    dz = curPos[2] - lastPos[2];

    angle = -0.8*sqrt(dx * dx + dy * dy + dz * dz);
    axis[0] = lastPos[1] * curPos[2] - lastPos[2] * curPos[1];
    axis[1] = lastPos[2] * curPos[0] - lastPos[0] * curPos[2];
    axis[2] = lastPos[0] * curPos[1] - lastPos[1] * curPos[0];
}

void Rubik::Render(){
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    GLfloat m[4][4];
  	build_rotmatrix(m, curquat);
  	Vec3f normal;
    //glBegin(GL_QUADS);
		Vec3f rect[4];
	for(int zz=0; zz<3;zz++)
		for(int yy=0; yy<3;yy++)
			for(int xx=0; xx<3; xx++){
				cube c = blocks[xx+yy*3+zz*3*3];
				for(unsigned int j=0; j<c.sf.size(); j++){
				Surface s = c.sf[j];

				float r,g,b;
				colorMap(s.init,r,g,b);
				//glColor3f(r,g,b);

				int x=c.pos[0];
				int y=c.pos[1];
				int z=c.pos[2];
				switch(s.now){
					case UP:
					normal = Vec3f(0,0,1);
					rect[0] = Vec3f((x+1)*edge_length,y*edge_length,3*edge_length);
					rect[1] = Vec3f((x+1)*edge_length,(y+1)*edge_length,3*edge_length);
					rect[2] = Vec3f(x*edge_length,(y+1)*edge_length,3*edge_length);
					rect[3] = Vec3f(x*edge_length,y*edge_length,3*edge_length);
					Paintrect(rect,m,prefix,r,g,b,normal);
					break;
					case DOWN:
					normal = Vec3f(0,0,-1);
					rect[0] = Vec3f(x*edge_length,y*edge_length,0);
					rect[1] = Vec3f(x*edge_length,(y+1)*edge_length,0);
					rect[2] = Vec3f((x+1)*edge_length,(y+1)*edge_length,0);
					rect[3] = Vec3f((x+1)*edge_length,(y)*edge_length,0);
					Paintrect(rect,m,prefix,r,g,b,normal);
					break;
					case LEFT:
					normal = Vec3f(0,-1,0);
					rect[0] = Vec3f((x+1)*edge_length,0,(z+1)*edge_length);
					rect[1] = Vec3f(x*edge_length,0,(z+1)*edge_length);
					rect[2] = Vec3f(x*edge_length,0,z*edge_length);
					rect[3] = Vec3f((x+1)*edge_length,0,z*edge_length);
					Paintrect(rect,m,prefix,r,g,b,normal);
					break;
					case RIGHT:
					normal = Vec3f(0,1,0);
					rect[0]=Vec3f(x*edge_length,3*edge_length,(z+1)*edge_length);
					rect[1]=Vec3f((x+1)*edge_length,3*edge_length,(z+1)*edge_length);
					rect[2]=Vec3f((x+1)*edge_length,3*edge_length,z*edge_length);
					rect[3]=Vec3f(x*edge_length,3*edge_length,z*edge_length);
					Paintrect(rect,m,prefix,r,g,b,normal);
					break;
					case FRONT:
					normal = Vec3f(1,0,0);
					rect[0] = Vec3f(3*edge_length,(y+1)*edge_length,(z+1)*edge_length);
					rect[1] = Vec3f(3*edge_length,y*edge_length,(z+1)*edge_length);
					rect[2] = Vec3f(3*edge_length,y*edge_length,z*edge_length);
					rect[3] = Vec3f(3*edge_length,(y+1)*edge_length,z*edge_length);
					Paintrect(rect,m,prefix,r,g,b,normal);
					break;
					case BACK:
					normal = Vec3f(-1,0,0);
					rect[0] = Vec3f(0,y*edge_length,(z+1)*edge_length);
					rect[1] = Vec3f(0,(y+1)*edge_length,(z+1)*edge_length);
					rect[2] = Vec3f(0,(y+1)*edge_length,z*edge_length);
					rect[3] = Vec3f(0,y*edge_length,z*edge_length);
					Paintrect(rect,m,prefix,r,g,b,normal);
					break;
					default:
					break;
			}

		}
	}

	//glEnd();
	glPopMatrix();
}

void Rubik::colorMap(Side s, float& r,float& g, float&b){
	switch(s){
		case UP:
		r=0;
		g=0;
		b=1;
		break;
		case DOWN:
		r=1;
		g=0;
		b=0;
		break;
		case LEFT:
		r=0;
		g=1;
		b=0;
		break;
		case RIGHT:
		r=1;
		g=0;
		b=1;
		break;
		case FRONT:
		r=0.2;
		g=0.5;
		b=0.5;
		break;
		case BACK:
		r=1;
		g=1;
		b=0;
		break;
		default:
		break;
	}
}
void Rubik::shuffle(Level lv){
	 srand(time(NULL));
	 for (int i = 0; i < lv; ++i)
	 {
	 	int l=rand()%3;
	 	int m=rand()%3;
	 	int n=rand()%2;
	 	transform(l, m, n==1?true:false);
	 }
}

void Rubik::rotate(Vec3i c, Side s, Direction dir){
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

void Rubik::transform(int fix,int pf, bool dir){
	int left = (dir?fix+1:fix-1)%3;
	int right = (dir?fix-1:fix+1)%3;
	if(left==-1) left=2;
	if(right==-1) right=2;
	for(int i=0; i<3*3*3; i++){
		if(blocks[i].pos[fix] == pf){
			int vl = blocks[i].pos[left];
			int vr = blocks[i].pos[right];
			blocks[i].pos[left] = vr;
			blocks[i].pos[right] = -vl+2;
			for(unsigned int j=0; j<blocks[i].sf.size(); j++){
				blocks[i].sf[j].now = surfaceRotate(blocks[i].sf[j].now,dir,fix);
			}
		}
	}

}

Side Rubik::surfaceRotate(Side s, bool dir, int pixel){
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

bool Rubik::judge(){
	for(int i=0; i<3*3*3; i++){
		for(unsigned int j=0; j<blocks[i].sf.size(); j++){
			if(blocks[i].sf[j].init != blocks[i].sf[j].now)
				return false;
		}
	}
	return true;
}

void Rubik::print2(){
		for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			for(int k=0; k<3; k++){
				int p = k+j*3+i*3*3;
				std::cout << blocks[p].pos << ":";
				for(unsigned int m=0; m<blocks[p].sf.size(); m++){
					std::cout << blocks[p].sf[m].now << " ";
				}
				std::cout << std::endl;
			}
		}
	}

}
void Rubik::printall(){

	int up[3][3];
	int down[3][3];
	int left[3][3];
	int right[3][3];
	int front[3][3];
	int back[3][3];

	for(int i=0; i<3*3*3; i++){
		for(unsigned int j=0; j<blocks[i].sf.size(); j++){
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
