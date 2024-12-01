#include <stdio.h>
#include <stdlib.h>


int* insertion_sort_into(int* vec, long size, int add) {
	int* n_vec = malloc((size + 1) * sizeof(int));
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
	printf("Advent of Code day 1 part 1\n");
	FILE* f = fopen("inputs.txt", "r");
	int one, two;
	int* one_vec = NULL;
	int* two_vec = NULL;
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
	int res = 0;
	for (int x = 0; x < one_size; x ++) {
		res += abs(one_vec[x] - two_vec[x]);
	}
	printf("result: %d\n", res);
}
