#ifndef LIGHT_H
#define LIGHT_H

#include "source.h"

class Light: public Source
{
    Vector3f position;
    Color color;

public:
    Light();
    Light(Vector3f, Color);

    Vector3f getLightPosition();
    Color getLightColor();
};


#endif