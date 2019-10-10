#ifndef JULIARENDERER_H
#define JULIARENDERER_H

#include "camera.h"

class QImage;

class JuliaRenderer{
private:
	Camera camera;
public:
	JuliaRenderer();
	void update();
	void render(QImage& image);
};

#endif // JULIARENDERER_H
