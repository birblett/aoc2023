#include "../include/str_utils.h"

int str_ints(char* str, int* arr, int max) {
    int count = 0, num = 0, sym = 1;
    char tmp, set = 0;
    for (; count < max && (tmp = *str); ++str) {
        if (tmp > 47 && tmp < 58) {
            set = 1;
            num = num * 10 + tmp - 48;
        }
        else if (set) {
            arr[count++] = num * sym;
            set = num = 0;
            sym = 1;
        }
        else sym = 1;
        if (tmp == '-') sym = -1;
    }
    if (set) arr[count++] = num * sym;
    return count;
}
