#include <bits/stdc++.h>
#include "cell_representation.hpp"

cell_representation::cell_representation() {}

void cell_representation::append(object * put_back) {
	representation.push_back(put_back);
}

void cell_representation::draw() {
	glPushMatrix();
	for (int i = 0; i < representation.size(); i++)
	{
		representation[i]->draw();
		glTranslatef(0, representation[i]->length, 0);
	}
	glPopMatrix();
}
