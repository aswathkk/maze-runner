
#ifndef MAZE_H
#define MAZE_H

#define MAX_X 100
#define MAX_Y 100

class Maze {

		int maxx;
		int maxy;

	public:

		int m[MAX_X][MAX_Y];

		Maze();
		void load();
		void printMaze();
		void draw();

		void drawWall(float, float);
		void drawFloor(float, float);
};

#endif