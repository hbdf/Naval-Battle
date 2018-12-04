#ifndef CUBE_H
#define CUBE_H

#include <bits/stdc++.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include "object.hpp"

class cube : public object {
public:
  cube (int l, int red, int green, int blue);
  void draw();
};


#endif