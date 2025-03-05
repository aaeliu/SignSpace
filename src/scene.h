#pragma once
#include <vector>
#include "color.h"
#include "primitives.h"


struct scene {
	std::vector<IR::primitive *> shapes;
	color background;
	scene ();
};