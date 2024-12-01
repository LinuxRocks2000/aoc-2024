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
				break;
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
	long pivot = length / 2;
	if (array[pivot] == el) {
		return pivot;
	}
	else if (array[pivot] < el) { // we need to search the upper half
		return pivot + binsearch_long(&array[pivot], length - pivot, el);
	}
	else { // we need to search the lower half
		return binsearch_long(array, pivot, el);
	}
}
