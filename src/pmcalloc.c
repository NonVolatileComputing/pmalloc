/****************************************************************************************
 Persist Memory allocator.
 *****************************************************************************************/

#include "pminternal.h"

void * pmcalloc(void * md, size_t nmemb, size_t size) {
	register void * result;

	if ((result = pmalloc(md, nmemb * size)) != NULL) {
		memset(result, 0, nmemb * size);
	}
	return (result);
}

