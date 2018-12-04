#include "object.hpp"

object::object (int l, int red, int green, int blue) {
	length = l;
	color.r = red;
	color.g = green;
	color.b = blue;
}

void object::set_color (int red, int green, int blue) {
	color.set_color(red, green, blue);
}

void object::draw() {}
