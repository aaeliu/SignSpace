#pragma once
#include <stack>
#include "scene.h"

struct user {
	scene* context;
	std::vector <std::shared_ptr<IR::primitive>> objects_temp;
	std::map <std::string, std::shared_ptr<std::vector<std::shared_ptr<IR::primitive>>>> custom_shapes;
	float current_blend_factor = 0.25f;
	user(scene* c);

	float current_rot_x = 0.0f;
	float current_rot_y = 0.0f;
	float current_rot_z = 0.0f;

	std::shared_ptr <Color> current_color = std::make_shared <Color>(128, 128, 128); 
	std::shared_ptr <Color> current_light_color = std::make_shared <Color>(255, 255, 255);
	std::shared_ptr<std::vector<std::shared_ptr<IR::primitive>>> current_custom_shape = nullptr;
	std::string current_custom_shape_name = "";

	void create_and_check();
	void create();

	void background(int g);
	void background(int r, int g, int b);

	void color (int r, int g, int b);
	void lightColor(int r, int g, int b); // white by default.
	// void color (std::shared_ptr<Color> c);

	void _default_prim_construct(std::shared_ptr<IR::primitive> s);

	// SHAPE PRIMITIVES

	/**
	* Create a sphere.
	* @param[in] x,y,z:  coordinates of the sphere's center.
	* @param[in] r:		 radius of the sphere.
	*/
	std::shared_ptr<IR::primitive> sphere (float x, float y, float z, float r);

	/**
	* Create a box.
	* @param[in] x,y,z:  coordinates of the box's center
	* @param[in] l,w,h:  the half-dimensions of the box.
	*/
	std::shared_ptr<IR::primitive> box (float x, float y, float z, float l, float w, float h);

	/**
	* Create a cone.
	* @param[in] x,y,z:  coordinates of the sphere's center.
	* @param[in] r, h:   radius and half-height of cone.
	*/
	std::shared_ptr<IR::primitive> cone (float x, float y, float z, float r, float h);

	/**
	* Create a cylinder.
	* @param[in] x,y,z:  coordinates of the sphere's center.
	* @param[in] r:		 radius of the sphere.
	*/
	std::shared_ptr<IR::primitive> cylinder (float x, float y, float z, float r, float h);

	/**
	* Create a torus.
	* @param[in] x,y,z:  coordinates of the torus's center.
	* @param[in] R, r:   big radius, inner radius.
	*/
	std::shared_ptr<IR::primitive> torus (float x, float y, float z, float R, float r);

	std::shared_ptr<IR::primitive> shape (const std::string& name, float x, float y, float z);
	// CUSTOM SHAPE CREATION
	void createShapeBegin(const std::string& name);
	void createShapeEnd();

	std::stack<std::shared_ptr <IR::combination>> combination_stack;

	/**
	* Adjust how smoothly smooth combination operations will combine shapes together.
	*/
	void smoothBlendFactor(float k);

	/**
	*	Begin a smooth union operation. All shapes enclosed between smoothUnionBegin()
	*	and smoothUnionEnd() will be joined with a smooth union.
	* 
	*	Modify smoothing factor with smoothBlendFactor.
	*/
	std::shared_ptr <IR::combination> smoothUnionBegin(void);
	void smoothUnionEnd(void);

	/**
	*	Begin a subtraction operation. All shapes enclosed between subtractionBegin() and subtractionEnd() 
	*	will be subtracted from the first shape after subtractionBegin().
	*/
	std::shared_ptr <IR::combination> subtractionBegin(void);
	void subtractionEnd(void);

	/**
	*	Begin a smooth subtraction operation. All shapes enclosed between smoothSubtractionBegin() and smoothSubtractionBegin()
	*	will be smooth subtracted from the first shape after smoothSubtractionBegin().
	* 
	*	Modify smoothing factor with smoothBlendFactor.
	*/
	std::shared_ptr <IR::combination> smoothSubtractionBegin(void);
	void smoothSubtractionEnd(void);

	/**
	*	Begin an intersection operation. All shapes enclosed between intersectionBegin()
	*	and intersectionEnd() will have the intersection operation applied.
	*
	*/
	std::shared_ptr <IR::combination> intersectionBegin(void);
	void intersectionEnd(void);

	/**
	*	Begin a smooth intersection operation. All shapes enclosed between smoothIntersectionBegin()
	*	and smoothIntersectionEnd() will have the smooth intersection operation applied.
	*
	*	Modify smoothing factor with smoothBlendFactor.
	*/
	std::shared_ptr <IR::combination> smoothIntersectionBegin(void);
	void smoothIntersectionEnd(void);

	// TRANSFORMATION OPERATORS
	void rotateX(float degs);
	void rotateY(float degs);
	void rotateZ(float degs);
	void rotate(float degs_x, float degs_y, float degs_z);

	/*void translateX(float units);
	void translateY(float units);
	void translateZ(float units);
	void translate(float u_x, float u_y, float u_z); */


	// LIGHTS
	/* directional light constructor
	* x, y, z: direction light points. ie (0, -1, 0) is a downward pointing light
	* i: directional light intensity. */
	void directionalLight(float x, float y, float z, float i);
	void ambientLight(float i);
	/* point light
	*  x, y, z: location of point light
	*  i: point light intensity
	*/
	void pointLight(float x, float y, float z, float i);

	

};

#define red 255, 0, 0
#define green 0, 255, 0
#define blue 0, 0, 255
#define yellow 255, 255, 0
#define cyan 0, 255, 255
#define magenta 255, 0, 255
#define black 0, 0, 0
#define white 255, 255, 255