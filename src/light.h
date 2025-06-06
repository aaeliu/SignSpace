#pragma once

#include "color.h"
#include <cmath>
#include <cassert>
#include "time.h"

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
		TimeExpr x, y, z; // direction; eg. (0, -1, 0) is downward facing light
		TimeExpr i;	   // intensity
		directional_light(const TimeExpr& x_, const TimeExpr& y_, const TimeExpr& z_, const TimeExpr& i_) :  i(i_) {
			TimeExpr len = sqrt(x_ * x_ + y_ * y_ + z_ * z_);
			// assert(len != 0);
			x = x_ / len;
			y = y_ / len;
			z = z_ / len;
		};
		~directional_light() override = default;
		int print(std::ofstream& f) const override;
	};

	struct point_light : public light {
		TimeExpr x, y, z;	// Position
		TimeExpr i;		// Intensity

		point_light(const TimeExpr& x_, const TimeExpr& y_, const TimeExpr& z_, const TimeExpr& i_) : x(x_), y(y_), z(z_), i(i_) {};
		int print(std::ofstream& f) const override;
	};
}
