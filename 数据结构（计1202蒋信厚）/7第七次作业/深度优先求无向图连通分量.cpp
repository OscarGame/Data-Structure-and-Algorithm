#include<iostream.h>
#define NumVertices 6
#define NumEdges  8
typedef char VertexData;//��������
typedef int EdgeData;//��Ȩֵ����

typedef struct{
    VertexData vexlist[NumVertices];//���㼯
    EdgeData edge[NumVertices][NumVertices];
    int n;
	int e;
} MTGraph;

bool visited[NumVertices];
int dfn[NumVertices];//������ȱ��

//�������������ͨ����
void DFS2(MTGraph *G, int i)//�ӵ�i�����㿪ʼ����
{
	int count = 0;//���ֵ
    cout << G->vexlist[i];//���
    visited[i]=true;
    dfn[i]=count;//���
    count++;
    for( int j=0; j<G->n; j++)
        if((G->edge[i][j]) && !visited[j] )//�б���δ����
            DFS2( G, j );//�ݹ�
}
void DFSTraverse(MTGraph G)//������ȱ���
{   
    for ( int i = 0; i < G.n; i++ ) 
		visited [i] = false;//��ʼ���������״̬
    int count = 0;
    for ( i = 0; i < G.n; i++ )
        if ( ! visited[i] ){
             count++;
             cout << count << ":";
             DFS2( &G, i );
        }
}

//��̨Ĭ��ֱ�Ӵ���
void CreateMGraph(MTGraph *G, VertexData V[], EdgeData E[][NumVertices], int n)
{
	int i, j;	
	G->n=n;
	for (i=0; i<n; i++) 			
		G->vexlist[i]=V[i];

	for (i=0; i<G->n; i++)
		for (j=0;j<G->n;j++)
			G->edge[i][j]=0; 		
	for(i=0; i<n; i++)				
		for(j=i; j<n; j++)
		{		
			if(E[i][j]!=0)
			{
				G-> edge[i][j]=E[i][j];
				G-> edge[j][i]=E[i][j];
				G->e++;
			}
		}
}

void main()
{
	//����ͼ
	MTGraph G;
    //�����Ȩֵ����
    EdgeData e[NumEdges][NumVertices];
    //���붥�����
	cout<<"�����붥�������"<<endl;
	int n;
    cin >> n;
	//����Ȩֵ
	cout<<"�밴���������Ȩֵ��"<<endl;
    for (int i = 0; i < n; i++ )
        for ( int j = 0; j < n; j++ )
            cin >> e[i][j];	
    //���㼯
    VertexData v[NumEdges];
    for ( i = 0; i < n; i++ )
        v[i] = 'a' + i;	
	CreateMGraph(&G, v, e, n);
	DFSTraverse(G);
	cout<<endl;	
}