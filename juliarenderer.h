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

	//! Camera, determines position, rotation and zoom of render
	Camera camera;

	//! constant 'c' for julia-set
	Vec2 julia_c = Vec2(0, 0);

	//! set to 0 julia-set, 1 for mandelbrot
	int rendering_mode = 0;

	//! maximum number of iterations
	int max_iterations = 25;

private:
	int color_mode = 1;
	bool descending_lightness = false;
	int orbit_trap_function = 0;
	double orbit_circle_radius_squared = 1;
	Vec2 orbit_point = Vec2(1, 0);

private:
	double orbit_rect_left = -0.5;
	double orbit_rect_right = 0.5;
	double orbit_rect_top = 0.5;
	double orbit_rect_bottom = -0.5;

private:
	double orbit_flower_radius_squared = 0.5;
	Vec2 orbit_flower_p1 = Vec2(1, 0);
	Vec2 orbit_flower_p2 = Vec2(-1, 0);
	Vec2 orbit_flower_p3 = Vec2(0, 1);
	Vec2 orbit_flower_p4 = Vec2(0, -1);

public:
	//! default constructor
	JuliaRenderer();

	/*!
	 * \brief update renderer
	 * updates camera position, colors, etc
	 */
	void update();

	/*!
	 * \brief render julia-set to image
	 * \param image the image to render the julia-set to
	 * \param scale_factor multiplicator for camera.zoom, used to keep zoom consistent for different quality settings
	 */
	void render(QImage& image, double scale_factor);

protected:
	bool eventFilter(QObject* Obj, QEvent* event) override;

private:
	unsigned int calcColorIter(const Vec2& coords, const Vec2& c);
	unsigned int calcColorOrbit(const Vec2& coords, const Vec2& c);
};

#endif // JULIARENDERER_H
