#include <bits/stdc++.h>

class object {
	int length;
	struct color_t {
		int r, g, b;
		void set_color(int re, int gr, int bl) : r(re), g(gr), b(bl) {}
	};
public:
	color_t color;
	object (int l, int red, int green, int blue) {
		length = l;
		color.r = red;
		color.g = green;
		color.b = blue;
	}
	void set_color (int red, int green, int blue) {
		color.set_color(red, green, blue);
	}
	virtual void draw() {}
};
