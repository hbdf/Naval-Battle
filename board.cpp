#include <bits/stdc++.h>
#include "board.hpp"

using namespace std;









void board::draw_mesh(GLuint * textures) {
		//glClearColor(0.0f, 40.0f / 256.0f, 100.0f / 256.0f, 1.0f);


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	// glColor4f(0, 0, 1,1);
	 glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
	glBegin(GL_POLYGON);
 glColor3f(0, 0, 1);

		glTexCoord2f(0.0f, 0.0f);
			glVertex3f(0, 0, 0);

		glTexCoord2f(0.0f, 0.5f);
			glVertex3f(0, 0, 10);

	  	glTexCoord2f(0.5f, 0.5f); 
			glVertex3f(10, 0, 10);

		glTexCoord2f(0.5f, 0.0f);
			glVertex3f(10, 0, 0);

	glEnd();
	// glColor3f(0, 0, 1);

	glDisable(GL_TEXTURE_2D);



		//Each cell has size 1
	for (int i = 0; i < sz; i++) {
		for (int j = 0; j < sz; j++) {
			glPushMatrix();
			glBegin(GL_LINE_LOOP);
			glVertex3f(i, 0, j);
			glVertex3f(i + 1, 0, j);
			glVertex3f(i + 1, 0, j + 1);
			glVertex3f(i, 0, j + 1);
			glEnd();
			glPopMatrix();
		}
	}
}


bool board::is_possible(ship * try_put, bool dire, int x, int y) {
	dir d = dire ? down : right;
	int ex = x + (d == down ? try_put->get_size() - 1 : 0);
	int ey = y + (d == right ? try_put->get_size() - 1: 0);
	if(x < 0 || y < 0 || ex >= sz || ey >= sz) return false;
	for (int i = x; i <= ex; i++) {
		for (int j = y; j <= ey; j++) {
			if(board_rep[i][j] != nullptr) {
				return false;
			}
		}
	}
	return true;
}

int board::get_size() {
	return list_board.size();
}

board::board(int N) {
	sz = N;
	std::vector <ship *> aux(N);
	for (int i = 0; i < sz; i++) {
		aux[i] = nullptr;
	}
	for (int i = 0; i < sz; i++) {
		board_rep.push_back(aux);
	}
}

void board::put(ship * try_put, bool dire, int x, int y) {
	ship_on_board * n_ship = new ship_on_board(x, y, try_put, dire);
	if(dire) {
		for (int i = x; i < x + try_put->get_size(); i++) {
			board_rep[i][y] = try_put;
		}
	} else {
		for (int i = y; i < y + try_put->get_size(); i++) {
			board_rep[x][i] = try_put;
		}
	}
	list_board.push_back(n_ship);
}

void board::draw(GLuint * textures) {
	draw_mesh(textures);
	for (int i = 0; i < list_board.size(); i++) 
	{
		for (int j = 0; j < list_board[i]->S->get_size(); j++)
		{
			glPushMatrix();
			glTranslatef(list_board[i]->x + (list_board[i]->d == down ? j : 0), 0, list_board[i]->y + (list_board[i]->d == right ? j : 0));
			list_board[i]->draw_at_position(j);
			glPopMatrix();
		}
	}
}

void board::shoot(int x, int y) {
	if(board_rep[x][y] == nullptr) {
		destroyed_positions.push_back(make_pair(x, y));
	} else {
		board_rep[x][y]->destroy();
	}
}

void board::draw_for_op(GLuint * textures) {
	draw_mesh(textures);
	for (int i = 0; i < list_board.size(); i++) 
	{
		if(list_board[i]->S->is_destroyed() == false) continue;
		for (int j = 0; j < list_board[i]->S->get_size(); j++)
		{
			glPushMatrix();
			glTranslatef(list_board[i]->x + (list_board[i]->d == down ? j : 0), 0, list_board[i]->y + (list_board[i]->d == right ? j : 0));
			list_board[i]->draw_at_position(j);
			glPopMatrix();
		}
	}
	for (int i = 0; i < destroyed_positions.size(); i++) 
	{
		glPushMatrix();
		glTranslatef(destroyed_positions[i].first, 0, destroyed_positions[i].second);
		glColor3f(1, 0, 0);
		glBegin(GL_POLYGON); 
		glVertex3f( 0, 0.02, 0 ); 
		glVertex3f( 0,  0.02, 1 );
		glVertex3f( 1,  0.02, 1 );
		glVertex3f( 1, 0.02, 0 ); 
		glEnd();
		glPopMatrix();
	}
}

bool board::loose() {
	for (int i = 0; i < list_board.size(); i++) {
		if(list_board[i]->S->is_destroyed() == false) return false;
	}
	return true;
}