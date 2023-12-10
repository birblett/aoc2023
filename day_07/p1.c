#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int to_index['T' + 1] = {['A'] 12, ['K'] 11, ['Q'] 10, ['J'] 9, ['T'] 8, ['9'] 7, ['8'] 6, ['7'] 5, ['6'] 4, ['5'] 3, ['4'] 2, ['3'] 1, ['2'] 0};

// calculate relative card strength
int get_score(char* s) {
    int counts[13] = {0}, i, max = 0, max2 = 0, tmp;
    for (i = 0; i < 5; ++i) counts[to_index[s[i]]]++;
    for (i = 0; i < 13; ++i)
        if ((tmp = counts[i]) > max && ((max2 = max) + 1)) max = tmp;
        else if (tmp > max2) max2 = tmp;
    return max - ((max < 4 && max2 != 2) ? 1 : 0) + (max < 3 ? 0 : 1);
}

int main() {
    FILE* f = fopen("in.txt", "r");
    char* hands[2000], *tmp[2000], buf[8192], temp;
    int counts[13] = {0}, len = 0, num = 0, total = 1, i, j, ind;
    while(fgets(buf, 8192, f)) memcpy((tmp[len] = (hands[len++] = (char*) malloc(12))), buf, 12);
    fclose(f);
    // radix sort by card value
    for (i = 4; memset(counts, 0, 13 * sizeof(int)) && i >= 0; --i) {
        for (j = 0; j < len; ++j) counts[to_index[hands[j][i]] + 1]++;
        for (j = 1; j < 13; ++j) counts[j] += counts[j - 1];
        for (j = 0; j < len; ++j) tmp[counts[to_index[hands[j][i]]]++] = hands[j];
        for (j = 0; j < len; ++j) hands[j] = tmp[j];
    }
    // radix sort by card strength
    for (i = 0; i < len; ++i) counts[get_score(hands[i]) + 1]++;
    for (i = 1; i < 8; ++i) counts[i] += counts[i - 1];
    for (i = 0; i < len; ++i) tmp[counts[get_score(hands[i])]++] = hands[i];
    // calc final total
    for (i = 0; ((total += num * i) && i < len && !(num = 0)); ++i) for (j = 6; j < 10; ++j) if ((temp = tmp[i][j]) < 58 && temp > 47) num = num * 10 + temp - 48;
    printf("total %d\n", total - 1);
}
