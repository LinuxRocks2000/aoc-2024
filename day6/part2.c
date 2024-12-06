#define DAY 6
#define PART 2
#define TIME_REPEAT 100
#define TRUTH_VALUE 1434
#include "../util.h"
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3



int to_guard_dir(char guard) {
	if (guard == 'v') {
		return DOWN;
	}
	if (guard == '^') {
		return UP;
	}
	if (guard == '<') {
		return LEFT;
	}
	if (guard == '>') {
		return RIGHT;
	}
}


int check_iloop(char* buffer, size_t guard, int guard_dir, size_t s, size_t line_size, int preload) {
	long moves = 0;
	while (1) {
		if (preload) {
			buffer[guard] = 'X';
		}
		else {
			buffer[guard] = guard_dir;
		}
		size_t old_guard = guard;
		if (guard_dir == DOWN) {
			guard += line_size + 1;
		}
		else if (guard_dir == LEFT) {
			guard -= 1; 
		}
		else if (guard_dir == RIGHT) {
			guard += 1;
		}
		else {
			guard -= line_size + 1;
		}
		if (guard < 0 || guard > s || buffer[guard] == '\n') {
			return 0;
		}
		if (buffer[guard] == '#') {
			guard_dir ++;
			guard_dir %= 4;
			guard = old_guard;
		}
		if (buffer[guard] == guard_dir) {
			return 1;
		}
		moves ++;
		if (moves == s) {
			return 1;
		}
	}
}


long aoc(FILE* f) {
	char buffer[1024 * 1024];
	char bcopy[1024 * 1024];
	size_t s = fread(buffer, 1, 1024 * 1024, f);
	size_t guard;
	for (guard = 0; buffer[guard] != '^' && buffer[guard] != 'v' && buffer[guard] != '<' && buffer[guard] != '>'; guard ++);
	int guard_dir = to_guard_dir(buffer[guard]);
	size_t line_size;
	for (line_size = 0; buffer[line_size] != '\n'; line_size ++) {}
	check_iloop(buffer, guard, guard_dir, s, line_size, 1); // set up the paths
	long ret = 0;
	for (size_t i = 0; i < s; i ++) {
		if (buffer[i] == 'X') {
			memcpy(bcopy, buffer, s);
			bcopy[i] = '#';
			if (check_iloop(bcopy, guard, guard_dir, s, line_size, 0)) {
				ret ++;
			}
		}
	}
	return ret;
}
