#define DAY 11
#define PART 1
#include "../util.h"


int logten(uint64_t thing) {
	int ret = 1;
	uint64_t tens = 10;
	while (tens <= thing) {
		ret ++;
		tens *= 10;
	}
	return ret;
}


uint64_t powtenint(int at) {
	uint64_t ret = 1;
	for (int i = 0; i < at; i ++) {
		ret *= 10;
	}
	return ret;
}


long blink(uint64_t* stones, long count) {
	long ret = count;
	for (long i = 0; i < count; i ++) {
		int l = logten(stones[i]);
		if (stones[i] == 0) {
			stones[i] = 1;
		}
		else if (l % 2 == 0) {
			uint64_t cache = stones[i];
			stones[i] = stones[i] / powtenint(l / 2);
			stones[ret] = cache - (stones[i] * powtenint(l / 2));
			ret ++;
		}
		else {
			stones[i] *= 2024;
		}
	}
	return ret;
}


long aoc(FILE* f) {
	uint64_t* stones = malloc(sizeof(uint64_t) * 1024 * 1024 * 64); // casually allocate 64 megs of buffer
	long stone_count = 0;
	while (!feof(f)) {
		uint64_t b = 0;
		fscanf(f, "%lu", &b);
		stones[stone_count] = b;
		stone_count ++;
		fgetc(f);
	}
	stone_count --; // the last one is junk
	for (int i = 0; i < 25; i ++) {
		//for (long i = 0; i < stone_count; i ++) {
		//	printf("%lu, ", stones[i]);
		//}
		//printf("\n");
		stone_count = blink(stones, stone_count);
	}
	return stone_count;
}
