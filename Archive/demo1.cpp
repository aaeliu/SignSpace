#include "user.h"

void user::create() {

	/* Primitives:
	*	sphere(), box(), cone(), torus(), cylinder()
	* 
	* Operations:
	*	smoothUnionBegin(), subtractionBegin(), smoothSubtractionBegin(), intersectionBegin(), smoothIntersectionBegin()
	* 
	* Lights:
	*	directionalLight(), pointLIght()
	* */
		

	background(5, 60, 2);
	lightColor(255, 10, 100);
	directionalLight(0, -0.8, 0.2, 10);
	pointLight(0.7, -0.2, 0.2, 10);
	//sphere(0.1, 10., -0.5, 1.);
	//smoothUnionBegin();
	//(0.2, 1., 0.5, 2.);
	//sphere(-0.2, -1., -0.5, 2.);
	///smoothUnionEnd();
	
	smoothUnionBegin();
	for (float i = 0; i < 4; i++) {
		for (float j = 0; j < 100; j++) {
			sphere(0.2 * j - 2, 0.2 * i - 2, -0.5 + 0.001 * i, 0.1);
		};
	};
	//sphere(0.4, 1., 0.5, 0.2);
	//sphere(0.8, 1., 0.5, 0.2);
	smoothUnionEnd();
	/*
	* 
	* 
	* BEGIN SAMPLE SNOWMAN SCENE
	background(7, 5, 20);
	directionalLight(0.4, -1, 0.4, 0.2);
	lightColor(30, 30, 255);
	directionalLight(0., -1, 0., 0.05);

	lightColor(255, 150, 30);
	pointLight(-1, 3.8, 0.3, 0.85);
	lightColor(255, 90, 10);
	pointLight(3, -1, 6, 1.0);

	// SNOWMAN BODY
	color(230, 230, 240);
	smoothBlendFactor(0.2);
	smoothUnionBegin();
		box(0, -2.75, 0.0,20, 0.75, 20);
		sphere(0, -0.75, 2.0, 2.);
		sphere(-0.15, 1.25, 2.0, 1.5);
		sphere(-0.3, 3.2, 2.0, 1.);
	smoothUnionEnd();

	// SNOWMAN EYE & BUTTONS
	color(10, 10, 10);
	sphere(-0.15, 1.25, 0.48, 0.08);
	sphere(-0.2, 1.8, 0.6, 0.08);
	sphere(0.1, 3.3, 1.12, 0.12); // Eye (right)
	sphere(-0.75, 3.1, 1.15, 0.12); // Eye (left)

	// SNOWMAN HAT
	rotateZ(-15);
	color(20, 20, 20);
	cylinder(-0.4, 3.8, 2.0, 1.25, 0.1);
	cylinder(-0.56, 4.6, 2.0, 1, 0.75);

	// SNOWMAN ARMS
	color(150, 70, 50);
	rotate(90, 30, 0);
	cylinder(-1.6, -1.8, 0.0, 0.2, 1.75);
	smoothBlendFactor(0.3);
	smoothSubtractionBegin();
		smoothBlendFactor(0.1);
		smoothUnionBegin();
			rotate(0, 0, 50);
			cylinder(1.4, 2.2, 2.0, 0.18, 1.75);
			rotateZ(110);
			cylinder(3., 3.3, 2.0, 0.07, 0.2);
			rotateZ(60);
			cylinder(3.0, 3.5, 2.0, 0.07, 0.2);
			rotateZ(15);
			cylinder(2.8, 3.6, 2.0, 0.07, 0.2);
		smoothUnionEnd();
		sphere(1.8, 2.7, 2.0, 0.1);
		sphere(2.5, 3.3, 2.0, 0.13);
	smoothSubtractionEnd();

	// TREEES
	rotate(0, 0, 0);
	createShapeBegin("tree");
		color(70, 159, 70);
		cone(0, 0, 0, 1., 0.8);
		cone(0, -1, 0, 1.4, 1.0);
		cone(0, -1.6, 0, 1.4, 1.2);
		color(150, 70, 50);
		cylinder(0, -2.0, 0, 0.4, 2.0);
	createShapeEnd();

	for (int i = 0; i < 5; i++) {
		shape("tree", -6 + 3.5 * i, 2., 6.);
	}

	END SAMPLE SNOWMAN SCENE

	*/
	/*background(25, 25, 25);
	lightColor(200, 190, 70);
	directionalLight(1.3, -0.2, 1.3, 0.7);

	color(red);
	sphere(-0.5, 0.5, 1.0, 0.2);

	rotateY(30);
	color(blue);
	box(0, 0.5, 1.0, 0.15, 0.2, 0.15);

	rotateY(0);
	color(yellow);
	cone(0.5, 0.5, 1.0, 0.15, 0.2);

	color(magenta);
	cylinder(0.25, 0., 1.0, 0.2, 0.2);

	rotateX(90);
	color(green);
	torus(-0.25, 0., 1.0, 0.2, 0.025);*/

	
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
	color(255, 20, 20);*/



	
	/* background(95, 2, 95);
	directionalLight(0, -10, 0, 1.0);
	color(cyan);
	createShapeBegin("crazy");
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
		color(red);
		sphere(0.2, 0.1, 1.5, 0.2);
	createShapeEnd();

	shape("crazy", 0., -0.2, 0 );
	shape("crazy", -1.0, 0, 0);
	shape("crazy", -0.3, -1.2, 0);
	*/
	/* color(red);
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
		
	smoothSubtractionEnd(); */
	
	

}

