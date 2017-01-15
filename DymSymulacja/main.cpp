#include "Window.h"
#include "parsowanie.h"
#include "MainWindow.h"
#include "Emiter.h"
#include <thread>

int main(int argc, char** argv) {
	Src *s = new Src;
	s->maxH = 30.f;
	s->range = 2.f;
	s->start = 0;
	s->end = 5000;
	s->startPos = glm::vec3(10.f, 0.f, 50.f);
	s->wind = glm::vec3(1.00, -1.0, 1.0);
	s->gravity = glm::vec3(0.00, -9.8, 0.0);
	s->smokeColor = glm::vec3(2.3, 2.3f, 2.3);
	s->particleSize = 1;
	s->startVelocity = glm::vec3(-5.0, 20, 0.0);
	s->startVelocityRange = glm::vec3(10.0, 0.0, 10.0);
	s->alpha = 0.005;
	QApplication a(argc, argv);
	MainWindow w(s);
	w.show();
	std::thread t(&MainWindow::checker, &w);
	Window *ww;
	ww = new Window(s);
	return a.exec();
}