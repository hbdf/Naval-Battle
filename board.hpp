#ifndef BOARD_H
#define BOARD_H

#include "ship.hpp"
#include <vector>
#include <bits/stdc++.h>
#include <GL/glut.h>
#include <GL/glu.h>
/*
 * This is the representation of a quadratic board sz x sz
 * It has a list of ship_on_board
*/

class board {
	int sz = 0;
	enum dir { down, right };
	struct ship_on_board {
		dir d;
		int x, y;
		ship * S;
		ship_on_board(int X, int Y, ship *ss, bool dd) {
			x = X; y = Y; S = ss;
			d = dd ? down : right; 
		}
		void draw_at_position(int i) {
			S->draw_at_position(i);
		}
	};
	void draw_mesh(GLuint * textures);
	std::vector <ship_on_board *> list_board;
	std::vector <std::vector <ship *> > board_rep;
	std::vector < std::pair <int, int> > destroyed_positions;
public:
    // Constructor
	board(int N);
	bool is_possible(ship * try_put, bool dire, int x, int y);
	
	void put(ship * try_put, bool dire, int x, int y);
	void shoot(int x, int y);
	int get_size();
	void draw(GLuint * textures);
	void draw_for_op(GLuint * textures);
	bool loose();
};


#endif