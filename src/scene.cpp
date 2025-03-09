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
}