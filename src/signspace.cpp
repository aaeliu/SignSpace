#include "user.h"

void user::create() {
	background(20, 5, 20);

	directionalLight(0, -1, 1.4, 1);

	color (255, 0, 0);
	sphere (0., 0., 1.0, 0.2);
	sphere (0.4, 0., 1.0, 0.1);

	color (0, 255, 0);
	sphere (-0.5, 0., 1.0, 0.1);

	color(255, 255, 0);
	box(-0.8, -0.25, 2.0, 0.3, 0.2, 0.1);

	color (0, 0, 255);
	sphere (-0.5, 0.25, 1.0, 0.1);

	sphere(-0.0, -0.4, 0.25, 0.3);
}

