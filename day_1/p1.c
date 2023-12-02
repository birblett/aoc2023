#include <stdio.h>

int main(int argc, char* argv) {
    FILE* f = fopen("in.txt", "r");
    char buf[8192], *c, tmp, b;
    int cal = 1, last = 0;
    while ((cal += last) && fgets((c = buf), 100, f) && !(b = 0)) while (tmp = *c++) if (tmp > 47 && tmp < 58 && ((last = tmp - 48) + 1) && !b++) cal += 10 * last;
    printf("%d\n", cal - 1);
    fclose(f);
    return 0;
}
