#define DAY 6
#define PART 1
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


long aoc(FILE* f) {
	char buffer[1024 * 1024];
	size_t s = fread(buffer, 1, 1024 * 1024, f);
	size_t line_size;
	for (line_size = 0; buffer[line_size] != '\n'; line_size ++) {}
	size_t guard;
	for (guard = 0; buffer[guard] != '^' && buffer[guard] != 'v' && buffer[guard] != '<' && buffer[guard] != '>'; guard ++);
	int guard_dir = to_guard_dir(buffer[guard]);
	while (1) {
		buffer[guard] = 'X';
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
			break;
		}
		if (buffer[guard] == '#') {
			guard_dir ++;
			guard_dir %= 4;
			guard = old_guard;
		}
	}
	long ret = 0;
	for (int i = 0; i < s; i ++) {
		if (buffer[i] == 'X') {
			ret ++;
		}
	}
	printf("%s\n", buffer);
	return ret;
}
