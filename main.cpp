// Game play

#include <GLUT/glut.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "camera.h"
#include "maze.h"
#include "human.h"
#include "staticdisplay.h"

int win_width = 500, win_height = 500;
int camView=0;
int x1, z1, x2, z2; // storing inital and final position of player

Maze maze;
Camera cam(2*2, 1, 1*2);
Camera cam2(10, 45, 10);
Human man;
StaticDisplay stati(win_width, win_height);

void light() {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	float position[] = {15,20,15,1},
		diffuse_l[] = {.8,.8,.8,1},
		ambient_l[] = {.2,.2,.2,1};

	glLightfv(GL_LIGHT0,GL_POSITION,position);
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambient_l);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse_l);
}

float cube_rot;
void rotatingCube(int x, int z){
	float cube_color[] = {.5,.5,0}, cube_color2[] = {1,0,0};
	glMaterialfv(GL_FRONT,GL_AMBIENT,cube_color2);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,cube_color);
	cube_rot ++;
	glPushMatrix();
	glTranslatef(x, .5, z);
	glRotatef(cube_rot,0,1,0);
	glutSolidCube(.25);
	glPopMatrix();
}

void display() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	stati.draw();
	glLoadIdentity();
	glColor3f(1,0,0);
	if(camView==0)
		cam2.view(); // top View
	else
		cam.view();
	cam2.rotateX(-89.9);
	cam.draw(); // Draw cmaera for debugging
	light();
	glPushMatrix();
	glScalef(2,1,2);
	maze.draw();
	glPopMatrix();
	man.draw(9.9 * (cam.x+cam.lx), 9.9 * (cam.z+cam.lz), cam.lx, cam.lz);
	man.flag=0; // Used for pause walking which is started on key up/down
	rotatingCube(x2*2,z2*2);
	glutSwapBuffers();
	glutPostRedisplay();
}

float anglex,angley;
int xf,yf,ox,oy;
void mouseMotion(int x, int y) {
	if(x>ox) {
		angley+=2.5;
		xf=1;
	}
	if(x<ox) {
		angley-=2.5;
		xf=0;
	}
	if(x == ox) {
		if(xf == 0)
			angley-=2.5;
		else
			angley+=2.5;
	}
	cam.rotateY(angley);

	// if(y>oy) {
	// 	if(anglex<2)
	// 		anglex++;
	// 	yf=1;
	// }
	// if(y<oy) {
	// 	if(anglex>-2)
	// 		anglex--;
	// 	yf=0;
	// }
	// if(y == oy) {
	// 	if(yf == 0)
	// 		if(anglex>-2)
	// 			anglex--;
	// 	else
	// 		if(anglex<2)
	// 			anglex++;
	// }
	// cam.rotateX(anglex);
	ox=x;
	oy=y;
}

float moveFactor=.25;
int xx = cam.x + cam.lx,
 zz = cam.z + cam.lz;
void specialKey(int k,int x,int y) {
	switch(k) {
		case GLUT_KEY_LEFT:
			anglex-=10;
			cam.rotateY(anglex);
			break;
		case GLUT_KEY_RIGHT:
			anglex+=10;
			cam.rotateY(anglex);
			break;
		case GLUT_KEY_UP: {
			xx = ((cam.x+moveFactor*cam.lx))/2;
			zz = ((cam.z+moveFactor*cam.lz))/2;
			if(maze.m[zz][xx]==0) {
				man.flag=1;
				cam.moveFront(moveFactor);
			}
			break;
		}
		case GLUT_KEY_DOWN: {
			xx = (cam.x-moveFactor*cam.lx)/2;
			zz = (cam.z-moveFactor*cam.lz)/2;
			if(maze.m[zz][xx]==0) {
				man.flag=1;
				cam.moveFront(-moveFactor);
			}
			break;	
		}
	}
	if(xx == x2 && zz == z2)
		printf("Win\n");
	maze.print(xx,zz);
}

void keyboard(unsigned char k, int x, int y) {
	switch(k) {
		case 'v':
		case 'V':
			camView=(++camView)%(Camera::count);
			break;
		case 27:
			exit(0);
	}	
}

void reshape(int w, int h) {
	win_width = w;
	win_height = h;
	glViewport(0, 0, w, h);
	stati.reshape(w,h);
}

void init() {
	glClearColor(0,0,0,0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	// glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	// glEnable(GL_BLEND);

	maze.getPosition(&x1, &z1, &x2, &z2);
	cam.moveTo(x1*2,1,z1*2);
	if(maze.m[z1][x1-1]==0)
		cam.rotateY(-90);
	else if(maze.m[z1][x1+1]==0)
		cam.rotateY(90);
	else if(maze.m[z1+1][x1]==0)
		cam.rotateY(180);

	anglex = -atan(cam.z+cam.lz/cam.x+cam.lx)*180/PI;
}

int main(int argc, char **argv) {
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(win_width, win_height);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("Maze Runner");
	glutDisplayFunc(display);
	glutSpecialFunc(specialKey);	
	glutKeyboardFunc(keyboard);
	glutPassiveMotionFunc(mouseMotion);
	init();
	glutReshapeFunc(reshape);
	//glutFullScreen();
	glutMainLoop();
}