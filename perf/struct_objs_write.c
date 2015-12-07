#include "common.h"

#define PM_CAPACITY 1024LL * 1024 * 1024 * 10

int main(int argc, char *argv[])
{
	size_t emp_count = 0;

	if (argc != 3) {
		printf("Usage: %s filename deep", argv[0]);
		exit(-1);
	}

	char *fn = argv[1];
	int deep = atoi(argv[2]);

	assert(NULL != fn);
	assert(deep > 0);

    printf("Start the example writing struct objects into %s with deep %d. \n", fn, deep);

    int fd = open(fn, O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
    if(fd < 0) {
        printf(ANSI_COLOR_RED "Open data file failure." ANSI_COLOR_RESET);
        return 1;
    }

    void *md = pmalloc_attach(fd, NULL, PM_CAPACITY);
    assert(NULL != md);

    printf("Seed is %u \n", init_random(0));

    init_roles(md);

    struct employee_t* emp_root = NULL;

    size_t ecnt;

    int cidx;
    for (cidx = COMPANY_MIN_INDEX; cidx <= COMPANY_MAX_INDEX; ++cidx) {
		emp_root = NULL;
		ecnt = gen_employees(md, &emp_root, deep);
		emp_count += ecnt;
		alloc_result(emp_root);
		pmalloc_setkey(md, cidx, emp_root);
		printf(ANSI_COLOR_GREEN "Generated %zx employees for company %d. \n" ANSI_COLOR_RESET,
				emp_count, cidx);
    }

    printf(ANSI_COLOR_BLUE "Generated %zx employees totally. \n" ANSI_COLOR_RESET, emp_count);

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

