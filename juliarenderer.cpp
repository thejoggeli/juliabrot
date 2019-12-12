#include "juliarenderer.h"
#include "colorhsl.h"
#include "juliatime.h"
#include <QDoubleSpinBox>
#include <QImage>
#include <cmath>
#include <iostream>
#include <thread>

using namespace std;

JuliaRenderer::JuliaRenderer()
{
	// Init Key Arrays
	for (u_int i = 0; i <= sizeof(keys) / sizeof(bool); i++) {
		keys[i] = false;
	}

	camera.position.x = 0.0; // -1.0;
	camera.position.y = 0.0;
	camera.zoom = 100.0;
	camera.rotation = 0.0; // M_PI * 2.0 * (1.0/8.0);
}

void JuliaRenderer::update()
{
	double vx = 0, vy = 0;
	double vcos, vsin;

	// rotate
	if (keys[81]) // Key Q
	{
		camera.rotation -= JuliaTime::deltaTime;
	}

	else if (keys[69]) // Key E
	{
		camera.rotation += JuliaTime::deltaTime;
	}

	if (keys[68]) // Key D
	{
		vx = 1;
	}

	else if (keys[65]) // Key A
	{
		vx = -1;
	}

	if (keys[83]) // Key S
	{
		vy = 1;
	}

	else if (keys[87]) // Key W
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
	if (keys[82]) {
		camera.zoom += camera.zoom * JuliaTime::deltaTime * 0.95;
	}

	else if (keys[70]) {
		camera.zoom -= camera.zoom * JuliaTime::deltaTime * 0.95;
	}
}

bool JuliaRenderer::eventFilter(QObject* obj, QEvent* event)
{
	if (event->type() == QEvent::KeyPress) {
		QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

		if (keyEvent->key() < 256 && !keyEvent->isAutoRepeat()) {
			keys[keyEvent->key()] = true;
			cout << keyEvent->key() << "pressed" << endl;
		}

		else if (keyEvent->key() == Qt::Key_Backspace && !keyEvent->isAutoRepeat()) {
			cout << "return pressed" << endl;
			camera.position.x = 0.0; // -1.0;
			camera.position.y = 0.0;
			camera.zoom = 100.0;
			camera.rotation = 0.0; // M_PI * 2.0 * (1.0/8.0);
		}
		return true;
	}

	else if (event->type() == QEvent::KeyRelease) {
		QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

		if (keyEvent->key() < 256 && !keyEvent->isAutoRepeat()) {
			keys[keyEvent->key()] = false;
			cout << keyEvent->key() << "released" << endl;
		}

		return true;
	}

	else {
		// standard event processing
		return QObject::eventFilter(obj, event);
	}
}

void JuliaRenderer::render(QImage& image, double scale_factor)
{
	double csin = sin(camera.rotation);
	double ccos = cos(camera.rotation);

	const int x_step = 4;
	const int y_step = 4;
	const int x_end = image.width();
	const int y_end = image.height();
	const int num_threads = x_step * y_step;
	std::thread threads[num_threads];

	int color_algorithm = 0;
	switch (color_mode) {
	case 0:
		color_algorithm = 0;
		descending_lightness = true;
		break;
	case 1:
		color_algorithm = 0;
		descending_lightness = false;
		break;
	case 7:
		color_algorithm = 1;
		orbit_trap_function = 0;
		orbit_point.set(1, 0);
		descending_lightness = false;
		break;
	case 8:
		color_algorithm = 1;
		orbit_trap_function = 0;
		orbit_point.set(1, 0);
		descending_lightness = true;
		break;
	case 9:
		color_algorithm = 1;
		orbit_trap_function = 0;
		orbit_point.set(-1, 0);
		descending_lightness = true;
		break;
	case 10:
		color_algorithm = 1;
		orbit_trap_function = 0;
		orbit_point.set(cos(JuliaTime::sinceStart), sin(JuliaTime::sinceStart));
		descending_lightness = true;
		break;
	case 2:
		color_algorithm = 1;
		orbit_trap_function = 1;
		orbit_circle_radius_squared = 1;
		descending_lightness = true;
		break;
	case 3:
		color_algorithm = 1;
		orbit_trap_function = 2;
		descending_lightness = true;
		break;
	case 4:
		color_algorithm = 1;
		orbit_trap_function = 3;
		descending_lightness = true;
		break;
	case 5:
		color_algorithm = 1;
		orbit_trap_function = 4;
		descending_lightness = true;
		break;
	case 6:
		color_algorithm = 1;
		orbit_trap_function = 5;
		descending_lightness = true;
		break;
	}

	double zoom = camera.zoom * scale_factor;

	auto f = [&](int x_start, int y_start) {
		for (int xi = x_start; xi < x_end; xi += x_step) {
			for (int yi = y_start; yi < y_end; yi += y_step) {
				Vec2 coords = Vec2(xi - image.width() / 2, -(yi - image.height() / 2));

				coords.set(coords.x * ccos + coords.y * csin, coords.x * csin - coords.y * ccos);
				coords.set(coords.x / zoom, coords.y / zoom);
				coords.set(coords.x + camera.position.x, coords.y + camera.position.y);
				Vec2 c = rendering_mode == 1 ? coords : julia_c;
				unsigned int color;
				switch (color_algorithm) {
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
	for (int xi = 0; xi < x_step; xi++) {
		for (int yi = 0; yi < y_step; yi++) {
			threads[i] = std::thread(f, xi, yi);
			i++;
		}
	}
	for (i = 0; i < num_threads; i++) {
		threads[i].join();
	}
}

inline unsigned int JuliaRenderer::calcColorIter(const Vec2& coords,
	const Vec2& c)
{
	Vec2 z = Vec2(coords.x, coords.y);
	Vec2 z_sqr = Vec2(0, 0);
	bool inside = 1;
	int iter = 0;
	for (iter = 0; iter < max_iterations; iter++) {
		z.set(z.x * z.x - z.y * z.y + c.x, z.x * z.y + z.y * z.x + c.y);
		z_sqr.set(z.x * z.x, z.y * z.y);
		if (z_sqr.x + z_sqr.y > 4.0) {
			inside = 0;
			break;
		}
	}
	if (inside)
		return 0xFF000000;
	float h = ((float)(iter)) / ((float)(max_iterations)) + JuliaTime::sinceStart * 0.025;
	h = fmod(h, 1.0f);
	float s = 1.0;
	float l;
	if (descending_lightness) {
		const float dampening = 1.5;
		l = 0.5 - exp(-((float)(iter)) / ((float)(max_iterations)) * dampening) * 0.5;
	} else {
		l = 0.5;
	}
	return ColorHsl::GetRgbUint32(h, s, l);
}

inline unsigned int JuliaRenderer::calcColorOrbit(const Vec2& coords,
	const Vec2& c)
{
	Vec2 z = Vec2(coords.x, coords.y);
	Vec2 z_sqr = Vec2(0, 0);
	bool inside = 1;
	int iter = 0;
	double min_dist = 1e20;
	for (iter = 0; iter < max_iterations; iter++) {
		z.set(z.x * z.x - z.y * z.y + c.x, z.x * z.y + z.y * z.x + c.y);
		z_sqr.set(z.x * z.x, z.y * z.y);
		switch (orbit_trap_function) {
		default:
		case 0: {
			// distance from point
			Vec2 point = orbit_point;
			Vec2 delta = Vec2(z.x - point.x, z.y - point.y);
			min_dist = min(min_dist, delta.getLengthSquared());
			break;
		}
		case 1: {
			// distance from circle
			min_dist = min(min_dist, fabs(z.getLengthSquared() - orbit_circle_radius_squared));
			break;
		}
		case 2: {
			// distance from x-axis
			min_dist = min(min_dist, fabs(z.y));
			break;
		}
		case 3: {
			// distance from y-axis
			min_dist = min(min_dist, fabs(z.x));
			break;
		}
		case 4: {
			// distance from rectangle
			double dx = max(max(orbit_rect_left - z.x, 0.0), z.x - orbit_rect_right);
			double dy = max(max(orbit_rect_bottom - z.y, 0.0), z.y - orbit_rect_top);
			min_dist = min(min_dist, dx*dx+dy*dy);
			break;
		}
		case 5: {
			// distance from rectangle
			Vec2 zz;
			zz.set(z.x - orbit_flower_p1.x, z.y - orbit_flower_p1.y);
			min_dist = min(min_dist, fabs(zz.getLengthSquared() - orbit_flower_radius_squared));
			zz.set(z.x - orbit_flower_p2.x, z.y - orbit_flower_p2.y);
			min_dist = min(min_dist, fabs(zz.getLengthSquared() - orbit_flower_radius_squared));
			zz.set(z.x - orbit_flower_p3.x, z.y - orbit_flower_p3.y);
			min_dist = min(min_dist, fabs(zz.getLengthSquared() - orbit_flower_radius_squared));
			zz.set(z.x - orbit_flower_p4.x, z.y - orbit_flower_p4.y);
			min_dist = min(min_dist, fabs(zz.getLengthSquared() - orbit_flower_radius_squared));
			break;
		}
		}
		if (z_sqr.x + z_sqr.y > 4.0) {
			inside = 0;
			break;
		}
	}
	if (inside)
		return 0xFF000000;
	min_dist = sqrt(min_dist);
	//	min_dist *= (double)max_iterations;
	//	min_dist /= 20.0;
	double h = min_dist + JuliaTime::sinceStart * 0.025;
	h = fmod(h, 1.0f);
	float s = 1.0;
	float l;
	if (descending_lightness) {
		const float dampening = 1.0;
		l = max(0.5, min(1.0, (min_dist)*0.5));
	} else {
		l = 0.5;
	}
	return ColorHsl::GetRgbUint32(h, s, l);
}
