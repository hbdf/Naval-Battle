#include <bits/stdc++.h>
#include "ship.hpp"


void ship::construct_ship(int cell_size) {
	for (int i = 0; i < sz; i++) {
		cell_representation *to_add = new cell_representation();
	    //This if-statement is to draw a cube and a sphere on the "head" of the ship
		if(i == 0) {
			object *n1 = new cube(cell_size, 0, 0, 1);
			to_add->append(n1);
			object *n2 = new sphere(cell_size, 0, 0, 0.3);
			to_add->append(n2);
			ship_representation.push_back(to_add);
		} else {
			object *n1 = new cube(cell_size, 0, 1, 1);
			to_add->append(n1);
			ship_representation.push_back(to_add);
		}
	}
}
ship::ship(int N, int cell_size) {
	sz = N;
	destroyed = false;
	construct_ship(cell_size);
}

void ship::modifiy_at_position(int pos, cell_representation* to_modify) {
	if(pos < sz) {
		ship_representation[pos] = to_modify;
	}
}

void ship::draw_at_position(int pos) {
	ship_representation[pos]->draw();
}

void ship::destroy() {
	destroyed = true;
}

bool ship::is_destroyed() {
	return destroyed;
}

int ship::get_size() {
	return sz;
}