/****************************************************************************************

 *****************************************************************************************/

#include "pminternal.h"

int pmalloc_setkey(void *md, int keyidx, void *key) {
	struct mdesc *mdp = (struct mdesc *) md;
	int result = 0;

	if ((mdp != NULL) && (keyidx >= 0) && (keyidx < PMALLOC_KEYS)) {
		mdp->persistkeys[keyidx] = key;
		result++;
	}
	return (result);
}

void * pmalloc_getkey(void *md, int keyidx) {
	struct mdesc *mdp = (struct mdesc *) md;
	void * keyval = NULL;

	if ((mdp != NULL) && (keyidx >= 0) && (keyidx < PMALLOC_KEYS)) {
		keyval = mdp->persistkeys[keyidx];
	}
	return (keyval);
}
