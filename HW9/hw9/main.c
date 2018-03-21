#include <stdlib.h>
#include <stdio.h>
#include "myLib.h"
#include "start.h"
#include "gameover.h"
#include "bowser.h"
#include "mario.h"
#include "text.h"

//State enum definition
enum GBAState {
	START,
	START_NODRAW,
	BEGIN,
	END,
	END_NODRAW
};

int y = 120;
int x = 80;
int rd = 3;
int cd = 3;
int rx = 3;
int ry = 0;
int size = 3;
int temp = -1;
int time = 0;

Bowser bowser1 = { .x_pos = 20, .y_pos = 20};


void moveMario() {
	if(KEY_DOWN_NOW(BUTTON_LEFT)) {
		if (y > 5) {
			y += -size;
			x += 0;
		}
	}
	else if(KEY_DOWN_NOW(BUTTON_RIGHT)) {
		if(y < 160) {
			y += size;
			x += 0;
		}
	}
	else if(KEY_DOWN_NOW(BUTTON_UP)) {
		if (x > 5) {
			y += 0;
			x += -size;
		}
	}
	else if(KEY_DOWN_NOW(BUTTON_DOWN)) {
		if (x < 145) {
			y += 0;
			x += size;
		}
	}
}


void moveAuto() {
	bowser1.x_pos += rd;
	bowser1.y_pos += cd;
}

void redraw() {
	drawImage3(x, y, 10, 10, mario);
	drawImage3(bowser1.x_pos, bowser1.y_pos, 20, 20, bowser);
	delay(1);
	drawRect(bowser1.x_pos, bowser1.y_pos, 20, 20, BLACK);
	drawRect(x, y, 10, 10, BLACK);
}

void checkBoundary_x(int position) {
	if(position < 0)
	{
		position = 0;
		rd = -rd;
	}
	if(position > 159-15+1)
	{
		position = 159-15+1;
		rd = -rd;
	}
}

void checkBoundary_y(int position) {
	if(position < 0)
	{
		position = 0;
		cd = -cd;
	}
	if(position > 159-10+1)
	{
		position = 159-10+1;
		cd = -cd;
	}
}

void clear() {
	x = 120;
	y = 80;
	rd = 3;
	cd = 3;
	rx = 3;
	ry = 3;
}

void zeroed(int position_x, int position_y) {
	if(position_x < 5 || position_x > 158) {
		position_x = 0;
		rx = 0;
	}
	if(position_y < 5 || position_y > 158) {
		position_y = 0;
		ry = 0;
	}
}

int main() {
	REG_DISPCTL = MODE3 | BG2_ENABLE;
	enum GBAState state = START;
	int released = 1;
	
	while(1) { // Game Loop
		
		switch(state) {
		case START:
			drawImage3(0, 0, 240, 160, start);
			clear();
			state = START_NODRAW;
			break;
		case START_NODRAW:
			if(released && KEY_DOWN_NOW(BUTTON_A)) {
				clearscreen();
				drawRect(0, 175, 240, 4, BLUE);
				char letter[6];
				sprintf(letter, "Timer:");
				state = BEGIN;
				drawString(25, 180, letter, WHITE);
			}
			break;
		case BEGIN:
			moveMario();
			if(KEY_DOWN_NOW(BUTTON_SELECT)) {
				state = START;
			}
			moveAuto();
			redraw();
			checkBoundary_x(bowser1.x_pos);
			checkBoundary_y(bowser1.y_pos);
			zeroed(x, y);
			if(x >= bowser1.x_pos && x <= bowser1.x_pos +20 && y >= bowser1.y_pos
				&& y <= bowser1.y_pos + 20) {
				state = END;
			}
			temp++;
			if (temp % 22 == 0) {
				time += 1;
				rd += 1;
				cd += 1;
				char timed[1];
				sprintf(timed, " %d", time);
				drawRect(25, 215, 15, 15, BLACK);
				drawString(25, 215, timed, WHITE);
			}
			
			waitForVblank();
			break;
		case END:
			drawImage3(0, 0, 240, 160, gameover);
			state = END_NODRAW;
			break;
		case END_NODRAW:
			if(KEY_DOWN_NOW(BUTTON_A)) {
				clearscreen();
				state = START;
			}
			break;
		}
		if(KEY_DOWN_NOW(BUTTON_A)) {
			released = 0;
		} else {
			released = 1;
		}
	} // Game Loop

	return 0;
}

