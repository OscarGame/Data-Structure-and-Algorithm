//�ڽӾ����ʾ��������������������������
#include<iostream>
using namespace std;
#define NumVertices 6//���嶥�����

typedef char VertexData;//������������
typedef int EdgeData;//����Ȩֵ����

typedef struct{
 VertexData vexlist[NumVertices];//��������
EdgeData edge[NumVertices][NumVertices];//�ڽӾ���
int n;//������
int e;//����
} MTGraph;//�ڽӾ����ʾ��ͼ�ṹ������������ͼ

void IniMGraph(MTGraph *G)//��ʼ���ڽӾ����ͼ�ṹ
{
	for(int i=0; i<NumVertices; i++)
		for(int j=0; j<NumVertices; j++)
			G->edge[i][j]=0;//�����еı�ɾ��
	G->n=0;
	G->e=0;
}

void NewNode(MTGraph *G, VertexData v)//������Ӷ���v������ӱ�
{
	G->vexlist[G->n]=v;
	G->n++;
	
}

void DelNode(MTGraph *G, int m)//ɾ����m������
{
	int i, j;
	if(G->n==0 || m>=NumVertices)//û�ж���||�����ڶ���m
		return;
	for(i=m; i<G->n-1; i++)//����m����Ķ���ǰ��
		G->vexlist[i]=G->vexlist[i+1];

	//ɾ�����m�����������ı�
	//ɾ������
	for(i=0; i<G->n; i++)
	{
		if(G->edge[i][m]!=0)
			G->e--;
	}
	//�ڽӾ��󽵽�
	for(i=m; i<G->n-1; i++)
		for(j=0; j<G->n; j++)
			G->edge[i][j]=G->edge[i+1][j];

	for(i=m; i<G->n-1; i++)
		for(j=0; j<G->n-1; j++)
			G->edge[j][i]=G->edge[j][i+1];
    //����������
	G->n--;
}
//�ж�v1��v2֮����û�б�
bool IsEdge(MTGraph *G, int v1, int v2)
{
	if(v1>=0 && v1<G->n && v2>=0 && v2<G->n && v1!=v2)
		if(G->edge[v1][v2]!=0)
			return true;
		else
			return false;
	return false;
}
//�ڶ���v1��v2֮�佨��һ����
void SetSucc(MTGraph *G, int v1, int v2, EdgeData w)
{	
	if(!IsEdge(G, v1, v2))
	{
		G->edge[v1][v2]=w;	
		G->edge[v2][v1]=w;
		G->e++;
	}	
}

//ɾ��v1��v2֮��ı�
void DelSucc(MTGraph *G, int v1, int v2)
{
	if(IsEdge(G, v1, v2))
	{
		G->edge[v1][v2]=0;
		G->edge[v2][v1]=0;
		G->e--;
	}	
}

//�û���������ͼ
void CreateMGraph (MTGraph *G) 	
{   
	int i, j, k, w;
	cout<<"���붥�����ͱ���:";
	cin>>G->n>>G->e;				

	cout<<"���붥����ַ�:";
	for (i=0; i<G->n; i++) 			
		cin>>G->vexlist[i];
    //��ʼ���ڽӾ���
	for (i=0; i<G->n; i++)
		for (j=0;j<G->n;j++)
			G->edge[i][j]=0; 
		
	for (k=0; k<G->e; k++) {		
		cout<<"����һ���ߵ���������ͱߵ�Ȩֵ: "<<endl;
		cin>>i>>j>>w;			
		G-> edge[i][j]=w;
		G-> edge[j][i]=w;
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
//��ʾ����ͼ
void PrintMT(MTGraph *G)
{
	cout<<'\t';
	//�������
	for(int i=0; i<G->n; i++)
	{
		cout<<G->vexlist[i]<<'\t';
	}
	cout<<endl;
	//���ÿ����������ӹ�ϵ
	for(i=0; i<G->n; i++)
	{
		cout<<G->vexlist[i]<<'\t';	
		for(int j=0; j<G->n; j++)
			cout<<G->edge[i][j]<<'\t';
		cout<<endl;
	}
}
//=====================================================================
//���е�ָ��ʵ��

#define maxlength 20
typedef int que_elementtype;//����Ԫ������

//����Ԫ�ؽڵ�����
struct celltype {
	que_elementtype element;
	celltype *next;
};
//���нṹ��
struct QUEUE {
	celltype *front;
	celltype *rear;
};
//���л�������
void MAKENULL( QUEUE &Q )
{
	Q.front = new celltype ;
	Q.front->next = NULL ;
	Q.rear = Q.front ;//����Ϊ��
}

bool EMPTY( QUEUE &Q )//�ж��Ƿ�Ϊ��
{ 
	if ( Q.front == Q.rear )
		return true ;
	else
		return false ;
}

celltype *FRONT(QUEUE Q)//���ص�һ��Ԫ�ؽڵ�
{
	if(Q.front==Q.rear)
		return NULL;
	else
		return Q.front->next;
}

void ENQUEUE ( que_elementtype x, QUEUE &Q )//��x�����β
{ 
	Q.rear->next = new celltype ;
	Q.rear = Q.rear->next ;
	Q.rear->element = x ;
	Q.rear->next = NULL ;
}

void DEQUEUE ( QUEUE &Q )//ɾ�����еĵ�һ��Ԫ��
{ 
	celltype *temp ;//��ʱԪ�ؽڵ�
	if ( EMPTY( Q ) )
		cout<<"����Ϊ��"<<endl ;
	else { 
		temp = Q.front->next ;
		Q.front->next = temp->next ;//��ͷ�ڵ�ָ��ڶ���Ԫ�ؽڵ�
		delete temp ;//ɾ����һ��Ԫ�ؽڵ�
	
		if ( Q.front->next == NULL )//����Ϊ��ʱ��rear��λ
			Q.rear = Q.front ; 
	}
}
//===============================================================
bool visited[NumVertices];//���ʱ��������ȫ�ֱ���
int dfn[NumVertices]; //�����������

void DFS2(MTGraph *G, int i);//����

void DFSTraverse(MTGraph G)
//��������һ�ڽӱ��ʾ��ͼG�������ڽӾ����ʾGʱ���㷨��ȫ��ͬ.
{   
	int i , count = 1;
    for ( i = 0; i < G.n; i++ )
        visited [i] =false; 		//��־�����ʼ����false��ʾnew
    for ( i = 0; i < G.n; i++ )
        if ( ! visited[i] )
            DFS2( &G, i ); //�Ӷ���i ������ʼ����search() DFSX(G, i )
}

void DFS2(MTGraph *G, int i)//��viΪ��������ڽӾ����ʾ��ͼG���������������
{ 
    int j;
	static int count=0;
    cout<<G->vexlist[i]; 	//���ʶ���vi
    visited[i]=true; 	//���vi�ѷ���
    dfn[i]=count; 		//��vi���б��
    count ++; 		//��һ������ı��
    for( j=0; j<G->n; j++) 	//��������vi���ڽӵ�
        if((G->edge[i][j] == 1) && !visited[j] ) 	//��vj��δ����
            DFS2( G, j );
}//DFS2

//�����������
//bool visited[NumVertices]; 	//���ʱ��������ȫ�ֱ���
int bfn[NumVertices]; 			//�����������

void BFS2 (MTGraph *G, int k)	//����û�н����ȹ���
{   
	int i , j; 
	QUEUE Q; 
	MAKENULL(Q);
    cout << G->vexlist[ k ]; 		//����vk
    visited[ k ] = true; 			//��vk�����ʹ����
    ENQUEUE (k, Q); 				// vk������

    while ( ! EMPTY (Q) )			//�ӿ�ʱ��������
	{ 		
        i=FRONT(Q)->element;
		DEQUEUE(Q); 				//vi����
        for(j=0; j<G->n; j++) { 	//��������vi���ڽӵ�vj
            if ( G->edge[ i ][ j ] ==1 && !visited[ j ]) //��vjδ���ʹ�
			{ 	
                cout << G->vexlist[ j ];		//����vj
				visited[j]=true; 				//��vj�����ʹ����
				ENQUEUE( j , Q ); 				//���ʹ���vj���
            }
        } 		//�ظ����vi�������ڽӶ���
    } 			//���ѭ�����ж��пշ�
} 				//��vkΪ������ʱ�����ڽӾ����ʾ��ͼG�����ȹ�����

void main()
{
	MTGraph G;
	IniMGraph(&G);
	VertexData v[6]={'v1', 'v2', 'v3', 'v4', 'v5','v6'};
	EdgeData e[6][NumVertices]={{0, 1, 0, 1, 0, 1},{1, 0, 1, 1, 1, 0},{0, 1, 0, 0, 1, 0},{1, 1, 0, 0, 1, 1},{0, 1, 1, 1, 0, 0},{1, 0, 0, 1, 0, 0}};
	CreateMGraph(&G, v, e, 6);
	PrintMT(&G);
	cout<<endl;
	cout<<"�������������"<<endl;
	DFSTraverse(G);
	cout<<endl;
	cout<<"�������������"<<endl;
	BFS2(&G,1);
	cout<<endl;
}