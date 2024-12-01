#define TIME_REPEAT 40000
#define DAY 1
#define PART 2
#include "../util.h"


long aoc(FILE* f) {
	long one, two;
	one = 0;
	two = 0;
	long* one_vec = malloc(2000 * sizeof(long)); // an homage to the age-old adage - the missile's memory leak
	long* two_vec = malloc(2000 * sizeof(long)); // allocating in place is, with few exceptions, a better strategy than ever reallocating. because the amounts are so small (just a few dozens of kbs!), this is fine, and much more performant than 2000+ reallocations!
	memset(one_vec, 0, 2000 * sizeof(long));
	memset(two_vec, 0, 2000 * sizeof(long));
	// interesting to note is that putting one_vec and two_vec on stack makes no noticeable performance difference compared to heap-allocating them, even over 40,000 iterations
	long one_size = 0;
	long two_size = 0;
	while (1) {
		fscanf(f, "%d   %d", &one, &two);
		if (feof(f)) {
			break;
		}
		one_vec[one_size] = one;
		two_vec[two_size] = two;
		one_size ++;
		two_size ++;
	}
	quicksort_long(two_vec, two_size);
	long res = 0;
	for (int x = 0; x < one_size; x ++) {
		int bindex = binsearch_long(two_vec, two_size, one_vec[x]); // get an index into two_vec
		if (bindex == -1) {
			continue;
		}
		int sim = 0;
		for (int i = bindex; i >= 0; i --) {
			if (two_vec[i] != one_vec[x]) {
				break;
			}
			sim ++;
		}
		for (int i = bindex + 1; i < two_size; i ++) {
			if (two_vec[i] != one_vec[x]) {
				break;
			}
			sim ++;
		}
		res += sim * one_vec[x];
	}
	free(one_vec);
	free(two_vec);
	return res;
}
