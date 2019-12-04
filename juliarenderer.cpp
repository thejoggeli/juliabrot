#include "juliarenderer.h"
#include <QDoubleSpinBox>
#include <QImage>
#include <cmath>
#include <iostream>
#include "juliatime.h"

using namespace std;

JuliaRenderer::JuliaRenderer()
{
  // Init Key Arrays
  for (u_int i = 0; i <= sizeof(keys) / sizeof(bool); i++)
  {
    keys[i] = false;
  }
  camera.position.x = 0.0;  // -1.0;
  camera.position.y = 0.0;
  camera.zoom = 100.0;
  camera.rotation = 0.0;  // M_PI * 2.0 * (1.0/8.0);
}

void JuliaRenderer::update()
{
  double vx = 0, vy = 0;
  double vcos, vsin;

  // rotate
  if (keys[81])  // Key Q
  {
    camera.rotation -= JuliaTime::deltaTime;
  }

  else if (keys[69])  // Key E
  {
    camera.rotation += JuliaTime::deltaTime;
  }

  if (keys[68])  // Key D
  {
    vx = 1;
  }

  else if (keys[65])  // Key A
  {
    vx = -1;
  }

  if (keys[83])  // Key S
  {
    vy = 1;
  }

  else if (keys[87])  // Key W
  {
    vy = -1;
  }

  // Motion adjustment and speed adjustment in Zoom&Rotation

  vx *= JuliaTime::deltaTime * 100;
  vy *= JuliaTime::deltaTime * 100;

  vx /= camera.zoom;
  vy /= camera.zoom;

  vcos = cos(camera.rotation);
  vsin = sin(camera.rotation);

  // move
  camera.position.add(vcos * vx - vsin * vy, vsin * vx + vcos * vy);

  // zoom
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
    else if (keyEvent->key() == Qt::Key_Backspace && !keyEvent->isAutoRepeat())
    {
      cout << "return pressed" << endl;
      camera.position.x = 0.0;  // -1.0;
      camera.position.y = 0.0;
      camera.zoom = 100.0;
      camera.rotation = 0.0;  // M_PI * 2.0 * (1.0/8.0);
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

void JuliaRenderer::render(QImage& image, int maxIterations, int getmode,
                           double getcomplex, double getreel)
{
  double csin = sin(camera.rotation);
  double ccos = cos(camera.rotation);

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

      if (getmode == 0)
      {
        Vec2 c = Vec2(getcomplex, getreel);  // Julia-set
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
      else if (getmode == 1)
      {
        Vec2 c = Vec2(coords.x, coords.y);  // Mandelbrot
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
}
