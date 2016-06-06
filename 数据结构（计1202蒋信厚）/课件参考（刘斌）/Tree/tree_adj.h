#ifndef _TREE_ADJ_H_
#define _TREE_ADJ_H_

#include "index.h"

#ifdef _TREE_ADJ_

// 树的邻接表表示

#define maxtanodes 12

typedef int nodeTA;
typedef char datatypeTA;

struct celltypeTA{
    nodeTA element;                      
    celltypeTA *next;                      
};

typedef celltypeTA *LISTTA;
typedef celltypeTA *positionta;

struct TREETA{
    LISTTA header[19];
    datatypeTA data[10];
    nodeTA root;
};

BOOLEAN Empty(LISTTA);
nodeTA LeftMostChild(TREETA, nodeTA);
nodeTA RightSibling(TREETA, nodeTA);
void PreOrder(TREETA, nodeTA);
void CreateTreeTA(TREETA &);
void CreateTreeTA(TREETA &, datatypeTA [], nodeTA [], int );

#endif

#endif