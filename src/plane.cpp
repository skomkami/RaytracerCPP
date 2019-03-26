#include "../include/plane.h"

Plane::Plane(): normal(0,1,0), color(Color(0.5, 0.5, 0.5, 0))
{}

Plane::Plane(const Vector3f& n, const Vector3f& p, const Color& col): normal(n), point(p), color(col)
{}

Plane::~Plane()
{}

Vector3f Plane::getPlaneNormal() const { return normal; }
Vector3f Plane::getPlanePoint() const { return point; }
Color Plane::getColor() const { return color; }

Vector3f Plane::getNormalAt(const Vector3f& point) const { return normal; }

double Plane::findIntersection (const Ray& ray) const {
  	
	double a = ray.getDirection().Dot(normal);
	if(a == 0) {
		// ray is parallel to the plane
		return -1;
	} else {
		double b = (point - ray.getOrigin()).Dot(normal);
		return b/a;
	}
}