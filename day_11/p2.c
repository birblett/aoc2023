#include <stdio.h>
#include <stdlib.h>
#include "inline.h"

int main() {
    FILE* f = fopen("in.txt", "r");
    char buf[8192], *c, tmp, row[140] = {0}, col[140] = {0};
    int gindex = 0, len = 0, depth = 0, gd[1000] = {0}, gx[1000] = {0}, i, j, k, e, end;
    long total = 0;
    for (; fgets((c = buf), 8192, f); ++depth, len = 0)
        while ((tmp = *c++) && (len++ < 140)) if (tmp == '#') 
            // if space contains a galaxy: update galaxy coord arrays, mark row/col as occupied
            gd[gindex] = depth, gx[gindex] = len - 1, gindex++, row[depth] = 1, col[len - 1] = 1;
    for (i = 0; i < gindex; ++i) for (j = i + 1; j < gindex; ++j) {
        // add manhattan dist without accounting for empty space
        total += abs(gd[j] - gd[i]) + abs(gx[j] - gx[i]);
        // add 999999 extra steps for empty rows
        for (k = imin(gd[i], gd[j]), end = imax(gd[i], gd[j]); k < end; ++k) if (!row[k]) total += 999999;
        // add 999999 extra steps for empty cols
        for (k = imin(gx[i], gx[j]), end = imax(gx[i], gx[j]); k < end; ++k) if (!col[k]) total += 999999;
    }
    printf("total %ld\n", total);
    fclose(f);
}
