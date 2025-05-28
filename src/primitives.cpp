#include "scene.h"
#include "primitives.h"
#include "user.h"
#include "light.h"

std::string IR::primitive::print_center_with_rotations() const {
	return print_center_with_transform(0, 0, 0);
}

std::string IR::primitive::print_center_with_transform(float tx, float ty, float tz) const {
	std::string c = "p - " + print_vec3(x + tx, y + ty, z + tz);
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


int IR::sphere::print(std::ofstream& f, int d) const {
	// note: there is no point in rotating a sphere
	f << "	float d" << d << " = sdSphere(p - " << print_center() << ", " << r << ");" << std::endl;
	return d;
}

int IR::box::print(std::ofstream& f, int d) const {
	f << "	float d" << d << " = sdBox(" << print_center_with_rotations () << ", " << print_vec3(l, w, h) << "); " << std::endl;
	return d;
}

int IR::cone::print(std::ofstream& f, int d) const {
	f << "	float d" << d << " = sdCone(" << print_center_with_rotations() << ", " << r << ", " << h << "); " << std::endl;
	return d;
}

int IR::torus::print(std::ofstream& f, int d) const {
	f << "	float d" << d << " = sdTorus(" << print_center_with_rotations() << ", vec2(" << R << ", " << r << ")); " << std::endl;
	return d;
}

int IR::cylinder::print(std::ofstream& f, int d) const {
	f << "	float d" << d << " = sdCylinder(" << print_center_with_rotations() << ", " << r << ", " << h << "); " << std::endl;
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

int IR::smooth_subtraction::print(std::ofstream& f, int d) const {
	int d0, d1, d2;
	d0 = shapes[0]->print(f, d);
	d2 = d0;
	for (int i = 1; i < shapes.size(); i++) {
		const auto& shape = shapes[i];
		d1 = shape->print(f, d0 + 1);
		d2 = d1 + 1;

		f << "	float d" << d2 << " = opSmoothSubtraction(d" << d0 << ", d" << d1 << "," << blend_factor << "); " << std::endl;
		d0 = d2;
	}
	return d2;
}

int IR::intersection::print(std::ofstream& f, int d) const {
	int d0, d1, d2;
	d0 = shapes[0]->print(f, d);
	d2 = d0;
	for (int i = 1; i < shapes.size(); i++) {
		const auto& shape = shapes[i];
		d1 = shape->print(f, d0 + 1);
		d2 = d1 + 1;

		f << "	float d" << d2 << " = opIntersection(d" << d0 << ", d" << d1 << ");" << std::endl;
		d0 = d2;
	}
	return d2;
}

int IR::smooth_intersection::print(std::ofstream& f, int d) const {
	int d0, d1, d2;
	d0 = shapes[0]->print(f, d);
	d2 = d0;
	for (int i = 1; i < shapes.size(); i++) {
		const auto& shape = shapes[i];
		d1 = shape->print(f, d0 + 1);
		d2 = d1 + 1;

		f << "	float d" << d2 << " = opSmoothIntersection(d" << d0 << ", d" << d1 << "," << blend_factor << "); " << std::endl;
		d0 = d2;
	}
	return d2;
}

// print WITH translation

int IR::sphere::print(std::ofstream& f, int d, float tx, float ty, float tz) const {
	// note: there is no point in rotating a sphere. like, cause like yknow it's like yknow like yknow???
	f << "	float d" << d << " = sdSphere(" << print_center_with_transform(tx, ty, tz) << ", " << r << ");" << std::endl;
	return d;
}


int IR::box::print(std::ofstream& f, int d, float tx, float ty, float tz) const {
	f << "	float d" << d << " = sdBox(" << print_center_with_transform(tx, ty, tz) << ", " << print_vec3(l, w, h) << "); " << std::endl;
	return d;
}

int IR::cone::print(std::ofstream& f, int d, float tx, float ty, float tz) const {
	f << "	float d" << d << " = sdCone(" << print_center_with_transform(tx, ty, tz) << ", " << r << ", " << h << "); " << std::endl;
	return d;
}

int IR::torus::print(std::ofstream& f, int d, float tx, float ty, float tz) const {
	f << "	float d" << d << " = sdTorus(" << print_center_with_transform(tx, ty, tz) << ", vec2(" << R << ", " << r << ")); " << std::endl;
	return d;
}

int IR::cylinder::print(std::ofstream& f, int d, float tx, float ty, float tz) const {
	f << "	float d" << d << " = sdCylinder(" << print_center_with_transform(tx, ty, tz) << ", " << r << ", " << h << "); " << std::endl;
	return d;
}

int IR::smooth_union::print(std::ofstream& f, int d, float tx, float ty, float tz) const {
	int d0, d1, d2;
	d0 = shapes[0]->print(f, d, tx, ty, tz);
	d2 = d0;
	for (int i = 1; i < shapes.size(); i++) {
		const auto& shape = shapes[i];
		d1 = shape->print(f, d0 + 1, tx, ty, tz);
		d2 = d1 + 1;

		f << "	float d" << d2 << " = opSmoothUnion(d" << d0 << ", d" << d1 << "," << blend_factor << "); " << std::endl;
		d0 = d2;
	}
	return d2;
}

int IR::subtraction::print(std::ofstream& f, int d, float tx, float ty, float tz) const {
	int d0, d1, d2;
	d0 = shapes[0]->print(f, d, tx, ty, tz);
	d2 = d0;
	for (int i = 1; i < shapes.size(); i++) {
		const auto& shape = shapes[i];
		d1 = shape->print(f, d0 + 1, tx, ty, tz);
		d2 = d1 + 1;

		f << "	float d" << d2 << " = opSubtraction(d" << d0 << ", d" << d1 << ");" << std::endl;
		d0 = d2;
	}
	return d2;
}

int IR::smooth_subtraction::print(std::ofstream& f, int d, float tx, float ty, float tz) const {
	int d0, d1, d2;
	d0 = shapes[0]->print(f, d, tx, ty, tz);
	d2 = d0;
	for (int i = 1; i < shapes.size(); i++) {
		const auto& shape = shapes[i];
		d1 = shape->print(f, d0 + 1, tx, ty, tz);
		d2 = d1 + 1;

		f << "	float d" << d2 << " = opSmoothSubtraction(d" << d0 << ", d" << d1 << "," << blend_factor << "); " << std::endl;
		d0 = d2;
	}
	return d2;
}

int IR::intersection::print(std::ofstream& f, int d, float tx, float ty, float tz) const {
	int d0, d1, d2;
	d0 = shapes[0]->print(f, d, tx, ty, tz);
	d2 = d0;
	for (int i = 1; i < shapes.size(); i++) {
		const auto& shape = shapes[i];
		d1 = shape->print(f, d0 + 1, tx, ty, tz);
		d2 = d1 + 1;

		f << "	float d" << d2 << " = opIntersection(d" << d0 << ", d" << d1 << ");" << std::endl;
		d0 = d2;
	}
	return d2;
}

int IR::smooth_intersection::print(std::ofstream& f, int d, float tx, float ty, float tz) const {
	int d0, d1, d2;
	d0 = shapes[0]->print(f, d, tx, ty, tz);
	d2 = d0;
	for (int i = 1; i < shapes.size(); i++) {
		const auto& shape = shapes[i];
		d1 = shape->print(f, d0 + 1, tx, ty, tz);
		d2 = d1 + 1;

		f << "	float d" << d2 << " = opSmoothIntersection(d" << d0 << ", d" << d1 << "," << blend_factor << "); " << std::endl;
		d0 = d2;
	}
	return d2;
}

int IR::custom_shape::print(std::ofstream& f, int d) const {

	f << "db = sdSphere(p -" << print_center() << ", " << bounding_rad << ");" << std::endl;
	f << "sdf_ = sdf;" << std::endl;
	f << "if (db < 0.001) {" << std::endl;

	d = (*shapes)[0]->print(f, d, tx, ty, tz);
	f << "   sdf_ = vec4(d" << d << ", " << (*shapes)[0]->col->print() << ");" << std::endl;

	for (int i = 1; i < (*shapes).size(); i++) {
		const auto& shape = (*shapes)[i];
		d = shape->print(f, d + 1, tx, ty, tz);

		f << "	sdf_ " << " = opUnion(sdf_" << ", vec4(d" << d << ", " << shape->col->print() << ")); " << std::endl;
	}
	f << "}" << std::endl;
	return d;
}

int IR::custom_shape::print (std::ofstream& f, int d, float tx, float ty, float tz) const {
	f << "db = sdSphere(p -" << print_center() << ", " << bounding_rad << ");" << std::endl;
	d = (*shapes)[0]->print(f, d, tx, ty, tz);
	f << "   sdf_ = vec4(d" << d << ", " << (*shapes)[0]->col->print() << ");" << std::endl;

	for (int i = 1; i < (*shapes).size(); i++) {
		const auto& shape = (*shapes)[i];
		d = shape->print(f, d + 1, tx, ty, tz);

		f << "	sdf_ " << " = opUnion(sdf_"  << ", vec4(d" << d  << ", " << shape->col->print()  << ")); " << std::endl;
	}
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

int IR::point_light::print(std::ofstream& f) const {
	f << "	distL = vec3(" << x << ", " << y << ", " << z << ") - p;" << std::endl;
	f << "	L = normalize ( distL );" << std::endl;
	f << "	shadL = shadow(p, L, 0.01, length(distL));" << std::endl;
	f << "	falloffL = dot(distL, distL);" << std::endl;
	f << "	falloffL *= falloffL; " << std::endl;
	f << "	CL = " << i << " * " << col->print() << "/falloffL;" << std::endl;
	f << "	LdotN = clamp(dot(L, N), 0., 1.);" << std::endl;
	f << "	col += Cd * CL * LdotN * shadL;" << std::endl;
	return 1;
}

/* Collection of methods to assist with calculate bounding sphere volumes etc
*/

float IR::sphere::get_bounding_rad() const {
	return r.expr->getMax();
}

float IR::box::get_bounding_rad() const {
	float l_ = l.expr->getMax();
	float w_ = w.expr->getMax();
	float h_ = h.expr->getMax();
	return 0.5 * sqrtf(
		l_ * l_ +
		w_ * w_ +
		h_ * h_
	);
}

float IR::cone::get_bounding_rad() const {
	float r_ = r.expr->getMax();
	float h_ = 0.5 * h.expr->getMax();

	return sqrtf (r_ * r_ + h_ * h_);
}

float IR::torus::get_bounding_rad() const {
	return R.expr->getMax();
}

float IR::cylinder::get_bounding_rad() const {
	float r_ = r.expr->getMax();
	float h_ = h.expr->getMax();

	return sqrtf(r_ * r_ + h_ * h_);
}

void IR::custom_shape::generate_bounding_sphere() {

	// For all shapes, calculate the distance from center to (0, 0, 0) and then 
	// add that distance to the half-radius of the primitive's bounding sphere...

	for (const auto& shape : *shapes) {
		float x_max = shape->x.expr->getMax();
		float x_min = shape->x.expr->getMin();
		float x = std::min(x_max * x_max, x_min * x_min);

		float y_max = shape->y.expr->getMax();
		float y_min = shape->y.expr->getMin();
		float y = std::min(y_max * y_max, y_min * y_min);

		float z_max = shape->z.expr->getMax();
		float z_min = shape->z.expr->getMin();
		float z = std::min(z_max * z_max, z_min * z_min);

		float dist = sqrtf(x + y + z) + shape->get_bounding_rad ();
		std::cout << "debug; dist: " << dist << std::endl;
		if (dist > bounding_rad)
			bounding_rad = dist;

	}

	std::cout << "bounding_rad: " << bounding_rad << std::endl;
	// bounding_rad = 3.8f;
}
