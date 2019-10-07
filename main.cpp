#include "mainwindow.h"
#include <QApplication>
#include <QLabel>
#include "juliarenderer.h"

int main(int argc, char *argv[]){

	QApplication a(argc, argv);
	MainWindow* window = new MainWindow();
	window->setWindowTitle("Juliabrot");
	window->show();

	QImage* image = new QImage(720, 480, QImage::Format_ARGB32);

	JuliaRenderer julia = JuliaRenderer();
	julia.render(*image);

	QLabel* label = new QLabel(window);
	label->setPixmap(QPixmap::fromImage(*image));
	label->show();



	window->setCentralWidget(label);

	if(!a.exec()){
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
