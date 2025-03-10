#pragma once
#include <vector>
#include <map>
#include <cassert>
#include "color.h"
#include "primitives.h"
#include "light.h"

// thanks StackOverflow https://stackoverflow.com/a/3767883
#define ASSERT(condition, message) \
    do { \
        if (! (condition)) { \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                      << " line " << __LINE__ << ": " << message << std::endl; \
            std::terminate(); \
        } \
    } while (false)


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