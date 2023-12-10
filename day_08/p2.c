#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// helper struct for hashmap
typedef struct hpair {
    char* key;
    char* l;
    char* r;
    struct hpair* next;
} pair;

// add key/left-right pair to map
pair* add(pair** map, char* key, char* l, char* r) {
    pair* tmp;
    // random hashing function, just cobble the rightmost 4 bits of each char in key together
    int hash = ((key[0] & 0xf) << 8) + ((key[1] & 0xf) << 4) + (key[2] & 0xf);
    // collision checking, append to end of list if necessary
    if ((tmp = map[hash])) {
        while (tmp->next) tmp = tmp->next;
        if (tmp->key[0] == key[0] && tmp->key[1] == key[1] && tmp->key[2] == key[2]) return NULL;
        *(tmp->next = malloc(sizeof(pair))) = (pair){memcpy(malloc(3), key, 3), memcpy(malloc(3), l, 3), memcpy(malloc(3), r, 3), NULL};
        return tmp->next;
    }
    // directly set if no collision
    *(map[hash] = malloc(sizeof(pair))) = (pair){memcpy(malloc(3), key, 3), memcpy(malloc(3), l, 3), memcpy(malloc(3), r, 3), NULL};
    return map[hash];
}

// get matching map entry corresponding to key
pair* get(pair** map, char* key) {
    pair* tmp;
    int hash = ((key[0] & 0xf) << 8) + ((key[1] & 0xf) << 4) + (key[2] & 0xf);
    for (tmp = map[hash]; tmp; tmp = tmp->next) if (tmp->key[0] == key[0] && tmp->key[1] == key[1] && tmp->key[2] == key[2]) return tmp;
    return NULL;
}

// recursive free of pair linkedlist
void free_entry(pair* p) {
    if (p->next) free_entry(p->next);
    free(p->key);
    free(p->l);
    free(p->r);
    free(p);
}

// recursive gcd of 2 numbers, used to calc lcm
long gcd(long h, long l) {
    if (!l) return h;
    return gcd(l, h % l);
}

int main() {
    FILE* f = fopen("in.txt", "r");
    // pseudo map of pairs
    pair* pairs[4096] = {0}, *current[100] = {0}, *tmp;
    char buf[8192], sequence[8192];
    // read sequence in
    fgets(sequence, 8192, f);
    int i = 0, iter = 1, len = strlen(sequence) - 1, current_len = 0, j;
    unsigned long steps = 0, step_count[100] = {0}, a, b;
    fgets(buf, 8192, f);
    // add all nodes to map
    while(fgets(buf, 8192, f)) if ((tmp = add(pairs, buf, buf + 7, buf + 12)) && tmp->key[2] == 'A') current[current_len++] = tmp;
    fclose(f);
    // iterate over all nodes until first step counts logged for each
    while(iter && ++steps) {
        // count for each starting node until first Z is reached for each
        for (j = 0; j < current_len; j++) if (!step_count[j]) {
            current[j] = sequence[i] == 'L' ? get(pairs, current[j]->l) : get(pairs, current[j]->r);
            if (current[j]->key[2] == 'Z') step_count[j] = steps;
        }
        if (++i >= len) i = 0;
        for (j = iter = 0; j < current_len; j++) if (!step_count[j]) iter = 1;
    }
    // find lcm of all step counts
    for ((steps = step_count[0]) && (i = 1); i < current_len; i++) steps = (a = steps) * (b = step_count[i]) / (a > b ? gcd(a, b) : gcd(b, a));
    printf("iters %ld\n", steps);
    for (i = 0; i < 4096; i++) if (pairs[i]) free_entry(pairs[i]);
}
