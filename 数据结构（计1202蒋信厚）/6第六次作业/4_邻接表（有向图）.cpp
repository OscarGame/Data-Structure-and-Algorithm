//�ڽӱ��ʾ��
#include<iostream>
using namespace std;

#define freever '#'
#define NumVertices 4 			//�������
typedef char VertexData; 		//������������
typedef int EdgeData; 			//����Ȩֵ����

typedef struct node { 			//�߱���
    int adjvex; 				//�ڽӵ���(�±�)
    EdgeData cost; 				//���ϵ�Ȩֵ
    struct node *next; 			//��һ������ָ��
} EdgeNode;

typedef struct { 				//�������
    VertexData vertex; 			//����������
    EdgeNode * firstedge; 		//������ͷָ��
} VertexNode;

typedef struct { 				//ͼ���ڽӱ�
    VertexNode vexlist[NumVertices+1];
    int n, e; 				//ͼ�е�ǰ�Ķ�����������
} AdjGraph;

bool IsEdge_directed(AdjGraph *G, int v1, int v2)// �ж�v1��v2֮���Ƿ��б�����	
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

void DelSucc_directed(AdjGraph *G, int v1, int v2)		// ɾ��v1��v2֮���һ����
{
	if(IsEdge_directed(G, v1, v2))   // v1��v2��Ϊ���㣬��֮����ڱ�
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

void DelNode_directed(AdjGraph *G, int m)				//ɾ����m������
{
	if(G->vexlist[m].vertex!=freever)			//�����m���������
	{
		G->vexlist[m].vertex=freever;
		EdgeNode *p=G->vexlist[m].firstedge;
		while(p!=NULL)      // ɾ�����m�����������ı�
		{
			DelSucc_directed(G, m, p->adjvex);
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
						DelSucc_directed(G, i, m);
						break;
					}
					p=p->next;
				}
			}
		}
	}
}

bool SetSucc_directed(AdjGraph *G, int v1, int v2, EdgeData w)   // ����v1��v2֮���һ����,Ȩ��Ϊw
{
	if(G->vexlist[v1].vertex!=freever && G->vexlist[v2].vertex!=freever )   // v1��v2��Ϊ����
	{
		EdgeNode *p=G->vexlist[v1].firstedge;
		if(IsEdge_directed(G, v1, v2))    //�ж�v1��v2֮���Ƿ���ڱߣ������ڣ���ɾ���ñ�
			DelSucc_directed(G, v1, v2);

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

void CreateADJGraph_directed(AdjGraph *G)
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

void CreateADJGraph_directed(AdjGraph *G, VertexData V[], EdgeData E[][NumVertices], int n) //�Ӹ�����ͼ�ľ����ʾ����ͼ��nΪ����ĸ���
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
	for(i=1; i<NumVertices; i++)
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
	for(i=1; i<NumVertices; i++)
	{
		cout<<ver[i]<<'\t';
		for(j=1; j<NumVertices; j++)
		{
			cout<<result[i][j]<<'\t';
		}
		cout<<endl;
	}
	cout<<endl;
}
void main()
{
	/*
     cout<<"����ͼ:"<<endl;
	AdjGraph G1;
	IniADJGraph(&G1);
  	VertexData v1[4]={'v1', 'v2', 'v3', 'v4'};
	EdgeData e14][NumVertices]={{0, 1, 1, 0},
								{0, 0, 0, 0},
								{0, 0, 0, 1},
								{1, 0, 0, 0}};	          
	CreateADJGraph_directed(&G1, v1, e1, 4);
	cout<<G1.n<<' '<<G1.e<<endl;
	CreateADJGraph_directed(&G1);
	NewNode(&G1, 'v1');
	NewNode(&G1, 'v2');
	NewNode(&G1, 'v3');
	NewNode(&G1, 'v4');
	SetSucc_directed(&G1, 1, 2, 1);
	SetSucc_directed(&G1, 1, 4, 1);
	SetSucc_directed(&G1, 1, 5, 1);
	SetSucc_directed(&G1, 2, 3, 1);
	SetSucc_directed(&G1, 2, 4, 1);
	SetSucc_directed(&G1, 3, 4, 1);
	SetSucc_directed(&G1, 3, 5, 1);
	SetSucc_directed(&G1, 4, 5, 1);
	SetSucc_directed(&G1, 2, 4, 3);
	cout<<G1.n<<' '<<G1.e<<endl;
	DelSucc_directed(&G1, 3, 4);
	cout<<G1.n<<' '<<G1.e<<endl;
	DelNode_directed(&G1, 2);
	cout<<G1.n<<' '<<G1.e<<endl;
	PrintADJ(&G1);
	*/
}