#pragma once
#include <fstream>
#include <iostream>
#include "color.h"


namespace IR {
	struct primitive {
		primitive() {};
		virtual ~primitive() = default;
		virtual int print(std::ofstream& f, int n) const = 0;

		std::shared_ptr <Color> col;
	};

	struct sphere : public primitive {
		float x, y, z, r;
		sphere(float x_, float y_, float z_, float r_) : x(x_), y(y_), z(z_), r(r_) {};
		~sphere() override = default;
		int print(std::ofstream& f, int n) const override;
	};
}