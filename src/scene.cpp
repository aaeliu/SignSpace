#include "scene.h"
#include "user.h"
#include "primitives.h"

scene::scene() {
	user* u = new user (this);
	u->create_and_check ();
	for (auto p : u->objects_temp) {
		shapes.push_back(p);
	}

}