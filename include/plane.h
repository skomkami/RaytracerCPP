#ifndef PLANE_H
#define PLANE_H

#include "vector3f.h"
#include "color.h"
#include "object.h"

class Plane: public Object
{
    Vector3f normal;
    Vector3f point;
    Color color;

public:
    Plane();
    Plane(const Vector3f&, const Vector3f&, const Color&);

    Vector3f getPlaneNormal() const;
    Vector3f getPlanePoint() const;
    Color getColor() const;

    Vector3f getNormalAt(const Vector3f& point) const;

    double findIntersection(const Ray& ray) const;

    ~Plane();
};

#endif 