#ifndef _MFSET_H_
#define _MFSET_H_

#include "index.h"

#ifdef _MFSET_

#define n 7

struct mfnode{
	int father;
	int count;
};

typedef mfnode MFSET[n+1];

void Union(int, int, MFSET);
int Find(int, MFSET);
void Initial(int, MFSET);
void Equivalence(MFSET);
void print_MFSET(MFSET);


#endif
#endif