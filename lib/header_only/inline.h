/*
 * contains useful inline function definitions
 */

#ifndef INLINE_H
#define INLINE_H

/**
 * returns the max of two integers
 */
extern inline int imax(int a, int b) {
    return a > b ? a : b;
}

/**
 * returns the min of two integers
 */
extern inline int imin(int a, int b) {
    return a < b ? a : b;
}

/**
 * returns the max of two longs
 */
extern inline long lmax(long a, long b) {
    return a > b ? a : b;
}

/**
 * returns the min of two longs
 */
extern inline long lmin(long a, long b) {
    return a < b ? a : b;
}

#endif
