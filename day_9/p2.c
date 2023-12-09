#include <stdio.h>
#include "strutils.h"

int main() {
    FILE* f = fopen("in.txt", "r");
    int nums[100], i, j, store, len = 0, total = 0;
    char buf[8192], *c, tmp;
    while(fgets(buf, 8192, f)) {
        for ((len = sgetints(buf, nums, 100)) && (store = i = 0); i < len - 1; ++i) 
            for (j = len - 1; j > i; --j) 
                nums[j] -= nums[j - 1];
        for (i = len - 1; i > 0; --i) store = nums[i] - store;
        total += nums[0] - store;
    }
    printf("total %d\n", total);
    fclose(f);
}
