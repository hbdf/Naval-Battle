#include "sphere.hpp"

sphere::sphere (int l, int red, int green, int blue) : object( l, red, green, blue) {}

void sphere::draw() {
	
	glColor3f(color.r, color.g, color.b);
	glPushMatrix();
	glTranslatef(0.5, 0.5, 0.5);
	glutSolidSphere(0.5, 20, 20);
	glPopMatrix();
}