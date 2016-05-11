
#ifndef CAMERA_H
#define CAMERA_H

struct Camera {

		float x;
		float y;
		float z;
		float lx;
		float ly;
		float lz;
		
		static int count;

		Camera(float,float,float);
		void moveFront(float);
		void moveUp(float);
		void moveTo(int, int, int);
		void rotateX(float);
		void rotateY(float);
		void view();
		void draw();
};

#endif