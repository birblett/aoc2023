#include <stdio.h>
#include <string.h>

#define SEED_MAX 1000
#define MAP_MAX 1000

// struct representing maps seek and left/right range values
typedef struct m {
    long seek;
    // intended: range inclusive
    long left;
    long right;
} map;

int main() {
    FILE *f = fopen("in.txt", "r");
    long seeds[SEED_MAX] = {0}, seeds_store[SEED_MAX] = {0}, tmap[3] = {0}, map_max[7] = {0}, last = 0, seek, left, right, min;
    map maps[7][MAP_MAX] = {{0}}, *mtmp;
    int current = -1, seed_max = 0, i, j, k, should_append;
    char buf[8192], *c, tmp, set = 0;
    while (fgets((c = buf), 8192, f) && !(set = i = 0)) {
        // single line break indicates next set of maps
        if (*c == '\n') !(j = 0) && current++;
        // process number inputs
        for(c += current >= 0 ? 0 : 7 ;tmp = *c++;) switch(tmp) {
            case 48 ... 57: set = 1 | !(last = last * 10 + tmp - 48); break;
            default:
                // put in array if processing seeds
                if (current == -1) seeds[seed_max++] = last ? last : 0;
                else if (set) tmap[i++] = last; 
                // store past 3 nums as seek/left/right map
                if (!(set = last = 0) && i == 3 && ++map_max[current]) maps[current][j++] = (map){tmap[0], tmap[1], tmap[1] + tmap[2] - 1};
        }
    }
    // iterate for each map set, each seed, each map in set
    for (i = 0; !(current = 0) && i < 7; ++i) {
        for ((j = 0); (should_append = 1) && j < seed_max; ++j) {
            for (k = 0; should_append && k < map_max[i]; ++k) {
                if (seeds[j] >= maps[i][k].left && seeds[j] <= maps[i][k].right)
                    // if seed matches map, put in set
                    !(should_append = 0) && (seeds_store[current++] = seeds[j] - maps[i][k].left + maps[i][k].seek);
            }
            // if seed did not match range, insert directly without change
            if (should_append) seeds_store[current++] = seeds[j];
        }
        // copy back
        memcpy(seeds, seeds_store, sizeof(long) * seed_max);
    }
    // get min
    for ((i = 1) && (min = seeds[0]); i < seed_max; i++) if (seeds[i] < min) min = seeds[i];
    printf("min %ld\n", min);
    fclose(f);
}
