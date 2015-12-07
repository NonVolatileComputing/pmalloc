/****************************************************************************************
 Allocate memory on a page boundary

 *****************************************************************************************/

#include "pminternal.h"

static size_t pagesize;

void * pmvalloc(void *md, size_t size) {
	if (pagesize == 0) {
		pagesize = getpagesize();
	}

	return (pmalign(md, pagesize, size));
}

