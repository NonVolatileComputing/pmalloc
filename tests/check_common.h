/****************************************************************************************
Declare all check related functions

*****************************************************************************************/

#ifndef __CHECK_COMMON_H
#define __CHECK_COMMON_H 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void init_random();

int number_binary_length(size_t num);

size_t random_number(size_t min_num, size_t max_num);

void clear_keydata(void *md, long pattern[], size_t count);

size_t refill_keydata(void *md, size_t sz);

void gen_pattern(long pattern[], size_t count, int mode);

int free_keydata(void *md, long keyidx);

#endif  /* __CHECK_COMMON_H */
