#include <stdio.h>
#include <string.h>

#define LEN 140

int main() {
    FILE* f = fopen("in.txt", "r");
    // initialize cache to track past 3 lines, gears, and surrounding gear num counts
    char c, buf[8192], line[3][LEN] = {{0}, {0}, {0}}, found_sym, *iter = buf;
    int total = 0, num, digits, silly, gearc[3][LEN] = {{0}, {0}, {0}}, gear[3][LEN] = {{-1}, {-1}, {-1}};
    while (iter) {
        iter = fgets(buf, 8192, f);
        // shift all caches up 1
        memcpy(line[0], line[1], LEN);
        memcpy(gear[0], gear[1], LEN * sizeof(int));
        memcpy(gearc[0], gearc[1], LEN * sizeof(int));
        memcpy(line[1], line[2], LEN);
        memcpy(gear[1], gear[2], LEN * sizeof(int));
        memcpy(gearc[1], gearc[2], LEN * sizeof(int));
        // if eof: set set last cache line to 0
        if(iter) memcpy(line[2], buf, LEN);
        else memset(line[2], '.', LEN);
        memset(gearc[2], 0, LEN * sizeof(int));
        // memset to -1 since gear ratios are multiplied: output negative of result later
        memset(gear[2], -1, LEN * sizeof(int));
        for (int i = 0; i < LEN; i++) {
            found_sym = num = digits = 0;
            // checks for nums, jump to end of num if found
            while ((c = line[1][i]) < 58 && c > 47) {
                num = num * 10 + c - 48;
                i++;
                digits++;
            }
            // iterate through matching section of cache to find symbols for previously found num, if applicable
            for (int start = i - digits - 1 > 0 ? i - digits - 1 : 0; num != 0 && start < i + 1 && start < LEN && !found_sym; start++) {
                for (int j = 0; j < 3 && !found_sym; j++) {
                    if ((c = line[j][start]) != '.' && c > 0 && c != 10 && (c >= 58 || c <= 47)) {
                        // if symbol found: update adjacent gears
                        if (found_sym = 1) {
                            for (start = i - digits - 1 > 0 ? i - digits - 1 : 0; num != 0 && start < i + 1 && start < LEN; start++) {
                                for (int j = 0; j < 3; j++) {
                                    if (line[j][start] == '*') {
                                        gear[j][start] *= num;
                                        gearc[j][start]++;
                                        // add if adjacent gear has 2 nums next, otherwise subtract and revert the multiplication
                                        if (gearc[j][start] == 2) total += gear[j][start];
                                        else if (gearc[j][start] == 3) total -= (gear[j][start] /= num);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    printf("total %d\n", -total);
    fclose(f);
}
