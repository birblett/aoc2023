#include <stdio.h>
#include <string.h>

#define LEN 140

int main() {
    FILE* f = fopen("in.txt", "r");
    char *c, t, buf[8192], line[3][LEN] = {{0}, {0}, {0}}, found_sym, *iter = buf;
    int num, digits, total = 0;
    while (iter && (1 + !(memcpy(line[0], line[1], LEN) && memcpy(line[1], line[2], LEN) && (iter = fgets(buf, 8192, f)) ? memcpy(line[2], buf, LEN) : memset(line[2], '.', LEN)))) for (int i = 0; i < LEN && (1 | *(c = line[1] + i) | (num = *c < 58 && *c > 47 ? *(c + 1) < 58 && *(c + 1) > 47 ? *(c + 2) < 58 && *(c + 2) > 47 ? *(c + 0 * (i += (digits = 3)) + 2) + 10 * (*(c + 1) - 48) + 100 * (*c - 48) - 48: *(c + 0 * (i += (digits = 2)) + 1) + 10 * (*c - 48) - 48: *c - 0 * (i += (digits = 1)) - 48 : 0)); i += 1 + (found_sym = digits = 0)) for (int start = i - digits - 1 > 0 ? i - digits - 1 : 0; num != 0 && start < i + 1 && start < LEN && !found_sym; start++) for (int j = 0; j < 3 && !found_sym; j++) if ((t = line[j][start]) != '.' && t > 0 && t != 10 && (t >= 58 || t <= 47)) found_sym = total += num;
    printf("total %d\n", total);
    fclose(f);
}


