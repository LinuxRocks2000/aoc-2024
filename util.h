// utilities for my advent of code solutions
// files using util.h should define void aoc() rather than int main(), and define the macros DAY and PART.
#include <sys/time.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



// insertion sort over a vector of longs
// faster than quicksort for small arrays, so we can cut off quite a few cpu cycles by using insertion sort for quicksort partitions under a certain size
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

// quicksort over a vector of longs
// lomuto variant
// eventually I'll hafta make it generic somehow, in C's special awful way (accept a raw bytearray, an element size, the length, and a comparator function?)
void quicksort_long(long* array, int size) {
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
	if (size <= 22) {
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
	quicksort_long(array, pivot);
	quicksort_long(&array[pivot + 1], size - pivot - 1);
}


// do a binary search to find some index matching an element in a sorted array of longs
// will freak out for unsorted arrays
// returns -1 if the element is not present


#ifdef RECURSIVE_BINSEARCH
int binsearch_long(long* array, int length, long el) {
	if (length == 0) {
		return -1;
	}
	if (length == 1) {
		if (array[0] == el) {
			return 0;
		}
		return -1;
	}
	int pivot = length / 2;
	long pivotal_value = array[pivot];
	if (pivotal_value == el) {
		return pivot;
	}
	else if (pivotal_value > el) { // we need to search the lower half
		return binsearch_long(array, pivot, el);
	}
	else { // we need to search the upper half
		int r = binsearch_long(&array[pivot], length - pivot, el);
		if (r == -1) {
			return -1;
		}
		return pivot + r;
	}
}
#else
int binsearch_long(long* array, int length, long el) {
	int pivot = length/2;
	int start = 0;
	while (1) {
		if (array[pivot] == el) {
			return pivot;
		}
		else if (array[pivot] < el) {
			start = pivot;
		}
		else {
			length = pivot;
		}
		if (length - start < 2) {
			return -1;
		}
		pivot = start + (length - start)/2;
	}
}
#endif


uint64_t timestamp() {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec*(uint64_t)1000000+tv.tv_usec;
}


long aoc(FILE* f);

int main() {
	FILE* f = fopen("inputs.txt", "r");
	printf("=== AOC2024 DAY %d PART %d ===\n", DAY, PART);
	#ifdef TIME_REPEAT
	printf("Running program for %d cycles\n", TIME_REPEAT);
	uint64_t start = timestamp();
	for (int i = 0; i < TIME_REPEAT; i ++) {
		aoc(f);
		rewind(f);
	}
	uint64_t duration = timestamp() - start;
	printf("Average duration: %dµs\n", duration / TIME_REPEAT);
	#else
	printf("DAY %d PART %d SOLUTION: %d\n", DAY, PART, aoc(f));
	#endif
}