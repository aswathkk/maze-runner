
#ifndef MAZE_H
#define MAZE_H

#define MAX_X 100
#define MAX_Y 100

class Maze {

		int maxx, maxy;
		int init_x, init_y, fin_x, fin_y;

	public:

		int m[MAX_X][MAX_Y];

		Maze();
		void load();
		void print();
		void print(int, int);
		void draw();
		void getPosition(int *, int *, int *, int *);

		void drawWall(float, float);
		void drawFloor(float, float);
};

#endif