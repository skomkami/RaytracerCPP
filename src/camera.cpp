#include "../include/camera.h"

Camera::Camera(): camDir(0,0,1)
{}

Camera::Camera(const Vector3f& campos, const Vector3f& look_at): camPos(campos)
{
	Vector3f diff_btw = look_at - campos;

	Vector3f Y(0, 1, 0);

	camDir = diff_btw.Normalised();
	camRight = Y.Cross(camDir).Normalised();
	camDown = camRight.Cross(camDir);
}

Vector3f Camera::getCameraPosition() { return camPos; }
Vector3f Camera::getCameraDirection() { return camDir; }
Vector3f Camera::getCameraRight() { return camRight; }
Vector3f Camera::getCameraDown() { return camDown; }