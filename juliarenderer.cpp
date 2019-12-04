#include "juliarenderer.h"
#include <QDoubleSpinBox>
#include <QImage>
#include <cmath>
#include <iostream>
#include "juliatime.h"
#include <thread>
#include "colorhsl.h"

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

  // Bewegungsanpassung sowie Geschwindigkeitsanpassung bei Zoom&Rotation

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

void JuliaRenderer::render(QImage& image)
{
  double csin = sin(camera.rotation);
  double ccos = cos(camera.rotation);

  Vec2 c = julia_c;

  const int x_step = 2;
  const int y_step = 2;
  const int x_end = image.width();
  const int y_end = image.height();
  const int num_threads = x_step*y_step;
  std::thread threads[num_threads];

  auto f = [&](int x_start, int y_start){
	  for (int xi = x_start; xi < x_end; xi+=x_step)
	  {
		for (int yi = y_start; yi < y_end; yi+=y_step)
		{
			Vec2 coords = Vec2(xi - image.width() / 2, -(yi - image.height() / 2));

			coords.set(coords.x * ccos + coords.y * csin,
					 coords.x * csin - coords.y * ccos);

			coords.set(coords.x / camera.zoom,
					 coords.y / camera.zoom);  //
											   //      scale
			coords.set(coords.x + camera.position.x,
					 coords.y + camera.position.y);  // move

			if(rendering_mode == 1){
				c.set(coords.x, coords.y); // mandelbrot
			}
			unsigned int color;
			switch(color_mode){
			case 0:
				color = calcColorIter(coords, c);
				break;
			case 1:
				color = calcColorOrbit(coords, c);
				break;
			}
			image.setPixel(xi, yi, color);
		}
	  }
  };

  int i = 0;
  for(int xi = 0; xi < x_step; xi++){
	  for(int yi = 0; yi < y_step; yi++){
			threads[i] = std::thread(f, xi, yi);
			i++;
	  }
  }
  for(i = 0; i < num_threads; i++){
	  threads[i].join();
  }


}

inline unsigned int JuliaRenderer::calcColorIter(const Vec2& coords, const Vec2& c)
{
	Vec2 z = Vec2(coords.x, coords.y);
	Vec2 z_sqr = Vec2(0, 0);
	bool inside = 1;
	int iter = 0;
	for (iter = 0; iter < max_iterations; iter++)
	{
	  z.set(z.x * z.x - z.y * z.y + c.x, z.x * z.y + z.y * z.x + c.y);
	  z_sqr.set(z.x * z.x, z.y * z.y);
	  if (z_sqr.x + z_sqr.y > 4.0)
	  {
		inside = 0;
		break;
	  }
	}
	if(inside) return 0xFF000000;
	float h = ((float)(iter))/((float)(max_iterations)) + JuliaTime::sinceStart * 0.025;
	h = fmod(h, 1.0f);
	float s = 1.0;
	float l = 0.5;
	ColorHsl hsl = ColorHsl(h, s, l);
	return hsl.GetRgbUint32();
}

inline unsigned int JuliaRenderer::calcColorOrbit(const Vec2& coords, const Vec2& c)
{
	Vec2 point = Vec2(1.0, 0);
	Vec2 z = Vec2(coords.x, coords.y);
	Vec2 z_sqr = Vec2(0, 0);
	bool inside = 1;
	int iter = 0;
	double min_dist = 1e20;
	for (iter = 0; iter < max_iterations; iter++)
	{
	  z.set(z.x * z.x - z.y * z.y + c.x, z.x * z.y + z.y * z.x + c.y);
	  z_sqr.set(z.x * z.x, z.y * z.y);
	  Vec2 delta = Vec2(z.x - point.x, z.y - point.y);
	  min_dist = min(min_dist, delta.getLengthSquared());
	  if (z_sqr.x + z_sqr.y > 4.0)
	  {
		inside = 0;
		break;
	  }
	}
	if(inside) return 0xFF000000;
	min_dist = sqrt(min_dist);
	double h = min_dist + JuliaTime::sinceStart * 0.025;
	h = fmod(h, 1.0f);
	float s = 1.0;
	float l = 0.5;
	ColorHsl hsl = ColorHsl(h, s, l);
	return hsl.GetRgbUint32();
}

