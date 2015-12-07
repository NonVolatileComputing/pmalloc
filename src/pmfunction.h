/****************************************************************************************
 Persist Memory allocator
 *****************************************************************************************/

#ifndef PMFUNCTION_H
#define PMFUNCTION_H 1

#include <config.h>
#include "pminternal.h"

#define PMALLOC_DEVZERO		(1 << 0)

#define PMALLOC_INITIALIZED	(1 << 1)

#define PMALLOC_PMCHECK_USED	(1 << 2)

#define PMALLOC_ANON		(1 << 3)

#define PMALLOC_FILE		(1 << 4)

#define REBASE_ADDRESS(A, O) ((void*)(A) + (O))

#ifndef MIN
#  define MIN(A, B) ((A) < (B) ? (A) : (B))
#endif

#define BLOCKSIZE	((unsigned int) 1 << BLOCKLOG)
#define BLOCKIFY(SIZE)	(((SIZE) + BLOCKSIZE - 1) / BLOCKSIZE)

#define RESIDUAL(addr, bsize) ((size_t) ((size_t)addr % (bsize)))

#define BLOCK(A) (((char *) (A) - mdp -> mblkinfobase) / BLOCKSIZE + 1)

#define ADDRESS(B) ((void *) (((B) - 1) * BLOCKSIZE + mdp -> mblkinfobase))

#ifndef HAVE_MEMMOVE
#  define memmove(dst,src,len) bcopy(src,dst,len)
#endif

#define INITMPOOLSIZE	(INT_BIT > 16 ? 4 * 1024 * 1024 : 64 * 1024)

void rebase_mdesc_infos(struct mdesc * mdp, void *e_addr, void *o_addr);

struct mdesc *reuse_mempool(int);

int initialize(struct mdesc *);

void *morespace(struct mdesc *, size_t);

void *align(struct mdesc *, size_t);

void *allocate_blockfrag(struct mdesc *mdp, size_t size);

void *allocate_blocks(struct mdesc *mdp, size_t blocks);

#endif  /* PMFUNCTION_H */
