#include <stdio.h>
#include <string.h>

int main() {
    FILE *f = fopen("in.txt","r");
    char buf[4096], *c, tmp;
    // rbg = color data in order of word length
    int len, total = 0, id = 1, store, rbg[4] = {0};
    while (fgets((c = buf), 4096, f) && (len = strlen(c))) {
        // jump to first numerical char
        while (*c++ != ':');
        c++;
        id++;
        memset(rbg, 0, 3 * sizeof(int));
        // determine min requirements for all games 
        while (c < buf + len && !(store = 0)) {
            // store number, knowing current index can only be ones or tens place
            store = (*(c + 1) == ' ' ? *((c += 2) - 2) : (*c - 48) * 10 + *((c += 3) - 2)) - 48;
            // jump by 5, 6, 7, or 0 based on red, blue, green or invalid (case where tmp = 8)
            tmp = *c == 'r' ? 5 : *c == 'b' ? 6 : *c == 'g' ? 7 : 8;
            // replace known minimum if current color count is greater
            rbg[tmp - 5] = store > rbg[tmp - 5] ? store : rbg[tmp - 5];
            c += tmp != 8 ? tmp : 0;
        }
        total += rbg[0] * rbg[2] * rbg[1];
    }
    printf("total %d\n", total);
    fclose(f);
}

