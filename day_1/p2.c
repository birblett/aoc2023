#include <stdio.h>

int main(int argc, char* argv) {
    FILE* f = fopen("in.txt", "r");
    char buf[8192], *c, tmp, b = 0;
    int cal = 1, i, last = 0;
    unsigned long valid[9] = {7302757ul, 7632751ul, 499968533861ul, 1718580594ul, 1718187621ul, 7563640ul, 495623497070ul, 435560081524ul, 1852403301ul}, bits[9]  = {16777215ul, 16777215ul, 1099511627775ul, 4294967295ul, 4294967295ul, 16777215ul, 1099511627775ul, 1099511627775ul, 4294967295ul}, sub=1ul;
    while ((cal += last) && fgets((c = buf), 100, f) && !(b = 0)) while ((tmp = *c++) && (sub = (sub << 8) + tmp)) for (i = 0; i < 9; i += 1 + (i > 0 ? 0 : (tmp > 47 && tmp < 58 && ((last = tmp - 48) + 1) && !b++ && (cal += 10 * last) * 0))) if (valid[i] == (sub & bits[i]) && (last = i + 1) && !b++) cal += 10 * last;
    printf("%d\n", cal - 1);
    fclose(f);
    return 0;
}
