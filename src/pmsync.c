/****************************************************************************************

 *****************************************************************************************/

#include "pminternal.h"

int pmsync(void *md, void *addr, size_t length) {
	struct mdesc *mdp = (struct mdesc *) md;
	int result = -1;
        if (mdp->mempoolbase < (char*)addr && length > 0) {
		result = msync(addr, length, MS_SYNC);
	}
	return (result);
}
