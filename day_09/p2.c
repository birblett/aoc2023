#include <stdio.h>
#include "strutils.h"

int main() {
    FILE* f = fopen("in.txt", "r");
    int nums[100], i, j, store, len = 0, total = 0, start, end;
    char buf[8192], *c, tmp;
    while(fgets(buf, 8192, f)) {
        // do work for segments of the "pyramid" until leftmost and rightmost elements of current slice are 0
        for ((len = sgetints(buf, nums, 100)) && (store = i = 0); (nums[len - 1] || nums[i]) && i < len - 1; ++i)
            // slice left index increases by 1; left num is always preserved since its value is final
            for (j = len - 1; j > i; --j) nums[j] -= nums[j - 1];
        // iterate down to sum differences
        for (i = len - 1; i > 0; --i) store = nums[i] - store;
        total += nums[0] - store;
    }
    printf("total %d\n", total);
    fclose(f);
}
