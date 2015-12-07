/****************************************************************************************
Persistent Memory Library Tests

*****************************************************************************************/

#define _LARGEFILE64_SOURCE
#define _FILE_OFFSET_BITS 64
#include <sys/types.h>
#include <unistd.h>

#include <stdio.h>
#include <fcntl.h>

int random_number(int min_num, int max_num);

int main()
{
    char buf = 0;
    int fd = open("ds2.data", O_CREAT|O_RDWR|O_LARGEFILE, S_IRUSR|S_IWUSR);
    if(fd < 0)
        return 1;
    off_t off = lseek(fd, (2LL<<42) + 10, SEEK_SET);
    write (fd, &buf, 1);
     
    close(fd);
    printf("Hello world... %zx \n", off);
    return 0;
}

int random_number(int min_num, int max_num)
{
    int result=0,low_num=0,hi_num=0;
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
