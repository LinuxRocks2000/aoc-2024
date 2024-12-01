#include <stdio.h>
#include <stdlib.h>
#include "../quicksort.h"


int main() {
	printf("Advent of Code day 1 part 2\n");
	FILE* f = fopen("inputs.txt", "r");
	long one, two;
	long* one_vec = malloc(2000 * sizeof(long)); // an homage to the age-old adage - the missile's memory leak
	long* two_vec = malloc(2000 * sizeof(long)); // allocating in place is, with few exceptions, a better strategy than ever reallocating. because the amounts are so small (just a few dozens of kbs!), this is fine, and much more performant than 2000+ reallocations!
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
	quicksort_long(one_vec, one_size);
	quicksort_long(two_vec, two_size);
	long res = 0;
	for (int x = 0; x < one_size; x ++) {
		long sim = 0;
		for (int y = 0; y < two_size; y ++) {
			if (two_vec[y] == one_vec[x]) {
				sim ++;
			}
		}
		res += sim * one_vec[x];
	}
	printf("result: %d\n", res);
}
