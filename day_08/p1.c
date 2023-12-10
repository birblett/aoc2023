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
        // do nothing, return nullptr if already in map
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

int main() {
    FILE* f = fopen("in.txt", "r");
    pair* pairs[4096] = {0};
    char buf[8192], sequence[8192], *current = "AAA";
    // read sequence in
    fgets(sequence, 8192, f);
    int i = 0, steps = 0, iter = 1, len = strlen(sequence) - 1;
    fgets(buf, 10, f);
    // add all nodes to map
    while(fgets(buf, 8192, f)) add(pairs, buf, buf + 7, buf + 12);
    fclose(f);
    // iterate over L/R instructionts until ZZZ is reached
    while((current[0] != 'Z' || current[1] != 'Z' || current[2] != 'Z') && ++steps) {
        current = sequence[i] == 'L' ? get(pairs, current)->l : get(pairs, current)->r;
        if (++i >= len) i = 0;
    }
    printf("iters %d\n", steps);
    for (i = 0; i < 4096; i++) if (pairs[i]) free_entry(pairs[i]);
}
