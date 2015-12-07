/****************************************************************************************
Persistent Memory Library Tests

*****************************************************************************************/

#include <config.h>
#include <stdio.h>
#include <time.h>
#include "pmalloc.h"
#include "check_common.h"

#define PM_CAPACITY 1024LL * 1024 * 1024 * 10
#define PM_MAX_ALLOCSIZE 1024LL * 20 //1024 * 200
#define PM_MIN_ALLOCSIZE 1LL
#define MAX_FREE_COUNT PMALLOC_KEYS
#define MAX_ALLOC_COUNT 200
#define SIMULATE_COUNT 10000

int main()
{
    printf("Start checking test simulate %ld times in max block size %zx . \n", SIMULATE_COUNT, PM_MAX_ALLOCSIZE);
    int fd = open("pmsimulate_ds.dat", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
    if(fd < 0) {
        printf(ANSI_COLOR_RED "Open test data file failure." ANSI_COLOR_RESET);
        return 1;
    }

    void *md = pmalloc_attach(fd, NULL, PM_CAPACITY);
    assert(NULL != md);

    init_random();

    void *data;
    size_t sz;
    long simcnt, i, alloccnt, freecnt, cnt, maxalloccnt, maxfreecnt;
    for (simcnt  = 0; simcnt < SIMULATE_COUNT; ++simcnt) {
        cnt = 0;
        maxalloccnt = random_number(1, MAX_ALLOC_COUNT);
        for (alloccnt  = 0; alloccnt < maxalloccnt; ++alloccnt) {
            for(i = 0; i < PMALLOC_KEYS; ++i) if (NULL == pmalloc_getkey(md, i)) break;
            if (i < PMALLOC_KEYS) {
                sz = random_number(PM_MIN_ALLOCSIZE, PM_MAX_ALLOCSIZE);
                data = pmalloc(md, sz);
                if (NULL == data) break;
                pmalloc_setkey(md, i, data);
                ++cnt;
                printf(ANSI_COLOR_BLUE "(Size %zx) Allocated data at %p with key %ld \n" ANSI_COLOR_RESET, sz, data, i);
            } else break;
        }
        printf(ANSI_COLOR_MAGENTA "Allocated %ld memory blocks \n" ANSI_COLOR_RESET, cnt);

        cnt = 0;
        maxfreecnt = random_number(1, MAX_FREE_COUNT);
        for (freecnt  = 0; freecnt < maxfreecnt; ++freecnt) {
            i = random_number(0, PMALLOC_KEYS);
            if(free_keydata(md, i) == 0) ++cnt;
        }
        printf(ANSI_COLOR_MAGENTA "Freed %ld memory blocks \n" ANSI_COLOR_RESET, cnt);
    }

    pmalloc_detach(md);
    close(fd);
    printf("PM Closed.\n");
    return 0;
}

