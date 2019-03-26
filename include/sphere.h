#ifndef SPHERE_H
#define SPHERE_H
#include <cmath>

#include "object.h"

class Sphere: public Object
{
    Vector3f center;
    double radius;
    Color color;

public:
    Sphere();
    Sphere(const Vector3f&, const double&, const Color&);

    Vector3f getSphereCenter() const;
    double getShereRadius() const;
    Color getColor() const;

    Vector3f getNormalAt(const Vector3f& point) const;

    double findIntersection(const Ray& ray) const;
    ~Sphere();
};


#endif