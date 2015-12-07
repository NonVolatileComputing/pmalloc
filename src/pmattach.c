/****************************************************************************************
 Initialization for access to a persistent memory allocator managed pool.
 Persist Memory allocator

 *****************************************************************************************/

#include "pmfunction.h"
#include "pminternal.h"

void * pmalloc_attach(int fd, void *baseaddr, size_t initial_size) {
	struct mdesc mtemp;
	struct mdesc *mdp;
	void * mbase;
	struct stat sbuf;

	if (fd >= 0) {
		if (fstat(fd, &sbuf) < 0) {
			return (NULL);
		} else if (sbuf.st_size > 0) {
			return ((void *) reuse_mempool(fd));
		}
	}

	mdp = &mtemp;
	memset((char *) mdp, 0, sizeof(mtemp));
	strncpy(mdp->magicwords, PMALLOC_MAGIC, PMALLOC_MAGIC_SIZE);
	mdp->headersize = sizeof(mtemp);
	mdp->version = PMALLOC_VERSION;
	mdp->morespace = __pmalloc_map_morespace;
	mdp->mappingfd = fd;
	mdp->mempoolbase = mdp->watermarkpos = mdp->limitpos = baseaddr;

	if (mdp->mappingfd < 0) {
#ifdef HAVE_MMAP_ANON
		mdp->flags |= MMALLOC_ANON;
#else
#ifdef HAVE_MMAP_DEV_ZERO
		if ((mdp -> mappingfd = open ("/dev/zero", O_RDWR)) < 0)
		{
			return (NULL);
		}
		else
		{
			mdp -> flags |= PMALLOC_DEVZERO;
		}
#else
		return NULL;
#endif
#endif
	}

	if ((mbase = mdp->morespace(mdp, sizeof(mtemp) + initial_size)) != NULL) {
		memcpy(mbase, mdp, sizeof(mtemp));
		mdp = (struct mdesc *) mbase;
		mdp->morespace(mdp, -initial_size);
	} else {
		if (mdp->flags & PMALLOC_DEVZERO) {
			close(mdp->mappingfd);
		}
		mdp = NULL;
	}

	return ((void *) mdp);
}
