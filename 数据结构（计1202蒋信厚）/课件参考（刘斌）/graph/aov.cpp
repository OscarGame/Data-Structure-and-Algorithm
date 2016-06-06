#include "aov.h"

#ifdef _AOV_

// �жϴӶ���v1������v2�Ƿ���ڱ�
BOOLEAN connect(AdjGraph G, int v1, int v2)
{
	EdgeNode *tmp;
	tmp=G.vexlist[v1].firstedge;
	if(tmp==NULL)
		return FALSE;
	while(1)
	{
		if(tmp->adjvex==v2)
			return TRUE;
		tmp=tmp->next;
		if(tmp==NULL)
			break;
	}

	return FALSE;
}

void Topologicalsort( AdjGraph G, int aov[NumVertices] )
{  
	int v, w, nodes;
	EdgeNode *tmp;
	EdgeData indegree[NumVertices+1]={0};

	QUEUE Q ;
	MAKENULL( Q ) ;

	// ����ÿ����������
	for( v=1; v<=G.n ; ++v )
	{
		tmp=G.vexlist[v].firstedge;
		while(tmp)
		{
			indegree[tmp->adjvex]++;
			tmp=tmp->next;
		}	
	}
	// �����Ϊ0�Ķ���������
	for(v=1; v<=G.n; ++v)
		if ( indegree[v] ==0 ) 
			ENQUEUE( v, Q ) ;
	
	nodes = 0 ;
	while ( !EMPTY( Q ) )
	{  
		v = FRONT(Q)->element ;
		DEQUEUE( Q ) ;
		//cout << v <<' '; 
		aov[nodes]=v;
		nodes ++ ;		// �ѿ��ǵĽڵ������1
		// ���(v, w)��һ���ߣ���w����ȼ�1�����w�����Ϊ0����w���
		for( w=1; w<=G.n; w++) 
		{
			if(connect(G, v, w))
			{
				--indegree[w];
				if( !(indegree[w])) 
					ENQUEUE(w,Q) ;
			}
		}
	}
	cout<<endl;
	if ( nodes < G.n ) 
		cout<<"ͼ���л�·"<<endl;
	
}

#ifndef _AOE_

void main()
{

	AdjGraph G1;
	IniADJGraph(&G1);
	// �Կγ�Ϊ��������һ������ͼ
  	VertexData v1[10]={'a', 'b', 'c', 'd', 'e','f', 'g', 'h', 'i', 'j'};
	EdgeData e1[10][NumVertices]={{0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 1, 1, 0, 1, 0, 0, 0, 0, 0},
								{0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 1, 0, 1, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 1, 0, 1, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
	
		          
	CreateADJGraph_directed(&G1, v1, e1, 10);
	int aov[NumVertices];
	Topologicalsort( G1, aov);
	for(int i=0; i<10; i++)
		cout<<aov[i]<<' ';
	cout<<endl;
}

#endif
#endif