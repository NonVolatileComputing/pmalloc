/****************************************************************************************
Persistent Memory Library Tests

*****************************************************************************************/

#include <config.h>
#include <stdio.h>
#include <time.h>
#include "pmalloc.h"
#include "check_common.h"

#define PM_CAPACITY 1024LL * 1024 * 1024 * 10
#define PM_MAX_ALLOCSIZE 1024LL * 1024 * 1024 * 8

int main()
{
    printf("Start checking test in block size %zx . \n", PM_MAX_ALLOCSIZE);
    int fd = open("pmclear_ds.dat", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
    if(fd < 0) {
        printf(ANSI_COLOR_RED "Open test data file failure." ANSI_COLOR_RESET);
        return 1;
    }
    
    void *md = pmalloc_attach(fd, NULL, PM_CAPACITY);
    
    init_random();
    
    size_t sz = 0, cntsz = number_binary_length(PM_MAX_ALLOCSIZE), fcount, i;
   
    size_t counters[cntsz];
    
    long fpattern[PMALLOC_KEYS];
    
    int quitflag = 0;
    
    for(i = 0; i < cntsz; ++i) counters[i] = -1;
    
    for ( sz = 1; sz <= PM_MAX_ALLOCSIZE && !quitflag; sz *= 2) {
        gen_pattern(fpattern, PMALLOC_KEYS, 2);
        clear_keydata(md, fpattern, PMALLOC_KEYS);
        fcount = refill_keydata(md, sz);
        counters[number_binary_length(sz) - 1] = fcount;
        //system( "read -n 1 -s -p \"Press any key to continue...\"; echo" );        
    }
    for ( sz = 1; sz <= PM_MAX_ALLOCSIZE && !quitflag; sz *= 2) {
        gen_pattern(fpattern, PMALLOC_KEYS, 0);
        clear_keydata(md, fpattern, PMALLOC_KEYS);
        fcount = refill_keydata(md, sz);
        if (counters[number_binary_length(sz) - 1] != fcount) {
            printf(ANSI_COLOR_RED "Fill count error! %zx <> %zx \n" ANSI_COLOR_RESET, 
                    counters[number_binary_length(sz)], fcount);
            quitflag = 1;
            break;
        }
        //system( "read -n 1 -s -p \"Press any key to continue...\"; echo" );        
    }
    
    for ( sz = PM_MAX_ALLOCSIZE; sz > 0 && !quitflag; sz /= 2) {
        gen_pattern(fpattern, PMALLOC_KEYS, 2);
        clear_keydata(md, fpattern, PMALLOC_KEYS);
        fcount = refill_keydata(md, sz);
        if (counters[number_binary_length(sz) - 1] != fcount) {
            printf(ANSI_COLOR_RED "Fill count error! %zx <> %zx \n" ANSI_COLOR_RESET, 
                    counters[number_binary_length(sz)], fcount);
            quitflag = 1;
            break;
        }
        //system( "read -n 1 -s -p \"Press any key to continue...\"; echo" );
    }
    for ( sz = PM_MAX_ALLOCSIZE; sz > 0 && !quitflag; sz /= 2) {
        gen_pattern(fpattern, PMALLOC_KEYS, 1);
        clear_keydata(md, fpattern, PMALLOC_KEYS);
        fcount = refill_keydata(md, sz);
        if (counters[number_binary_length(sz) - 1] != fcount) {
            printf(ANSI_COLOR_RED "Fill count error! %zx <> %zx \n" ANSI_COLOR_RESET, 
                    counters[number_binary_length(sz)], fcount);
            quitflag = 1;
            break;
        }
        //system( "read -n 1 -s -p \"Press any key to continue...\"; echo" );
    }
        
    pmalloc_detach(md);
    close(fd);
    printf("PM Closed.\n");
    return quitflag;
}

