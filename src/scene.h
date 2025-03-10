#pragma once
#include <vector>
#include <map>
#include "color.h"
#include "primitives.h"
#include "light.h"

enum prim_type {
	SPHERE,
	RECT,
	CONE
};

struct scene {
	std::vector<std::shared_ptr<IR::primitive>> shapes;
	std::vector<std::shared_ptr<IR::light>> lights;
	Color background = Color (0, 0, 0);
	float ambient_factor = 0.25; // Default ambient factor.

	std::shared_ptr <Color> current_color = std::make_shared <Color> (0, 0, 0);
	std::shared_ptr <Color> current_light_color = std::make_shared <Color> (255, 255, 255);

	std::map <prim_type, bool> prim_present;
	scene ();
};