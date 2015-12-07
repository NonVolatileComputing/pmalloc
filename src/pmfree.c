/****************************************************************************************

 *****************************************************************************************/

#include "pmfunction.h"
#include "pminternal.h"

void __pmalloc_free(struct mdesc *mdp, void *addr) {
	size_t block = BLOCK(addr);

	int fragtype = mdp->mblkinfo[block].inuse.fragtype;
	switch (fragtype) {
	case 0:
		free_blocks(mdp, block);
		break;

	default:
		free_blockfrag(mdp, block, fragtype, addr);
		break;
	}
}

void pmfree(void *md, void *addr) {
	struct mdesc *mdp = (struct mdesc *) md;
	register struct alignlist *l;

	if (addr != NULL) {
		for (l = mdp->aligned_blocks; l != NULL; l = l->next) {
			if (l->alignedaddr == addr) {
				l->alignedaddr = NULL;
				addr = l->unalignedaddr;
				break;
			}
		}
		__pmalloc_free(mdp, addr);
		// if (check_heap_free_info(mdp) < 0) exit(1);
	}

}

