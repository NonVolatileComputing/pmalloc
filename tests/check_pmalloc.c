/****************************************************************************************
Persistent Memory Library Tests

*****************************************************************************************/

#include <config.h>
#include <stdio.h>
#include "pmalloc.h"
#include "check_common.h"

int main()
{
    /*srand(time(NULL));*/
    int fd = open("pmalloc_test.dat", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
    if(fd < 0)
        return 1;
    void *md = pmalloc_attach(fd, NULL, 1024LL * 1024 * 1024 * 10);

    void *key = NULL;
    int i;

    /*key = pmalloc_getkey(md, 3);
    pmfree(md, key);
    pmalloc_setkey(md, 3, NULL);*/

    for (i = 0; i < 16; ++i)
    {
        key = pmalloc_getkey(md, i);
        if (NULL != key)
            printf("Prekey... %p --> %s %lu\n", key, (char*)key, sizeof(size_t));
        else break;
    }



    void *data = pmalloc(md, 0x1000 * 5);
    if (NULL != data) {
        sprintf(data, "output data row %d", i);
        pmalloc_setkey(md, i, data);
    }
    
    size_t sz;
    do {
       sz = 0x1000 * random_number(1, 200);
       printf("Allocating %zx... \n", sz);
    } while (NULL != pmalloc(md, sz));

    pmalloc_detach(md);
    close(fd);
    printf("Hello world... %p \n",data);
    return 0;
}

