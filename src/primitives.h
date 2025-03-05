#pragma once
#include <fstream>
#include <iostream>

namespace IR {
	struct primitive {
		primitive() {};
		virtual ~primitive() = default;
		virtual int print(std::ofstream& f, int n) const = 0;
	};

	struct sphere : public primitive {
		float x, y, z, r;
		sphere(float x_, float y_, float z_, float r_) : x(x_), y(y_), z(z_), r(r_) {};
		~sphere() override = default;
		int print(std::ofstream& f, int n) const override;
	};
}