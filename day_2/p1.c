#include <stdio.h>
#include <string.h>

int main() {
    FILE *f = fopen("in.txt","r");
    char buf[4096], *c, tmp, add;
    // rbg = color data in order of word length
    int len, total = 0, id = 0, store, rbg[4] = {0};
    while (fgets((c = buf), 4096, f) && (len = strlen(c))) {
        // jump to first numerical char
        while (*c++ != ':');
        c++;
        id++;
        add = 1;
        // iterate over all games
        while (c < buf + len) {
            // clear rbg data
            memset(rbg, 0, 3 * sizeof(int));
            // get current game data
            for (int i = 0; i < 3 && c < buf + len; i++) {
                // store number, knowing current index can only be ones or tens place
                store = (*(c + 1) == ' ' ? *((c += 2) - 2) : (*c - 48) * 10 + *((c += 3) - 2)) - 48;
                // jump by 5, 6, 7, or 0 based on red, blue, green or bad read
                rbg[(tmp = *c == 'r' ? 5 : *c == 'b' ? 6 : *c == 'g' ? 7 : 8) - 5] = store;
                c += tmp != 8 ? tmp : 0;
                // ';' used in input format as game delimiter
                if (*(c - 2) == ';') break;
            }
            if (rbg[0] > 12 || rbg[2] > 13 || rbg[1] > 14) add = 0;
        }
        // add if current game satisfies conditions
        if (add) total += id;
    }
    printf("total %d\n", total);
    fclose(f);
}

