#include <bits/stdc++.h>
#include <unistd.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <stdlib.h> 
using namespace std;

void gameController(void) {

}

void receiveKey(unsigned char key, int posX, int posY) {

}

void temporizador () {
    glutPostRedisplay();
}

int main(int argc, char ** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | G7LUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Naval Battle");
    glutKeyboardFunc(receiveKey);
    glutDisplayFunc(gameController);
    glutIdleFunc(temporizador);

    glutMainLoop();
}
