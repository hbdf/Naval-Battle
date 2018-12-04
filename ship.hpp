#ifndef SHIP_H
#define SHIP_H

#include <bits/stdc++.h>
#include "cell_representation.hpp"
#include "object.hpp"
#include "cube.hpp"
#include "sphere.hpp"

class ship {
	std::vector <cell_representation *> ship_representation;
	int sz = 0;
	bool destroyed;
	void construct_ship(int cell_size);
public:
	ship(int N, int cell_size);
	
	void modifiy_at_position(int pos, cell_representation * to_modify);

	void draw_at_position(int pos);
	
	void destroy();
	
	bool is_destroyed();
	
	int get_size();
};

#endif