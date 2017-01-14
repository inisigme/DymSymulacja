#include "wszystko.h"
#include "View.h"
#include "Program1.h"
#include "system1.h"
#include "Uklad.h"
#include "Krzyzyk.h"
#include "ShaderProgram.h"
#include "System2.h"
#include "Skybox.h"
#pragma once

class Window
{
public:
	static System2 *s2;
	static GLFWwindow* window;
	static View*		view;
	static system1*		p2;
	static Uklad *		u;
	static Krzyzyk *	k;
	static ShaderProgram * sh;
	static Skybox	*sky;
	Program1 *p1;
	static void error_callback(int error, const char* description);
	static void MouseMotionCallback(GLFWwindow* window, double x, double y);
	static void MouseClickCallback(GLFWwindow* window, int button, int action, int mods);
	void mainLoop();
	void renderScene();
	static void Resize(GLFWwindow * window, int w, int h);
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	Window();
	~Window();
};


