/****************************************************************************************
Persistent Memory Library Tests

*****************************************************************************************/

#include <config.h>
#include <stdio.h>
#include <time.h>
#include "pmalloc.h"
#include "check_common.h"

#define LEAK_SLOTS 1
#define USE_SLOTS 2

#define PM_CAPACITY 1024LL * 1024 * 1024 * 10

int main()
{
    printf("Start checking test using %d leak slots\n", LEAK_SLOTS);
    //srand(time(NULL)); 
    init_random();
    int fd = open("pmrecycle_ds.dat", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
    if(fd < 0) {
        printf(ANSI_COLOR_RED "Open test data file failure." ANSI_COLOR_RESET);
        return 1;
    }
    
    void *md = pmalloc_attach(fd, NULL, PM_CAPACITY);
    
    long keyidx = -1;
    
    size_t sz;
    
    void *data = NULL, *keydata = NULL;
    
    do {
        keyidx = random_number(0, USE_SLOTS - 1 + LEAK_SLOTS);
        printf("key index is %ld, ", keyidx);
        
        if (keyidx < USE_SLOTS) {
            keydata = pmalloc_getkey(md, keyidx);
            if (NULL != keydata) {
                pmfree(md, keydata);
                pmalloc_setkey(md, keyidx, NULL);
                printf(ANSI_COLOR_GREEN "Released original key data at %p! \n" ANSI_COLOR_RESET, keydata);
            } else 
                printf(ANSI_COLOR_CYAN "No original key data set in this key slot! \n" ANSI_COLOR_RESET);
        } else 
            printf(ANSI_COLOR_MAGENTA "out of range! \n" ANSI_COLOR_RESET);
        
        sz = random_number(1, PM_CAPACITY / 3); //sz = sz < 0x4000 ? 0x4000 : sz;
        
        data = pmalloc(md, sz);
        
        if (NULL != data)
            printf(ANSI_COLOR_BLUE "Allocated a pm block size %zx in %p \n" ANSI_COLOR_RESET, sz, data);
        else
            break;
        
        pmalloc_setkey(md, keyidx, data);
                
    }while(1);
    
    pmalloc_detach(md);
    close(fd);
    printf("PM Closed.\n");
    return 0;
}

