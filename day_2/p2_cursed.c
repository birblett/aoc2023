#include <stdio.h>
#include <string.h>

int main() {
    FILE *f = fopen("in.txt","r");
    char buf[4096], *c, tmp;
    int len, total = 0, store, rbg[4] = {0}, inner;
    while (((total += rbg[0] * rbg[2] * rbg[1]) + 1) && !(rbg[0] = rbg[1] = rbg[2] = 0) && fgets((c = buf), 4096, f) && (len = strlen(c)) && (c += 5) && !(inner = 0)) while ((c += inner ? 0 : (inner = 1)) < buf + len) !(store = (*(c + 1) == ' ' ? *((c += 2) - 2) : (*c - 48) * 10 + *((c += 3) - 2)) - 48) + !((tmp = *c == 'r' ? 5 : *c == 'b' ? 6 : *c == 'g' ? 7 : 8) && (rbg[tmp - 5] = (store < rbg[tmp - 5] ? rbg[tmp - 5] : store))) + !(c += tmp != 8 ? tmp : 0);
    printf("total: %d\n", total);
    fclose(f);
}
