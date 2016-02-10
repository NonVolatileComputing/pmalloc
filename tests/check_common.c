/****************************************************************************************
Persistent Memory Library Tests

*****************************************************************************************/

#include <config.h>
#include <stdio.h>
#include <time.h>
#include "pmalloc.h"
#include "check_common.h"

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

void init_random() 
{
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
    srand((unsigned)ts.tv_nsec);
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
            init_random();
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
    printf("\n" ANSI_COLOR_RESET);
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
