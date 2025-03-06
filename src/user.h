#pragma once
#include "scene.h"

struct user {
	scene* context;
	user(scene* c);

	void start();
	void loop();

	void background(int g);
	void background(int r, int g, int b);

	void color (int r, int g, int b);
	IR::sphere* sphere(float x, float y, float z, float r);

	void smoothCombine(std::shared_ptr<IR::primitive> p1, 
						std::shared_ptr<IR::primitive> p2);


	// COLOR VARIABLES

};