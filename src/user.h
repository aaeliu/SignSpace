#pragma once
#include "scene.h"

struct user {
	scene* context;
	user(scene* c);

	void start();
	void loop();

	void sphere(float x, float y, float z, float r);
};