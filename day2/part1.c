#define DAY 2
#define PART 1
#include "../util.h"


int safecheck(int* vec, int len) {
	int does_increase = 0;
	int does_decrease = 0;
	for (int i = 0; i < len - 1; i ++) {
		int j = i + 1;
		if (vec[i] > vec[j]) {
			does_decrease = 1;
		}
		if (vec[j] > vec[i]) {
			does_increase = 1;
		}
		if (vec[i] == vec[j]) {
			return 0;
		}
		if (abs(vec[i] - vec[j]) > 3) {
			return 0;
		}
	}
	return does_increase ^ does_decrease;
}


long aoc(FILE* f) {
	int v = 0;
	int lbuf[64]; // ah, the magic of stack preallocation...
	int lbuf_len = 0;
	long ret = 0;
	while (!feof(f)) {
		fscanf(f, "%d", &v);
		lbuf[lbuf_len] = v;
		lbuf_len += 1;
		char c = fgetc(f);
		if (c == ' ') {}
		else if (c == 10) { // newline! time to safety check
			if (safecheck(lbuf, lbuf_len)) {
				ret ++;
			}
			lbuf_len = 0;
		}
		else {
			break;
		}
	}
	return ret;
}
