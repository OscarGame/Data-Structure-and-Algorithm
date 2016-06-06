#ifndef _HEAP_H_
#define _HEAP_H_

#include "index.h"

#ifdef _HEAP_

#define Maxsize 200
typedef struct{
    int key;
    datatype data;
}elementtype;

typedef struct{
    elementtype elements[Maxsize];
    int n;
}HEAP;


#endif


#endif