#include <GLUT/glut.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "camera.h"
#include "maze.h"
#include "human.h"

int win_width = 900, win_height = 700;
int camView=0;

Camera cam(4, 1, 5);
Camera cam2(15, 45, 15);

Maze maze;

Human man;

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

void display() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glColor3f(1,0,0);
	if(camView==0)
		cam2.view(); // top View
	else
		cam.view();
	cam2.rotateX(-89.9);
	cam.draw(); // Draw cmaera for debugging
	light();
	maze.draw();
	man.draw(10 * (cam.x+cam.lx), 10 * (cam.z+cam.lz), cam.lx, cam.lz);
	man.flag=0;
	glutSwapBuffers();
	glutPostRedisplay();
}

float anglex,angley;
int xf,yf,ox,oy;
void mouseMotion(int x, int y) {
	if(x>ox) {
		angley+=2;
		xf=1;
	}
	if(x<ox) {
		angley-=2;
		xf=0;
	}
	if(x == ox) {
		if(xf == 0)
			angley-=2;
		else
			angley+=2;
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

float moveFactor=.1;
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
			int xx = (cam.x+moveFactor*cam.lx);
			int zz = (cam.z+moveFactor*cam.lz);
			if(maze.m[zz][xx]==0) {
				man.flag=1;
				cam.moveFront(moveFactor);
			}
			break;
		}
		case GLUT_KEY_DOWN: {
			int xx = cam.x-moveFactor*cam.lx;
			int zz = cam.z-moveFactor*cam.lz;
			if(maze.m[zz][xx]==0) {
				man.flag=1;
				cam.moveFront(-moveFactor);
			}
			break;	
		}
	}
}

void keyboard(unsigned char k, int x, int y) {
	switch(k) {
		case 'v':
		case 'V':
			camView=(++camView)%(Camera::count);
			break;
		case 'Q':
		case 'q':
			exit(0);
	}	
}

void reshape(int w, int h) {
	win_width = w;
	win_height = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,(float)win_width/(float)win_height,.1,100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void init() {
	glClearColor(0,0,0,0);
	
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
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}