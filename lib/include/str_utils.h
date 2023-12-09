#ifndef STR_UTILS_H
#define STR_UTILS_H

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
int str_ints(char* str, int* arr, int max);

#endif
