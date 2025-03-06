#pragma once

#include "color.h"

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
		directional_light(float x_, float y_, float z_, float i_) : x(x_), y(y_), z(z_), i(i_) {};
		~directional_light() override = default;
		int print(std::ofstream& f) const override;
	};
}
