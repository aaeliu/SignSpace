#include "primitives.h"
#include "user.h"
#include <cassert>
# define M_PI           3.14159265358979323846

user::user(scene* c) {
	context = c;
}

void user::create_and_check() {
	create();
	ASSERT(combination_stack.empty(), "Unclosed combination operation (Hint: if you call [combination]Begin(), you must call [combination]End().");
}

void user::background(const TimeExpr& g) {
	background(g, g, g);
}

void user::background(const TimeExpr& r, const TimeExpr& g, const TimeExpr& b) {
	context->background = std::make_shared<Color>(r, g, b);

}

void user::ambientColor(const TimeExpr& r, const TimeExpr& g, const TimeExpr& b) {
	context->ambient_color = std::make_shared<Color>(r * context->ambient_factor, g * context->ambient_factor, b * context->ambient_factor);
}

void user::color(const TimeExpr& r, const TimeExpr& g, const TimeExpr& b) {
	current_color = std::make_shared<Color>(r, g, b);
}

void user::lightColor(const TimeExpr& r, const TimeExpr& g, const TimeExpr& b) {
	current_light_color = std::make_shared<Color>(r, g, b);
}


/* NOTE ON Z - COORDINATES!!
* GLSL CODE HAS NEGATIVE-Z INTO THE SCREEN!
* SIGNSPACE CODE HAS POSITIVE-Z INTO THE SCREEN! */


/* applies state settings to newly constructed primitive... */
void::user::_default_prim_construct(std::shared_ptr<IR::primitive> s) {
	s->col = current_color;
	s->rot_x = current_rot_x;
	s->rot_y = current_rot_y;
	s->rot_z = current_rot_z;
	if (!combination_stack.empty()) {
		ASSERT(!s->is_custom, "Combination operations will not work with custom shapes.");
		combination_stack.top()->shapes.push_back(s);
	}
	else if (current_custom_shape != nullptr) {
		current_custom_shape->shapes->push_back(s);
	} else {
		objects_temp.push_back(s);
	}
}

std::shared_ptr<IR::primitive> user::sphere(const TimeExpr& x, const TimeExpr& y, const TimeExpr& z, const TimeExpr& r) {
	std::shared_ptr<IR::primitive> s = std::make_shared<IR::sphere>(x, y, z * -1, r);
	_default_prim_construct(s);
	
	return s;
}
std::shared_ptr<IR::primitive> user::box(const TimeExpr& x, const TimeExpr& y, const TimeExpr& z, const TimeExpr& l, const TimeExpr& w, const TimeExpr& h) {
	std::shared_ptr<IR::primitive> s = std::make_shared<IR::box>(x, y, z * -1, l, w, h);
	_default_prim_construct(s);
	return s;
}

std::shared_ptr<IR::primitive> user::cone(const TimeExpr& x, const TimeExpr& y, const TimeExpr& z, const TimeExpr& r, const TimeExpr& h) {
	std::shared_ptr<IR::primitive> s = std::make_shared<IR::cone>(x, y, z * -1, r, h * 2);
	_default_prim_construct(s);
	return s;
}

std::shared_ptr<IR::primitive> user::torus(const TimeExpr& x, const TimeExpr& y, const TimeExpr& z, const TimeExpr& R, const TimeExpr& r) {
	std::shared_ptr<IR::primitive> s = std::make_shared<IR::torus>(x, y, z * -1, R, r);
	_default_prim_construct(s);
	return s;
}

std::shared_ptr<IR::primitive> user::cylinder(const TimeExpr& x, const TimeExpr& y, const TimeExpr& z, const TimeExpr& r, const TimeExpr& h) {
	std::shared_ptr<IR::primitive> s = std::make_shared<IR::cylinder>(x, y, z * -1, r, h);
	_default_prim_construct(s);
	return s;
}

/*template <typename ... prims>
std::shared_ptr<IR::primitive> user::smoothUnion(std::shared_ptr<IR::primitive> p1, std::shared_ptr<IR::primitive> p2, const prims& ... rest) {
	std::cout << "Meow??\n";
	// return smoothUnion(p1, p2);
	return smoothUnion(smoothUnion(p1, p2), rest);
}*/

void user::smoothBlendFactor(const TimeExpr& k) {
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
	ASSERT(!combination_stack.empty(), "No active combination operation to end.");
	std::shared_ptr<IR::combination> s = combination_stack.top();
	ASSERT(s->get_comb_type() == IR::comb_type::SMOOTH_UNION, "smoothUnionBegin() does not close off smoothUnionEnd().");
	combination_stack.pop();
}

std::shared_ptr <IR::combination> user::subtractionBegin(void) {
	std::shared_ptr<IR::combination> s = std::make_shared<IR::subtraction>();
	_default_prim_construct(s);
	combination_stack.push(s);
	return s;
}

void user::subtractionEnd(void) {
	ASSERT(!combination_stack.empty(), "No active combination operation to end.");
	std::shared_ptr<IR::combination> s = combination_stack.top();
	ASSERT(s->get_comb_type() == IR::comb_type::SUBTRACTION, "subtractionEnd() does not close off subtractionBegin().");
	combination_stack.pop();
}

std::shared_ptr <IR::combination> user::smoothSubtractionBegin(void) {
	std::shared_ptr<IR::smooth_subtraction> s = std::make_shared<IR::smooth_subtraction>();
	s->blend_factor = current_blend_factor;
	_default_prim_construct(s);
	combination_stack.push(s);
	return s;
}

void user::smoothSubtractionEnd(void) {
	ASSERT(!combination_stack.empty(), "No active combination operation to end.");
	std::shared_ptr<IR::combination> s = combination_stack.top();
	ASSERT (s->get_comb_type() == IR::comb_type::SMOOTH_SUBTRACTION, "smoothSubtractionEnd() does not close off smoothSubtractionBegin().");
	combination_stack.pop();
}

std::shared_ptr <IR::combination> user::intersectionBegin(void) {
	std::shared_ptr<IR::combination> s = std::make_shared<IR::intersection>();
	_default_prim_construct(s);
	combination_stack.push(s);
	return s;
}

void user::intersectionEnd(void) {
	ASSERT(!combination_stack.empty(), "No active combination operation to end.");
	std::shared_ptr<IR::combination> s = combination_stack.top();
	ASSERT (s->get_comb_type() == IR::comb_type::INTERSECTION, "intersectionEnd() does not close off intersectionBegin().");
	combination_stack.pop();
}

std::shared_ptr <IR::combination> user::smoothIntersectionBegin(void) {
	std::shared_ptr<IR::smooth_intersection> s = std::make_shared<IR::smooth_intersection>();
	s->blend_factor = current_blend_factor;
	_default_prim_construct(s);
	combination_stack.push(s);
	return s;
}

void user::smoothIntersectionEnd(void) {
	ASSERT(!combination_stack.empty(), "No active combination operation to end.");
	std::shared_ptr<IR::combination> s = combination_stack.top();
	ASSERT (s->get_comb_type() == IR::comb_type::SMOOTH_INTERSECTION, "smoothIntersectionEnd() does not close off smoothIntersectionBegin().");
	combination_stack.pop();
}

// LIGHTSSS

void user::directionalLight(float x, float y, float z, float i) {
	std::shared_ptr<IR::directional_light> new_light = std::make_shared<IR::directional_light>(x, y, -z, i);
	new_light->col = current_light_color;
	context->lights.push_back(new_light);
}

void user::pointLight(float x, float y, float z, float i) {
	std::shared_ptr<IR::point_light> new_light = std::make_shared<IR::point_light>(x, y, -z, i);
	new_light->col = current_light_color;
	context->lights.push_back(new_light);
}

// TRANSFORMATIONAL 

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

// CUSTOM SHAPE CREATION!
std::shared_ptr<IR::primitive> user::shape(const std::string& name, float x, float y, float z) {
	ASSERT(custom_shapes.find(name) != custom_shapes.end(), "A custom shape with this name does not exist!");
	ASSERT(current_custom_shape_name != name, "Cannot instantiate the shape currently being created!");
	ASSERT(current_custom_shape == nullptr, "This version of SignSpace currently does not support custom shapes within custom shapes.");
	std::shared_ptr<IR::custom_shape> s = std::make_shared<IR::custom_shape>(custom_shapes[name], x, y, -z);
	_default_prim_construct(s);
	return s;
}
void user::createShapeBegin(const std::string& name) {
	ASSERT(combination_stack.empty(), "Cannot create shape inside combation operator.");
	ASSERT(current_custom_shape == nullptr, "Cannot create new shape while other shape is being created.");
	ASSERT(name != "", "Invalid name for shape");
	current_custom_shape = std::make_shared<IR::custom_shape>();
	current_custom_shape_name = name;
	custom_shapes[name] = current_custom_shape;

}
void user::createShapeEnd() {
	ASSERT(current_custom_shape != nullptr, "No shape is currently being created.");
	current_custom_shape->generate_bounding_sphere();
	current_custom_shape = nullptr;
	current_custom_shape_name = "";
}

