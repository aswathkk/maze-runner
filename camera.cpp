#include <GLUT/glut.h>
#include <math.h>
#define PI 3.14

#include "camera.h"

int Camera::count = 0;

Camera::Camera(float a, float b, float c) {
	x=a;
	y=b;
	z=c;
	lx = 0;
	ly = -0.1;
	lz = -1;

	count++;
}

void Camera::moveTo(int xx, int yy, int zz) {
	x = xx;
	y = yy;
	z = zz;
}

void Camera::moveFront(float factor) {
	x += lx * factor;
	z += lz * factor;
}

void Camera::moveUp(float factor) {
	x += lx * factor;
	y += ly * factor;
}

void Camera::rotateX(float angle) {
	// if(angle > 360) angle -= 360;
	// if(angle < 0) angle += 360;
	ly = sin(angle * PI / 180);
	lz = -cos(angle * PI / 180);
}

void Camera::rotateY(float angle) {
	// if(angle > 360) angle -= 360;
	// if(angle < 0) angle += 360;
	lx = sin(angle * PI / 180);
	lz = -cos(angle * PI / 180);
}

void Camera::view() {
	gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0, 1, 0);
}

void Camera::draw() {
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glPointSize(5);
	glBegin(GL_POINTS);
	glColor3f(0,1,0);
	glVertex3f(x,y,z);
	glColor3f(0,0,1);
	glVertex3f(x+lx,y+ly,z+lz);
	glEnd();
	glColor3f(1,0,0);
	glBegin(GL_LINES);
	glVertex3f(x,y,z);
	glVertex3f(x+lx,y+ly,z+lz);
	glEnd();
}