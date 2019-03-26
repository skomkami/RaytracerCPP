#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "object.h"

class Triangle: public Object
{
    Vector3f A, B, C;
    Vector3f normal;
    double distance;
    Color color;

public:
    Triangle();
    Triangle(const Vector3f&, const Vector3f&, const Vector3f&, const Color&);

    Vector3f getTriangleNormal() const;
    double getTriangleDistance() const;
    Color getColor() const;

    Vector3f getNormalAt(const Vector3f& point) const;

    double findIntersection(const Ray& ray) const;

    ~Triangle();
};

#endif 