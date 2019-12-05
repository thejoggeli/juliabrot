// Merge Programm: sudo apt install kdiff3
// philippe war hier

// Basil war auch hier :)

// Include Tools
#include <QApplication>
#include <QLabel>
#include <iostream>

// Include Header
#include "juliarenderer.h"
#include "juliatime.h"
#include "mainwindow.h"

using namespace std;

int main(int argc, char* argv[])
{
  // Init Programmfenster
  QApplication a(argc, argv);
  MainWindow* window = new MainWindow();
  window->setWindowTitle("Juliabrot");
  window->show();

  JuliaRenderer* julia = new JuliaRenderer();  // Init Renderobject

  // Init Grafics Window
  QLabel* label = window->getRenderTarget();
  QImage* image =
      new QImage(label->width(), label->height(), QImage::Format_ARGB32);

  QLabel* fps = window->getFPS();  // Anzeige FPS

  JuliaTime::start();  // Time Counter

  label->installEventFilter(julia);

  while (true)
  {
    a.processEvents();
    JuliaTime::update();  // Timer update
    julia->update();      // Cameraposition update
    julia->render(*image, window->getValue(), window->getmode(),
                  window->getcomplex(),
                  window->getreel());  //Übergabe diverser Parameter
    label->setPixmap(QPixmap::fromImage(*image));
    label->show();
    fps->setNum(1.0 / JuliaTime::deltaTime);  // Frame per second
    fps->show();
  }

  if (!a.exec())
  {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
