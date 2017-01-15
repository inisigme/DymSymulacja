#include "MainWindow.h"


MainWindow::MainWindow(Src *s)
{
	mainLayout = new QGridLayout;
	przeladuj = new QPushButton;


	przeladuj->setText("Dodaj kolejny warunek");
	tablica = new QTextEdit[40];
	podpisy = new QLabel[40];
	this->s = s;
	podpisy[0].setText("start");
	mainLayout->addWidget(&podpisy[0], 0, 0);
	mainLayout->addWidget(&tablica[0], 0, 1);

	podpisy[1].setText("end");
	mainLayout->addWidget(&podpisy[1], 1, 0);
	mainLayout->addWidget(&tablica[1], 1, 1);

	podpisy[2].setText("startPos");
	mainLayout->addWidget(&podpisy[2], 2, 0);
	mainLayout->addWidget(&tablica[2], 2, 1);
	mainLayout->addWidget(&tablica[3], 2, 2);
	mainLayout->addWidget(&tablica[4], 2, 3);

	podpisy[3].setText("range");
	mainLayout->addWidget(&podpisy[3], 3, 0);
	mainLayout->addWidget(&tablica[5], 3, 1);


	podpisy[4].setText("maxH");
	mainLayout->addWidget(&podpisy[4], 4, 0);
	mainLayout->addWidget(&tablica[6], 4, 1);

	podpisy[5].setText("noiseType");
	mainLayout->addWidget(&podpisy[5], 5, 0);
	mainLayout->addWidget(&tablica[7], 5, 1);

	podpisy[6].setText("smokeColor");
	mainLayout->addWidget(&podpisy[6], 6, 0);
	mainLayout->addWidget(&tablica[8], 6, 1);
	mainLayout->addWidget(&tablica[9], 6, 2);
	mainLayout->addWidget(&tablica[10], 6, 3);

	podpisy[7].setText("particleSize");
	mainLayout->addWidget(&podpisy[7], 7, 0);
	mainLayout->addWidget(&tablica[11], 7, 1);

	podpisy[8].setText("startVelocity");
	mainLayout->addWidget(&podpisy[8], 8, 0);
	mainLayout->addWidget(&tablica[12], 8, 1);
	mainLayout->addWidget(&tablica[13], 8, 2);
	mainLayout->addWidget(&tablica[14], 8, 3);

	podpisy[9].setText("startVelocityRange");
	mainLayout->addWidget(&podpisy[9],9, 0);
	mainLayout->addWidget(&tablica[15], 9, 1);
	mainLayout->addWidget(&tablica[16], 9, 2);
	mainLayout->addWidget(&tablica[17], 9, 3);

	podpisy[10].setText("alpha");
	mainLayout->addWidget(&podpisy[10], 10, 0);
	mainLayout->addWidget(&tablica[18], 10, 1);

	podpisy[11].setText("gravity");
	mainLayout->addWidget(&podpisy[11], 11, 0);
	mainLayout->addWidget(&tablica[19], 11, 1);
	mainLayout->addWidget(&tablica[20], 11, 2);
	mainLayout->addWidget(&tablica[21], 11, 3);

	podpisy[12].setText("wind");
	mainLayout->addWidget(&podpisy[12], 12, 0);
	mainLayout->addWidget(&tablica[22], 12, 1);
	mainLayout->addWidget(&tablica[23], 12, 2);
	mainLayout->addWidget(&tablica[24], 12, 3);

	podpisy[13].setText("temperature");
	mainLayout->addWidget(&podpisy[13], 13, 0);
	mainLayout->addWidget(&tablica[25], 13, 1);

	podpisy[14].setText("mass");
	mainLayout->addWidget(&podpisy[14], 14, 0);
	mainLayout->addWidget(&tablica[26], 14, 1);
	wyswietl();
	setLayout(mainLayout);
	

	//connect(przeladuj, SIGNAL(clicked()), this, SLOT(przeladujFun()));
	//QObject::connect(przeladuj, SIGNAL(clicked()), this, SLOT(przeladujFun()));
	void update();
}

void MainWindow::checker() {
	for (;;) {
		_sleep(3000);
		przeladujFun();
	}
}

void MainWindow::wyswietl()  {
	tablica[0].setText(QString::number(s->start));
	tablica[1].setText(QString::number(s->end));
	tablica[2].setText(QString::number(s->startPos.x));
	tablica[3].setText(QString::number(s->startPos.y));
	tablica[4].setText(QString::number(s->startPos.z));
	tablica[5].setText(QString::number(s->range));
	tablica[6].setText(QString::number(s->maxH));
	tablica[7].setText(QString::number(s->noiseType));
	tablica[8].setText(QString::number(s->smokeColor.x));
	tablica[9].setText(QString::number(s->smokeColor.y));
	tablica[10].setText(QString::number(s->smokeColor.z));
	tablica[11].setText(QString::number(s->particleSize));
	tablica[12].setText(QString::number(s->startVelocity.x));
	tablica[13].setText(QString::number(s->startVelocity.y));
	tablica[14].setText(QString::number(s->startVelocity.z));
	tablica[15].setText(QString::number(s->startVelocityRange.x));
	tablica[16].setText(QString::number(s->startVelocityRange.y));
	tablica[17].setText(QString::number(s->startVelocityRange.z));
	tablica[18].setText(QString::number(s->alpha));
	tablica[19].setText(QString::number(s->gravity.x));
	tablica[20].setText(QString::number(s->gravity.y));
	tablica[21].setText(QString::number(s->gravity.z));
	tablica[22].setText(QString::number(s->wind.x));
	tablica[23].setText(QString::number(s->wind.y));
	tablica[24].setText(QString::number(s->wind.z));
	tablica[25].setText(QString::number(s->temperature));
	tablica[26].setText(QString::number(s->mass));

}


void MainWindow::przeladujFun() {
	s->start = tablica[0].toPlainText().toInt();
	s->end = tablica[1].toPlainText().toInt();
	s->startPos = glm::vec3(tablica[2].toPlainText().toFloat(), tablica[3].toPlainText().toFloat(), tablica[4].toPlainText().toFloat());
	s->range = tablica[5].toPlainText().toFloat();
	s->maxH = tablica[6].toPlainText().toFloat();
	s->noiseType = tablica[7].toPlainText().toInt();
	s->smokeColor = glm::vec3(tablica[8].toPlainText().toFloat(), tablica[9].toPlainText().toFloat(), tablica[10].toPlainText().toFloat());
	s->particleSize = tablica[11].toPlainText().toFloat();
	s->startVelocity = glm::vec3(tablica[12].toPlainText().toFloat(), tablica[13].toPlainText().toFloat(), tablica[14].toPlainText().toFloat());
	s->startVelocityRange = glm::vec3(tablica[15].toPlainText().toFloat(), tablica[16].toPlainText().toFloat(), tablica[17].toPlainText().toFloat());
	s->alpha = tablica[18].toPlainText().toFloat();
	s->gravity = glm::vec3(tablica[19].toPlainText().toFloat(), tablica[20].toPlainText().toFloat(), tablica[21].toPlainText().toFloat());
	s->wind = glm::vec3(tablica[22].toPlainText().toFloat(), tablica[23].toPlainText().toFloat(), tablica[24].toPlainText().toFloat());
	s->temperature = tablica[25].toPlainText().toFloat();
	s->mass = tablica[26].toPlainText().toFloat();
	//wyswietl();
}

MainWindow::~MainWindow()
{
}