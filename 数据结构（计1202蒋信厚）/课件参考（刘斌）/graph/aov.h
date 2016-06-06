#include "index.h"
#include "adjgraph.h"
#include "queue.h"

#ifdef _AOV_

// 判断从顶点v1到顶点v2是否存在边
BOOLEAN connect(AdjGraph G, int v1, int v2);

void Topologicalsort( AdjGraph G, int aov[NumVertices] );

#endif