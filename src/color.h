#pragma once
#include <sstream>

struct Color {
	float r, g, b;
	int r_i, g_i, b_i;
	Color(int r_, int g_, int b_) : r_i(r_), g_i(g_), b_i(b_) {
		r = r_ / 255.0f;
		g = g_ / 255.0f;
		b = b_ / 255.0f;
	}

	bool operator==(const Color& other) {
		return (r_i == other.r_i && g_i == other.g_i && b_i == other.b_i);
	}

	std::string print() {
		std::stringstream ss;
		ss << "vec3(" << r << ", " << g << ", " << b << ")";
		return ss.str();
	}
};