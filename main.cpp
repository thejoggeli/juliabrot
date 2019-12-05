// Merge Programm: sudo apt install kdiff3
// philippe war hier

// Include Tools
#include <QApplication>
#include <QLabel>
#include <iostream>

// Include Header
#include "juliarenderer.h"
#include "juliatime.h"
#include "juliawidget.h"
#include "mainwindow.h"

using namespace std;

int main(int argc, char* argv[])
{
  // Init Programmfenster
  QApplication a(argc, argv);
  MainWindow* window = new MainWindow();
  window->setWindowTitle("Juliabrot");
  window->show();

  // Init Grafics Window
  JuliaWidget* label = window->getRenderTarget();
  QImage* image = new QImage(720, 540, QImage::Format_ARGB32);

  JuliaRenderer* julia = new JuliaRenderer();  // Init Renderobject

  label->setImage(image);

  JuliaTime::start();  // Time Counter

  label->installEventFilter(julia);

  while (window->isVisible())
  {
    a.processEvents();
    JuliaTime::update();  // Timer update
    julia->update();      // Cameraposition update
	julia->julia_c.set(window->getReal(), window->getImaginary());
	julia->rendering_mode = window->getRenderingMode();
	julia->color_mode = window->getColorMode();
	julia->max_iterations = window->getValue();
	julia->render(*image);
	label->repaint();
//	QPixmap pixmap = QPixmap::fromImage(*image);
//	label->setPixmap(pixmap.scaled(label->width(), label->height(), Qt::KeepAspectRatioByExpanding));
 //   label->show();
	//fps->setNum(1.0 / JuliaTime::deltaTime);  // Frame per second
	//fps->show();
  }
/*
  if (!a.exec())
  {
    return EXIT_FAILURE;
  } */

  return EXIT_SUCCESS;
}
