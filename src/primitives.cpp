#include "scene.h"
#include "primitives.h"
#include "user.h"
#include "light.h"

int custom_shape_counter = 0;

std::string IR::primitive::print_center_with_rotations() const {
	std::string c = "p - " + print_vec3(x, y, z);
	if (rot_z.has_value()) {
		c = "rotate_z(" + c + "," + rot_z.value().expr->str() + ")";
	}
	if (rot_y.has_value()) {
		c = "rotate_y(" + c + "," + rot_y.value().expr->str() + ")";
	}
	if (rot_x.has_value()) {
		c = "rotate_x(" + c + "," + rot_x.value().expr->str() + ")";
	}
	return c;
}

std::string IR::primitive::print_center_with_transform(int t) const {
	std::string c = "t" + std::to_string(t) + " - " + print_vec3(x, y, z);
	if (rot_z.has_value()) {
		c = "rotate_z(" + c + "," + rot_z.value().expr->str() + ")";
	}
	if (rot_y.has_value()) {
		c = "rotate_y(" + c + "," + rot_y.value().expr->str() + ")";
	}
	if (rot_x.has_value()) {
		c = "rotate_x(" + c + "," + rot_x.value().expr->str() + ")";
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
		std::cout << "blend_factor: " << blend_factor << std::endl;
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

int IR::sphere::print(std::ofstream& f, int d, int t) const {
	f << "	float d" << d << " = sdSphere(" << print_center_with_transform(t) << ", " << r << ");" << std::endl;
	return d;
}

int IR::box::print(std::ofstream& f, int d, int t) const {
	f << "	float d" << d << " = sdBox(" << print_center_with_transform(t) << ", " << print_vec3(l, w, h) << "); " << std::endl;
	return d;
}
int IR::cone::print(std::ofstream& f, int d, int t) const {
	f << "	float d" << d << " = sdCone(" << print_center_with_transform(t) << ", " << r << ", " << h << "); " << std::endl;
	return d;
}
int IR::torus::print(std::ofstream& f, int d, int t) const {
	f << "	float d" << d << " = sdTorus(" << print_center_with_transform(t) << ", vec2(" << R << ", " << r << ")); " << std::endl;
	return d;
}

int IR::cylinder::print(std::ofstream& f, int d, int t) const {
	f << "	float d" << d << " = sdCylinder(" << print_center_with_transform(t) << ", " << r << ", " << h << "); " << std::endl;
	return d;
}
int IR::smooth_union::print(std::ofstream& f, int d, int t) const {
	int d0, d1, d2;
	d0 = shapes[0]->print(f, d, t);
	d2 = d0;
	for (int i = 1; i < shapes.size(); i++) {
		const auto& shape = shapes[i];
		d1 = shape->print(f, d0 + 1, t);
		d2 = d1 + 1;

		f << "	float d" << d2 << " = opSmoothUnion(d" << d0 << ", d" << d1 << "," << blend_factor << "); " << std::endl;
		d0 = d2;
	}
	return d2;
}

int IR::subtraction::print(std::ofstream& f, int d, int t) const {
	int d0, d1, d2;
	d0 = shapes[0]->print(f, d, t);
	d2 = d0;
	for (int i = 1; i < shapes.size(); i++) {
		const auto& shape = shapes[i];
		d1 = shape->print(f, d0 + 1, t);
		d2 = d1 + 1;

		f << "	float d" << d2 << " = opSubtraction(d" << d0 << ", d" << d1 << ");" << std::endl;
		d0 = d2;
	}
	return d2;
}


int IR::smooth_subtraction::print(std::ofstream& f, int d, int t) const {
	int d0, d1, d2;
	d0 = shapes[0]->print(f, d, t);
	d2 = d0;
	for (int i = 1; i < shapes.size(); i++) {
		const auto& shape = shapes[i];
		d1 = shape->print(f, d0 + 1, t);
		d2 = d1 + 1;

		f << "	float d" << d2 << " = opSmoothSubtraction(d" << d0 << ", d" << d1 << "," << blend_factor << "); " << std::endl;
		d0 = d2;
	}
	return d2;
}

int IR::intersection::print(std::ofstream& f, int d, int t) const {
	int d0, d1, d2;
	d0 = shapes[0]->print(f, d, t);
	d2 = d0;
	for (int i = 1; i < shapes.size(); i++) {
		const auto& shape = shapes[i];
		d1 = shape->print(f, d0 + 1, t);
		d2 = d1 + 1;

		f << "	float d" << d2 << " = opIntersection(d" << d0 << ", d" << d1 << ");" << std::endl;
		d0 = d2;
	}
	return d2;
}


int IR::smooth_intersection::print(std::ofstream& f, int d, int t) const {
	int d0, d1, d2;
	d0 = shapes[0]->print(f, d, t);
	d2 = d0;
	for (int i = 1; i < shapes.size(); i++) {
		const auto& shape = shapes[i];
		d1 = shape->print(f, d0 + 1, t);
		d2 = d1 + 1;

		f << "	float d" << d2 << " = opSmoothIntersection(d" << d0 << ", d" << d1 << "," << blend_factor << "); " << std::endl;
		d0 = d2;
	}
	return d2;
}

int IR::custom_shape::print(std::ofstream& f, int d, int t) const {
	f << "db = sdSphere( t" << t << ", " << bounding_rad << ");" << std::endl;
	f << "if (db < 1.0) {" << std::endl;

	d = (*shapes)[0]->print(f, d, t);
	if (!(*shapes)[0]->is_custom) {
		if (d == 0) {
			f << "   sdf = vec4(d" << d << ", " << (*shapes)[0]->col->print() << ");" << std::endl;
		}
		else {
			f << "	sdf " << " = opUnion(sdf" << ", vec4(d" << d << ", " << (*shapes)[0]->col->print() << ")); " << std::endl;
		}
	}

	for (int i = 1; i < (*shapes).size(); i++) {
		const auto& shape = (*shapes)[i];
		d = shape->print(f, d + 1, t);

		if (!shape->is_custom) {
			f << "	sdf " << " = opUnion(sdf" << ", vec4(d" << d << ", " << shape->col->print() << ")); " << std::endl;
		}
	}
	f << "}" << std::endl;
	return d;
}

int IR::custom_shape::print(std::ofstream& f, int d) const {

	int init_d = d;
	int t_count = custom_shape_counter++;
	std::string t = "p - " + print_center();
	if (rot_z.has_value()) {
		t = "rotate_z(" + t + "," + rot_z.value().expr->str() + ")";
	}
	if (rot_y.has_value()) {
		t = "rotate_y(" + t + "," + rot_y.value().expr->str() + ")";
	}
	if (rot_x.has_value()) {
		t = "rotate_x(" + t + "," + rot_x.value().expr->str() + ")";
	}

	f << "vec3 t" << t_count << " = " << t << ";" << std::endl;
	f << "db = 0;";
	f << "if (db < 1.0) {" << std::endl;

	d = (*shapes)[0]->print(f, d, t_count);
	if (!(*shapes)[0]->is_custom) {
		if (init_d == 0) {
			f << "   sdf = vec4(d" << d << ", " << (*shapes)[0]->col->print() << ");" << std::endl;
		}
		else {
			f << "	sdf " << " = opUnion(sdf" << ", vec4(d" << d << ", " << (*shapes)[0]->col->print() << ")); " << std::endl;
		}
	}

	for (int i = 1; i < (*shapes).size(); i++) {
		const auto& shape = (*shapes)[i];
		d = shape->print(f, d + 1, t_count);

		if (!shape->is_custom) {
			f << "	sdf " << " = opUnion(sdf" << ", vec4(d" << d << ", " << shape->col->print() << ")); " << std::endl;
		}
	}
	f << "}" << std::endl;
	f << "else { sdf = opUnion (sdf, vec4(db, 1.0, 1.0, 1.0)); }" << std::endl;
	return d;
}

int IR::directional_light::print(std::ofstream& f) const {

	f << "	L = vec3(" << x << ", " << y << ", " << z << ");" << std::endl;
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
		bounding_rad = std::max(shape->get_bounding_dist(), bounding_rad);
	}
	std::cout << "bounding_rad: " << bounding_rad << std::endl;
}
