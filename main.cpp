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
  QImage* image = nullptr;

  JuliaRenderer* julia = new JuliaRenderer();  // Init Renderobject
  window->juliaRenderer = julia;

  JuliaTime::start();  // Time Counter

  label->installEventFilter(julia);

  double img_quality = 0.9;
  bool img_quality_changed = false;

  while (window->isVisible())
  {
    a.processEvents();
	if(window->getQuality() != img_quality){
		img_quality = window->getQuality();
		img_quality_changed = true;
	}
	if(window->resized || image == nullptr || img_quality_changed){
		double aspect = ((double)label->width())/((double)label->height());
		int img_h = ceil(((double)label->height())*img_quality);
		int img_w = ceil(((double)img_h)*aspect);
		image = new QImage(img_w, img_h, QImage::Format_ARGB32);
		label->setImage(image);
	}
    JuliaTime::update();  // Timer update
    julia->update();      // Cameraposition update
    julia->julia_c.set(window->getReal(), window->getImaginary());
    julia->rendering_mode = window->getRenderingMode();
    julia->color_mode = window->getColorMode();
    julia->max_iterations = window->getValue();
	julia->render(*image, img_quality);
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
	window->resized = false;
	img_quality_changed = false;
  }

  return EXIT_SUCCESS;
}
