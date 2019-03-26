#include "../include/light.h"


Vector3f Light::getLightPosition() { return position; }
Color Light::getLightColor() { return color; }

Light::Light(): color(Color(1, 1, 1, 0))
{}

Light::Light(Vector3f pos, Color col): position(pos), color(Color(col))
{}