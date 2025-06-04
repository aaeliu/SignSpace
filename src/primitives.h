#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <optional>
#include "color.h"

namespace IR {
	struct primitive {
		TimeExpr x, y, z;
		std::optional<TimeExpr> rot_x, rot_y, rot_z;
		// float trans_x = 0, trans_y = 0, trans_z = 0;
		primitive(const TimeExpr& x_, const TimeExpr& y_, const TimeExpr& z_): x(x_), y(y_), z(z_) {};
		primitive() = default;
		virtual ~primitive() = default;

		virtual int print(std::ofstream& f, int n) const = 0;
		// Print with translation
		virtual int print(std::ofstream& f, int n, int t) const = 0;

		float get_dist() const {
			float x_max = x.expr->getMax();
			float x_min = x.expr->getMin();
			float x = std::min(x_max * x_max, x_min * x_min);

			float y_max = y.expr->getMax();
			float y_min = y.expr->getMin();
			float y = std::min(y_max * y_max, y_min * y_min);

			float z_max = z.expr->getMax();
			float z_min = z.expr->getMin();
			float z = std::min(z_max * z_max, z_min * z_min);
			return sqrtf(x + y + z);
		}
		virtual float get_bounding_rad() const = 0;
		virtual float get_bounding_dist() const = 0;

		bool is_custom  = false;
		bool is_combination = false;

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
		std::string print_center_with_transform(const TimeExpr& tx, const TimeExpr& ty, const TimeExpr& tz) const;
		std::string print_center_with_transform(int t) const;
		std::string print_center_with_transform(const TimeExpr& tx, const TimeExpr& ty, const TimeExpr& tz,
												const std::optional<TimeExpr>& rx, 
												const std::optional<TimeExpr>& ry, 
												const std::optional<TimeExpr>& rz) const;

	};

	struct sphere : public primitive {
		TimeExpr r;
		sphere(const TimeExpr& x_, const TimeExpr& y_, const TimeExpr& z_, const TimeExpr& r_) : primitive(x_,y_,z_), r(r_) {};
		~sphere() override = default;
		float get_bounding_rad() const override;
		float get_bounding_dist() const override { return get_dist() + get_bounding_rad(); }
		int print(std::ofstream& f, int n) const override;
		int print(std::ofstream& f, int n, int t) const override;
	};

	struct box : public primitive {
		TimeExpr l, w, h;
		box(const TimeExpr& x_, const TimeExpr& y_, const TimeExpr& z_, const TimeExpr& l_, const TimeExpr& w_, const TimeExpr& h_) : primitive(x_, y_, z_),
																		  l(l_), w(w_), h(h_) {};
		float get_bounding_rad() const override;
		float get_bounding_dist() const override { return get_dist() + get_bounding_rad(); }
		int print(std::ofstream& f, int n) const override;
		int print(std::ofstream& f, int n, int t) const override;
	};

	struct cone : public primitive {
		TimeExpr r, h;
		cone(const TimeExpr& x_, const TimeExpr& y_, const TimeExpr& z_, const TimeExpr& r_, const TimeExpr& h_) : primitive(x_, y_, z_), r(r_), h(h_) {};
		float get_bounding_rad() const override;
		float get_bounding_dist() const override { return get_dist() + get_bounding_rad(); }
		int print(std::ofstream& f, int n) const override;
		int print(std::ofstream& f, int n, int t) const override;
	};

	struct torus : public primitive {
		TimeExpr R, r;
		torus(const TimeExpr& x_, const TimeExpr& y_, const TimeExpr& z_, const TimeExpr& R_, const TimeExpr& r_) : primitive(x_, y_, z_), R(R_), r(r_) {};
		float get_bounding_rad() const override;
		float get_bounding_dist() const override { return get_dist() + get_bounding_rad(); }
		int print(std::ofstream& f, int n) const override;
		int print(std::ofstream& f, int n, int t) const override;
	};

	struct cylinder : public primitive {
		TimeExpr r, h;
		cylinder(const TimeExpr& x_, const TimeExpr& y_, const TimeExpr& z_, const TimeExpr& r_, const TimeExpr& h_) : primitive(x_, y_, z_), r(r_), h(h_) {};
		float get_bounding_rad() const override;
		float get_bounding_dist() const override { return get_dist() + get_bounding_rad(); }
		int print(std::ofstream& f, int n) const override;
		int print(std::ofstream& f, int n, int t) const override;
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
		combination() { is_combination = true; };
		float get_bounding_rad() const override { return 0.0f; };
		float get_bounding_dist() const override { 
			float d = 0;
			for (const auto& shape : shapes) {
				float d_ = shape->get_bounding_dist();
				d = std:: max(d, d_);
			}
			return d; 
		}
		virtual ~combination() = default;
		virtual comb_type get_comb_type() const = 0;
	};

	struct smooth_union : public combination {
		const TimeExpr& blend_factor = 0.25;
		smooth_union() : combination() { }
		comb_type get_comb_type() const override  { return comb_type::SMOOTH_UNION; }
		int print(std::ofstream& f, int n) const override;
		int print(std::ofstream& f, int n, int t) const override;
	};

	// if we have subtraction on a, b, c, d, e... result is a - b - c - d - e
	struct subtraction : public combination {
		subtraction() : combination() {}
		comb_type get_comb_type() const override { return comb_type::SUBTRACTION; }
		int print(std::ofstream& f, int n) const override;
		int print(std::ofstream& f, int n, int t) const override;
	};

	struct smooth_subtraction : public combination {
		const TimeExpr& blend_factor = 0.25;
		smooth_subtraction() : combination() {}
		comb_type get_comb_type() const override { return comb_type::SMOOTH_SUBTRACTION; }
		int print(std::ofstream& f, int n) const override;
		int print(std::ofstream& f, int n, int t) const override;
	};

	struct intersection : public combination {
		intersection() : combination() {}
		comb_type get_comb_type() const override { return comb_type::INTERSECTION; }
		int print(std::ofstream& f, int n) const override;
		int print(std::ofstream& f, int n, int t) const override;
	};

	struct smooth_intersection : public combination {
		const TimeExpr& blend_factor = 0.25;
		smooth_intersection() : combination() {}
		comb_type get_comb_type() const override { return comb_type::SMOOTH_INTERSECTION; }
		int print(std::ofstream& f, int n) const override;
		int print(std::ofstream& f, int n, int t) const override;
	};

	struct custom_shape : public primitive {
		std::shared_ptr<std::vector<std::shared_ptr<IR::primitive>>> shapes;
		std::string transform_string;
		float bounding_rad;

		custom_shape() {
			shapes = std::make_shared <std::vector<std::shared_ptr<IR::primitive>>>();
			is_custom = true;
		}
		custom_shape(std::shared_ptr<IR::custom_shape> s, const TimeExpr& tx, const TimeExpr& ty, const TimeExpr& tz) : primitive (tx, ty, tz) {
			shapes = s->shapes;
			bounding_rad = s->bounding_rad;
			is_custom = true;
		}

		float get_bounding_dist() const override { return get_dist() + get_bounding_rad(); }
		float get_bounding_rad() const override { return bounding_rad;  }
		void generate_bounding_sphere ();

		int print(std::ofstream& f, int n) const override;
		int print(std::ofstream& f, int n, int t) const override;
	};
}