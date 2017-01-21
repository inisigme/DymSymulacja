#include "Window.h"
#include "parsowanie.h"
#include "MainWindow.h"
#include "Emiter.h"
#include <thread>

int main(int argc, char** argv) {
	Src *source = new Src;
	source->start = 0;
	source->end = 5000;
	source->maxH = 300.f;
	source->range = 4.f;
	source->startPos = glm::vec3(0.f, -10.f, 0.f);
	source->startVelocity = glm::vec3(0.0, 0, 0.0);
	source->startVelocityRange = glm::vec3(5.0, 10.0, 5.0);
	
	source->particleSize = 1.0;
	source->alpha = 0.003;

	source->mass = 0.2;

	source->wind = glm::vec3(-1.0, 0.0, -1.0);
	source->gravity = glm::vec3(0.00, -9.8, 0.0);
	source->smokeColor = glm::vec3(1, 1, 1);

	source->airTemperature = 30.f;
	source->temperature = 300.f;
	
	QApplication a(argc, argv);
	MainWindow w(source);
	w.resize(300, 600);
	w.show();
	
	std::thread t(&MainWindow::checker, &w);
	Window *ww;
	ww = new Window(source);
	
	return a.exec();
}