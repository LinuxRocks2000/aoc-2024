#define DAY 8
#define PART 1
#include "../util.h"


int magic_mod(int base, int by) {
	while (base < 0) {
		base += by;
	}
	while (base >= by) {
		base -= by;
	}
	return base;
}


uint64_t aoc(FILE* f) {
	char buffer[64 * 1024];
	char map[64 * 1024]; // a map that we write a-node positions into
	int len = fread(buffer, 1, 64 * 1024, f);
	int line_len;
	for (line_len = 0; buffer[line_len] != '\n'; line_len ++) {}
	line_len ++;
	for (int i = 0; i < len; i++) {
		map[i] = '.';
		if (i % line_len == line_len - 1) {
			map[i] = '\n';
		}
	}
	map[len] = 0;
	//printf("line length %d\n", line_len);
	for (int i = 0; i < len; i ++) {
		if (buffer[i] == '\n' || buffer[i] == '.') {
			continue;
		}
		for (int j = 0; j < len; j++) {
			if (i == j) {
				continue;
			}
			if (buffer[j] == '\n') {
				continue;
			}
			if (buffer[i] == buffer[j]) {
				int delta = i - j;
				int node = i;
				int i_line_pos = magic_mod(i, line_len);
				int j_line_pos = magic_mod(j, line_len);
				int i_line = i / line_len;
				int j_line = j / line_len;
				int l_delta = i_line - j_line;
				int l = i_line;
				int lp_delta = i_line_pos - j_line_pos;
				int lp = i_line_pos;
				while (1) {
					int node_line_pos = magic_mod(node, line_len);
					if (node_line_pos != lp) {
						break;
					}
					if (node_line_pos == line_len - 1) {
						break;
					}
					if (node < 0 || node >= len) {
						break;
					}
					int n_line = node / line_len;
					//printf("lines: %d, %d: %d\n", i_line, j_line, n_line);
					//if (i_line * 2 - j_line != n_line) {
					//	continue;
					//}
					map[node] = '#';
					node += delta;
					lp += lp_delta;
					l += l_delta;
				}
			}
		}
	}
	long ret = 0;
	for (int i = 0; i < len; i++) {
		if (map[i] == '#') {
			ret ++;
		}
	}
	return ret;
}
