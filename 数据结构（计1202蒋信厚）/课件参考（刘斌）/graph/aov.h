#include "index.h"
#include "adjgraph.h"
#include "queue.h"

#ifdef _AOV_

// �жϴӶ���v1������v2�Ƿ���ڱ�
BOOLEAN connect(AdjGraph G, int v1, int v2);

void Topologicalsort( AdjGraph G, int aov[NumVertices] );

#endif