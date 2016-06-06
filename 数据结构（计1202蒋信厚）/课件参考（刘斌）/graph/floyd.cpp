#include "mtgraph.h"

#ifdef _FLOYD_

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
} /* 时间复杂性O(n3) */

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

void Warshall(int A[NumVertices][NumVertices],MTGraph C,int n)
{
	int i, j, k;
	for ( i = 0; i < n; i++ )
        for ( j = 0; j<n; j++ )
		{
            if(C.edge[i][j]!=MaxValue/2)			
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
} /* 时间复杂性O(n3) */

void CenterPoint(EdgeData A[NumVertices][NumVertices], int n, int &cp)
{
	EdgeData E[NumVertices]={0};
	int min=MaxValue/2;
	for(int j=0; j<n; j++)
	{
		for(int i=0; i<n; i++)
			if(A[i][j]<MaxValue/2)
				E[j]+=A[i][j];
		if(E[j]==0)
			E[j]=MaxValue/2;
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
	
	VertexData v[5]={'a', 'b', 'c', 'd', 'e'};
	EdgeData e[5][NumVertices]={
								{MaxValue/2,       10, MaxValue/2,       30,      100},
								{MaxValue/2, MaxValue/2,       50, MaxValue/2, MaxValue/2},
								{MaxValue/2, MaxValue/2, MaxValue/2,       20,       10},
								{MaxValue/2, MaxValue/2,       20, MaxValue/2,       60},
								{MaxValue/2, MaxValue/2, MaxValue/2, MaxValue/2, MaxValue/2}};
	CreateMGraph_directed(&G, v, e, 5);

	EdgeData A[NumVertices][NumVertices]={0};
	int A1[NumVertices][NumVertices]={0};
	int P[NumVertices][NumVertices];
	
	Floyd(A, G, P, G.n);
	cout<<"每一对顶点之间的最短路径:"<<endl;
	for(i=0; i<G.n; i++)
	{
		for(int j=0; j<G.n; j++)
			cout<<A[i][j]<<'\t';
		cout<<endl;
	}
	cout<<"相通节点之间的路径长以及中间节点: "<<endl;
	for(i=0; i<G.n; i++)
		for(j=0; j<G.n; j++)
		{
			if(A[i][j]<MaxValue/2)
			{
				cout<<G.vexlist[i]<<"->"<<G.vexlist[j]<<", 最短路径长度: "<<A[i][j]<<", 中间结点"<<':'<<endl;		
				Path(P, i, j);
			}
		}

	Warshall(A1, G, G.n);

	cout<<"\n传递闭包为:"<<endl;
	for(i=0; i<G.n; i++)
	{
		for(int j=0; j<G.n; j++)
			cout<<A1[i][j]<<'\t';
		cout<<endl;
	}

	CenterPoint(A, G.n, cp);
	cout<<"\n\n中心点为: "<<G.vexlist[cp+1]<<endl;


}


#endif