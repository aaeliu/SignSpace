#include "scene.h"
#include "primitives.h"
#include "user.h"



user::user(scene* c) {
	context = c;
}

void user::sphere(float x, float y, float z, float r) {
	IR::sphere* s = new IR::sphere(x, y, z, r);
	context->shapes.push_back( s );
	return;
}

int IR::sphere::print(std::ofstream& f, int d) const {
	f << "	float d" << d << " = sdSphere(p + vec3(" << x << ", " << y << ", " << z << "), " << r << ");" << std::endl;
	return d;
}