#include<iostream.h>

#define MaxValue 1000
#define NumEdges 50 			//����
#define NumVertices 6 			//�������

typedef char VertexData; 		//������������
typedef int EdgeData;			//����Ȩֵ����

typedef struct{
    VertexData vexlist[NumVertices]; 	//�����
    EdgeData edge[NumVertices][NumVertices];
            		//�ڽӾ��󡪱߱�, ����Ϊ��֮��Ĺ�ϵ
    int n;			//ͼ�е�ǰ�Ķ������
	int e; 			//ͼ�е�ǰ�ı���
} MTGraph;

// ����ͼ
void IniMGraph_directed(MTGraph *G)
{
	for(int i=0; i<NumVertices; i++)
		for(int j=0; j<NumVertices; j++)
			G->edge[i][j]=MaxValue;
	G->n=0;
	G->e=0;
}

void CreateMGraph_directed(MTGraph *G, VertexData V[], EdgeData E[][NumVertices], int n)
{
	int i, j;	
	G->n=n;

	for (i=0; i<n; i++) 			//2.���붥����Ϣ�����������
		G->vexlist[i]=V[i];

	for (i=0; i<G->n; i++)
		for (j=0;j<G->n;j++)
			G->edge[i][j]=MaxValue; 		//3.�ڽӾ����ʼ��
	
	for(i=0; i<n; i++)				//4.����e���߽����ڽӾ���
		for(j=0; j<n; j++)
		{		
			if(E[i][j]!=0)
			{
				G-> edge[i][j]=E[i][j];			
				G->e++;
			}
		}
}
//Floyd�㷨��ÿ�Զ���֮������·��
void Floyd(int A[NumVertices][NumVertices],MTGraph C,int P[NumVertices][NumVertices],int n)
{   
	int i, j, k;
	for ( i = 0; i < n; i++ )
        for ( j = 0; j<n; j++ )
		{
            A[i][j] = C.edge[i][j] ;       
			P[i][j] = -1; 
    } 

    for ( k = 0; k < n; k++ )
        for ( i = 0; i < n; i++ )
            for ( j = 0; j <n; j++ )
                  if ( A[i][k] + A[k][j] < A[i][j] )
				  {
                        A[i][j] = A[i][k] + A[k][j] ;   
						P[i][j] = k;
				  }
} /* ʱ�临����O(n3) */

void Path(int P[NumVertices][NumVertices], int i, int j)
{
	int k=P[i][j];
	if(k!=-1)
	{
		Path(P, i, k);
		cout<<k+1<<endl;
		Path(P, k, j);
	}
	
}

//Warllshall�㷨���ڽӾ���Ĵ��ݱհ�
void Warshall(int A[NumVertices][NumVertices],MTGraph C,int n)
{
	int i, j, k;
	for ( i = 0; i < n; i++ )
        for ( j = 0; j<n; j++ )
		{
            if(C.edge[i][j]!=MaxValue)			
				A[i][j] =1 ; 				
			else			
				A[i][j]=0;
		
			
    } 
    for ( k = 0; k < n; k++ )
        for ( i = 0; i < n; i++ )
            for ( j = 0; j <n; j++ )
                  if ( A[i][k] && A[k][j] )
				  {
                        A[i][j] =A[i][j] || ( A[i][k] && A[k][j]) ; 					
				  }
} /* ʱ�临����O(n3) */

//�����ĵ�
void CenterPoint(EdgeData A[NumVertices][NumVertices], int n, int &cp)
{
	EdgeData E[NumVertices]={0};
	int min=MaxValue;
	for(int j=0; j<n; j++)
	{
		for(int i=0; i<n; i++)
			if(A[i][j]<MaxValue)
				E[j]+=A[i][j];
		if(E[j]==0)
			E[j]=MaxValue;
		if(E[j]<min)
		{
			min=E[j];
			cp=j;
		}
	}		
}

void main()
{
	int i, j, cp;
	MTGraph G;
	IniMGraph_directed(&G);
	VertexData v[]={'a', 'b', 'c', 'd', 'e','f'};//���㼯
	EdgeData e[NumVertices][NumVertices]={
		{0,3,MaxValue,4,MaxValue,5},
		{MaxValue,0,1, MaxValue, MaxValue,1},
		{MaxValue, MaxValue,0,2,MaxValue,MaxValue},
		{MaxValue,3,MaxValue,0,MaxValue,MaxValue},
		{MaxValue, MaxValue, MaxValue,3,0,2},
		{MaxValue,MaxValue,MaxValue,2,MaxValue,0}
	};//�߼����ڽӾ���
	CreateMGraph_directed(&G, v, e, 6);

	EdgeData A[NumVertices][NumVertices]={0};
	int A1[NumVertices][NumVertices]={0};
	int P[NumVertices][NumVertices];
	
	Floyd(A, G, P, G.n);
	cout<<"ÿһ�Զ���֮������·��:"<<endl;
	for(i=0; i<G.n; i++)
	{
		for(int j=0; j<G.n; j++)
			cout<<A[i][j]<<'\t';
		cout<<endl;
	}
	cout<<"��ͨ�ڵ�֮���·�����Լ��м�ڵ�: "<<endl;
	for(i=0; i<G.n; i++)
		for(j=0; j<G.n; j++)
		{
			if(A[i][j]<MaxValue)
			{
				cout<<G.vexlist[i]<<"->"<<G.vexlist[j]<<", ���·������: "<<A[i][j]<<", �м���"<<':'<<endl;;		
				Path(P, i, j);
			}
		}
//�󴫵ݱհ�
	Warshall(A1, G, G.n);
	cout<<"\n���ݱհ�Ϊ:"<<endl;
	for(i=0; i<G.n; i++)
	{
		for(int j=0; j<G.n; j++)
			cout<<A1[i][j]<<'\t';
		cout<<endl;
	}
//�����Ľڵ�
	CenterPoint(A, G.n, cp);
	cout<<"\n\n���ĵ�Ϊ: "<<G.vexlist[cp+1]<<endl;

}
