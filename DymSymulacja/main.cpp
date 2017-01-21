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
	source->particleSize = 1.0;
	source->smokeColor = glm::vec3(1, 1, 1);
	source->alpha = 0.003;
	source->gravity = glm::vec3(0.00, -9.8, 0.0);

	switch (4)
	{
	case 1: // plaski po wyrownaniu temperatur (velo_start_y=0, unosi tylko roznica temperatur)
			source->startVelocity = glm::vec3(0.0, 0, 0.0);
			source->startVelocityRange = glm::vec3(5.0, 0.0, 5.0);
			source->wind = glm::vec3(-0.5, 0.0, -0.5);
			source->mass = 0.3;
			source->airTemperature = 30.f;
			source->temperature = 30.89f;
			break;
	case 2: // swobodne rozproszenie w gore
			source->startVelocity = glm::vec3(0.0, 0, 0.0);
			source->startVelocityRange = glm::vec3(5.0, 5.0, 5.0);
			source->wind = glm::vec3(-0.5, 0.0, -0.5);
			source->mass = 0.6;
			source->airTemperature = 30.f;
			source->temperature = 32.f;
			break;
	case 3: // chmura wiszaca
			source->startVelocity = glm::vec3(0.0, 0, 0.0);
			source->startVelocityRange = glm::vec3(10.0, 10.0, 10.0);
			source->wind = glm::vec3(-0.5, 0.0, -0.5);
			source->mass = 0.5;
			source->airTemperature = 30.f;
			source->temperature = 31.5f;
			break;
	case 4: // chmura wiszaca - 2
			source->startVelocity = glm::vec3(0.0, 0, 0.0);
			source->startVelocityRange = glm::vec3(10.0, 10.0, 10.0);
			source->wind = glm::vec3(-0.5, 0.0, -0.5);
			source->mass = 0.5;
			source->airTemperature = 30.f;
			source->temperature = 31.5f;
			source->particleSize = 2.f;
			source->alpha = 0.00127f;
			break;
	default:
			source->startVelocity = glm::vec3(0.0, 0, 0.0);
			source->startVelocityRange = glm::vec3(5.0, 10.0, 5.0);
			source->wind = glm::vec3(-1.0, 0.0, -1.0);
			source->mass = 0.4;
			source->airTemperature = 30.f;
			source->temperature = 31.f;
			source->alpha = 0.00127f;
			break;
	}
	
	QApplication a(argc, argv);
	MainWindow w(source);
	w.resize(300, 600);
	w.show();
	
	std::thread t(&MainWindow::checker, &w);
	Window *ww;
	ww = new Window(source);
	
	return a.exec();
}