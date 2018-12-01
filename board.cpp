#include <bits/stdc++.h>

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
	    x(X); y(Y); S(ss);
	    d = dd ? down : right; 
	}
    };
    vector <ship_on_board *> list_board;
    vector <vector <ship *> > board_rep;
public:
    // Constructor
    board(int N) {
	sz = N;
	vector <ship *> aux;
	for (int i = 0; i < sz; i++) {
	    aux = nullptr;
	}
	for (int i = 0; i < sz; i++) {
	    board_rep = nullptr;
	}
    }
    
    bool is_possible(ship * try_put, bool dire, int x, int y) {
	dir d = dire ? down : right;
	int ex = x + (d == down ? try_put->get_size() : 0);
	int ey = y + (d == right ? try_put->get.size() : 0);
	if(x < 0 || y < 0 || ex > sz || ey > sz) return false;
	for (int i = x; i < ex; i++) {
	    for (int j = y; j < ey; j++) {
		if(board_rep[i][j] != nullptr) {
		    return false;
		}
	    }
	}
	return true;
    }
    
    void put(ship * try_put, bool dire, int x, int y) {
	ship_on_board * n_ship = new ship_on_board(x, y, try_put, dire);
	if(dire) {
	    for (int i = x; i < x + try_put->get_size(); i++) {
		board_rep[i][y] = try_put;
	    }
	} else {
	    for (int i = y; i < y + try_put->get_size(); i++) {
		board_rep[x][i] = try_put;
	    }
	}
	list_board.push_back(n_ship);
    }
};
