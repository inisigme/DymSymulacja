#include "Window.h"
#include <conio.h>

GLFWwindow * Window::window;
View * Window::view;
system1 *Window::p2;
 Uklad* Window::u;
 Krzyzyk *	Window::k;
 ShaderProgram * Window::sh;
 System2 *Window::s2;
 Skybox *Window::sky;
Window::Window(Src *s)
{
	
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);
	window = glfwCreateWindow(1024, 768, "Simple example", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(432432);
	}
	glfwMakeContextCurrent(window);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetWindowSizeCallback(window, Resize);
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetMouseButtonCallback(window, MouseClickCallback);
	glfwSetCursorPosCallback(window, MouseMotionCallback);

	GLenum error = glGetError();

	if (error != GL_NO_ERROR)
	{
		std::cout << "OpenGL Error: " << error << std::endl;
	}

	GLint GlewInitResult = glewInit();
	if (GLEW_OK != GlewInitResult)
	{
		printf("ERROR: %s\n", glewGetErrorString(GlewInitResult));
		getchar();
		exit(EXIT_FAILURE);
	}


	glfwSwapInterval(0);
	view = new View();

//	p1 = new Program1();
//	p2 = new system1();
//	u = new Uklad();
//	sky = new Skybox();
s2 = new System2(s);
//	k = new Krzyzyk();
//	sh = new ShaderProgram();
	for (GLenum err; (err = glGetError()) != GL_NO_ERROR;)
	{
		std::cout << "po konstruktorze    " << err << std::endl;
	}
	//glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_CUBE_MAP);
	glfwSetTime(0.0);
	mainLoop();
}
void Window::mainLoop() {
	while(1){
		ERR
		renderScene();
		glfwSwapBuffers(window);
		glfwPollEvents();
	
	}
}
void Window::renderScene() {
	static int a = 0;
	std::cout << a++  << "      " << glfwGetTime() << std::endl;
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//std::cout << this->view->eyes.x << "      " << this->view->eyes.y << "     " << this->view->eyes.z << "__________" <<
	//this->view->centers.x << "      " << this->view->centers.y << "     " << this->view->centers.z << std::endl;
	//std::cout << 1000.0 / glfwGetTime() << std::endl;
	ERR
	
	//	k->render(this->view->MVPMatrix, this->view->centers);
	//	p1->render(this->view->MVPMatrix);
	//	u->render(this->view->MVPMatrix);
	//	sh->render(this->view->MVPMatrix);
	
	//sky->render(view->MVPMatrix);
	s2->render(this->view->MVPMatrix, view);
	//	p2->render(this->view->MVPMatrix);
}
void Window::Resize(GLFWwindow* window, int w, int h) {
	if (h < 1)
		h = 1;
	glViewport(0, 0, w, h);
}
void Window::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	switch (key) {
	case GLFW_KEY_W:
		view->stepFoward();
		
		break;
	case GLFW_KEY_S:
		view->stepBack();
		
		break;
	default:
		break;
	}
}

void Window::MouseClickCallback(GLFWwindow* window, int button, int action, int mods) {
	
}

void Window::MouseMotionCallback(GLFWwindow* window, double x, double y) {
	static int lastx = -1;
	static int lasty = -1;
	double deltax =  lastx-x;
	double deltay = lasty - y;
	lastx = x;
	lasty = y;
	view->rotateHorizontal((GLfloat)deltax);
	view->rotateVertical(deltay);
}

void Window::error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

Window::~Window()
{
	delete view;
	glfwDestroyWindow(window);
}
