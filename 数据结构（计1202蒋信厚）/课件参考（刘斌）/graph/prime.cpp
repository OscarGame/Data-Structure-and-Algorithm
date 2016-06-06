#include "mtgraph.h"//�ڽӾ����ʾ��ͼ
#include "tree_array.h"//������

#ifdef _PRIME_
//Prim�㷨
void Prim(MTGraph G, TREE_ARRAY T)
{   
	int i, j, k; 
	EdgeData min;//�洢��С�߳�
	EdgeData LOWCOST[NumVertices];    // �����i������δ����U����LOWCOST[i]��ʾ��i��������U�о�������Ķ���֮��ľ���
	int CLOSSET[NumVertices];  //  �����i������δ����U����LOWCOST[i]��ʾ��i��������U�о�������Ķ���
    //��ʼ��
	int n=G.n;
	for( i=1; i<n; i++ )
	{ 
		LOWCOST[i] = G.edge[0][i];  //���������붥��i֮��ľ���
		CLOSSET[i] = 0; 
		T[i+1].data=G.vexlist[i];
		T[i+1].parent=0;
	}
	T[1].data=G.vexlist[0];//������ʼ����һ������
	T[1].parent=0;
	//�ҳ�����ĵ�
	for( i = 1; i < n; i++ )
	{   
		min = LOWCOST[i];    
		k = i;
		for( j = 1; j < n; j++ )
			if ( LOWCOST[j] < min )
			{   
				min = LOWCOST[j] ;
				k=j; 
			}

		cout << "��"<<i<<"������ĸ��ף�"<< G.vexlist[CLOSSET[k]] <<'\t'<< "����Ķ��㣺"<<G.vexlist[k] <<"�������Ϊ��"<<G.edge[CLOSSET[k]][k]<< endl;  

		T[k].parent=CLOSSET[k];   //���������¼�����Ϊ���н��ĺ��ӽ��
		
		LOWCOST[k] = INT_MAX ;   // ��ʶ��k�������ѷ���U��

		for ( j = 1; j < n; j++ )
			if ( G.edge[k][j] < LOWCOST[j] && LOWCOST[j]!=INT_MAX)
			{   
				LOWCOST[j]=G.edge[k][j]; 
				CLOSSET[j]=k; 
			}
	}
}

void main()
{
	MTGraph G;
	IniMGraph(&G);
	VertexData v[6]={ 'a', 'b', 'c', 'd', 'e', 'f'};
	EdgeData e[6][6] = {{0,6,3,0,0,0},{6,0,0,1,0,5},{3,0,0,6,6,0},{0,1,6,0,0,5},{0,0,6,0,0,2},{0,5,0,5,2,0}};
	CreateMGraph(&G, v, e, 6);
	TREE_ARRAY T;
	Prim(G, T);
	PreOrder(T, 1);
	cout<<endl;
}

#endif