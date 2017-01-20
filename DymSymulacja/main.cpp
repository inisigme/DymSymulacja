#include "Window.h"
#include "parsowanie.h"
#include "MainWindow.h"
#include "Emiter.h"
#include <thread>

int main(int argc, char** argv) {
	Src *s = new Src;
	s->maxH = 50.f;
	s->range = 2.f;
	s->start = 0;
	s->end = 1000;
	s->startPos = glm::vec3(0.f, 0.f, 0.f);
	s->wind = glm::vec3(0.00, -1.0, 0.0);
	s->gravity = glm::vec3(0.00, -9.8, 0.0);
	s->smokeColor = glm::vec3(1, 1, 1);
	s->particleSize = 1.2;
	s->startVelocity = glm::vec3(0.0, 2, 0.0);
	s->startVelocityRange = glm::vec3(2.0, 0.0, 2.0);
	s->airTemperature = 30.f;
	s->temperature = 70.f;
	s->temperature = 10.f;
	s->alpha = 0.006;
	QApplication a(argc, argv);
	MainWindow w(s);
	w.resize(300, 600);
	w.show();
	
	std::thread t(&MainWindow::checker, &w);
	Window *ww;
	ww = new Window(s);
	
	return a.exec();
}