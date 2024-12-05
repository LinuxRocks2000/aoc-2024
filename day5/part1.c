#define DAY 5
#define PART 1
#include "../util.h"


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
		int test = 0;
		int tc = 0;
		char* tbuf = linebuf;
		while (1) {
			if (*tbuf >= '0' && *tbuf <= '9') {
				test *= 10;
				test += *tbuf - '0';
			}
			else {
				printf(": %d\n", test);
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
							break;
						}
					}
					if (!valid) {
						break;
					}
				}
			}
		}
		if (valid) {
			ret += test_reprint[tc / 2 - 1];
		}
	}
	return ret;
}
