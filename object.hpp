#ifndef OBJECT_H
#define OBJECT_H

#include <bits/stdc++.h>
#include <GL/glut.h>
#include <GL/glu.h>
class object {
	
	struct color_t {
		int r, g, b;
		void set_color(int re, int gr, int bl) {
			r = re; g = gr; b = bl;
		}
	};
public:
	int length;
	color_t color;
	object (int l, int red, int green, int blue);

	void set_color (int red, int green, int blue);
	virtual void draw();
};

#endif