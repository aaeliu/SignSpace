#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "color.h"

namespace IR {
	struct primitive {
		TimeExpr x, y, z;
		float rot_x =0, rot_y=0, rot_z=0;
		// float trans_x = 0, trans_y = 0, trans_z = 0;
		primitive(const TimeExpr& x_, const TimeExpr& y_, const TimeExpr& z_): x(x_), y(y_), z(z_) {};
		primitive() = default;
		virtual ~primitive() = default;

		virtual int print(std::ofstream& f, int n) const = 0;
		// Print with translation
		virtual int print(std::ofstream& f, int n, float tx, float ty, float tz) const = 0;

		bool to_combine = false;
		bool is_custom  = false;

		std::shared_ptr <Color> col;
		std::string print_vec3(const TimeExpr& a, const TimeExpr& b, const TimeExpr& c) const {
			std::stringstream ss;
			ss << "vec3(" << a << ", " << b << ", " << c << ")";
			return ss.str();
		}
		std::string print_center() const {
			return print_vec3(x, y, z);
		}
		std::string print_center_with_rotations() const;
		std::string print_center_with_transform(float tx, float ty, float tz) const;

	};

	struct sphere : public primitive {
		TimeExpr r;
		sphere(const TimeExpr& x_, const TimeExpr& y_, const TimeExpr& z_, const TimeExpr& r_) : primitive(x_,y_,z_), r(r_) {};
		~sphere() override = default;
		int print(std::ofstream& f, int n) const override;
		int print(std::ofstream& f, int n, float tx, float ty, float tz) const override;
	};

	struct box : public primitive {
		TimeExpr l, w, h;
		box(const TimeExpr& x_, const TimeExpr& y_, const TimeExpr& z_, const TimeExpr& l_, const TimeExpr& w_, const TimeExpr& h_) : primitive(x_, y_, z_),
																		  l(l_), w(w_), h(h_) {};
		int print(std::ofstream& f, int n) const override;
		int print(std::ofstream& f, int n, float tx, float ty, float tz) const override;
	};

	struct cone : public primitive {
		TimeExpr r, h;
		cone(const TimeExpr& x_, const TimeExpr& y_, const TimeExpr& z_, const TimeExpr& r_, const TimeExpr& h_) : primitive(x_, y_, z_), r(r_), h(h_) {};
		int print(std::ofstream& f, int n) const override;
		int print(std::ofstream& f, int n, float tx, float ty, float tz) const override;
	};

	struct torus : public primitive {
		TimeExpr R, r;
		torus(const TimeExpr& x_, const TimeExpr& y_, const TimeExpr& z_, const TimeExpr& R_, const TimeExpr& r_) : primitive(x_, y_, z_), R(R_), r(r_) {};
		int print(std::ofstream& f, int n) const override;
		int print(std::ofstream& f, int n, float tx, float ty, float tz) const override;
	};

	struct cylinder : public primitive {
		TimeExpr r, h;
		cylinder(const TimeExpr& x_, const TimeExpr& y_, const TimeExpr& z_, const TimeExpr& r_, const TimeExpr& h_) : primitive(x_, y_, z_), r(r_), h(h_) {};
		int print(std::ofstream& f, int n) const override;
		int print(std::ofstream& f, int n, float tx, float ty, float tz) const override;
	};


	enum comb_type{
		SMOOTH_UNION,
		SUBTRACTION,
		SMOOTH_SUBTRACTION,
		INTERSECTION,
		SMOOTH_INTERSECTION
	};

	struct combination : public primitive {
		std::vector <std::shared_ptr<primitive>> shapes;
		combination() = default;
		virtual ~combination() = default;
		virtual comb_type get_comb_type() const = 0;
	};

	struct smooth_union : public combination {
		const TimeExpr& blend_factor = 0.25;
		smooth_union() { }
		comb_type get_comb_type() const override  { return comb_type::SMOOTH_UNION; }
		int print(std::ofstream& f, int n) const override;
		int print(std::ofstream& f, int n, float tx, float ty, float tz) const override;
	};

	// if we have subtraction on a, b, c, d, e... result is a - b - c - d - e
	struct subtraction : public combination {
		subtraction() {}
		comb_type get_comb_type() const override { return comb_type::SUBTRACTION; }
		int print(std::ofstream& f, int n) const override;
		int print(std::ofstream& f, int n, float tx, float ty, float tz) const override;
	};

	struct smooth_subtraction : public combination {
		const TimeExpr& blend_factor = 0.25;
		smooth_subtraction() {}
		comb_type get_comb_type() const override { return comb_type::SMOOTH_SUBTRACTION; }
		int print(std::ofstream& f, int n) const override;
		int print(std::ofstream& f, int n, float tx, float ty, float tz) const override;
	};

	struct intersection : public combination {
		intersection() {}
		comb_type get_comb_type() const override { return comb_type::INTERSECTION; }
		int print(std::ofstream& f, int n) const override;
		int print(std::ofstream& f, int n, float tx, float ty, float tz) const override;
	};

	struct smooth_intersection : public combination {
		const TimeExpr& blend_factor = 0.25;
		smooth_intersection () {}
		comb_type get_comb_type() const override { return comb_type::SMOOTH_INTERSECTION; }
		int print(std::ofstream& f, int n) const override;
		int print(std::ofstream& f, int n, float tx, float ty, float tz) const override;
	};

	struct custom_shape : public primitive {
		std::shared_ptr<std::vector<std::shared_ptr<IR::primitive>>> shapes;
		float bounding_rad;
		float tx, ty, tz;
		// bool is_custom = true;

		custom_shape() {
			shapes = std::make_shared <std::vector<std::shared_ptr<IR::primitive>>>();
		}

		/*custom_shape(std::shared_ptr<std::vector<std::shared_ptr<IR::primitive>>> s, float tx_, float ty_, float tz_) :
			shapes(s), tx(tx_), ty(ty_), tz(tz_) {
			is_custom = true;
		};*/

		custom_shape(std::shared_ptr<IR::custom_shape> s, float tx_, float ty_, float tz_) : primitive (tx_, ty_, tz_), 
																								tx(tx_), ty(ty_), tz(tz_) {
			shapes = s->shapes;
			bounding_rad = s->bounding_rad;
			is_custom = true;
		}

		void generate_bounding_sphere ();

		int print(std::ofstream& f, int n) const override;
		int print(std::ofstream& f, int n, float tx, float ty, float tz) const override;
	};
}