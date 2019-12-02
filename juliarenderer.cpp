#include "juliarenderer.h"
#include <QImage>
#include <cmath>
#include <iostream>
#include "juliatime.h"

using namespace std;

JuliaRenderer::JuliaRenderer()
{
  for (int i = 0; i < sizeof(keys) / sizeof(bool); i++)
  {
    keys[i] = false;
  }
  camera.position.x = 0.0;  // -1.0;
  camera.position.y = 0.0;
  camera.zoom = 100.0;
  camera.rotation = 0.0;  // M_PI * 2.0 * (1.0/8.0);
}

void JuliaRenderer::update()
{ /*
   camera.zoom = sin(JuliaTime::sinceStart) * 50 + 200;  // origin Zoom
   //  camera.zoom = sin(JuliaTime::sinceStart) * 1 + 200;  // no zoom

   camera.rotation += JuliaTime::deltaTime;
   //  camera.rotation = camera.rotation;  // no rotation

   camera.position.x = sin(JuliaTime::sinceStart) * 1.0;
   //  camera.position.x = camera.position.x;  // no move*/
  // rotation move
  double vx = 0, vy = 0;
  if (keys[81])
  {
    camera.rotation -= JuliaTime::deltaTime;
  }
  else if (keys[69])
  {
    camera.rotation += JuliaTime::deltaTime;
  }
  // move move
  if (keys[68])
  {
    vx = 1;
  }
  else if (keys[65])
  {
    vx = -1;
  }

  if (keys[83])
  {
    vy = 1;
  }
  else if (keys[87])
  {
    vy = -1;
  }
  vx *= JuliaTime::deltaTime * 100;
  vy *= JuliaTime::deltaTime * 100;

  vx /= camera.zoom;
  vy /= camera.zoom;

  double vcos, vsin;

  vcos = cos(camera.rotation);
  vsin = sin(camera.rotation);

  camera.position.add(vcos * vx - vsin * vy, vsin * vx + vcos * vy);

  // zoom move
  if (keys[82])
  {
    camera.zoom += camera.zoom * JuliaTime::deltaTime * 0.95;
  }
  else if (keys[70])
  {
    camera.zoom -= camera.zoom * JuliaTime::deltaTime * 0.95;
  }
}

bool JuliaRenderer::eventFilter(QObject* obj, QEvent* event)
{
  if (event->type() == QEvent::KeyPress)
  {
    QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
    if (keyEvent->key() < 256 && !keyEvent->isAutoRepeat())
    {
      keys[keyEvent->key()] = true;
      cout << keyEvent->key() << "pressed" << endl;
    }

    return true;
  }
  else if (event->type() == QEvent::KeyRelease)
  {
    QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
    if (keyEvent->key() < 256 && !keyEvent->isAutoRepeat())
    {
      keys[keyEvent->key()] = false;
      cout << keyEvent->key() << "released" << endl;
    }

    return true;
  }
  else
  {
    // standard event processing
    return QObject::eventFilter(obj, event);
  }
}

void JuliaRenderer::render(QImage& image)
{
  double csin = sin(camera.rotation);
  double ccos = cos(camera.rotation);
  int maxIterations = 20;

  for (int xi = 0; xi < image.width(); xi++)
  {
    for (int yi = 0; yi < image.height(); yi++)
    {
      Vec2 coords = Vec2(xi - image.width() / 2, -(yi - image.height() / 2));

      coords.set(coords.x * ccos + coords.y * csin,
                 coords.x * csin - coords.y * ccos);

      coords.set(coords.x / camera.zoom, coords.y / camera.zoom);  //
                                                                   //      scale
      coords.set(coords.x + camera.position.x,
                 coords.y + camera.position.y);  // move

      Vec2 c = Vec2(coords.x, coords.y);  // Mandelbrot

      //      Vec2 c = Vec2(-0.8, 0.156);  // Julia-set
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
        image.setPixel(xi, yi, 0xFF0000FFu);
      }
      else
      {
        image.setPixel(xi, yi, 0xFFFF00FFu);
      }
    }
  }
}
