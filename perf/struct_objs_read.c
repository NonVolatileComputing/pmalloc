#include "common.h"

#define PM_CAPACITY 1024LL * 1024 * 1024 * 10

int main(int argc, char *argv[])
{
  /*	size_t emp_count = 0; */

	if (argc != 2) {
		printf("Usage: %s filename", argv[0]);
		exit(-1);
	}

	char *fn = argv[1];

	assert(NULL != fn);

    printf("Start the example reading struct objects from %s . \n", fn);

    int fd = open(fn, O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
    if(fd < 0) {
        printf(ANSI_COLOR_RED "Open data file failure." ANSI_COLOR_RESET);
        return 1;
    }

    void *md = pmalloc_attach(fd, NULL, PM_CAPACITY);
    assert(NULL != md);

    init_roles(md);

    struct employee_t* emp_root = NULL;

    int cidx;

    for (cidx = COMPANY_MIN_INDEX; cidx <= COMPANY_MAX_INDEX; ++cidx) {
		printf(ANSI_COLOR_GREEN "Show company %d. \n" ANSI_COLOR_RESET, cidx);
    	emp_root = pmalloc_getkey(md, cidx);
    	if (NULL != emp_root) {
    		print_employees(md, emp_root, 0);
    	}
    }

    pmalloc_detach(md);
    close(fd);
    printf("PM Closed.\n");
    return 0;
}

