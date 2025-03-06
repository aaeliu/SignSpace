#pragma once
#include <sstream>

struct Color {
	float r, g, b;
	Color(int r_, int g_, int b_) {
		r = r_ / 255.0f;
		g = g_ / 255.0f;
		b = b_ / 255.0f;
	}

	std::string print() {
		std::stringstream ss;
		ss << "vec3(" << r << ", " << g << ", " << b << ")";
		return ss.str();
	}
};