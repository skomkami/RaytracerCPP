#include "../include/object.h"

Object::Object(){}

Color Object::getColor() const { return Color(0.5, 0.0, 0.0, 0.0); }
double Object::findIntersection(const Ray& ray) const {
	return 0;
}

Vector3f Object::getNormalAt(const Vector3f& point) const { return Vector3f(0, 1, 0); };

Object::~Object(){};