#include "mainwindow.h"
#include <QApplication>
#include <QLabel>
#include "juliarenderer.h"
#include "juliatime.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]){

	QApplication a(argc, argv);
	MainWindow* window = new MainWindow();
	window->setWindowTitle("Juliabrot");
	window->show();

	QImage* image = new QImage(720, 480, QImage::Format_ARGB32);

	JuliaRenderer julia = JuliaRenderer();
	QLabel* label = new QLabel(window);

	window->setCentralWidget(label);

	JuliaTime::start();

	while(true){
		a.processEvents();
		JuliaTime::update();
		julia.update();
		julia.render(*image);
		label->setPixmap(QPixmap::fromImage(*image));
		label->show();
		cout << 1.0/JuliaTime::deltaTime << endl;
	}

	if(!a.exec()){
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
