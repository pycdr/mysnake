#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <sys/ioctl.h>
#define SNAKE_LENGTH 7 // length of the snake (pos variable)

void get_size(int *width, int *height) {
	struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        *width = w.ws_col;
	*height = w.ws_row;
}

_Bool found(int width, int height, int pos[SNAKE_LENGTH][2]) {
	for (int i = 0; i < SNAKE_LENGTH; i++) {
		if (pos[i][0] == width && pos[i][1] == height){
			return true;
		}
	}
	return false;
}

void move_snake(int width, int height, int pos[SNAKE_LENGTH][2]) {
	for (int i = 0; i < SNAKE_LENGTH - 1; i++) {
		pos[i][0] = pos[i+1][0];
		pos[i][1] = pos[i+1][1];
	}
	if (pos[SNAKE_LENGTH - 1][0] == 0){
		if (pos[SNAKE_LENGTH - 1][1] == 0) {
			if (rand() % 2 && !found(pos[SNAKE_LENGTH - 1][0]+1, pos[SNAKE_LENGTH - 1][1], pos)) {
				pos[SNAKE_LENGTH - 1][0] += 1;
			} else {
				pos[SNAKE_LENGTH - 1][1] += 1;
			}
		} else if (pos[SNAKE_LENGTH - 1][1] == height - 1) {
			if (rand() % 2 && !found(pos[SNAKE_LENGTH - 1][0]+1, pos[SNAKE_LENGTH - 1][1], pos)) {
				pos[SNAKE_LENGTH - 1][0] += 1;
			} else {
				pos[SNAKE_LENGTH - 1][1] -= 1;
			}
		} else {
			int r = rand() % 3;
			if (r == 0 && !found(pos[SNAKE_LENGTH - 1][0]+1, pos[SNAKE_LENGTH - 1][1], pos)) {
				pos[SNAKE_LENGTH - 1][0] += 1;
			} else if (r == 1 && !found(pos[SNAKE_LENGTH - 1][0], pos[SNAKE_LENGTH - 1][1]+1, pos)) {
				pos[SNAKE_LENGTH - 1][1] += 1;
			} else {
				pos[SNAKE_LENGTH - 1][1] -= 1;
			}
		}
	} else if (pos[SNAKE_LENGTH - 1][0] == width - 1) {
		if (pos[SNAKE_LENGTH - 1][1] == 0) {
			if (rand() % 2 && !found(pos[SNAKE_LENGTH - 1][0]-1, pos[SNAKE_LENGTH - 1][1], pos)) {
				pos[SNAKE_LENGTH - 1][0] -= 1;
			} else {
				pos[SNAKE_LENGTH - 1][1] += 1;
			}
		} else if (pos[SNAKE_LENGTH - 1][1] == height - 1) {
			if (rand() % 2 && !found(pos[SNAKE_LENGTH - 1][0]-1, pos[SNAKE_LENGTH - 1][1], pos)) {
				pos[SNAKE_LENGTH - 1][0] -= 1;
			} else {
				pos[SNAKE_LENGTH - 1][1] -= 1;
			}
		} else {
			int r = rand() % 3;
			if (r == 0 && !found(pos[SNAKE_LENGTH - 1][0]-1, pos[SNAKE_LENGTH - 1][1], pos)) {
				pos[SNAKE_LENGTH - 1][0] -= 1;
			} else if (r == 1 && !found(pos[SNAKE_LENGTH - 1][0], pos[SNAKE_LENGTH - 1][1]+1, pos)) {
				pos[SNAKE_LENGTH - 1][1] += 1;
			} else {
				pos[SNAKE_LENGTH - 1][1] -= 1;
			}
		}
	} else {
		if (pos[SNAKE_LENGTH - 1][1] == 0) {
			int r = rand() % 3;
			if (r == 0 && !found(pos[SNAKE_LENGTH - 1][0]+1, pos[SNAKE_LENGTH - 1][1], pos)) {
				pos[SNAKE_LENGTH - 1][0] += 1;
			} else if (r == 1 && !found(pos[SNAKE_LENGTH - 1][0]-1, pos[SNAKE_LENGTH - 1][1], pos)) {
				pos[SNAKE_LENGTH - 1][0] -= 1;
			} else {
				pos[SNAKE_LENGTH - 1][1] += 1;
			}
		} else if (pos[SNAKE_LENGTH - 1][1] == height - 1) {
			int r = rand() % 3;
			if (r == 0 && !found(pos[SNAKE_LENGTH - 1][0]+1, pos[SNAKE_LENGTH - 1][1], pos)) {
				pos[SNAKE_LENGTH - 1][0] += 1;
			} else if (r == 1 && !found(pos[SNAKE_LENGTH - 1][0]-1, pos[SNAKE_LENGTH - 1][1], pos)) {
				pos[SNAKE_LENGTH - 1][0] -= 1;
			} else {
				pos[SNAKE_LENGTH - 1][1] -= 1;
			}
		} else {
			int r = rand() % 4;
			if (r == 0 && !found(pos[SNAKE_LENGTH - 1][0]+1, pos[SNAKE_LENGTH - 1][1], pos)) {
				pos[SNAKE_LENGTH - 1][0] += 1;
			} else if (r == 1 && !found(pos[SNAKE_LENGTH - 1][0]-1, pos[SNAKE_LENGTH - 1][1], pos)) {
				pos[SNAKE_LENGTH - 1][0] -= 1;
			} else if (r == 2 && !found(pos[SNAKE_LENGTH - 1][0], pos[SNAKE_LENGTH - 1][1]+1, pos)) {
				pos[SNAKE_LENGTH - 1][1] += 1;
			} else {
				pos[SNAKE_LENGTH - 1][1] -= 1;
			}
		}
	}
}

int main() {
	srand(time(NULL));
	char* screen_char = "\u2588"; // █
	char* snake_char = "\u2591"; // ░
	//char food_char = '@';
	int pos[SNAKE_LENGTH][2] = {
		{0, 0},
		{0, 1},
		{1, 1},
		{2, 1},
		{2, 0},
		{3, 0},
		{4, 0}
	};
	int width, height;
	while (1) {
		printf("\033[H"); // \033[2J
		get_size(&width, &height);
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if ( found(j, i, pos) ) {
					printf("%s", snake_char);
				} else {
					printf("%s", screen_char);
				}
			}
			if (i < height-1)
				printf("\n");
		}
		move_snake(width, height, &pos);
		sleep(1);
	}
	return 0;
}
