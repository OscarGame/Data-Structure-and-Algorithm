
#include "index.h"
#include "adjgraph.h"
#include "mtgraph.h"
#include "queue.h"

#ifdef _BFS_

#ifdef _ADJGRAPH_
//�����������-�����ʾ
BOOLEAN visited[NumVertices]; 	//���ʱ��������ȫ�ֱ���
int bfn[NumVertices]; 			//�����������

void BFS1 (AdjGraph *G, int k)   //����û�н��й�����ȱ��
{   
	int i; 
	EdgeNode *p; 
	QUEUE Q; 
	MAKENULL(Q);
    cout << G->vexlist[ k ] .vertex;   
	visited[ k ] = TRUE;
    ENQUEUE (k, Q); 			//������
    while ( !EMPTY (Q) ) 		//�ӿ���������
	{ 	
        i=FRONT(Q)->element;
		DEQUEUE(Q); 			//vi����
        p =G->vexlist[ i ].firstedge; 	//ȡvi�ı߱�ͷָ��
        while ( p ) 			//��vi���ڽӵ�vj (j= p->adjvex)����,��������
		{ 
			if (!visited[p->adjvex ])  	//��vjδ���ʹ�
			{
				cout << G->vexlist[ p->adjvex ].vertex;	//����vj
				visited[ p->adjvex ]=TRUE; 		//��vj�����ʹ����
				ENQUEUE ( p->adjvex , Q ); 		//���ʹ���vj���
        	}
            p = p->next; 	//��vi����һ���ڽӵ�
        } 	//�ظ����vi�������ڽӶ���
    } 		//���ѭ�����ж��пշ�
}			//��vkΪ������ʱ�����ڽӱ��ʾ��ͼG�����ȹ�����

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

	BFS1(&G, 1);
	cout<<endl;
}

#endif

#ifdef _MTGRAPH_

BOOLEAN visited[NumVertices]; 	//���ʱ��������ȫ�ֱ���
int bfn[NumVertices]; 			//�����������

void BFS2 (MTGraph *G, int k)	//����û�н����ȹ���
{   
	int i , j; 
	QUEUE Q; 
	MAKENULL(Q);
    cout << G->vexlist[ k ]; 		//����vk
    visited[ k ] = TRUE; 			//��vk�����ʹ����
    ENQUEUE (k, Q); 				// vk������
    while ( ! EMPTY (Q) )			//�ӿ�ʱ��������
	{ 		
        i=FRONT(Q)->element;
		DEQUEUE(Q); 				//vi����
        for(j=0; j<G->n; j++) { 	//��������vi���ڽӵ�vj
            if ( G->edge[ i ][ j ] ==1 && !visited[ j ]) //��vjδ���ʹ�
			{ 	
                cout << G->vexlist[ j ];		//����vj
				visited[j]=TRUE; 				//��vj�����ʹ����
				ENQUEUE( j , Q ); 				//���ʹ���vj���
            }
        } 		//�ظ����vi�������ڽӶ���
    } 			//���ѭ�����ж��пշ�
} 				//��vkΪ������ʱ�����ڽӾ����ʾ��ͼG�����ȹ�����

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

	BFS2(&G, 0);
	cout<<endl;
}

#endif
#endif