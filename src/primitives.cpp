#include "scene.h"
#include "primitives.h"
#include "user.h"
#include "light.h"

int IR::sphere::print(std::ofstream& f, int d) const {
	// note: there is no point in rotating a sphere. like, cause like yknow it's like yknow like yknow???
	f << "	float d" << d << " = sdSphere(p - " << print_center () << ", " << r << ");" << std::endl;
	return d;
}

std::string IR::primitive::print_center_with_rotations() const {
	std::string c = "p - " + print_center();
	if (rot_z != 0) {
		c = "rotate_z(" + c + "," + std::to_string(rot_z) + ")";
	}
	if (rot_y != 0) {
		c = "rotate_y(" + c + "," + std::to_string(rot_y) + ")";
	}
	if (rot_x != 0) {
		c = "rotate_x(" + c + "," + std::to_string(rot_x) + ")";
	}
	return c;
}

int IR::box::print(std::ofstream& f, int d) const {
	f << "	float d" << d << " = sdBox(" << print_center_with_rotations () << ", " << print_vec3(l, w, h) << "); " << std::endl;
	return d;
}

int IR::cone::print(std::ofstream& f, int d) const {
	f << "	float d" << d << " = sdCone(" << print_center_with_rotations() << ", " << r << ", " << h << "); " << std::endl;
	return d;
}

int IR::smooth_union::print(std::ofstream& f, int d) const {
	int d0, d1, d2;
	d0 = shapes[0]->print(f, d);
	d2 = d0;
	for (int i = 1; i < shapes.size(); i++) {
		const auto& shape = shapes[i];
		d1 = shape->print(f, d0 + 1);
		d2 = d1 + 1;

		f << "	float d" << d2 << " = opSmoothUnion(d" << d0 << ", d" << d1 << "," << blend_factor << "); " << std::endl;
		d0 = d2;
	}
	return d2;
}

int IR::subtraction::print(std::ofstream& f, int d) const {
	int d0, d1, d2;
	d0 = shapes[0]->print(f, d);
	d2 = d0;
	for (int i = 1; i < shapes.size(); i++) {
		const auto& shape = shapes[i];
		d1 = shape->print(f, d0 + 1);
		d2 = d1 + 1;

		f << "	float d" << d2 << " = opSubtraction(d" << d0 << ", d" << d1 << ");" << std::endl;
		d0 = d2;
	}
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

int IR::point_light::print(std::ofstream& f) const {
	f << "	distL = vec3(" << x << ", " << y << ", " << z << ") - p;" << std::endl;
	f << "	L = normalize ( distL );" << std::endl;
	f << "	shadL = shadow(p, L, 0.01, 1.0);" << std::endl;
	f << "	falloffL = dot(distL, distL);" << std::endl;
	f << "	falloffL *= falloffL; " << std::endl;
	f << "	CL = " << i << " * " << col->print() << "/falloffL;" << std::endl;
	f << "	LdotN = clamp(dot(L, N), 0., 1.);" << std::endl;
	f << "	col += Cd * CL * LdotN * shadL;" << std::endl;
	return 1;
}
