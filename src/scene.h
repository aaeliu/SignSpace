#pragma once
#include <vector>
#include "color.h"
#include "primitives.h"


struct scene {
	std::vector<IR::primitive *> shapes;
	Color background = Color (0, 0, 0);
	std::shared_ptr <Color> current_color = std::make_shared <Color> (0, 0, 0);
	scene ();
};