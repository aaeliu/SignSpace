#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include "color.h"


namespace IR {
	struct primitive {
		float x, y, z;
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

	struct smooth_union : public primitive {
		std::shared_ptr<primitive> shape_1;
		std::shared_ptr<primitive> shape_2;
		smooth_union(std::shared_ptr<primitive> p1, std::shared_ptr<primitive> p2) {
			shape_1 = p1;
			shape_2 = p2;
		};
		int print(std::ofstream& f, int n) const override;
	};
}