#include <stdio.h>
#include <string.h>

int main(int argc, char* argv) {
    FILE* f = fopen("in.txt", "r");
    char buf[8192], tmp, first;
    int i, j, cal = 0, last = 0;
    // use ulong as cache for last 8 chars
    unsigned long cache = 0ul;
    while (fgets(buf, 8192, f)) {
        first = last = 0;
        for (i = 0; i < strlen(buf); i++) {
            tmp = buf[i];
            // shift cache to make room for incoming char
            cache = (cache << 8) + tmp;
            if (tmp >= 48 && tmp <= 57) {
                // if numerical, just store to last directly
                last = tmp - 48;
                if (!first) {
                    // add 10 * last if first not yet found
                    cal += 10 * last;
                    first = 1;
                }
            }
            // do string pattern matching on ulong cache
            else {
                // lookup table to match past 3 letters; for nums with str len > 3, have
                // additional case inside to handle pattern matching
                switch(cache & 0xffffff) {
                    case 0x6f6e65: last = 1; break;
                    case 0x74776f: last = 2; break;
                    case 0x726565: if (((cache >> 24) & 0xffff) == 0x7468) last = 3; break;
                    case 0x6f7572: if (((cache >> 24) & 0xff) == 0x66) last = 4; break;
                    case 0x697665: if (((cache >> 24) & 0xff) == 0x66) last = 5; break;
                    case 0x736978: last = 6; break;
                    case 0x76656e: if (((cache >> 24) & 0xffff) == 0x7365) last = 7; break;
                    case 0x676874: if (((cache >> 24) & 0xffff) == 0x6569) last = 8; break;
                    case 0x696e65: if (((cache >> 24) & 0xff) == 0x6e) last = 9; break;
                }
                // add 10 * last if first not yet found
                if (last && !first++) cal += 10 * last; 
            }
        }
        // add last num found
        cal += last;
    }
    printf("%d\n", cal);
    fclose(f);
    return 0;
}
