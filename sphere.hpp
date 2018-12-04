#ifndef SPHERE_H
#define SPHERE_H

#include "object.hpp"

class sphere : public object {
public:
	sphere (int l, int red, int green, int blue);
	void draw();
};


#endif