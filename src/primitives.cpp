#include "scene.h"
#include "primitives.h"
#include "user.h"

int IR::sphere::print(std::ofstream& f, int d) const {
	f << "	float d" << d << " = sdSphere(p - vec3(" << x << ", " << y << ", " << z << "), " << r << ");" << std::endl;
	return d;
}