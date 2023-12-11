#include <stdio.h>
#include <string.h>

int main() {
    FILE* f = fopen("in.txt", "r");
    char buf[8192], *tmp, c, in[141][141] = {{0}}, paths[3][3] = {{'7', '|', 'F'}, {'-', 'S', '-'},{'J', '|', 'L'}};
    int i, y, x, dy, dx, sy, sx, swap, len, inside, lines = 1, vert = 0, hori = 0, total = 0;
    for (;fgets(buf, 8192, f) && !(i = 0); lines++) {
        while((c = *(buf + i++))) if (c == 'S') sy = lines - 1, sx = i - 1;
        memcpy(in[lines - 1], buf, (len = 140));
        in[lines - 1][140] = '\0';
    }
    // determine pipe shape of S and write back to array
    if (sy > 0 && ((c = in[sy - 1][sx]) == '|' || c == '7' || c == 'F')) vert = 1;
    if (sy < len - 1 && ((c = in[sy + 1][sx]) == '|' || c == 'L' || c == 'J')) vert = -1;
    if (sx > 0 && ((c = in[sy][sx - 1]) == '-' || c == 'L' || c == 'F')) hori = -1;
    if (sy < lines - 1 && ((c = in[sy][sx + 1]) == '-' || c == '7' || c == 'J')) hori = 1;
    in[(y = sy)][(x = sx)] = paths[vert + 1][hori + 1];
    // iterate over path until start index is reached, replace cycle chars with placeholder chars
    for (x += (dx = hori), y -= (dy = !dx ? -vert : 0); y != sy || x != sx; y -= dy, x += dx) {
        if ((c = in[y][x]) == 'F' || c == 'J') swap = dy, dy = dx, dx = swap;
        else if (c == '7' || c == 'L') swap = dy, dy = -dx, dx = -swap;
        in[y][x] = (c == '|' || c == '7' || c == 'F') ? '*' : '%';
    }
    // tally up interior chars - if at a downward-facing edge or vertical pipe then toggle inside state
    in[y][x] = ((c = in[y][x]) == '|' || c == '7' || c == 'F') ? '*' : '%';
    for (i = 0; i < lines - 1; i++) for (tmp = in[i], inside = 0; (c = *tmp); tmp++)
        if (c == '*') inside = !inside;
        else if (inside && c != '%') total++;
    printf("total %d\n", total);
    fclose(f);
}
