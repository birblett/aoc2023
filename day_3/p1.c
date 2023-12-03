#include <stdio.h>
#include <string.h>

#define LEN 140

int main() {
    FILE* f = fopen("in.txt", "r");
    // initialize cache to track past 3 lines
    char c, buf[8192], line[3][LEN] = {{0}, {0}, {0}}, found_sym, *iter = buf;
    int num, digits, total = 0, silly;
    while (iter) {
        // shift cached lines up, top line no longer needed
        memcpy(line[0], line[1], LEN);
        memcpy(line[1], line[2], LEN);
        // store line into bottom of cache, or zero if eof
        if((iter = fgets(buf, 8192, f))) memcpy(line[2], buf, LEN);
        else memset(line[2], '.', LEN);
        for (int i = 0; i < LEN; i++) {
            found_sym = num = digits = 0;
            // checks for nums, jump to end of num if found
            while ((c = line[1][i]) < 58 && c > 47) {
                num = num * 10 + c - 48;
                i++;
                digits++;
            }
            // iterate through matching section of cache to find symbols for previously found num, if applicable
            for (int start = i - digits - 1 > 0 ? i - digits - 1 : 0; num != 0 && start < i + 1 && start < LEN && !found_sym; start++)
                for (int j = 0; j < 3 && !found_sym; j++)
                    if ((c = line[j][start]) != '.' && c > 0 && c != 10 && (c >= 58 || c <= 47))
                        found_sym = total += num;
        }
    }
    printf("total %d\n", total);
    fclose(f);
}
