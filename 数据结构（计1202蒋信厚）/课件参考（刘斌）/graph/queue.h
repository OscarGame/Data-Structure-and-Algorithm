#ifndef _QUEUE_ARRAY_H_
#define _QUEUE_ARRAY_H_

#include "index.h"

#ifdef _QUEUE_

#define maxlength 20
typedef int que_elementtype;

struct celltype {
	que_elementtype element;
	celltype *next;
};

struct QUEUE {
	celltype *front;
	celltype *rear;
};

void error(char *str);

void MAKENULL( QUEUE &Q );

BOOLEAN EMPTY( QUEUE &Q );

celltype *FRONT(QUEUE Q);

void ENQUEUE ( que_elementtype x, QUEUE &Q );

void DEQUEUE ( QUEUE &Q );

#endif
#endif