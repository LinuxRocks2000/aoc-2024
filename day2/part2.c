#define DAY 2
#define PART 2
#include "../util.h"


int safecheck(int* vec, int len, int check_subfails) {
	int does_increase = 0;
	int does_decrease = 0;
	int early_abort = 0;
	for (int i = 0; i < len - 1; i ++) {
		int j = i + 1;
		if (vec[i] > vec[j]) {
			does_decrease = 1;
		}
		if (vec[j] > vec[i]) {
			does_increase = 1;
		}
		if (vec[i] == vec[j]) {
			early_abort = 1;
			break;
		}
		if (abs(vec[i] - vec[j]) > 3) {
			early_abort = 1;
			break;
		}
	}
	if (check_subfails) {
		int* test = malloc(sizeof(int) * (len - 1));
		for (int i = 0; i < len; i ++) {
			for (int j = 0; j < len - 1; j ++) {
				if (j < i) {
					test[j] = vec[j];
				}
				else {
					test[j] = vec[j + 1];
				}
			}
			if (safecheck(test, len - 1, 0)) {
				return 1;
			}
		}
		free(test);
	}
	if (early_abort) {
		return 0;
	}
	return does_increase ^ does_decrease;
}


long aoc(FILE* f) {
	int v = 0;
	int lbuf[64]; // ah, the magic of stack preallocation...
	int lbuf_len = 0;
	long ret = 0;
	while (!feof(f)) {
		fscanf(f, "%d", &v); // I've got a serious fscanf fetish
		lbuf[lbuf_len] = v;
		lbuf_len += 1;
		char c = fgetc(f);
		if (c == ' ') {}
		else if (c == 10) { // newline! time to safety check
			if (safecheck(lbuf, lbuf_len, 1)) {
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
