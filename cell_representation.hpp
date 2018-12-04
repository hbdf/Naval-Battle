#ifndef CELL_REPRESENTATION_H
#define CELL_REPRESENTATION_H

#include "object.hpp"
#include <vector>

class cell_representation {
	std::vector <object *> representation;
public:
	cell_representation();
	void append(object * put_back);
	void draw();
};


#endif