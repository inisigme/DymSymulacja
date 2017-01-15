#pragma once
#include <QtWidgets\qapplication.h>
#include <QtWidgets\qlayoutitem.h>
#include <QtWidgets\QMainWindow>
#include <QtWidgets\QPushButton>
#include <QtWidgets\QLabel>
#include <QtWidgets\QGridLayout>
#include <QtGui\QMouseEvent>
#include <QtWidgets\QTextEdit>
#include <QtWidgets\QWidget>
#include "Emiter.h"
#include <string>
#include <thread>

class MainWindow : public QWidget
{
	//Q_OBJECT
public:
	explicit MainWindow(Src *);
	~MainWindow();
	Src *s;
	QPushButton *przeladuj;
	QTextEdit *tablica;
	QGridLayout *mainLayout;
	QLabel *podpisy;

	void wyswietl();

	void przeladujFun();


	void checker();
};
