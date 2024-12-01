// run performance comparisons on my quicksort/insertion_sort implementations to find the optimal insertion sort cutoff that saves the most time
// literally just a brute force solution

// spits out 22 as being the ideal lc, shaving off a whole... three microseconds. this was a waste of time *sigh*
// the time saving is "noticeable" in my day 2 solution - where it would normally cost something like 72-73 microseconds, now it only costs 70! (with gcc -O8)


#include <time.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define ITEM_COUNT 1000 // target length of the test
#define ITERATIONS 5000 // number of iterations to use when testing a cutoff


int logical_cutoff = 0; // quicksort will delegate any partitions smaller than this size to insertion_sort


uint64_t timestamp() {
    struct timespec tv;
    clock_gettime(CLOCK_MONOTONIC_RAW, &tv);
    return tv.tv_sec*(uint64_t)1000000000+tv.tv_nsec;
}


void insertion_sort_long(long* array, int size) {
	if (size < 2) {
		return;
	}
	for (int track = 1; track < size; track ++) {
		int to; // the index that we're going to swap into
		for (to = track - 1; to >= 0; to --) {
			if (array[to] < array[track]) {
				break;
			}
		}
		to ++;
		long swap = array[track];
		for (int i = track - 1; i >= to; i --) {
			array[i + 1] = array[i];
		}
		array[to] = swap;
	}
}


void quicksort_long(long* array, int size, int lc) {
	if (size < 2) {
		return;
	}
	if (size == 2) {
		if (array[0] > array[1]) {
			long swap = array[1];
			array[1] = array[0];
			array[0] = swap;
		}
		return;
	}
	if (size < lc) {
		insertion_sort_long(array, size);
		return;
	}
	long pivot = 0;
	while (1) {
		int did_swap = 0;
		for (int i = pivot + 1; i < size; i ++) {
			if (array[i] < array[pivot]) {
				long swap = array[pivot + 1];
				array[pivot + 1] = array[i];
				array[i] = swap;
				swap = array[pivot];
				array[pivot] = array[pivot + 1];
				array[pivot + 1] = swap;
				pivot ++;
				did_swap = 1;
			}
		}
		if (!did_swap) {
			break;
		}
	}
	quicksort_long(array, pivot, lc);
	quicksort_long(&array[pivot + 1], size - pivot - 1, lc);
}


void fill_random_longs(long* array, int len) {
	for (int i = 0; i < len; i ++) {
		array[i] = random();
	}
}


int main() {
	long* array = malloc(sizeof(long) * ITEM_COUNT);
	uint64_t lowest_delta = 100000;
	int optimal_lc = 0;
	for (logical_cutoff = 0; logical_cutoff < 100; logical_cutoff ++) { // this program only considers the first 100 lcs.
		// this is where I've noted the sweet spot to be, and in my case, performance drops hilariously as expected past 100.
		uint64_t stime = timestamp();
		for (int i = 0; i < ITERATIONS; i ++) {
			fill_random_longs(array, ITEM_COUNT);
			quicksort_long(array, ITEM_COUNT, logical_cutoff);
		}
		uint64_t etime = timestamp() - stime;
		uint64_t delta = etime / ITERATIONS;
		printf("delta time at lc %d is %d\n", logical_cutoff, delta);
		if (delta < lowest_delta) {
			lowest_delta = delta;
			optimal_lc = logical_cutoff;
		}
	}
	printf("\nthe ideal logical cutoff for array size %d (tested for %d iterations) is %d (delta-t %d)\n", ITEM_COUNT, ITERATIONS, optimal_lc, lowest_delta);
}
