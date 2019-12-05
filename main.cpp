// Merge Programm: sudo apt install kdiff3
// philippe war hier

// Include Tools
#include <math.h>
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
    QString statustext = "FPS: ";
    statustext += QString::number(JuliaTime::fps);
    statustext += " | X: ";
    statustext += QString::number(julia->camera.position.x, 'G', 20);
    statustext += " | Y: ";
    statustext += QString::number(julia->camera.position.y, 'G', 20);
    statustext += " | Zoom: ";
    statustext += QString::number(julia->camera.zoom);
    statustext += "x";
    statustext += " | Winkel: ";
    double angle = fmod((julia->camera.rotation / M_PI) * 180.0, 360.0);
    if (angle < 0)
    {
      angle += 360;
    }
    statustext += QString::number(angle);
    statustext += "°";
    window->setStatusText(statustext);
  }

  return EXIT_SUCCESS;
}
