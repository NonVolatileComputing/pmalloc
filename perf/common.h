/****************************************************************************************
Declare all examples related functions

*****************************************************************************************/

#ifndef __COMMON_H
#define __COMMON_H 1

#include <config.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "pmalloc.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define ROLES_PKEYID 200
#define COMPANY_MIN_INDEX 1
#define COMPANY_MAX_INDEX 100

unsigned int init_random(unsigned int seed);

int number_binary_length(size_t num);

size_t random_number(size_t min_num, size_t max_num);

void clear_keydata(void *md, long pattern[], size_t count);

size_t refill_keydata(void *md, size_t sz);

void gen_pattern(long pattern[], size_t count, int mode);

void alloc_result(void *ptr);

/*******************************************/

typedef struct employee_t {
	char* name;
	int age;
	char* role;
	struct employee_t **members;
	int mcount;
} employee_t;

extern char **g_roles;

void init_roles(void *md);

size_t gen_employees(void *md, struct employee_t** pemp, int avail_deep);

void print_employees(void *md, struct employee_t* emp, int deep);


#endif  /* __COMMON_H */
