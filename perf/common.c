/****************************************************************************************
Persistent Memory Library Example

*****************************************************************************************/

#include <config.h>
#include <stdio.h>
#include <time.h>
#include "pmalloc.h"
#include "common.h"

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

unsigned int init_random(unsigned int seed)
{
    unsigned int ret = seed;
    if (0 == seed) {
        struct timespec ts;
        #ifdef __MACH__ // OS X does not have clock_gettime, use clock_get_time
        clock_serv_t cclock;
        mach_timespec_t mts;
        host_get_clock_service(mach_host_self(), SYSTEM_CLOCK, &cclock);
        clock_get_time(cclock, &mts);
        mach_port_deallocate(mach_task_self(), cclock);
        ts.tv_sec = mts.tv_sec;
        ts.tv_nsec = mts.tv_nsec;
        #else
        clock_gettime(CLOCK_MONOTONIC, &ts);
        #endif
        ret = (unsigned)ts.tv_nsec;
    }
    srand(ret);
    return ret;
}

size_t random_number(size_t min_num, size_t max_num)
{
    size_t result=0,low_num=0,hi_num=0;
    if(min_num<max_num)
    {
        low_num=min_num;
        hi_num=max_num+1; // this is done to include max_num in output.
    }else{
        low_num=max_num+1;// this is done to include max_num in output.
        hi_num=min_num;
    }
    result = (rand()%(hi_num-low_num))+low_num;
    return result;
}

int number_binary_length(size_t num)
{
    int ret = 0;
    while(num) {
        num = num >> 1;
        ++ret;
    }
    return ret;
}

int free_keydata(void *md, long keyidx)
{
    int ret = -1;
    void *keydata = pmalloc_getkey(md, keyidx);
    if (NULL != keydata) {
        pmfree(md, keydata);
        pmalloc_setkey(md, keyidx, NULL);
        printf(ANSI_COLOR_GREEN "Released original key data at %p with key %ld \n" ANSI_COLOR_RESET, keydata, keyidx);
        ret = 0;
    }
    return ret;
}


void clear_keydata(void *md, long pattern[], size_t count)
{
    long keyidx = 0;

    for ( keyidx = 0; keyidx < count; ++keyidx) {
        free_keydata(md, keyidx);
    }
}

void gen_pattern(long pattern[], size_t count, int mode)
{
    size_t idx;
    long val;
    switch (mode)
    {
        case 0:
            for ( idx = 0; idx < count; ++idx) pattern[idx] = (long)idx;
            break;
        case 1:
            val = 0;
            idx = count - 1;
            do {
                pattern[idx--] = val++;
            }while (idx != 0); //siz_t must be great or equal to zero
            break;
        case 2:
            for ( idx = 0; idx < count; ++idx) pattern[idx] = (long)idx;
            size_t swapidx;
            init_random(0);
            for ( idx = 0; idx < count; ++idx) {
                swapidx = random_number(0, count);
                if (swapidx != idx) {
                    val = pattern[idx];
                    pattern[idx] = pattern[swapidx];
                    pattern[swapidx] = val;
                }
            }
            break;
        default:
            ;
    }
    printf(ANSI_COLOR_CYAN "Free Pattern: " ANSI_COLOR_RESET);
    for( idx = 0; idx < count; ++idx) printf("%ld,",pattern[idx]);
    printf("\n", ANSI_COLOR_RESET);
}

size_t refill_keydata(void *md, size_t sz)
{
    size_t fillcount = 0;

    long keyidx = 0;

    void *data = NULL;

    printf(ANSI_COLOR_CYAN "Set allocation size as %zx! \n" ANSI_COLOR_RESET, sz);

    for ( keyidx = 0; keyidx < PMALLOC_KEYS; ++keyidx) {
        data = pmalloc(md, sz);
        if (NULL != data) {
            pmalloc_setkey(md, keyidx, data);
            printf(ANSI_COLOR_BLUE "(Size %zx) Allocated data at %p with key %ld \n" ANSI_COLOR_RESET, sz, data, keyidx);
            ++fillcount;
        } else {
            printf(ANSI_COLOR_CYAN "Filled it up !!! \n" ANSI_COLOR_RESET);
            break;
        }
    }
    return fillcount;
}

/*******************************************/

void alloc_result(void *ptr) {
	if (NULL == ptr) {
		printf(ANSI_COLOR_RED "Out of Memory! \n" ANSI_COLOR_RESET);
		exit(-2);
	}
}


void init_roles(void *md) {
	g_roles = e_addr(md, pmalloc_getkey(md, ROLES_PKEYID));

	if (NULL == g_roles) {
		g_roles = (char**)pmalloc(md, sizeof(char*) * 6);

		g_roles[0] = p_addr(md, pmalloc(md, 20));
		alloc_result(g_roles[0]);
		sprintf(e_addr(md, g_roles[0]), "manager");

		g_roles[1] = p_addr(md, pmalloc(md, 20));
		alloc_result(g_roles[1]);
		sprintf(e_addr(md, g_roles[1]), "trainer");

		g_roles[2] = p_addr(md, pmalloc(md, 20));
		alloc_result(g_roles[2]);
		sprintf(e_addr(md, g_roles[2]), "engineer");

		g_roles[3] = p_addr(md, pmalloc(md, 20));
		alloc_result(g_roles[3]);
		sprintf(e_addr(md, g_roles[3]), "sales");

		g_roles[4] = p_addr(md, pmalloc(md, 20));
		alloc_result(g_roles[4]);
		sprintf(e_addr(md, g_roles[4]), "lawyer");

		g_roles[5] = p_addr(md, pmalloc(md, 20));
		alloc_result(g_roles[5]);
		sprintf(e_addr(md, g_roles[5]), "accountant");

		pmalloc_setkey(md, ROLES_PKEYID, p_addr(md, g_roles));
	}
}

size_t gen_employees(void *md, struct employee_t** pemp, int avail_deep) {
	size_t ret = 0;
	assert(NULL != pemp);

	struct employee_t* emp;
	emp = pmalloc(md, sizeof(struct employee_t));
	alloc_result(emp);
	*pemp = p_addr(md, emp);

	emp->name = (char*)p_addr(md, pmcalloc(md, sizeof(char), random_number(200, 1000)));
	alloc_result(emp->name);
	sprintf(e_addr(md, emp->name), "employee %d", random_number(0, 60000));

	emp->age = random_number(24, 90);

	emp->role = g_roles[random_number(0 == avail_deep ? 1 : 0, 5)];

	emp->members = NULL;

	emp->mcount = 0;

	if (g_roles[0] == emp->role) { // manager
		struct employee_t ** members = NULL;
		emp->mcount = random_number(1, 10);
		members = pmalloc(md, emp->mcount * sizeof(struct employee_t*));
		alloc_result(members);
		int i;
		for (i = 0; i < emp->mcount; ++i) {
			ret += gen_employees(md, &members[i], avail_deep - 1);
		}
		emp->members = p_addr(md, members);
	}

	fprintf(stderr, "Generating %s, age: %d, role: %s, the number of members: %d \n",
			e_addr(md, emp->name), emp->age, e_addr(md, emp->role), emp->mcount);

	++ret;

	return ret;
}

void print_employees(void *md, struct employee_t* emp, int deep) {
	assert(NULL != emp);
	struct employee_t* e_emp = e_addr(md, emp);
	int dp = deep;
	while (dp--) {
		printf("--");
	}
	printf("%s, age: %d, role: %s, the number of members: %d \n",
			e_addr(md, e_emp->name), e_emp->age, e_addr(md, e_emp->role), e_emp->mcount);
	if (g_roles[0] == e_emp->role) { // manager
		int i;
		struct employee_t ** members = e_addr(md, e_emp->members);
		assert(NULL != members);
		for (i = 0; i < e_emp->mcount; ++i) {
			print_employees(md, members[i], deep + 1);
		}
	}
}
