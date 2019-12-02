#include <QApplication>
#include <QLabel>
#include <iostream>
#include "juliarenderer.h"
#include "juliatime.h"
#include "mainwindow.h"

using namespace std;

// static bool start;

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  MainWindow* window = new MainWindow();
  window->setWindowTitle("Juliabrot");
  window->show();

  JuliaRenderer* julia = new JuliaRenderer();
  QLabel* label = window->getRenderTarget();
  QImage* image =
      new QImage(label->width(), label->height(), QImage::Format_ARGB32);

  //  window->setCentralWidget(label);

  JuliaTime::start();

  label->installEventFilter(julia);

  while (true)
  {
    a.processEvents();
    JuliaTime::update();
    // tastenfunktion
    julia->update();
    julia->render(*image);
    label->setPixmap(QPixmap::fromImage(*image));
    label->show();
    //    cout << 1.0 / JuliaTime::deltaTime << endl;
  }

  if (!a.exec())
  {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
