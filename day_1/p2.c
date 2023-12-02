#include <stdio.h>
#include <string.h>

unsigned long str_bits[9] = {
    0x00000000006f6e65ul, 0x000000000074776ful, 0x0000007468726565ul,
    0x00000000666f7572ul, 0x0000000066697665ul, 0x0000000000736978ul,
    0x000000736576656eul, 0x0000006569676874ul, 0x000000006e696e65ul
};
unsigned long mask[9]  = {
    0x0000000000fffffful, 0x0000000000fffffful, 0x000000fffffffffful,
    0x00000000fffffffful, 0x00000000fffffffful, 0x0000000000fffffful,
    0x000000fffffffffful, 0x000000fffffffffful, 0x00000000fffffffful
};

int main(int argc, char* argv) {
    FILE* f = fopen("in.txt", "r");
    char buf[8192], tmp, first;
    int i, j, cal = 0, last = 0;
    unsigned long cache = 0ul;
    while (fgets(buf, 8192, f)) {
        first = 0;
        for (i = 0; i < strlen(buf); i++) {
            tmp = buf[i];
            cache = (cache << 8) + tmp;
            if (tmp >= '0' && tmp <= '9') {
                last = tmp - '0';
                if (!first) {
                    cal += 10 * last;
                    first = 1;
                }
            }
            else for (j = 0; j < 9; j++) {
                if (str_bits[j] == (cache & mask[j])) {
                    last = j + 1;
                    if (!first) {
                        cal += 10 * last;
                        first = 1;
                    }
                    break;
                }
            }
        }
        cal += last;
    }
    printf("%d\n", cal);
    fclose(f);
    return 0;
}
