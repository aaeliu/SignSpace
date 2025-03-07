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
	int d0 = shape_1->print(f, d);
	int d1 = shape_2->print(f, d0 + 1);
	int d2 = d1 + 1;
	f << "	float d" << d2 << " = opSmoothUnion(d" << d0 << ", d" << d1 << ", 0.1);" << std::endl;

	return d2;
}

int IR::directional_light::print(std::ofstream& f) const {

	f << "	L = vec3(" << -x << ", " << -y << ", " << -z << ");" << std::endl;
	f << "	CL = " << i << " * " << col->print() << ";" << std::endl;
	f << "	LdotN = clamp(dot(L, N), 0., 1.);" << std::endl;
	f << "	shadL = shadow(p, L, 0.01, 1.0);" << std::endl;
	f << "	col += Cd * CL * LdotN * shadL;" << std::endl;
	return 1;

}

