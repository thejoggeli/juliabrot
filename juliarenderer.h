#ifndef JULIARENDERER_H
#define JULIARENDERER_H

#include <QKeyEvent>
#include "camera.h"
#include "vec2.h"

class QImage;

class JuliaRenderer : public QObject
{
 private:
  bool keys[256];

 public:
  Camera camera;
  Vec2 julia_c = Vec2(0, 0);
  int rendering_mode = 0;
  int max_iterations = 25;
  int color_mode = 1;
  bool descending_lightness = false;

  JuliaRenderer();
  void update();
  void render(QImage& image, double scale_factor);
  bool eventFilter(QObject* Obj, QEvent* event) override;

 private:
  unsigned int calcColorIter(const Vec2& coords, const Vec2& c);
  unsigned int calcColorOrbit(const Vec2& coords, const Vec2& c);
};

#endif  // JULIARENDERER_H
