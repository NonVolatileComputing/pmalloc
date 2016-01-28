A portable persistent memory allocation library.

### Features:
* Optimized memory layout arrangement
* persistent key-value pair storage (fixed length)
* portable address support
* in-place structured data persistence

### How to use it ?
#### setup a memory descriptor for persistent memory pool 
```c
    /* attache to a file hander */
    void *md = pmalloc_attach(fd, NULL, PM_CAPACITY);
    /* capture error */
    assert(NULL != md);
    ....
    /* close it */
    pmalloc_detach(md);
```

#### manipulate persistent memory blocks 
```c
    for (i = 0; i < 16; ++i)
    {
        /* fetch persistent key values */
        key = pmalloc_getkey(md, i);
        if (NULL != key)
            printf("Prekey... %p --> %s %lu\n", key, (char*)key, sizeof(size_t));
        else break;
    }
    ...
    /* allocate a memory block with specified size */
    void *data = pmalloc(md, 0x1000 * 5);
    if (NULL != data) {
        sprintf(data, "output data row %d", i);
        /* put it on key-value pair store */
        pmalloc_setkey(md, i, data);
    }
    ...
    /* retrieve a persisted memory block from key-value pair store with a specified key */
    keydata = pmalloc_getkey(md, keyidx);
    if (NULL != keydata) {
        /* free up an allocated block
        pmfree(md, keydata);
        pmalloc_setkey(md, keyidx, NULL);
        printf(ANSI_COLOR_GREEN "Released original key data at %p! \n" ANSI_COLOR_RESET, keydata);
    } else 
        printf(ANSI_COLOR_CYAN "No original key data set in this key slot! \n" ANSI_COLOR_RESET);
```

### How to Build it ?
```sh
$ mkdir build
$ cd build
$ cmake ..
$ make
$ sudo make install
```

### How to package it ?
```sh
$ cd build
$ cpack -C CPackConfig.cmake
```
