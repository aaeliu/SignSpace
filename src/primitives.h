#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "color.h"


namespace IR {
	struct primitive {
		float x, y, z;
		float rot_x =0, rot_y=0, rot_z=0;
		primitive(float x_, float y_, float z_): x(x_), y(y_), z(z_) {};
		primitive() = default;
		virtual ~primitive() = default;
		virtual int print(std::ofstream& f, int n) const = 0;

		bool to_combine = false;
		std::shared_ptr <Color> col;
		std::string print_vec3(float a, float b, float c) const {
			std::stringstream ss;
			ss << "vec3(" << a << ", " << b << ", " << c << ")";
			return ss.str();
		}
		std::string print_center() const {
			return print_vec3(x, y, z);
		}
		std::string print_center_with_rotations() const;

	};

	struct sphere : public primitive {
		float r;
		sphere(float x_, float y_, float z_, float r_) : primitive(x_,y_,z_), r(r_) {};
		~sphere() override = default;
		int print(std::ofstream& f, int n) const override;
	};

	struct box : public primitive {
		float l, w, h;
		box(float x_, float y_, float z_, float l_, float w_, float h_) : primitive(x_, y_, z_),
																		  l(l_), w(w_), h(h_) {};
		int print(std::ofstream& f, int n) const override;
	};

	enum comb_type{
		SMOOTH_UNION,
		SUBTRACTION,
		SMOOTH_SUBRACTION,
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
		float blend_factor = 0.25;
		smooth_union() { }
		comb_type get_comb_type() const override  { return comb_type::SMOOTH_UNION; }
		int print(std::ofstream& f, int n) const override;
	};

	// if we have subtraction on a, b, c, d, e... result is a - b - c - d - e
	struct subtraction : public combination {
		subtraction() {}
		comb_type get_comb_type() const override { return comb_type::SUBTRACTION; }
		int print(std::ofstream& f, int n) const override;
	};
}