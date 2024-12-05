#define DAY 5
#define PART 2
#include "../util.h"


void ermsort(int* target, int target_len, int* left, int* right, int rc) {
	while(1) {
		int did_pass = 1;
		for (int i = 1; i < target_len; i ++) {
			int reset = 0;
			for (int rule_check = 0; rule_check < rc; rule_check ++) {
				if (left[rule_check] == target[i]) {
					for (int j = i - 1; j >= 0; j --) {
						if (right[rule_check] == target[j]) {
							int swap = target[i];
							target[i] = target[j];
							target[j] = swap;
							reset = 1;
							break;
						}
					}
					if (reset) {
						break;
					}
				}
			}
			if (reset) {
				i -= 1;
				did_pass = 0;
			}
		}
		if (did_pass) {
			break;
		}
	}
}


long aoc(FILE* f) {
	int rl[1024 * 64];
	int rr[1024 * 64];
	int test_reprint[1024 * 64];
	int rc = 0;
	// rip out rules
	char linebuf[128];
	while (!feof(f)) {
		fgets(linebuf, 128, f);
		int len = strlen(linebuf);
		if (len < 2) {
			break;
		}
		int left, right;
		left = 0;
		right = 0;
		sscanf(linebuf, "%d|%d", &left, &right);
		rl[rc] = left;
		rr[rc] = right;
		rc ++;
	}
	long ret = 0;
	while (!feof(f)) {
		fgets(linebuf, 128, f);
		if (feof(f)) {
			break;
		}
		int test = 0;
		int tc = 0;
		char* tbuf = linebuf;
		while (1) {
			if (*tbuf >= '0' && *tbuf <= '9') {
				test *= 10;
				test += *tbuf - '0';
			}
			else {
				test_reprint[tc] = test;
				test = 0;
				tc ++;
			}
			if (*tbuf == 0) {
				break;
			}
			tbuf++;
		}
		int valid = 1;
		for (int x = 0; x < tc - 1; x ++) {
			for (int rule = 0; rule < rc; rule ++) {
				if (rr[rule] == test_reprint[x]) {
					for (int y = x + 1; y < tc; y ++) {
						if (rl[rule] == test_reprint[y]) {
							valid = 0;
							ermsort(test_reprint, tc, rl, rr, rc);
						}
					}
				}
			}
		}
		if (!valid) {
			ret += test_reprint[tc / 2 - 1];
		}
	}
	return ret;
}
