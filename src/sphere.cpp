#include "../include/sphere.h"


Sphere::Sphere():  radius(1.0), color(Color(1, 1, 1, 0))
{}

Sphere::Sphere(const Vector3f& c, const double& r, const Color& col): center(c), radius(r), color(Color(col))
{}

Sphere::~Sphere()
{}

Vector3f Sphere::getSphereCenter() const { return center; }
double Sphere::getShereRadius() const { return radius; }
Color Sphere::getColor() const { return color; }

Vector3f Sphere::getNormalAt(const Vector3f& point) const  {
	Vector3f normal_Vect = (point - center).Normalised();
	return normal_Vect;
}

double Sphere::findIntersection(const Ray& ray) const {
	Vector3f ray_origin = ray.getOrigin();
	
	Vector3f ray_direction = ray.getDirection();

	Vector3f distance = ray_origin - center;
	
	double a = ray_direction.LengthSq();
	double b = 2 * distance.Dot(ray_direction);
	double c = distance.LengthSq() - radius * radius;

	double discriminant = b * b - 4 * c;

	if(discriminant > 0) {
		// the ray intersects the sphere

		// the first root
		double root_1 = (-b - sqrt(discriminant))/(2*a);
		if(root_1 > 0) {
			// the first root is the smallest positive root
			return root_1;
		} else {
			// the second root is the smallest positive root
			double root_2 = (-b + sqrt(discriminant))/(2*a);
			return root_2;
		}
	} else {
		// the ray missed the sphere
		return -1;
	}
}