#include "pmfunction.h"
#include "pminternal.h"

void *pmalign(void *md, size_t alignment, size_t size) {
	void * result;
	unsigned long int adj;
	struct alignlist *ablist;
	struct mdesc *mdp = (struct mdesc *) md;

	if ((result = pmalloc(md, size + alignment - 1)) != NULL) {
		adj = RESIDUAL(result, alignment);
		if (adj != 0) {
			for (ablist = mdp->aligned_blocks; ablist != NULL;
					ablist = ablist->next) {
				if (ablist->alignedaddr == NULL) {
					break;
				}
			}
			if (ablist == NULL) {
				ablist = (struct alignlist *) pmalloc(md,
						sizeof(struct alignlist));
				if (ablist == NULL) {
					pmfree(md, result);
					return (NULL);
				}
				ablist->next = mdp->aligned_blocks;
				mdp->aligned_blocks = ablist;
			}
			ablist->unalignedaddr = result;
			result = ablist->alignedaddr = (char *) result + alignment - adj;
		}
	}
	return (result);
}
