#include <stdio.h>
#include <stdlib.h>


long* insertion_sort_into(long* vec, long size, long add) {
	long* n_vec = malloc((size + 1) * sizeof(long));
	int at;
	for (at = 0; at < size; at ++) {
		if (vec[at] > add) {
			break;
		}
	}
	for (int i = 0; i < size + 1; i ++) {
		if (i < at) {
			n_vec[i] = vec[i];
		}
		else if (i == at) {
			n_vec[i] = add;
		}
		else {
			n_vec[i] = vec[i - 1];
		}
	}
	free(vec);
	return n_vec;
}


int main() {
	printf("Advent of Code day 1 part 2\n");
	FILE* f = fopen("inputs.txt", "r");
	long one, two;
	long* one_vec = NULL;
	long* two_vec = NULL;
	long one_size = 0;
	long two_size = 0;
	while (1) {
		fscanf(f, "%d   %d", &one, &two);
		if (feof(f)) {
			break;
		}
		one_vec = insertion_sort_into(one_vec, one_size, one);
		two_vec = insertion_sort_into(two_vec, two_size, two);
		one_size ++;
		two_size ++;
	}
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
