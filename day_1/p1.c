#include <stdio.h>
#include <string.h>

int main(int argc, char* argv) {
    FILE* f = fopen("in.txt", "r");
    char buf[8192], tmp, first;
    int i, cal = 0, last = 0;
    while (fgets(buf, 8192, f)) {
        first = 0;
        for (i = 0; i < strlen(buf); i++) {
            tmp = buf[i];
            if (tmp >= 48 && tmp <= 57) {
                // if numerical, store as last num
                last = tmp - 48;
                if (!first) {
                    // if first not yet found, add 10 * last
                    cal += 10 * last;
                    first = 1;
                }
            }
        }
        // add last num found
        cal += last;
    }
    printf("%d\n", cal);
    fclose(f);
    return 0;
}
