#pragma once
#include <sstream>
#include "time.h"

struct Color {
	TimeExpr r, g, b;
	Color(const TimeExpr& r_, const TimeExpr& g_, const TimeExpr& b_) : r(r_/255.0f), g(g_/255.0f), b(b_/255.0f) {
		//r = r_ / 255.0f;
		//g = g_ / 255.0f;
		//b = b_ / 255.0f;
	}

	/*bool operator==(const Color& other) {
		return (r_i == other.r_i && g_i == other.g_i && b_i == other.b_i);
	}*/

	std::string print() {
		std::stringstream ss;
		ss << "vec3(" << r << ", " << g << ", " << b << ")";
		return ss.str();
	}
};