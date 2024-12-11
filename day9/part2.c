#define DAY 9
#define PART 2

#include "../util.h"


typedef struct {
	int type; // 0 = file, 1 = free
	int size;
	long id;
} fblock_t;


uint64_t aoc(FILE* f) {
	char buf[1024 * 1024];
	long len = fread(buf, 1, 64 * 1024, f);
	fblock_t blocks[1024 * 64];
	long block_count = 0;
	int state = 0; // 0 = file, 1 = free
	long id = 0;
	for (long i = 0; i < len; i ++) {
		blocks[block_count].type = state;
		blocks[block_count].size = buf[i] - '0';
		if (!state) {
			blocks[block_count].id = id;
			id ++;
		}
		state = !state;
		block_count++;
	}
	#ifdef DEBUG_PRINTOUTS
	for (long i = 0; i < block_count; i ++) {
		if (blocks[i].type == 0) {
			for (int z = 0; z < blocks[i].size; z ++) {
				 printf("%d", blocks[i].id);
			}
		}
		else {
			for (int z = 0; z < blocks[i].size; z ++) {
				 printf(".");
			}
		}
	}
	printf("\n");
	#endif
	for (long head = block_count; head >= 0; head --) {
		if (blocks[head].type == 0) {
			for (long front = 0; front < head; front ++) {
				if (blocks[front].type == 1) {
					if (blocks[front].size >= blocks[head].size) {
						// shift all the blocks between head and front up, and insert head behind front
						blocks[front].size -= blocks[head].size;
						fblock_t swap = blocks[head];
						for (long i = head; i >= front; i --) {
							blocks[i] = blocks[i - 1];
						}
						blocks[front] = swap;
						// shift every block ahead of the old head position, increasing the size of the list, and insert a new free space the size of the old head
						for (long i = block_count; i > head + 1; i --) {
							blocks[i] = blocks[i - 1];
						}
						block_count ++;
						blocks[head + 1].type = 1;
						blocks[head + 1].size = swap.size;
						break;
					}
				}
			}
		}
		#ifdef DEBUG_PRINTOUTS
		for (long i = 0; i < block_count; i ++) {
			if (blocks[i].type == 0) {
				for (int z = 0; z < blocks[i].size; z ++) {
					 printf("%d", blocks[i].id);
				}
			}
			else {
				for (int z = 0; z < blocks[i].size; z ++) {
					 printf(".");
				}
			}
		}
		printf("\n");
		#endif
	}
	#ifdef DEBUG_PRINTOUTS
	for (long i = 0; i < block_count; i ++) {
		if (blocks[i].type == 0) {
			for (int z = 0; z < blocks[i].size; z ++) {
				 printf("%d", blocks[i].id);
			}
		}
		else {
			for (int z = 0; z < blocks[i].size; z ++) {
				 printf(".");
			}
		}
	}
	printf("\n");
	#endif
	uint64_t ret = 0;
	long pos = 0;
	for (long i = 0; i < block_count; i ++) {
		for (int j = 0; j < blocks[i].size; j ++) {
			if (blocks[i].type == 0) {
				ret += blocks[i].id * pos;
			}
			pos ++;
		}
	}
	return ret;
}

