#define DAY 11
#define PART 2
#define ULTRALONG_AOC
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


typedef struct {
	uint64_t stone; // the number
	int drop; // the blink depth
	uint64_t result; // the result
} cache_t; // the goal here is to eliminate *most* of the tree traversal


uint64_t blink(uint64_t stone, long n, cache_t* cache, long* cache_len) { // return how many stones a stone becomes after blinking n times
	if (n == 0) {
		return 1;
	}
	for (long i = 0; i < *cache_len; i ++) {
		if (cache[i].stone == stone && cache[i].drop == n) {
			return cache[i].result;
		}
	}
	int l = logten(stone);
	uint64_t rv;
	if (stone == 0) {
		rv = blink(1, n - 1, cache, cache_len);
	}
	else if (l % 2 == 0) {
		uint64_t one = stone / powtenint(l / 2);
		uint64_t two = stone - (one * powtenint(l / 2));
		rv = blink(one, n - 1, cache, cache_len) + blink(two, n - 1, cache, cache_len);
	}
	else {
		rv = blink(stone * 2024, n - 1, cache, cache_len);
	}
	cache[*cache_len].stone = stone;
	cache[*cache_len].drop = n;
	cache[*cache_len].result = rv;
	cache_len[0] ++;
	return rv;
}


uint64_t aoc(FILE* f) {
	uint64_t* stones = malloc(sizeof(uint64_t) * 1024 * 1024); // casually allocate a meg of buffer
	cache_t* cache = malloc(sizeof(cache_t) * 1024 * 1024);
	long stone_count = 0;
	long cache_len = 0;
	while (!feof(f)) {
		uint64_t b = 0;
		fscanf(f, "%lu", &b);
		stones[stone_count] = b;
		stone_count ++;
		fgetc(f);
	}
	stone_count --; // the last one is junk
	uint64_t ret = 0;
	for (long i = 0; i < stone_count; i ++) {
		//for (long i = 0; i < stone_count; i ++) {
		//	printf("%lu, ", stones[i]);
		//}
		//printf("\n");
		ret += blink(stones[i], 75, cache, &cache_len);
		printf("handled stone %lu, ret is now %lu\n", i, ret);
	}
	return ret;
}
