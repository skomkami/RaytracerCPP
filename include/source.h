#ifndef _SOURCE_H
#define _SOURCE_H

#include "color.h"
#include "vector3f.h"

class Source {
public:
	Source();

	virtual Vector3f getLightPosition();
	virtual Color getLightColor();

};

#endif