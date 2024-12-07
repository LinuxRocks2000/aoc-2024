#define DAY 7
#define PART 2
#include "../util.h"
#include <math.h>


uint64_t logten(uint64_t val) { // crappy int 10 ^ log base ten
	uint64_t i = 10;
	while (i <= val) {
		i *= 10;
	}
	return i;
}


uint64_t powli(uint64_t base, uint64_t to) {
	uint64_t ret = 1;
	for (int i = 0; i < to; i ++) {
		ret *= base;
	}
	return ret;
}


uint64_t assemble_from(uint64_t check, uint64_t* nums, int nc) {
	uint64_t ret = nums[0];
	for (uint64_t i = 1; i < nc; i ++) {
		uint64_t bits_at = (check / powli(3, i - 1)) % 3;
		if (bits_at == 0) {
			ret += nums[i];
		}
		else if (bits_at == 1) {
			ret *= nums[i];
		}
		else {
			ret *= logten(nums[i]);
			ret += nums[i];
		}
	}
	return ret;
}


uint64_t aoc(FILE* f) {
	uint64_t ret = 0;
	uint64_t numbahz[64];
	uint64_t nc = 0;
	while (!feof(f)) {
		uint64_t test_result = 0;
		uint64_t num = 0;
		nc = 0;
		char _c = fgetc(f);
		if (feof(f)) {
			break;
		}
		ungetc(_c, f);
		fscanf(f, "%lu: ", &test_result, &num);
		char c = 1;
		while (c != '\n' && !feof(f)) {
			fscanf(f, "%d%c", &num, &c);
			numbahz[nc] = num;
			nc ++;
			num = 0;
		}
		uint64_t check = 0;
		while (check < powli(3, nc - 1)) {
			if (assemble_from(check, numbahz, nc) == test_result) {
				ret += test_result;
				break;
			}
			check ++;
		}
	}
	return ret;
}
