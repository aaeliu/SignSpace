#pragma once

#include "color.h"
#include <cmath>
#include <cassert>

namespace IR {
	
	enum light_type {
		DIRECTIONAL,
		POINT
	};

	struct light {
		light() {};
		virtual ~light() = default;
		virtual int print(std::ofstream& f) const = 0;

		std::shared_ptr <Color> col;
	};

	struct directional_light : public light {
		float x, y, z; // direction; eg. (0, -1, 0) is downward facing light
		float i;	   // intensity
		directional_light(float x_, float y_, float z_, float i_) :  i(i_) {
			float len = sqrtf(x_ * x_ + y_ * y_ + z_ * z_);
			assert(len != 0);
			x = x_ / len;
			y = y_ / len;
			z = z_ / len;
		};
		~directional_light() override = default;
		int print(std::ofstream& f) const override;
	};

	struct point_light : public light {
		float x, y, z;	// Position
		float i;		// Intensity

		point_light(float x_, float y_, float z_, float i_) : x(x_), y(y_), z(z_), i(i_) {};
		int print(std::ofstream& f) const override;
	};
}
