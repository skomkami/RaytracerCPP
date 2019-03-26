#ifndef CAMERA_H
#define CAMERA_H

#include "vector3f.h"

class Camera{
	Vector3f camPos, camDir, camRight, camDown;
public:
	Camera();
	Camera(const Vector3f&, const Vector3f&);
	Vector3f getCameraPosition();
	Vector3f getCameraDirection();
	Vector3f getCameraRight();
	Vector3f getCameraDown();
};

#endif