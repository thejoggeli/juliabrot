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

	//! determines how the fractal gets colorized
	int color_mode = 1;

private:

	//! if true, the color falls off gradually
	bool descending_lightness = false;

	//! which orbit trap function to use (internal)
	int orbit_trap_function = 0;

	//! squared circle radius for circle coloring
	double orbit_circle_radius_squared = 1;

	//!  position for point coloring
	Vec2 orbit_point = Vec2(1, 0);

private:

	//! left border for rectangle coloring
	double orbit_rect_left = -0.5;
	//! right border for rectangle coloring
	double orbit_rect_right = 0.5;
	//! top border for rectangle coloring
	double orbit_rect_top = 0.5;
	//! bottom border for rectangle coloring
	double orbit_rect_bottom = -0.5;

	//! squared radius for flower coloring
	double orbit_flower_radius_squared = 0.5;
	//! point 1 for flower coloring
	Vec2 orbit_flower_p1 = Vec2(1, 0);
	//! point 2 for flower coloring
	Vec2 orbit_flower_p2 = Vec2(-1, 0);
	//! point 3 for flower coloring
	Vec2 orbit_flower_p3 = Vec2(0, 1);
	//! point 4 for flower coloring
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
