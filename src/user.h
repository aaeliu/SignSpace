#pragma once
#include "scene.h"

struct user {
	scene* context;
	std::vector <std::shared_ptr<IR::primitive>> objects_temp;
	user(scene* c);

	void create();

	void background(int g);
	void background(int r, int g, int b);

	void color (int r, int g, int b);
	void lightColor(int r, int g, int b); // white by default.
	// void color (std::shared_ptr<Color> c);

	// SHAPE PRIMITIVES
	std::shared_ptr<IR::primitive> sphere(float x, float y, float z, float r);
	std::shared_ptr<IR::primitive> box(float x, float y, float z, float l, float w, float h);

	// TOOD: modify smoothUnion to accept multiple parameters.
	template <typename ... prims>
	std::shared_ptr<IR::primitive> smoothUnion(std::shared_ptr<IR::primitive> p1, const prims& ... rest);
	std::shared_ptr<IR::primitive> smoothUnion(std::shared_ptr<IR::primitive> p1,
												 std::shared_ptr<IR::primitive> p2);
	std::shared_ptr<IR::primitive> subtract(std::shared_ptr<IR::primitive> p1,
											std::shared_ptr<IR::primitive> p2);
	std::shared_ptr<IR::primitive> smoothSubtract(std::shared_ptr<IR::primitive> p1,
												 std::shared_ptr<IR::primitive> p2);

	// TRANSLATIONAL OPERATORS
	void rotateX(float degs);
	void rotateY(float degs);
	void rotateZ(float degs);


	// LIGHTS
	/* directional light constructor
	* x, y, z: direction light points. ie (0, -1, 0) is a downward pointing light
	* i: directional light intensity. */
	void directionalLight(float x, float y, float z, float i);

	// COLOR VARIABLES
	

};