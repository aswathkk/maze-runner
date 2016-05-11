#include <stdio.h>
#include <GLUT/glut.h>

#include "maze.h"

#define FILE_NAME "maze.txt"

Maze::Maze() {
	load();
}

void Maze::load() {
	FILE *fp;
	fp=fopen(FILE_NAME, "r");
	char c;
	int i = 0, j = 0, tmp_j;
	while((c = fgetc(fp)) != EOF) {
		if(c == '\n') {
			i++;
			tmp_j = j;
			j = 0;
		} else {
			if(c == '0')
				m[i][j] = 0;
			else if(c == '1')
				m[i][j] = 1;
			else if(c == 's') {
				m[i][j] = 2;
				init_x = j;
				init_y = i;
			}
			else if(c == 'f') {
				m[i][j] = 3;
				fin_x = j;
				fin_y = i;
			}
			j++;
		}
	}
	maxx = i;
	maxy = tmp_j;
//	printMaze();
}

void Maze::getPosition(int *x1, int *y1, int *x2, int *y2) {
	*x1 = init_x;
	*y1 = init_y;
	*x2 = fin_x;
	*y2 = fin_y;
}

void Maze::print() {
	int i,j;
	for(i = 0; i < maxx; i++){
		for(j = 0; j < maxy; j++)
			printf("%d ", m[i][j]);
		printf("\n");
	}
	printf("--------------\n");
}

void Maze::print(int x, int y) {
	int i,j;
	for(i = 0; i < maxx; i++){
		for(j = 0; j < maxy; j++){
			if(i==y&&j==x)
				printf("x ");
			else
				printf("%d ", m[i][j]);
		}
		printf("\n");
	}
	printf("--------------\n");
}

void Maze::draw() {

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	float wall_color[] = {0,0,1,1},
			shininess[] = {10};

	glMaterialfv(GL_FRONT,GL_AMBIENT,wall_color);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,wall_color);
	//glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
	glMaterialfv(GL_FRONT,GL_SHININESS,shininess);

	glPushMatrix();
	//glScalef(2,1,2);

	int i, j;
	for(i = 0; i < maxx; i++)
		for(j = 0; j < maxy; j++)
			if( m[j][i] == 1)
				drawWall(i, j);
	drawFloor(i+2, j+2);
	glPopMatrix();
}

void Maze::drawWall(float x, float z) {
	glPushMatrix();
	glTranslatef(x,1,z);
	glScalef(1,2,1);
	glColor3f(1,0,0);
	glutSolidCube(1);
	glPopMatrix();
}

void Maze::drawFloor(float x, float z) {

	float floor_color[] = {0,.5,0,1};
	glMaterialfv(GL_FRONT,GL_AMBIENT,floor_color);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,floor_color);

	glPushMatrix();
	glTranslatef(x/2.2,0,z/2.2);
	glScalef(x,.1,z);
	glutSolidCube(1);
	glPopMatrix();
}