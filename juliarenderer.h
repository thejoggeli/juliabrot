#ifndef JULIARENDERER_H
#define JULIARENDERER_H

#include <QKeyEvent>
#include "camera.h"

class QImage;

class JuliaRenderer : public QObject
{
 private:
  Camera camera;
  bool keys[256];

 public:
  JuliaRenderer();
  void update();
  void render(QImage& image);
  bool eventFilter(QObject* Obj, QEvent* event) override;
};

#endif  // JULIARENDERER_H
