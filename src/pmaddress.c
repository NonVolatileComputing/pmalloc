/****************************************************************************************
 Support portable address conversion.

 *****************************************************************************************/

#include "pminternal.h"

inline void * p_addr(void *md, void *addr) {
	struct mdesc *mdp = (struct mdesc *) md;
	return NULL == addr ? NULL : addr - (size_t) (mdp->mempoolbase);
}

inline void * e_addr(void *md, void *addr) {
	struct mdesc *mdp = (struct mdesc *) md;
	return NULL == addr ? NULL : (size_t) addr + mdp->mempoolbase;
}

inline void * b_addr(void *md) {
	struct mdesc *mdp = (struct mdesc *) md;
	return mdp->mempoolbase;
}
