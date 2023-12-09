#ifndef STRUTILS_H
#define STRUTILS_H

/**
 * takes an input string and extracts any numbers, writing results to an array provided by the 
 * caller. handles ints.
 * 
 * str: input string, assumes properly formatted. segfaults if not properly terminated.
 * arr: output array. no automatic bounds checking; max parameter must be passed.
 * max: max index of the output array. if max is reached then the function returns immediately
 *
 * returns: number of numbers found
 */
int sgetints(char* str, int* arr, int max);

/**
 * takes an input string and extracts any numbers, writing results to an array provided by the 
 * caller. handles long.
 * 
 * str: input string, assumes properly formatted. segfaults if not properly terminated.
 * arr: output array. no automatic bounds checking; max parameter must be passed.
 * max: max index of the output array. if max is reached then the function returns immediately
 *
 * returns: number of numbers found
 */
int sgetlongs(char* str, long* arr, int max);

#endif
