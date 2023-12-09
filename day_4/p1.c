#include <stdio.h>
#include <string.h>

int main() {
    FILE* f = fopen("in.txt", "r");
    char *c, tmp, buf[8192], count;
    int total = 0, winning[10] = {0}, add = 0, last, i;
    while (1 | (total += add) && fgets((c = buf), 8192, f) && (c += 10) && !(i = last = count = add = 0))
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
                        // look for matches and update total val
                        else for (i = 0; i < 10; i++) 
                            if (winning[i] == last) 
                                add = add ? add * 2 : 1;
                    last = 0;
            }
    printf("total %d\n", total);
    fclose(f);
}
