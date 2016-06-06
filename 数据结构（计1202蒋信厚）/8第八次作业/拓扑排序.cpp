//��������
#include<iostream>
#include<String>
using namespace std;

#define freever "#"
#define NumVertices 9 			//�������
typedef string VertexData; 		//������������
typedef int EdgeData; 			//����Ȩֵ����
//ͼ���ڽӱ��ʾ
//�߱���
typedef struct node { 
    int adjvex; 				//�ڽӵ���(�±�)������һ������±�
    EdgeData cost; 				//���ϵ�Ȩֵ
    node *next; 			//��һ������ָ��
} EdgeNode;
//�������
typedef struct { 
    VertexData vertex; 			//����������
    EdgeNode * firstedge; 		//������ͷָ��
} VertexNode;
//ͼ���ڽӱ�
typedef struct { 
    VertexNode vexlist[NumVertices+1];//vexlist[0]����
	int indegree[NumVertices+1];//������ȼ���,indegree[0]����
    int n, e; 				//ͼ�е�ǰ�Ķ�����������
} AdjGraph;

void InitADJGraph(AdjGraph *G)	//��ʼ��ͼ					
{
	G->e=0;
	G->n=0;
	for(int i=1; i<NumVertices; i++)
	{
		G->vexlist[i].vertex=freever;
		G->vexlist[i].firstedge=NULL;
		G->indegree[i]=0;//��ʼ����ȶ�Ϊ��
	}
}
bool NewNode(AdjGraph *G, VertexData v)// ����һ�����㣬����ӱߣ��ɹ�������true�����򷵻�false	
{
	if(G->n<NumVertices-1)
	{
		for(int i=1; i<NumVertices; i++)
		{
			if(G->vexlist[i].vertex==freever)
			{
				G->vexlist[i].vertex=v;
				G->vexlist[i].firstedge=NULL;
				G->n++;
				return true;
			}
		}
	}	
	return false;
}
bool IsEdge(AdjGraph *G, int v1, int v2)	// �ж�v1��v2֮���Ƿ��б�����
{
		EdgeNode *p=G->vexlist[v1].firstedge;
		if(p==NULL)
			return false;
		while(1)  
		{
			if(p->adjvex==v2)
			{
				return true;
			}
			p=p->next;
			if(p==NULL)
				return false;
		}
		return false;
}
void DelSucc(AdjGraph *G, int v1, int v2)		// ɾ��v1��v2֮���һ����
{
	if(IsEdge(G, v1, v2))   // v1��v2��Ϊ���㣬��֮����ڱ�
	{
		EdgeNode *p=G->vexlist[v1].firstedge, *p1;
		if(p->adjvex==v2)
		{
			p1=p;
			G->vexlist[v1].firstedge=p->next;
			G->e--;
			delete p1;
		}
		else
		{
			do
			{
				p1=p->next;
				if(p1==NULL)
					break;
				if(p1->adjvex==v2)
				{
					p->next=p1->next;
					delete p1;
					G->e--;
				}
				p=p->next;
			}while(p!=NULL);
		}
	}
}
void DelNode(AdjGraph *G, int m)				//ɾ����m������
{
	if(G->vexlist[m].vertex!=freever)			//�����m���������
	{
		G->vexlist[m].vertex=freever;
		EdgeNode *p=G->vexlist[m].firstedge;
		while(p!=NULL)      // ɾ�����m�����������ı�
		{
			DelSucc(G, m, p->adjvex);
			p=G->vexlist[m].firstedge;
		}
		G->vexlist[m].firstedge=NULL;

		// ɾ����������ָ���m������ı�
		for(int i=1; i<NumVertices; i++)
		{
			if(G->vexlist[i].vertex!=freever)
			{
				p=G->vexlist[i].firstedge;
				while(p!=NULL)
				{
					if(p->adjvex==m)
					{
						DelSucc(G, i, m);
						break;
					}
					p=p->next;
				}
			}
		}
	}
}
bool SetSucc(AdjGraph *G, int v1, int v2, EdgeData w)   // ����v1��v2֮���һ����,Ȩ��Ϊw
{
	if(G->vexlist[v1].vertex!=freever && G->vexlist[v2].vertex!=freever )   // v1��v2��Ϊ����
	{
		EdgeNode *p=G->vexlist[v1].firstedge;
		if(IsEdge(G, v1, v2))    //�ж�v1��v2֮���Ƿ���ڱߣ������ڣ���ɾ���ñ�
			DelSucc(G, v1, v2);

		//Ϊ����v1��v2���ӱ�
		p = new EdgeNode; 		
        p->adjvex = v2;				
		p->cost = w; 	
        p->next = G->vexlist[v1].firstedge;
        G->vexlist[v1].firstedge = p;		
		
		G->e++;    // ������1
		return true;
	}
	return false;
}



void CreateADJGraph(AdjGraph *G)
{   
	cout<<"���붥�����ͱ���: ";
	cin >> G->n >> G->e; 					//1.���붥������ͱ���
    for ( int i = 1; i <= G->n; i++)			//2.���������
	{ 		
		cout<<"����� "<<i<<" ��������Ϣ: ";
        cin >> G->vexlist[i].vertex; 		//2.1���붥����Ϣ
        G->vexlist[i].firstedge = NULL;		//2.2�߱���Ϊ�ձ�
	}	
    for ( i = 1; i <= G->e; i++)				//3.����������,�����߱�
	{ 		
		int tail, head;
		EdgeData weight;

		cout<<"����� "<<i<<" ���ߵ���ʼ�㡢��ֹ���Լ�Ȩ��: ";
        cin >> tail >> head >> weight; 		//3.1����
        
		EdgeNode * p = new EdgeNode; 		//3.2�����߽��
        p->adjvex = head;					//3.3���ñ߽��
		p->cost = weight; 	
        p->next = G->vexlist[tail].firstedge; 	//3.4�����tail �������ǰ��
        G->vexlist[tail].firstedge = p;       
	}
}		 //ʱ�临�Ӷȣ�O(2e+n)

void CreateADJGraph(AdjGraph *G, VertexData V[], EdgeData E[][NumVertices], int n) //�Ӹ�����ͼ�ľ����ʾ����ͼ��nΪ����ĸ���
{
	G->n=n;
	for ( int i = 1; i <= n; i++)			//2.���������
	{ 		
		G->vexlist[i].vertex=V[i-1]; 		//2.1���붥����Ϣ
        G->vexlist[i].firstedge = NULL;		//2.2�߱���Ϊ�ձ�
	}	
    for ( i = 1; i <=n; i++)				//3.����������,�����߱����ڶԳ��ԣ�ֻ�����ϰ��������
		for(int j=1; j<=n; j++)
		{ 		
		    if(E[i-1][j-1]!=0)
			{
				EdgeNode * p = new EdgeNode; 		//3.2�����߽��
				p->adjvex = j;					//3.3���ñ߽��
				p->cost = E[i-1][j-1]; 	
				p->next = G->vexlist[i].firstedge; 	//3.4�����tail �������ǰ��
				G->vexlist[i].firstedge = p;        
				G->e++;
			}
		}
}

void PrintADJ(AdjGraph *G)
{
	EdgeNode * p;
	int i, j;
	EdgeData result[NumVertices][NumVertices]={0};
	VertexData ver[NumVertices];
	cout<<'\t';
	for(i=1; i<=NumVertices; i++)
	{
		cout<<G->vexlist[i].vertex<<'\t';
		ver[i]=G->vexlist[i].vertex;
	}
	cout<<endl;	
	for(i=1; i<NumVertices; i++)
	{	
		p=G->vexlist[i].firstedge;
		while(p!=NULL)
		{
			result[i][p->adjvex]=p->cost;
			p=p->next;
		}
	}
	for(i=1; i<=NumVertices; i++)
	{
		cout<<ver[i]<<'\t';
		for(j=1; j<=NumVertices; j++)
		{
			cout<<result[i][j]<<'\t';
		}
		cout<<endl;
	}
	cout<<endl;
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
//�ö���ʵ�ֵ���������
void topoOrder(AdjGraph *G)
{
	celltype *t;
	int v,w;
	int nodeCount=0;//�������˽ڵ�
	QUEUE Q;
	MAKENULL(Q);
	for(v=1;v<=G->n;v++)//���������Ϊ0�Ķ������
	{
		if(G->indegree[v]==0)
			ENQUEUE(v,Q);
	}

	while(!EMPTY(Q))
	{
		t = FRONT(Q);//���׳��Ӳ�ɾ��
		v=t->element;
		DEQUEUE(Q);
		cout<<G->vexlist[v].vertex<<'\t';//���˹��������������Ķ���
		nodeCount++;
		//�����ڽ���v���������㣬ͬ�����Ϊ������
		for(w=1;w<=G->n;w++)
		{
			if(IsEdge(G,v,w))
			{
				--G->indegree[w];
				if(G->indegree[w] == 0)
					ENQUEUE(w,Q);
			}

		}
	}
	cout<<endl;
	if(nodeCount<G->n)
		cout<<"�������ͼ�л�·��"<<endl;

}
void main()
{
	AdjGraph G;
	InitADJGraph(&G);
	VertexData v[9]={"v1", "v2", "v3", "v4", "v5","v6","v7", "v8","v9"};//����
	EdgeData e[9][NumVertices]={
		{0,1,1,0,0,0,0,0,0},
		{0,0,0,1,1,0,0,0,0},
		{0,0,0,0,1,1,0,0,0},
		{0,0,0,0,0,0,1,1,0},
		{0,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,1,0},
		{0,0,0,0,0,0,0,1,0},
		{0,0,0,0,0,0,0,0,1},
		{0,0,0,0,0,0,0,0,0}
	};
	CreateADJGraph(&G, v, e, 9);//��������ͼ
	cout<<"��������"<<endl;
	topoOrder(&G);
  }
