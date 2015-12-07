/****************************************************************************************
 Report statistical information.

 *****************************************************************************************/

#include "pmfunction.h"
#include "pminternal.h"


size_t report_used_inbyte(struct mdesc * mdp)
{
	assert(NULL != mdp);
	return mdp -> mblkstats.bytes_used;
}

size_t report_free_inbyte(struct mdesc * mdp)
{
	assert(NULL != mdp);
	return mdp -> mblkstats.bytes_free;
}

