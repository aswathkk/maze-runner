#ifndef HUMAN_H
#define HUMAN_H

#include <math.h>
#include <stdio.h>
#define PI 3.14

struct Human {
	float w;
	int flag;

	void hand(float);
	void leg(float);
	void body();
	void draw(float, float, float, float);
};

#endif