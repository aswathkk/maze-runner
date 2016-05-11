#include "human.h"
#include <GLUT/glut.h>

void Human::hand(float x){
	glPushMatrix();
	glTranslatef(x,-1.8,0);
	glScalef(.5,2.5,.5);
	glutSolidCube(1);
	glPopMatrix();
}

void Human::leg(float x){
	glPushMatrix();
	glTranslatef(x,-5,0);
	glScalef(.5,3,.5);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(x,-6.5,.2);
	glScalef(.5,.25,1);
	glutSolidCube(1);
	glPopMatrix();
}

void Human::body() {
	float body_color[] = {1,0,0};
	glMaterialfv(GL_FRONT,GL_AMBIENT,body_color);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,body_color);
	glPushMatrix();
	glTranslatef(0,-2,0);
	glScalef(2,3,1);
	glutSolidCube(1);
	glPopMatrix();
}

void Human::draw(float x, float z, float lx, float lz) {

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	float ambient[] = {0,0,0,1},
		diffuse[] = {1,1,0,1},
		specular[] = {.5,.5,.5,1},
		shininess[] = {10};
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,ambient);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
	glMaterialfv(GL_FRONT,GL_SHININESS,shininess);
	
	if(flag)
		w+=.5;

	glPushMatrix();
	glScalef(.1,.1,.1);
	float angle = atan(lz/lx) * 180/PI; // angle need to be checked to fix sudden change in orientation of player
	// if(angle > 360) angle -= 360;
	// if(angle < 0) angle += 360;
	//printf("%f\n", angle);
	glTranslatef(x,6.8,z);
	glRotatef(90-angle,0,1,0);
	glPushMatrix();

	glTranslatef(0,.25*sin(w),0); // change z value to adjust relative position of player

	glutSolidSphere(.7,10,10);

	body();


	float skin_color[] = {.8,.5,0};
	glMaterialfv(GL_FRONT,GL_AMBIENT,skin_color);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,skin_color);

	glPushMatrix();
	glRotatef(20*sin(w),1,0,0);
	hand(1.25);
	glPopMatrix();

	glPushMatrix();
	glRotatef(20*cos(w),1,0,0);
	hand(-1.25);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(.5,-2.5,0);
	glRotatef(20*cos(w),1,0,0);
	glTranslatef(-.5,2.5,0);
	leg(.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(.5,-2.5,0);
	glRotatef(20*sin(w),1,0,0);
	glTranslatef(-.5,2.5,0);
	leg(-.5);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();
}