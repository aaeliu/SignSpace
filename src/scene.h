#pragma once
#include <vector>
#include "color.h"
#include "primitives.h"
#include "light.h"


struct scene {
	std::vector<std::shared_ptr<IR::primitive>> shapes;
	std::vector<std::shared_ptr<IR::light>> lights;
	Color background = Color (0, 0, 0);
	float ambient_factor = 0.1; // Default ambient factor.

	std::shared_ptr <Color> current_color = std::make_shared <Color> (0, 0, 0);
	std::shared_ptr <Color> current_light_color = std::make_shared <Color> (255, 255, 255);

	scene ();
};