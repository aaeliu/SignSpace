#include "primitives.h"
#include "user.h"
# define M_PI           3.14159265358979323846

user::user(scene* c) {
	context = c;
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
	s->rot_z = current_rot_z;
	if (!smooth_union_stack.empty()) {
		smooth_union_stack.top()->shapes.push_back(s);
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

std::shared_ptr <IR::smooth_union> user::smoothUnionBegin() {
	smooth_union_stack.push(std::make_shared<IR::smooth_union>());
	std::shared_ptr<IR::smooth_union> s = smooth_union_stack.top();
	s->col = context->current_color;
	s->rot_z = current_rot_z;
	objects_temp.push_back(s);
	return s;
}

void user::smoothUnionEnd() {
	std::shared_ptr<IR::smooth_union> s = smooth_union_stack.top();
	smooth_union_stack.pop();
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

void user::rotateZ(float degs) {
	current_rot_z = degs * M_PI / 180.f;
}
