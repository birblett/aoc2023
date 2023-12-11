#include <stdio.h>
#include "strutils.h"

int main() {
    FILE* f = fopen("in.txt", "r");
    int nums[100], i, j, len, total = 0;
    char buf[8192], *c, tmp;
    while(fgets(buf, 8192, f)) {
        len = sgetints(buf, nums, 100);
        // do work for segments of the "pyramid" until leftmost and rightmost elements of current slice are 0
        for (i = len - 1; (nums[0] || nums[i]) && i > 0; --i) 
            // slice right index increases by 1; left num is always preserved since its value is final
            for (j = 0; j < i; ++j) nums[j] = nums[j + 1] - nums[j];
        // sum array since all values are final
        for (i = 0; i < len; i++) total += nums[i];
    }
    printf("total %d\n", total);
    fclose(f);
}
