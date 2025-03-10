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
	float ambient_factor = 0.2; // Default ambient factor.

	std::map <prim_type, bool> prim_present;
	scene ();
};