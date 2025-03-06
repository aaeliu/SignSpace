#include "scene.h"
#include "user.h"
#include "primitives.h"

scene::scene() {
	user* u = new user (this);
	u->create ();
}