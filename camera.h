#ifndef CAMERA_H
#define CAMERA_H

#include "vec2.h"

class Camera{
public:
	Vec2 position;
	double zoom, rotation;
	Camera();
};

#endif // CAMERA_H
