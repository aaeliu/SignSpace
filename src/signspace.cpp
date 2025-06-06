#include "user.h"

void user::create() {

	/* Primitives:
	*	sphere(), box(), cone(), torus(), cylinder()
	* 
	* Operations:
	*	smoothUnionBegin(), subtractionBegin(), smoothSubtractionBegin(), intersectionBegin(), smoothIntersectionBegin()
	* 
	* Lights:
	*	directionalLight(), pointLight()
	* */

	/*directionalLight(0, -1, 0.4, 0.7);
	background(199, 232, 255);

	color(255, 199, 245);
	sphere(0, 1.6, 2, 1.5);

	color(171, 127, 89);
	rotateZ(180);
	cone(0, -1.5, 2, 1.0, 2);

	lightColor(255, 221, 140);
	pointLight(2.0, 3.0, 1.0, 0.5);*/

	
	/*background(127);
	color(255, 119, 0);
	sphere(0, 0, 0, 1);
	
	color(0, 255, 0);
	rotate(45, 45, 45);
	float rt2 = 0.62; //1.0f / sqrtf(2.0);
	smoothUnionBegin();
	box(rt2, rt2, -rt2, 0.1, 0.1, 0.1);
	box(rt2 - 0.08, rt2 - 0.08, -rt2 + 0.08, 0.14, 0.14, 0.14);
	smoothUnionEnd();

	pointLight(3, 3, 0, 25);
	directionalLight(0, -1, 0, 0.4);

	rotate(90, 0, 0);
	color(255, 255, 0);
	smoothSubtractionBegin();
		torus(-2, 2, 2, 1, 0.7);
		rotate(0, 0, 45);
		box(-3, 3, 2, 1.2, 1.7, 4);
	smoothSubtractionEnd();
	color(86, 41, 0);
	box(-1.75, 2.5, 2, 0.25, 0.25, 0.25);


	color(150, 0, 10);
	sphere(-2, -2, -2, 1.3);
	color(0, 200, 0);S

	smoothUnionBegin();
	box(-2, -0.65, -2.3, 0.2, 0.2, 0.2);
	box(-1.88, -0.65, -2.3, 0.2, 0.2, 0.2);
	smoothUnionEnd();*/
	
	ambientColor((1 + sin(t)) * 50.f + 20.f, 15, 100);
	background(sin(t) * 120, 5, t + 3);
	directionalLight(0.4, -1, 0.4, 0.2);

	lightColor(30, 30, 255);
	directionalLight(0., -1, 0., 0.05);

	lightColor(255, 150, 30);
	pointLight(-1, 3.8, 0.3, 0.85);
	lightColor(255, 90, 10);
	pointLight(3, -1, 6, 1.0);

	// SNOWMAN BODY
	color(230, 230, 240);
	// color(230, (sin(t) + 1.f) * 120 + 120, 240);
	box(0., -2.75, 0.0,20., 0.75, 20.);

	createShapeBegin("snowman body");
	smoothBlendFactor(cos(t));
	smoothUnionBegin();
		
		sphere(0., -0.75, 0, 2.);
		sphere(-0.15, 1.25, 0, 1.5);
		sphere(-0.3 * sin(t), 3.2, 0, 1.);
	smoothUnionEnd();
	createShapeEnd();

	// shape("snowman body", 0, 0, 2.0);
	// shape("snowman body", 2.0, 0.0, 4.0);

	// SNOWMAN EYE & BUTTONS
	color(10, 10, 10);
	sphere(-0.15, 1.25, 0.48, 0.08);
	sphere(-0.2, 1.8, 0.6, 0.08);
	sphere(0.1, 3.3, 1.12, 0.12); // Eye (right)
	sphere(-0.75, 3.1, 1.15, 0.12); // Eye (left)

	// SNOWMAN HAT
	createShapeBegin("snowman hat");
		rotateZ(-15);
		color(20, 20, 20);
		cylinder(-0.4, 3.8, 0.0, 1.25, 0.1);
		cylinder(-0.56, 4.6, 0.0, 1., 0.75);
	createShapeEnd();

	createShapeBegin("snowman");
		shape("snowman body", 0, 0, 0);
		shape("snowman hat", 0, 0, 0);
	createShapeEnd();

	shape("snowman", 0, 0, 2.0);
	// SNOWMAN ARMS
	color(150, 70, 50);
	// rotate(90, 30 * cos(2 * t), 0);
	cylinder(-1.6, -1.8, 0.0, 0.2, 1.75);
	smoothBlendFactor(0.3);
	smoothSubtractionBegin();
		smoothBlendFactor(0.1);
		smoothUnionBegin();
			// rotate(0, 0, 50 * cos(2 * t));
			cylinder(1.4f, 2.2f, 2.0f, 0.18f, 1.75f);
			// rotateZ(110 * cos (2 * t));
			cylinder(3., 3.3, 2.0, 0.07, 0.2);
			// rotateZ(60 * cos(2 * t));
			cylinder(3.0, 3.5, 2.0, 0.07, 0.2);
			// rotateZ(15 * cos(2 * t));
			cylinder(2.8, 3.6, 2.0, 0.07, 0.2);
		smoothUnionEnd();
		sphere(1.8, 2.7, 2.0, 0.1);
		sphere(2.5, 3.3, 2.0, 0.13);
	smoothSubtractionEnd();

	// TREEES
	rotate(0, 0, 0);
	createShapeBegin("tree");
		color(70, 159, 70);
		smoothUnionBegin();
			cone(0., 0., 0., 1., 0.8);
			cone(0., -1., 0., 1.4, 1.0);
			cone(0., -1.6, 0., 1.4, 1.2);
		smoothUnionEnd();
		color(150, 70, 50);
		cylinder(0., -2.0, 0., 0.4, 2.0);
	createShapeEnd();

	rotate(0, 0, 0);
	for (int i = 0; i < 10; i++) {
		rotateX(20 * i);
		shape("tree", -10 + 2.5 * i + sin(3 * t), 2. + cos(3 * t), 15.);
	}

	
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


/*
	
	background(95, 2, 95);
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

