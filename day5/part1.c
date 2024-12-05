#define DAY 5
#define PART 1
#define TIME_REPEAT 1000
#include "../util.h"


typedef struct {
	int left;
	int right;
} rule_t;


int rule_t_cmp(void* _one, void* _two) { // compare only the right half of the rule - this is the half we use for lookups
	rule_t one = *(rule_t*)_one;
	rule_t two = *(rule_t*)_two;
	if (one.right < two.right) {
		return CMP_LESSTHAN;
	}
	if (one.right == two.right) {
		return CMP_EQUAL;
	}
	return CMP_MORETHAN;
}


long aoc(FILE* f) {
	rule_t rules[1024 * 64];
	int rc = 0;
	int test_reprint[1024 * 64];
	// rip out rules
	char linebuf[128];
	while (!feof(f)) {
		fgets(linebuf, 128, f);
		int len = strlen(linebuf);
		if (len < 2) {
			break;
		}
		int left, right;
		left = 0;
		right = 0;
		sscanf(linebuf, "%d|%d", &left, &right);
		rules[rc].left = left;
		rules[rc].right = right;
		rc ++;
	}
	quicksort_any((char*)rules, sizeof(rule_t), rc, rule_t_cmp);
	long ret = 0;
	while (!feof(f)) {
		fgets(linebuf, 128, f);
		int test = 0;
		int tc = 0;
		char* tbuf = linebuf;
		while (1) {
			if (*tbuf >= '0' && *tbuf <= '9') {
				test *= 10;
				test += *tbuf - '0';
			}
			else {
				test_reprint[tc] = test;
				test = 0;
				tc ++;
			}
			if (*tbuf == 0) {
				break;
			}
			tbuf++;
		}
		int valid = 1;
		for (int x = 0; x < tc - 1; x ++) {
			rule_t rule_target = { 0, test_reprint[x] };
			int rule_root_i = binsearch_any(rules, sizeof(rule_t), rc, &rule_target, rule_t_cmp); // this is some index in a blob of rules that pertain to test_reprint[x]
			if (rule_root_i == -1) {
				continue;
			}
			for (int y = x + 1; y < tc; y ++) { // look ahead for any rule violations
				for (int rule_i = rule_root_i; rule_i >= 0; rule_i --) {
					if (rules[rule_i].right != test_reprint[x]) {
						break;
					}
					if (test_reprint[y] == rules[rule_i].left) {
						valid = 0;
						break;
					}
				}
				for (int rule_i = rule_root_i; rule_i < rc; rule_i ++) {
					if (rules[rule_i].right != test_reprint[x]) {
						break;
					}
					if (test_reprint[y] == rules[rule_i].left) {
						valid = 0;
						break;
					}
				}
			}
		}
		if (valid) {
			ret += test_reprint[tc / 2 - 1];
		}
	}
	return ret;
}
