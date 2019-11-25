#include "juliarenderer.h"
#include <QImage>
#include <cmath>
#include "juliatime.h"

JuliaRenderer::JuliaRenderer()
{
  camera.position.x = 0.0;  // -1.0;
  camera.position.y = 0.0;
  camera.zoom = 200.0;
  camera.rotation = 0.0;  // M_PI * 2.0 * (1.0/8.0);
}

void JuliaRenderer::update()
{
  camera.zoom = sin(JuliaTime::sinceStart) * 50 + 200;
  camera.rotation += JuliaTime::deltaTime;
  camera.position.x = sin(JuliaTime::sinceStart) * 1.0;
}

void JuliaRenderer::render(QImage& image)
{
  double csin = sin(camera.rotation);
  double ccos = cos(camera.rotation);
  int maxIterations = 50;

  for (int xi = 0; xi < image.width(); xi++)
  {
    for (int yi = 0; yi < image.height(); yi++)
    {
      Vec2 coords = Vec2(xi - image.width() / 2, -(yi - image.height() / 2));
      coords.set(coords.x * ccos - coords.y * csin,
                 coords.x * csin + coords.y * ccos);
      coords.set(coords.x / camera.zoom, coords.y / camera.zoom);  // scale
      coords.set(coords.x + camera.position.x,
                 coords.y + camera.position.y);  // move
      //	Vec2 c = Vec2(coords.x, coords.y);
      Vec2 c = Vec2(-0.8, 0.156);
      Vec2 z = Vec2(coords.x, coords.y);
      Vec2 z_sqr = Vec2(0, 0);
      bool inside = 1;
      for (int i = 0; i < maxIterations; i++)
      {
        z.set(z.x * z.x - z.y * z.y + c.x, z.x * z.y + z.y * z.x + c.y);
        z_sqr.set(z.x * z.x, z.y * z.y);
        if (z_sqr.x + z_sqr.y > 4.0)
        {
          inside = 0;
          break;
        }
      }
      if (inside)
      {
        image.setPixel(xi, yi, 0xFF00FFFFu);
      }
      else
      {
        image.setPixel(xi, yi, 0xFFFF00FFu);
      }
    }
  }
}
