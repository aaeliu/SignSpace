#include "user.h"

void user::create() {
	background(20, 5, 20);

	directionalLight(0, -10, 0, 1.0);
	// directionalLight(0.3, -1, 0, 0.3);

	color (red);
	subtractionBegin();
		sphere (0., 0., 1.0, 0.2);
		box(0.15, 0., 1.0, 0.08, 0.1, 0.2);
	subtractionEnd();
	sphere (0.4, 0., 1.0, 0.1);

	color (0, 255, 0);
	sphere (-0.5, 0., 1.0, 0.1);
	pointLight(-0.5, -1.00, 1.0, 1.0);
	cone(-0.5, 0.5, 1.0, 0.2, 0.3);

	color(255, 255, 0);
	// rotateZ(45);
	rotateY(45);
	box(-1, -0.25, 2.0, 0.3, 0.2, 0.5);

	rotateY(0);
	rotateZ(0);
	color (0, 0, 255);
	sphere (-0.5, 0.25, 1.0, 0.1);
	sphere (-0.0, -0.4, 0.25, 0.3);

	color(0, 255, 255); 

	rotateZ(45);
	subtractionBegin();
		smoothUnionBegin();
			box(0.4, 0.5, 1.5, 0.2, 0.2, 0.2);
			sphere(0.5, 0.2, 1.5, 0.3);
			sphere(0.8, 0.3, 1.5, 0.1);
			sphere(0.3, 0.8, 1.5, 0.3);
		smoothUnionEnd(); 
		
		smoothUnionBegin();
		rotateZ(0);
		box(0.4, 0.5, 1.5, 0.1, 0.1, 2.0);
		rotateZ(30);
		box(0.4, 0.5, 1.5, 0.1, 0.1, 2.0);
		smoothUnionEnd();
		box(0.3, 0.8, 1.5, 0.2, 0.2, 0.5);
	subtractionEnd();
	
	

}

