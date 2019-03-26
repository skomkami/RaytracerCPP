#ifndef OBJECT_H
#define OBJECT_H

#include "ray.h"
#include "color.h"
#include "vector3f.h"

class Object
{
public:
	Object();
    virtual Color getColor() const;
    virtual double findIntersection(const Ray& ray) const;
    virtual Vector3f getNormalAt(const Vector3f& point) const;

    virtual ~Object();
};

#endif