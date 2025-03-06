#include "primitives.h"
#include "user.h"

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

IR::sphere* user::sphere(float x, float y, float z, float r) {
	IR::sphere* s = new IR::sphere(x, y, -z, r);
	s->col = context->current_color;
	context->shapes.push_back(s);
	return s;
}
