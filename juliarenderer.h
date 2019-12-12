#ifndef JULIARENDERER_H
#define JULIARENDERER_H

#include "camera.h"
#include "vec2.h"
#include <QKeyEvent>

class QImage;

class JuliaRenderer : public QObject {
private:
	bool keys[256];

public:
	Camera camera;
	Vec2 julia_c = Vec2(0, 0);
	int rendering_mode = 0;
	int max_iterations = 25;
	int color_mode = 1;
	bool descending_lightness = false;
	int orbit_trap_function = 0;
	double orbit_circle_radius_squared = 1;
	Vec2 orbit_point = Vec2(1, 0);

	double orbit_rect_left = -0.5;
	double orbit_rect_right = 0.5;
	double orbit_rect_top = 0.5;
	double orbit_rect_bottom = -0.5;

	double orbit_flower_radius_squared = 0.5;
	Vec2 orbit_flower_p1 = Vec2(1, 0);
	Vec2 orbit_flower_p2 = Vec2(-1, 0);
	Vec2 orbit_flower_p3 = Vec2(0, 1);
	Vec2 orbit_flower_p4 = Vec2(0, -1);

	JuliaRenderer();
	void update();
	void render(QImage& image, double scale_factor);
	bool eventFilter(QObject* Obj, QEvent* event) override;

private:
	unsigned int calcColorIter(const Vec2& coords, const Vec2& c);
	unsigned int calcColorOrbit(const Vec2& coords, const Vec2& c);
};

#endif // JULIARENDERER_H
