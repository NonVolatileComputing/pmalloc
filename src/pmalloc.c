/****************************************************************************************
 Persist Memory allocator

 *****************************************************************************************/

#include "pmfunction.h"
#include "pminternal.h"

void * pmalloc(void *md, size_t size) {
	assert(NULL != md);
	struct mdesc *mdp = (struct mdesc *) md;
	void *result = NULL;

	if (size == 0) {
		return (NULL);
	}

	if (!(mdp->flags & PMALLOC_INITIALIZED)) {
		if (!initialize(mdp)) {
			return (NULL);
		}
	}

	if (size < sizeof(struct list)) {
		size = sizeof(struct list);
	}

	if (size <= BLOCKSIZE / 2) {
		result = allocate_blockfrag(mdp, size);
	} else {
		size_t blocks = BLOCKIFY(size);
		result = allocate_blocks(mdp, blocks);
	}

	return (result);
}
