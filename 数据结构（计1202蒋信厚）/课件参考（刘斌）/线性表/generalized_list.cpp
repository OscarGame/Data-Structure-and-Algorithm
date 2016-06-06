#include "index.h"

#ifdef _GENERALIZED_LIST_

struct listnode {
	listnode *link;
	boolean tag;
	union {
		char data;
		listnode *dlink;
	} element;
};
typedef listnode *listpointer;



#endif