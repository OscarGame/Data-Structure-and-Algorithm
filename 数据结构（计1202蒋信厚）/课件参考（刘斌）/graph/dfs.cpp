#include "adjgraph.h"
#include "mtgraph.h"

#ifdef _DFS_

#ifdef _ADJGRAPH_
// ���ӱ��ʾ
BOOLEAN visited[NumVertices]; 	//���ʱ��������ȫ�ֱ���
int dfn[NumVertices]; 			//�����������

void DFS1 (AdjGraph* G, int i);

void DFSTraverse(AdjGraph G)
//��������һ�ڽӱ��ʾ��ͼG�������ڽӾ����ʾGʱ���㷨��ȫ��ͬ.
{   
	int i , count = 1;
    for ( i = 0; i < G.n; i++ )
        visited [i] =FALSE; 		//��־�����ʼ��
    for ( i = 0; i < G.n; i++ )
        if ( ! visited[i] )
            DFS1( &G, i+1 ); //�Ӷ���i ������ʼ����search() DFSX(G, i )
}

void DFS1 (AdjGraph* G, int i)//��viΪ������ʱ���ڽӱ��ʾ��ͼG������������
{   
	static int count=0;
	EdgeNode *p;
    cout<<G->vexlist[i].vertex;		//���ʶ���vi;
    visited[i]=TRUE;	 			//���vi�ѷ���
    dfn[i]=count++; 				//��vi���б��
    p=G->vexlist[i].firstedge; 		//ȡvi�߱��ͷָ��
    while( 1 )						//��������vi���ڽӵ�vj, ����j=p->adjvex
	{ 			
        if( !visited[p->adjvex] ) 	//��vj��δ����
            DFS1(G, p->adjvex); 	//����vjΪ��������������
        p=p->next;
		if(p==NULL)
			break;
    }	
} //DFS1

void main()
{
	AdjGraph G;
	IniADJGraph(&G);
	VertexData v[5]={'a', 'b', 'c', 'd', 'e'};
	EdgeData e[5][NumVertices]={{0, 1, 0, 1, 0},
								{1, 0, 1, 1, 0},
								{0, 1, 0, 1, 0},
								{1, 1, 1, 0, 1},
								{0, 0, 0, 1, 0}};	
		          
	CreateADJGraph(&G, v, e, 5);
	DFSTraverse(G);
	cout<<endl;
}

#endif

//���Ӿ����ʾ
#ifdef _MTGRAPH_

BOOLEAN visited[NumVertices]; 	//���ʱ��������ȫ�ֱ���
int dfn[NumVertices]; 			//�����������

void DFS2(MTGraph *G, int i);

void DFSTraverse(MTGraph G)
//��������һ�ڽӱ��ʾ��ͼG�������ڽӾ����ʾGʱ���㷨��ȫ��ͬ.
{   
	int i , count = 1;
    for ( i = 0; i < G.n; i++ )
        visited [i] =FALSE; 		//��־�����ʼ��
    for ( i = 0; i < G.n; i++ )
        if ( ! visited[i] )
            DFS2( &G, i ); //�Ӷ���i ������ʼ����search() DFSX(G, i )
}

void DFS2(MTGraph *G, int i)//��viΪ��������ڽӾ����ʾ��ͼG���������������
{ 
    int j;
	static int count=0;
    cout<<G->vexlist[i]; 	//���ʶ���vi
    visited[i]=TRUE; 	//���vi�ѷ���
    dfn[i]=count; 		//��vi���б��
    count ++; 		//��һ������ı��
    for( j=0; j<G->n; j++) 	//��������vi���ڽӵ�
        if((G->edge[i][j] == 1) && !visited[j] ) 	//��vj��δ����
            DFS2( G, j );
}//DFS2

void main()
{
	MTGraph G;
	IniMGraph(&G);

	VertexData v[5]={'a', 'b', 'c', 'd', 'e'};
	EdgeData e[5][NumVertices]={
								{0, 1, 0, 1, 1},
								{1, 0, 1, 0, 0},
								{0, 1, 0, 0, 1},
								{1, 0, 0, 0, 1},
								{1, 0, 1, 1, 0}};
	CreateMGraph(&G, v, e, 5);
	PrintMT(&G);

	DFSTraverse(G);
	cout<<endl;

}


#endif
#endif