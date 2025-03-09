#include "primitives.h"
#include "user.h"
#include <cassert>
# define M_PI           3.14159265358979323846

user::user(scene* c) {
	context = c;
}

void user::create_and_check() {
	create();
	assert(combination_stack.empty());
}

void user::background(int g) {
	background(g, g, g);
}

void user::background(int r, int g, int b) {
	context->background = Color::Color(r, g, b);

}

void user::color(int r, int g, int b) {
	context->current_color = std::make_shared<Color>(r, g, b);
}

/* NOTE ON Z - COORDINATES!!
* GLSL CODE HAS NEGATIVE-Z INTO THE SCREEN!
* SIGNSPACE CODE HAS POSITIVE-Z INTO THE SCREEN! */


/* applies state settings to newly constructed primitive... */
void::user::_default_prim_construct(std::shared_ptr<IR::primitive> s) {
	s->col = context->current_color;
	s->rot_x = current_rot_x;
	s->rot_y = current_rot_y;
	s->rot_z = current_rot_z;
	if (!combination_stack.empty()) {
		combination_stack.top()->shapes.push_back(s);
	}
	else {
		objects_temp.push_back(s);
	}
}

std::shared_ptr<IR::primitive> user::sphere(float x, float y, float z, float r) {
	std::shared_ptr<IR::primitive> s = std::make_shared<IR::sphere>(x, y, -z, r);
	_default_prim_construct(s);
	
	return s;
}
std::shared_ptr<IR::primitive> user::box(float x, float y, float z, float l, float w, float h) {
	std::shared_ptr<IR::primitive> s = std::make_shared<IR::box>(x, y, -z, l, w, h);
	_default_prim_construct(s);
	return s;
}

/*template <typename ... prims>
std::shared_ptr<IR::primitive> user::smoothUnion(std::shared_ptr<IR::primitive> p1, std::shared_ptr<IR::primitive> p2, const prims& ... rest) {
	std::cout << "Meow??\n";
	// return smoothUnion(p1, p2);
	return smoothUnion(smoothUnion(p1, p2), rest);
}*/

void user::smoothBlendFactor(float k) {
	current_blend_factor = k;
}

std::shared_ptr <IR::combination> user::smoothUnionBegin() {
	std::shared_ptr<IR::smooth_union> s = std::make_shared<IR::smooth_union>();
	_default_prim_construct(s);
	s->blend_factor = current_blend_factor;
	combination_stack.push(s);

	return s;
}

void user::smoothUnionEnd() {
	std::shared_ptr<IR::combination> s = combination_stack.top();
	assert(s->get_comb_type() == IR::comb_type::SMOOTH_UNION);
	combination_stack.pop();
}

std::shared_ptr <IR::combination> user::subtractionBegin(void) {
	std::shared_ptr<IR::combination> s = std::make_shared<IR::subtraction>();
	_default_prim_construct(s);
	combination_stack.push(s);
	return s;
}

void user::subtractionEnd(void) {
	std::shared_ptr<IR::combination> s = combination_stack.top();
	assert(s->get_comb_type() == IR::comb_type::SUBTRACTION);
	combination_stack.pop();
}

/*
* not supported.
std::shared_ptr<IR::primitive> user::smoothUnion(std::shared_ptr<IR::primitive> p1, std::shared_ptr<IR::primitive> p2) {
	p1->to_combine = true;
	p2->to_combine = true;
	
	std::shared_ptr<IR::primitive> s = std::make_shared<IR::smooth_union>(p1, p2);
	s->rot_z = current_rot_z;
	s->col = context->current_color;

	objects_temp.push_back(s);
	return s;

}*/

void user::directionalLight(float x, float y, float z, float i) {
	std::shared_ptr<IR::directional_light> new_light = std::make_shared<IR::directional_light>(x, y, -z, i);
	new_light->col = context->current_light_color;
	context->lights.push_back(new_light);
}

void user::rotateX(float degs) {
	current_rot_x = degs * M_PI / 180.f;
}
void user::rotateY(float degs) {
	current_rot_y = degs * M_PI / 180.f;
}
void user::rotateZ(float degs) {
	current_rot_z = degs * M_PI / 180.f;
}
void user::rotate(float degs_x, float degs_y, float degs_z) {
	rotateX(degs_x); rotateY(degs_y); rotateZ(degs_z);
}