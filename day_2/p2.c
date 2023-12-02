#include <stdio.h>
#include <string.h>

int main() {
    FILE *f = fopen("in.txt","r");
    char buf[4096], *c, tmp;
    int len, total = 0, id = 1, store, rbg[4] = {0};
    while (fgets((c = buf), 4096, f) && (len = strlen(c))) {
        c += 5;
        while ((tmp = *c++) < 58 && tmp > 47) {
            id = id * 10 + tmp - 48;
        }
        c++;
        memset(rbg, 0, 4 * sizeof(int));
        while (c < buf + len) {
            for (int i = 0; i < 3 && c < buf + len; i++) {
                store = (*(c + 1) == ' ' ? *((c += 2) - 2) : (*c - 48) * 10 + *((c += 3) - 2)) - 48;
                tmp = *c == 'r' ? 5 : *c == 'b' ? 6 : *c == 'g' ? 7 : 8;
                rbg[tmp - 5] = store > rbg[tmp - 5] ? store : rbg[tmp - 5];
                c += tmp != 8 ? tmp : 0;
                store = 0;
                if (*(c - 2) == ';') break;
            }
        }
        total += rbg[0] * rbg[2] * rbg[1];
        id = 0;
    }
    printf("total %d\n", total);
    fclose(f);
}

