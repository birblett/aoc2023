#include <stdio.h>
#include <string.h>

int main() {
    FILE* f = fopen("in.txt", "r");
    char *c, tmp, buf[8192], count;
    // if the stack can't afford a 4000 byte memo it should be ashamed of itself
    int total = -1, winning[10] = {-1}, add[] = {[0 ... 1000] = 1}, ind = 0, last, i, offset;
    while (1 | (total += add[++ind]) && fgets((c = buf), 8192, f) && (c += 10) && !(i = offset = last = count = 0))
        while (tmp = *c++)
            switch(tmp) {
                case 48 ... 57:
                    // if num, update current previous val
                    last = last * 10 + tmp - 48;
                    break;
                case 124:
                    // '|' lets it know that winning num are all updated
                    count = 1;
                    break;
                default:
                    // default case is any whitespace; just process nums here
                    if (last)
                        // add prev val to winning array if not finished getting winning num
                        if (!count) winning[i++] = last;
                        // look for matches and next un-updated card
                        else for (i = 0; i < 10; i++) 
                            if (winning[i] == last)
                                add[ind + (++offset)] += add[ind];
                    last = 0;
                    break;
            }
    printf("total %d\n", total);
    fclose(f);
}
