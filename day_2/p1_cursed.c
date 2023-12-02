#include <stdio.h>
#include <string.h>

int main() {
    FILE *f = fopen("in.txt","r");
    char buf[4096], *c, tmp, add;
    int len, total = 0, id = 0, store, rbg[4] = {0}, inner;
    while (((total += add ? id : 0) + 1) && ++id && fgets((c = buf), 4096, f) && (len = strlen(c)) && (c += 5) && !(inner = 0)) while ((1 + (add = add & (rbg[0] <= 12 && rbg[2] <= 13 && rbg[1] <= 14))) && (c += inner ? 0 : (add = inner = 1)) < buf + len && !(rbg[0] = rbg[1] = rbg[2] = 0)) for (int i = 0; i < 3 && c < buf + len + !(store = (*(c + 1) == ' ' ? *((c += 2) - 2) : (*c - 48) * 10 + *((c += 3) - 2)) - 48) + !(rbg[(tmp = *c == 'r' ? 5 : *c == 'b' ? 6 : *c == 'g' ? 7 : 8) - 5] = store) + !(c += tmp != 8 ? tmp : 0); i++) if (*(c - 2) == ';') break;
    printf("total: %d\n", total);
    fclose(f);
}
