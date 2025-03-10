#include "user.h"

void user::create() {
	
	/*background(70, 55, 245);
	directionalLight(1.3, -0.2, 1.3, 0.7);
	//directionalLight(0, 0, -1, 1.0);
	color(200, 0, 0);

	rotateY(45);
	box(0.5, 0, 1.0, 0.25, 0.5, 0.25);
	rotateY(0);
	box(-0.5, 0, 1.0, 0.25, 0.5, 0.25);

	color(50, 200, 200);
	box(0, -0.75, 1.0, 10, 0.25, 10);

	torus(0, 1, 1, 0.5, 0.1);
	cylinder(2, 1, 1, 0.5, 1);*/
	/*lightColor(blue);
	pointLight(0., 4.0, 0.0, 1);
	// directionalLight(0, -1, 0, 1.0);
	// pointLight(0, 0, -1, 2);
	color(255, 20, 20);
x
	int time = 0;


	sphere(3 * cos(time), 2, 3 * sin(time), 0.4);*/



	
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

	lightColor(255, 255, 0);
	pointLight(-0.5, -1.00, 1.0, 1.0);

	lightColor(255, 0, 255);
	pointLight(1.5, -1.00, 1.0, 1.0);
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
	smoothBlendFactor(0.1);
	smoothSubtractionBegin();
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
	smoothSubtractionEnd(); 
	
	

}

