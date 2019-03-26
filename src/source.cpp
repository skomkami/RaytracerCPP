#include "../include/source.h"

Source::Source()
{}

Vector3f Source::getLightPosition() { return Vector3f(0, 0, 0); }
Color Source::getLightColor() { return Color(1, 1, 1, 0); }