#include "../include/ray.h"
#include <limits>

Ray::Ray(): origin(Vector3f()), direction(Vector3f(1,0,0))
{}

Ray::Ray(Vector3f o, Vector3f d): origin(o), direction(d.Normalised())
{}

Vector3f Ray::getOrigin()const
{
	Vector3f vec(this->origin);
	return vec;
}

Vector3f Ray::getDirection()const
{
	Vector3f vec(this->direction);
	return vec;
}

void Ray::setOrigin(const Vector3f& vec)
{
	origin = vec;
}

void Ray::setDirection(const Vector3f& vec)
{
	direction = vec.Normalised();
}

Ray::~Ray()
{}

const double Ray::Epsilon = 0.00001;
const double Ray::Huge = std::numeric_limits<double>::max();