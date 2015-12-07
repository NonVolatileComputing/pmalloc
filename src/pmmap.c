/****************************************************************************************
 Support for functions that uses mmap.

 *****************************************************************************************/

#include "pmfunction.h"
#include "pminternal.h"

static size_t pagesize = 0;

#define PAGE_ALIGN(addr) \
	(void *) (((long)(addr) + pagesize - 1) & ~(pagesize - 1))

void * __pmalloc_map_morespace(struct mdesc *mdp, size_t size) {
	void * result = NULL;
	off_t foffset;
	size_t mapbytes;
	void *moveto;
	void *mapto;
	char buf = 0;

	if (pagesize == 0) {
		pagesize = getpagesize();
	}
	if (size == 0) {
		result = mdp->watermarkpos;
	} else if (size < 0) {
		if (mdp->watermarkpos + size >= mdp->mempoolbase) {
			result = (void *) mdp->watermarkpos;
			mdp->watermarkpos += size;
		}
	} else {
		if (mdp->watermarkpos + size > mdp->limitpos) {
			if (0 == mdp->limitpos) { /*Initial memory pool*/
				assert(mdp->watermarkpos == 0);
				moveto = PAGE_ALIGN(size);
				mapbytes = (size_t) moveto;

				if (!(mdp->flags & (PMALLOC_DEVZERO | PMALLOC_ANON))) {
					lseek(mdp->mappingfd, mapbytes - 1, SEEK_SET);
					write(mdp->mappingfd, &buf, 1);
				}
				mapto = mmap(NULL, mapbytes, PROT_READ | PROT_WRITE,
				MAP_SHARED, mdp->mappingfd, 0);
				if (mapto != MAP_FAILED) /* initial */
				{
					mdp->mempoolbase = mdp->watermarkpos = result = mapto;
					mdp->watermarkpos += size;
					mdp->limitpos = PAGE_ALIGN(mdp->watermarkpos);
				}
			}
		} else {
			result = (void *) mdp->watermarkpos;
			mdp->watermarkpos += size;
		}
	}
	return (result);
}

void * __pmalloc_remap_mempool(struct mdesc *mdp) {
	void* base;

	base = mmap(mdp->mempoolbase, (size_t) (mdp->limitpos - mdp->mempoolbase),
	PROT_READ | PROT_WRITE, MAP_SHARED, mdp->mappingfd, 0);
	if (base == MAP_FAILED) {
		fprintf(stderr, "Mapping ERROR:(%d) %s \n", errno, strerror(errno));
	}
	return base;
}

