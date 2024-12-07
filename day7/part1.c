#define DAY 7
#define PART 1
#include "../util.h"


long assemble_from(uint16_t check, long* nums, int nc) {
	long ret = nums[0];
	for (int i = 1; i < nc; i ++) {
		if (check & (1 << (i - 1))) {
			ret += nums[i];
		}
		else {
			ret *= nums[i];
		}
	}
	return ret;
}


unsigned long aoc(FILE* f) {
	unsigned long ret = 0;
	long numbahz[64];
	int nc = 0;
	while (!feof(f)) {
		unsigned long test_result = 0;
		long num = 0;
		nc = 0;
		fscanf(f, "%lu: ", &test_result, &num);
		char c = 1;
		while (c != '\n' && !feof(f)) {
			fscanf(f, "%d%c", &num, &c);
			numbahz[nc] = num;
			nc ++;
			num = 0;
		}
		uint16_t check = 0;
		while (check < (1 << (nc - 1))) {
			if (assemble_from(check, numbahz, nc) == test_result) {
				printf("%lu is solvable at variant %d\n", test_result, check);
				ret += test_result;
				break;
			}
			check ++;
		}
	}
	return ret;
}
