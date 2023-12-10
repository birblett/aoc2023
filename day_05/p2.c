#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SEED_MAX 1000
#define MAP_MAX 1000
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

// struct representing maps seek and left/right range values
typedef struct m {
    long seek;
    // intended: range inclusive
    long left;
    long right;
} map;

int main() {
    FILE *f = fopen("in.txt", "r");
    long tmap[3] = {0}, map_max[7] = {0}, last = 0, seek, left, right, min, rangel, ranger;
    map maps[7][MAP_MAX] = {{0}}, seeds[SEED_MAX] = {{0}}, seeds_store[SEED_MAX] = {{0}},*mtmp;
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
                if (current == -1 && (tmap[i] = last)) {
                    if (++i == 2) seeds[seed_max++] = (map){(i = 0), tmap[0], tmap[0] + tmap[1] - 1};
                }
                else if (set) tmap[i++] = last;
                // store past 3 nums as seek/left/right map
                if (!(set = last = 0) && i == 3 && ++map_max[current]) maps[current][j++] = (map){tmap[0], tmap[1], tmap[1] + tmap[2] - 1};
        }
    }
    // iterate for each map set, each seed, each map in set
    for (i = 0; !(current = 0) && i < 7; ++i) {
        for ((j = 0); (should_append = 1) && j < seed_max; ++j) {
            for (k = 0; should_append && k < map_max[i]; ++k) {
                left = maps[i][k].left, right = maps[i][k].right, seek = maps[i][k].seek, rangel = seeds[j].left, ranger = seeds[j].right;
                if (MAX(rangel, left) < MIN(ranger, right)) {
                    if (rangel < left) seeds[seed_max++] = (map){0, rangel, left - 1};
                    if (ranger > right) seeds[seed_max++] = (map){0, right + 1, ranger};
                    // put matching seed range in set, put in set
                    seeds_store[current++] = (map){(should_append = 0), MAX(rangel, left) - left + seek, MIN(ranger, right) - left + seek};
                }
            }
            // if seed did not match range, insert directly without change
            if (should_append) seeds_store[current++] = seeds[j];
        }
        // copy back
        memcpy(seeds, seeds_store, sizeof(map) * seed_max);
    }
    // get min of all seeds
    for ((i = 1) && (min = seeds[0].left); i < seed_max; i++) if (seeds[i].left < min) min = seeds[i].left;
    printf("min %ld\n", min);
    fclose(f);
}
