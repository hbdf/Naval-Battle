#include <bits/stdc++.h>
/*
  This is the ship representation, it is only possible to draw it by position.
  You cannot draw it entirely because it can vary according to the direction 
 */
class ship {
    vector <cell_representation> ship_representation;
    int sz = 0;
    bool destroyed;
    void construct_ship(int cell_size) {
	for (int i = 0; i < sz; i++) {
	    cell_representation *to_add = new cell_representation(cell_size);
	    //This if-statement is to draw a cube and a sphere on the "head" of the ship
	    if(i == 0) {
		object *n1 = new cube(cell_size);
		to_add.append(n1);
		object *n2 = new sphere(cell_size);
		to_add.append(n2);
		ship_representation.push_back(to_add);
	    } else {
		object *n1 = new cube(cell_size);
		to_add.append(n1);
		ship_representation.push_back(to_add);
	    }
	}
    }
public:
    ship(int N, int cell_size) {
	sz = N;
	destroyed = false;
	construct_ship(cell_size);
    }
    void modifiy_at_position(int pos, object * to_modify) {
	if(pos < sz) {
	    ship_representation[pos] = to_modify;
	}
    }
    void draw_at_position(int pos) {
	ship_representation[pos]->draw();
    }
    void destroy() {
	destroyed = true;
    }
    bool is_destroyed() {
	return destroyed;
    }
    int get_size() {
	return sz;
    }
};
