#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    FILE* f = fopen("in.txt", "r");
    char buf[8192], *c = 0, tmp = 0;
    long race[2] = {0}, i = 0, total = 1;
    for (;fgets((c = buf), 8192, f) && ((tmp = *c) + 1); i++) 
        while (tmp = *c++) if (tmp < 58 && tmp > 47) race[i] = 10 * race[i] + tmp - 48;
    // number of ways to win is just area between roots for 0 = tx - x^2 - d
    printf("total %ld\n", abs((int) (ceil((race[0] + sqrt(race[0] * race[0] - 4 * race[1]))/2) - ceil((race[0] - sqrt(race[0] * race[0] - 4 * race[1]))/2))));
    fclose(f);
}
