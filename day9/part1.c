#define DAY 9
#define PART 1

#include "../util.h"


uint64_t aoc(FILE* f) {
	char buf[1024 * 1024];
	size_t len = fread(buf, 1, 64 * 1024, f);
	int obuff[1024 * 1024];
	size_t o_len = 0;
	int id = 0;
	int state = 1;
	for (size_t i = 0; i < len; i ++) {
		if (state) {
			for (int j = 0; j < buf[i] - '0'; j ++) {
				obuff[o_len] = id;
				o_len++;
			}
			id++;
		}
		else {
			for (int j = 0; j < buf[i] - '0'; j ++) {
				obuff[o_len] = -1;
				o_len++;
			}
		}
		state = !state;
	}
	size_t back = o_len - 1;
	for (size_t space = 0; space < o_len; space++) {
		if (space >= back - 1) {
			break;
		}
		if (obuff[space] == -1) {
			while (obuff[back] == -1) {
				back --;
			}
			obuff[space] = obuff[back];
			obuff[back] = -1;
		}
	}
	uint64_t ret = 0;
	for (size_t i = 0; i < o_len; i ++) {
		if (obuff[i] == -1) {
			continue;
		}
		ret += obuff[i] * i;
	}
	return ret;
}

