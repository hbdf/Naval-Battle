#include "board.hpp"
#include "cell_representation.hpp"
#include "cube.hpp"
#include "object.hpp"
#include "ship.hpp"
#include "sphere.hpp"
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
#include <unistd.h>
#include <fstream>
#include <mutex>
#include <thread>
using namespace std;



GLuint *textures = new GLuint[2];


unsigned char* readBMP(const char* filename)
{
    int i;
    FILE* f = fopen(filename, "rb");
    unsigned char info[54];
    size_t s = fread(info, sizeof(unsigned char), 54, f); 

    int width = *(int*)&info[18];
    int height = *(int*)&info[22];

    int size = 3 * width * height;
    unsigned char* data = new unsigned char[size];
    s = fread(data, sizeof(unsigned char), size, f); 
    fclose(f);

    for(i = 0; i < size; i += 3)
    {
            unsigned char tmp = data[i];
            data[i] = data[i+2];
            data[i+2] = tmp;
    }

    return data;
}

GLuint* getTextures(const char* filenames[], int qt_textures, int width=1024, int height=1024){
    glColor3f(0, 0, 1);
    GLuint *textures = new GLuint[qt_textures];
    glGenTextures(qt_textures, textures);
    
    for(int i = 0; i < qt_textures; i++){
        GLuint texture;
        unsigned char *data;
        
        FILE *file;
 
        data = readBMP(filenames[i]);
        glColor3f(0, 0, 1);
        glBindTexture(GL_TEXTURE_2D, textures[i]);
        
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        

    //     glGenTextures(1, &textures[i]);
    // glBindTexture(GL_TEXTURE_2D, textures[i]);
    // glPixelStorei(GL_UNPACK_ROW_LENGTH, width);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
    // glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);



            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_DECAL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_DECAL);
            
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
             
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
         
        gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
        
    }
    return textures;
    
    
}




int first_play = 0;
int dir = 0;
enum game_state {
    PLAYER1_CHOOSE_POS,
    PLAYER2_CHOOSE_POS,
    PLAYER1_TURN_PLAY,
    PLAYER2_TURN_PLAY,
    GAME_END
};

board *player1, *player2;
game_state curr_state = PLAYER1_CHOOSE_POS;
double xx = 7, yy = 8, zz = 2.5;
void init() {
    player1 = new board(5);
    player2 = new board(5);
    glClearColor(0.8, 0.8, 0.8, 0.0);

    GLfloat posicaoLuz[4]={0.0, 20.0, 20.0, 1.0};
    glShadeModel(GL_FLAT);
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    const char* textures_filenames[] = {"textura02.bmp", "textura01.bmp"};
    textures = getTextures(textures_filenames, 2);
    glMatrixMode(GL_PROJECTION);
    glFrustum(-2, 2, -2, 2, 1.5, 20.0);
}

void show_text(const string &s) {
    glRasterPos2f(-0.5, -0.5);
// String a ser escrita na tela
    for (auto & it : s) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, it);
    }
}

struct point {
    double x, y, z;
    point():x(0),y(0),z(0){}
    point(double X, double Y, double Z):x(X),y(Y),z(Z){}
    point operator* ( double op) {
        point ans;
        ans.x = x * op; ans.y = y * op; ans.z = z * op;
        return ans;
    }
    point operator+ ( point a)  {
        point ans;
        ans.x = x + a.x; ans.y = y + a.y; ans.z = z + a.z; 
        return ans;
    }
};


void change_state() {

 //   cout << "player1 " << player1->get_size() << endl;
 //   cout << "player2 " << player2->get_size() << endl << endl << endl;
    if(curr_state == PLAYER1_CHOOSE_POS && player1->get_size() == 2) {
        curr_state = PLAYER2_CHOOSE_POS;
    } else if(curr_state == PLAYER2_CHOOSE_POS  && player2->get_size() == 2) {
        if(first_play) curr_state = PLAYER2_TURN_PLAY;
        else curr_state = PLAYER1_TURN_PLAY;
    } else if(curr_state == PLAYER1_TURN_PLAY) curr_state = PLAYER2_TURN_PLAY;
    else if(curr_state == PLAYER2_TURN_PLAY) curr_state = PLAYER1_TURN_PLAY; 
}

int XX = 0, YY = 0;
double t  = 0;
void do_animation(double x, double y) {
    point ori, dest, mid;
    ori.x = 15; ori.y = 0; ori.z = 5;
    dest.x = x + 0.5; dest.y = 1; dest.z = y + 0.5;
    mid.y = 10;
    mid.x = (ori.x + dest.x) / 2;
    mid.z = (ori.z + dest.z) / 2;

        //Bezier Curve
    point moment = ori * (1 - t) * (1 - t) + mid * 2 * t * (1 - t)  + dest * t * t;
    glColor3f(0.2,0.2,0.2);
    glPushMatrix();
    glTranslatef(moment.x, moment.y, moment.z);
    glutSolidSphere(0.4, 20, 20);
    glPopMatrix();
    t += 0.003;
    if(t > 1) {
        t = 0;
        // change state
        change_state();
        return;
    }
 //   do_animation(x, y);
}

int get_size_ship() {
    if(curr_state == PLAYER1_CHOOSE_POS) {
        return 3 - player1->get_size();
    } else if(curr_state == PLAYER2_CHOOSE_POS) return 3 - player2->get_size();
    return -1;
}

void do_move(int lx, int lz) {
    if(curr_state == PLAYER1_CHOOSE_POS) {
        ship * s = new ship(get_size_ship(), 1);
        if(player1->is_possible(s, dir, (int)lx, (int)lz)) {
            player1->put(s, dir, (int)lx, (int)lz);
        }
        
        glutPostRedisplay();
        change_state();
    } else if(curr_state == PLAYER2_CHOOSE_POS) {
        ship * s = new ship(get_size_ship(), 1);
        if(player2->is_possible(s, dir, (int)lx, (int)lz)) {
            player2->put(s, dir, (int)lx, (int)lz);
        }

        glutPostRedisplay();

        change_state();
    } else if(curr_state == PLAYER1_TURN_PLAY) {
        player2->shoot((int)lx, (int)lz);
        if(player2->loose()) {
            cout << "PLAYER 1 LEVOU ESSA!\n";
            exit(0);
        }
        XX = lx;YY=lz;
        do_animation((int)lx, (int)lz);
    } else {
        player1->shoot((int)lx, (int)lz);
        if(player1->loose()) {
            cout << "PLAYER 2 LEVOU ESSA!\n";
            exit(0);
        }
        XX = lx;YY=lz;
        do_animation((int)lx, (int)lz);
    }
}

queue <vector <pair <int, int> >  >movements;
mutex mtx;

bool has_next() {
    mtx.lock();
    int sz = movements.size();
    mtx.unlock();
    return (sz > 0);
}

void put_vec(vector <pair <int, int> > to_put) {
    mtx.lock(); 
    movements.push(to_put);
    mtx.unlock();
}

vector <pair <int, int> > get_ship() {
    vector <pair <int, int> > ans;
    mtx.lock();
    ans = movements.front();
    movements.pop();
    mtx.unlock();
    return ans;
}

int linha = 0;
void get_arduino_ship() {

    ifstream myReadFile;
    myReadFile.open("/dev/ttyACM0");
    
    vector < pair <int, int> > positions;
    string output;
    if (myReadFile.is_open()) {
        
        while (!myReadFile.eof()) {
            myReadFile >> output;
            if(output == "END") {
                put_vec(positions);
                cout << "tam " << positions.size() << endl;
                positions.clear(); 
                continue;               
            }

            int p1 = output[0] - '0';
            int p2 = output[2] - '0';
            cout << p1 << ' ' << p2 << endl;
            positions.push_back(make_pair(p1, 4 - p2));
        }
    }

}

void funcaoDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//limpa a tela com a cor de fundo
    glClear(GL_COLOR_BUFFER_BIT);

    if(has_next()) {
        vector <pair <int, int> > positions = get_ship();
        sort(positions.begin(), positions.end());
        int sz_ship = get_size_ship();
        if(sz_ship > 0) {
            if(positions.size() != sz_ship) goto out;
            int dx = positions[0].first - positions.back().first;
            int dy = positions[0].second - positions.back().second;
            int tam = abs(dx + dy) + 1;
          //  cout << sz_ship << ' ' << tam << endl;
            if(sz_ship != tam) goto out;
            if(dx) dir = 1;
            else dir = 0;
            cout << "aqui\n";
            do_move(positions[0].first, positions[0].second);
        } else {
            if(positions.size() == 1) {
                do_move(positions[0].first, positions[0].second);
            }
        }
    }
    out :;

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    glColor3f(0, 0, 1);
    gluLookAt(xx, yy, zz, 2.5, 0, 2.5, 0, 1, 0);
    if(t > 1e-9) do_animation(XX,YY);
    if(curr_state == PLAYER1_CHOOSE_POS) {
        show_text("Jogador 1 escolhe posicao do navio");
        player1->draw(textures);
    } else if(curr_state == PLAYER2_CHOOSE_POS) {
        show_text("Jogador 2 escolhe posicao do navio");
        player2->draw(textures);
    } else if(curr_state == PLAYER1_TURN_PLAY) {
        show_text("Jogador 1 ataca!");
        player2->draw_for_op(textures);
    } else {
        show_text("Jogador 2 ataca!");
        player1->draw_for_op(textures);
    }
    glutSwapBuffers();

}


void gameController(void) {
  funcaoDisplay();
}


void funcaoKeyboard(unsigned char key, int x, int y) {
    if(key == 'i') {
        dir ^= 1;
    } 
    else if (key == 'w') {
        xx += 0.5;
    } else if (key == 'e') {
        xx -= 0.5;
    }
    else if(key == 's'){
        zz += -.5;
    }
    else if(key == 'd'){
        zz -= -.5;
    } else if (key == 'q') {
        exit(0);
    } 
    cout << xx << ' ' << zz << endl;
    glutPostRedisplay();
}



void draw_opacity(int x, int y, int sz) {
    ship * cur = new ship(sz, 1);
    if(curr_state == PLAYER1_CHOOSE_POS) {

        bool can = player1->is_possible(cur, dir, x, y);
        glPushMatrix();
         if(can) glColor3f(1, 0, 0);
         else glColor3f(1, 0, 0);
        glTranslatef(x, 0, y);
        for (int i = 0; i < sz; i++) {
           // cout << "i " << i << endl;
            
            glutSolidSphere(0.5, 20, 20);
            if(dir == 0) {
                //right
                glTranslatef(0, 0, 1);
            } else {
                //down
                glTranslatef(1, 0, 0);
            }
        }
       glPopMatrix();
    }
}

void My_mouse_routine(int x, int y) {
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble worldX, worldY, worldZ;

    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);

    winX = (double)x;
    winY = (double)viewport[3] - (double)y;
    winZ = 0;

    gluUnProject(winX, winY, winZ, modelview, projection, viewport, &worldX, &worldY, &worldZ);

    double vx = xx - worldX;
    double vy = yy - worldY;
    double vz = zz - worldZ;
    double t = -worldY /vy;
    double lx = worldX + vx*t;
    double lz = worldZ + vz * t;

    if(curr_state == PLAYER1_CHOOSE_POS || curr_state == PLAYER2_CHOOSE_POS) {
       // cout << "entrei " << lx << " " << lz << " " << get_size_ship() << endl;
        draw_opacity((int)lx, (int)lz, get_size_ship()); 
    } else {
     draw_opacity((int)lx, (int)lz, 1);  
 }
}

void mouse_pressed(int l1, int l2, int x, int y) {
    if(GLUT_UP != l2) return;
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble worldX, worldY, worldZ;

    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);

    winX = (double)x;
    winY = (double)viewport[3] - (double)y;
    winZ = 0;

    gluUnProject(winX, winY, winZ, modelview, projection, viewport, &worldX, &worldY, &worldZ);

    double vx = xx - worldX;
    double vy = yy - worldY;
    double vz = zz - worldZ;
    double t = -worldY /vy;
    double lx = worldX + vx*t;
    double lz = worldZ + vz * t;

    if(lx < 0 || lx>10 || lz<0 ||lz > 10) return;
    do_move(lx, lz);
}

void temporizador () {
    glutPostRedisplay();
}




int main(int argc, char **argv) {
    thread th1 (get_arduino_ship);
    first_play = rand() % 2;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Batalha Naval");
    glutKeyboardFunc(funcaoKeyboard);
    glutPassiveMotionFunc( My_mouse_routine );
    glutMouseFunc(mouse_pressed);
    glutDisplayFunc(gameController);
    glutIdleFunc(temporizador);
    init();

    glutMainLoop();

    return 0;
}

