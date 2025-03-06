#include "scene.h"
#include "primitives.h"
#include "user.h"
#include "light.h"

int IR::sphere::print(std::ofstream& f, int d) const {
	f << "	float d" << d << " = sdSphere(p - " << print_center () << ", " << r << ");" << std::endl;
	return d;
}

int IR::box::print(std::ofstream& f, int d) const {
	f << "	float d" << d << " = sdBox(p - " << print_center() << ", " << print_vec3 (l, w, h) << ");" << std::endl;
	return d;
}

int IR::smooth_union::print(std::ofstream& f, int d) const {
	return d;
}

int IR::directional_light::print(std::ofstream& f) const {

	f << "	L = vec3(" << -x << ", " << -y << ", " << -z << ");" << std::endl;
	f << "	CL = " << i << " * " << col->print() << ";" << std::endl;
	f << "	LdotN = clamp(dot(L, N), 0., 1.);" << std::endl;
	f << "	shadL = shadow(p, L, 0.01, 1.0);" << std::endl;
	f << "	col += Cd * CL * LdotN * shadL;" << std::endl;
	return 1;

}