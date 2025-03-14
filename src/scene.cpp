#include "scene.h"
#include "user.h"
#include "primitives.h"

scene::scene() {
	user* u = new user (this);
	u->create_and_check ();
	for (auto p : u->objects_temp) {
		if (!p->to_combine)
			shapes.push_back(p);
	}
	ambient_color.r *= ambient_factor;
	ambient_color.g *= ambient_factor;
	ambient_color.b *= ambient_factor;
}