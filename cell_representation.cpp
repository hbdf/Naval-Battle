#include <bits/stdc++.h>

class cell_representation {
    vector <object *> representation;
public:
    cell_representation() {}
    void append(object * put_back) {
	representation.push_back(put_back);
    }
    void draw() {
	//TODO DRAW EACH OBJECT REMEMBER TO MOVE THE "WORLD" BEFORE PUTTING THE LAST ELEMENT
    }
};
