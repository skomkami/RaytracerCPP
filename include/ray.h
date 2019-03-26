#ifndef RAY_H
#define RAY_H

#include "vector3f.h"

struct Ray
{
    static const double Epsilon;
    static const double Huge;

    Vector3f origin;
    Vector3f direction;

    Ray();

    Ray(Vector3f o, Vector3f d);
 
    Vector3f getOrigin()const;
    Vector3f getDirection()const;

    void setOrigin(const Vector3f &vec);
    void setDirection(const Vector3f &vec);

    ~Ray();
};

#endif