#include <stdio.h>
#include <string.h>

int main() {
    FILE* f = fopen("in.txt", "r");
    char buf[8192], c, in[200][200] = {{0}}, paths[3][3] = {{'7', '|', 'F'}, {'-', 'S', '-'},{'J', '|', 'L'}};
    int i, y, x, dy, dx, sy, sx, swap, len, lines = 1, vert = 0, hori = 0, steps = 1;
    for (;fgets(buf, 8192, f) && !(i = 0); lines++) {
        while((c = *(buf + i++)))
            if (c == 'S') sy = lines - 1, sx = i - 1;
            else if (c == '\n') *(buf + i - 1) = '\0';
        memcpy(in[lines - 1], buf, (len = strlen(buf)));
    }
    // determine pipe shape of S and write back to array
    if (sy > 0 && ((c = in[sy - 1][sx]) == '|' || c == '7' || c == 'F')) vert = 1;
    if (sy < len - 1 && ((c = in[sy + 1][sx]) == '|' || c == 'L' || c == 'J')) vert = -1;
    if (sx > 0 && ((c = in[sy][sx - 1]) == '-' || c == 'L' || c == 'F')) hori = -1;
    if (sy < lines - 1 && ((c = in[sy][sx + 1]) == '-' || c == '7' || c == 'J')) hori = 1;
    in[(y = sy)][(x = sx)] = paths[vert + 1][hori + 1];
    // iterate over path until start index is reached
    for (x += (dx = hori), y -= (dy = !dx ? -vert : 0); y != sy || x != sx; y -= dy, x += dx, ++steps)
        if ((c = in[y][x]) == 'F' || c == 'J') swap = dy, dy = dx, dx = swap;
        else if (c == '7' || c == 'L') swap = dy, dy = -dx, dx = -swap;
    printf("max %d\n", steps / 2);
    fclose(f);
}
