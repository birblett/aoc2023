#include <stdio.h>
#include "str_utils.h"

int main() {
    FILE* f = fopen("in.txt", "r");
    int nums[100], i, j, len, total = 0;
    char buf[8192], *c, tmp;
    while(fgets(buf, 8192, f)) {
        len = str_ints(buf, nums, 100);
        for (i = len - 1; i > 0; --i) 
            for (j = 0; j < i; ++j) nums[j] = nums[j + 1] - nums[j];
        for (i = 0; i < len; i++) total += nums[i];
    }
    printf("total %d\n", total);
    fclose(f);
}
