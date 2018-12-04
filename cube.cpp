#include "cube.hpp"

cube::cube (int l, int red, int green, int blue) : object (l,red, green, blue) {}

void cube::draw() {
	glColor3f(color.r, color.g, color.b);
	int i = 0,j = 0;
	glBegin(GL_POLYGON); 
	glVertex3f( 0, 0, 0 ); 
	glVertex3f( 0,  0, length );
	glVertex3f( length,  0, length );
	glVertex3f( length, 0, 0 ); 
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f( i, 0, j ); 
	glVertex3f( i,  0, j + 1 );
	glVertex3f( i,  1, j + 1 );
	glVertex3f( i, 1, j ); 
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f( i + 1, 0, j ); 
	glVertex3f( i + 1,  0, j + 1 );
	glVertex3f( i + 1,  1, j + 1 );
	glVertex3f( i + 1, 1, j ); 
	glEnd();

	glBegin(GL_POLYGON);   
	glVertex3f(i + 1, 0, j + 1); 
	glVertex3f(i, 0, j + 1 );
	glVertex3f(i, 1, j + 1 );
	glVertex3f(i + 1, 1, j + 1); 
	glEnd();

	glBegin(GL_POLYGON);  
	glVertex3f(i + 1, 0, j); 
	glVertex3f(i,  0, j );
	glVertex3f(i,  1, j );
	glVertex3f(i + 1, 1, j); 
	glEnd();

	glBegin(GL_POLYGON);  
	glVertex3f(i , 1, j); 
	glVertex3f(i +1,  1, j );
	glVertex3f(i+1,  1, j+1 );
	glVertex3f(i, 1, j+1); 
	glEnd();

}
