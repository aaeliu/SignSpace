#pragma once
#include <stack>
#include "scene.h"

struct user {
	scene* context;
	std::vector <std::shared_ptr<IR::primitive>> objects_temp;
	user(scene* c);

	float current_rot_x = 0.0f;
	float current_rot_y = 0.0f;
	float current_rot_z = 0.0f;

	void create();

	void background(int g);
	void background(int r, int g, int b);

	void color (int r, int g, int b);
	void lightColor(int r, int g, int b); // white by default.
	// void color (std::shared_ptr<Color> c);

	void _default_prim_construct(std::shared_ptr<IR::primitive> s);

	// SHAPE PRIMITIVES
	std::shared_ptr<IR::primitive> sphere(float x, float y, float z, float r);
	std::shared_ptr<IR::primitive> box(float x, float y, float z, float l, float w, float h);


	// Deprecated operators... 
	/* template <typename ... prims>
	std::shared_ptr<IR::primitive> smoothUnion(std::shared_ptr<IR::primitive> p1, std::shared_ptr<IR::primitive> p2, const prims& ... rest); */

	/* std::shared_ptr<IR::primitive> smoothUnion(std::shared_ptr<IR::primitive> p1,
												 std::shared_ptr<IR::primitive> p2);
	std::shared_ptr<IR::primitive> subtract(std::shared_ptr<IR::primitive> p1,
											std::shared_ptr<IR::primitive> p2);
	std::shared_ptr<IR::primitive> smoothSubtract(std::shared_ptr<IR::primitive> p1,
												 std::shared_ptr<IR::primitive> p2);*/ 

	std::stack<std::shared_ptr <IR::smooth_union>> smooth_union_stack;
	std::shared_ptr <IR::smooth_union> smoothUnionBegin(void);
	void smoothUnionEnd(void);

	std::shared_ptr <IR::smooth_union> subtractionBegin(void);
	void subtractionEnd(void);

	std::shared_ptr <IR::smooth_union> smoothSubtractionBegin(void);
	void smoothSubtractionEnd(void);

	// TRANSLATIONAL OPERATORS
	void rotateX(float degs);
	void rotateY(float degs);
	void rotateZ(float degs);
	void rotate(float degs_x, float degs_y, float degs_z);


	// LIGHTS
	/* directional light constructor
	* x, y, z: direction light points. ie (0, -1, 0) is a downward pointing light
	* i: directional light intensity. */
	void directionalLight(float x, float y, float z, float i);

	// COLOR VARIABLES
	

};