/****************************************************************************************
 Finish access to a persist memory allocator managed region.
 *****************************************************************************************/

#include "pmfunction.h"
#include "pminternal.h"

void *pmalloc_detach(void *md) {
	struct mdesc mtemp;

	if (md != NULL) {

		mtemp = *(struct mdesc *) md;

		if ((mtemp.morespace(&mtemp, mtemp.mempoolbase - mtemp.limitpos))
				== NULL) {
			*(struct mdesc *) md = mtemp;
		} else {
			if (mtemp.flags & PMALLOC_DEVZERO) {
				close(mtemp.mappingfd);
			}
			md = NULL;
		}
	}

	return (md);
}
