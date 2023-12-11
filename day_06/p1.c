#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    FILE* f = fopen("in.txt", "r");
    char buf[8192], *c = 0, tmp = 0;
    int race[8] = {0}, last = 0, num = 0, i = 0, set = 0, total = 1, t, d;
    for (fgets((c = buf), 8192, f); *c || (fgets((c = buf), 8192, f)) || set; (tmp = *c) && c++) 
        if (!(tmp < 58 && tmp > 47 && (num = num * 10 + tmp - 48) && (set = 1))) if (set) (race[i++] = num) && (num = set = 0);
    // number of ways to win per race is just area between roots for 0 = tx - x^2 - d
    for (i = 0; (t = race[i]) && (d = race[i + 4]) && i < 4; i++) 
        total *= abs((int) (ceil((t + sqrt(t * t - 4 * d))/2) - ceil((t - sqrt(t * t - 4 * d))/2)));
    printf("total %d\n", total);
    fclose(f);
}
