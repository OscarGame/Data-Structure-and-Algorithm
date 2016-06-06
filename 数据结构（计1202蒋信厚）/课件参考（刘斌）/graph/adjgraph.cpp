#include "adjgraph.h"

#ifdef _ADJGRAPH_

VertexData freever='#';

void IniADJGraph(AdjGraph *G)						// ��ʼ��ͼ
{
	G->e=0;
	G->n=0;
	for(int i=1; i<NumVertices; i++)
	{
		G->vexlist[i].vertex=freever;
		G->vexlist[i].firstedge=NULL;		
	}
}

BOOLEAN NewNode(AdjGraph *G, VertexData v)		// ����һ�����㣬�ɹ�������TRUE�����򷵻�FALSE
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
				return TRUE;
			}
		}
	}
	
	return FALSE;
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

	}
}

BOOLEAN SetSucc(AdjGraph *G, int v1, int v2, EdgeData w)   // ����v1��v2֮���һ����,Ȩ��Ϊw
{
	if(G->vexlist[v1].vertex!=freever && G->vexlist[v2].vertex!=freever )   // v1��v2��Ϊ����
	{
		EdgeNode *p=G->vexlist[v1].firstedge;
		if(IsEdge(G, v1, v2))    //�ж�v1��v2֮���Ƿ���ڱߣ������ڣ���ɾ���ñ�
			DelSucc(G, v1, v2);

		//Ϊ����v1���ӱ�
		p = new EdgeNode; 		
        p->adjvex = v2;				
		p->cost = w; 	
        p->next = G->vexlist[v1].firstedge;
        G->vexlist[v1].firstedge = p;

		//Ϊ����v2���ӱ�
		p = new EdgeNode; 		
        p->adjvex = v1;				
		p->cost = w; 	
        p->next = G->vexlist[v2].firstedge;
        G->vexlist[v2].firstedge = p;
		
		G->e++;    // ������1
		return TRUE;
	}
	return FALSE;
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

		p=G->vexlist[v2].firstedge;
		if(p->adjvex==v1)
		{
			p1=p;
			G->vexlist[v2].firstedge=p->next;
			delete p1;
		}
		else
		{
			do
			{
				p1=p->next;
				if(p1==NULL)
					break;

				if(p1->adjvex==v1)
				{
					p->next=p1->next;
					delete p1;				
				}
				p=p->next;
			}while(p!=NULL);
		}

	}
}

BOOLEAN IsEdge(AdjGraph *G, int v1, int v2)	// �ж�v1��v2֮���Ƿ��б�����
{
		EdgeNode *p=G->vexlist[v1].firstedge;
		if(p==NULL)
			return FALSE;
		while(1)  
		{
			if(p->adjvex==v2)
			{
				return TRUE;
			}
			p=p->next;
			if(p==NULL)
				return FALSE;
		}
		return FALSE;
}

void CreateADJGraph (AdjGraph *G)
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
        
		p = new EdgeNode;
        p->adjvex = tail; 
		p->cost = weight;
        p->next = G->vexlist[head].firstedge; 	//�����head �������ǰ��
        G->vexlist[head].firstedge = p; 
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
		for(int j=i+1; j<=n; j++)
		{ 		
		    if(E[i-1][j-1]!=0)
			{
				EdgeNode * p = new EdgeNode; 		//3.2�����߽��
				p->adjvex = j;					//3.3���ñ߽��
				p->cost = E[i-1][j-1]; 	
				p->next = G->vexlist[i].firstedge; 	//3.4�����tail �������ǰ��
				G->vexlist[i].firstedge = p;
        
				p = new EdgeNode;
				p->adjvex = i; 
				p->cost = E[i-1][j-1];
				p->next = G->vexlist[j].firstedge; 	//�����head �������ǰ��
				G->vexlist[j].firstedge = p; 
				G->e++;
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

BOOLEAN SetSucc_directed(AdjGraph *G, int v1, int v2, EdgeData w)   // ����v1��v2֮���һ����,Ȩ��Ϊw
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
		return TRUE;
	}
	return FALSE;
}

void DelSucc_directed(AdjGraph *G, int v1, int v2)		// ɾ��v1��v2֮���һ����
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

BOOLEAN IsEdge_directed(AdjGraph *G, int v1, int v2)	// �ж�v1��v2֮���Ƿ��б�����
{
		EdgeNode *p=G->vexlist[v1].firstedge;
		if(p==NULL)
			return FALSE;
		while(1)  
		{
			if(p->adjvex==v2)
			{
				return TRUE;
			}
			p=p->next;
			if(p==NULL)
				return FALSE;
		}
		return FALSE;
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


#ifndef _DFS_
#ifndef _BFS_
#ifndef _AOV_

void main()
{/*		
	cout<<"����ͼ:"<<endl;
	AdjGraph G;
	IniADJGraph(&G);
	VertexData v[5]={'a', 'b', 'c', 'd', 'e'};
	EdgeData e[5][NumVertices]={{0, 1, 0, 1, 0},
								{1, 0, 1, 1, 1},
								{0, 1, 0, 1, 0},
								{1, 1, 1, 0, 1},
								{0, 1, 0, 1, 0}};
	
		          
	CreateADJGraph(&G, v, e, 5);
	cout<<G.n<<' '<<G.e<<endl;

	//CreateADJGraph(&G);

	NewNode(&G, 'a');
	NewNode(&G, 'b');
	NewNode(&G, 'c');
	NewNode(&G, 'd');
	NewNode(&G, 'e');

	cout<<G.n<<' '<<G.e<<endl;

	SetSucc(&G, 1, 2, 1);
	SetSucc(&G, 1, 4, 1);
	SetSucc(&G, 1, 5, 1);
	SetSucc(&G, 2, 3, 1);
	SetSucc(&G, 2, 4, 1);
	SetSucc(&G, 3, 4, 1);
	SetSucc(&G, 3, 5, 1);
	SetSucc(&G, 4, 5, 1);
	SetSucc(&G, 2, 4, 3);
	cout<<G.n<<' '<<G.e<<endl;

	DelSucc(&G, 3, 4);
	cout<<G.n<<' '<<G.e<<endl;

	DelNode(&G, 2);
	cout<<G.n<<' '<<G.e<<endl;

	PrintADJ(&G);
*/
	

	cout<<"����ͼ:"<<endl;
	AdjGraph G1;
	IniADJGraph(&G1);

  	VertexData v1[5]={'a', 'b', 'c', 'd', 'e'};
	EdgeData e1[5][NumVertices]={{0, 1, 0, 1, 0},
								{1, 0, 0, 1, 1},
								{0, 1, 0, 1, 0},
								{1, 0, 1, 0, 1},
								{0, 1, 0, 1, 0}};
	
		          
	CreateADJGraph_directed(&G1, v1, e1, 5);
	cout<<G1.n<<' '<<G1.e<<endl;
/*
	//CreateADJGraph_directed(&G1);
	
	NewNode(&G1, 'a');
	NewNode(&G1, 'b');
	NewNode(&G1, 'c');
	NewNode(&G1, 'd');
	NewNode(&G1, 'e');



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
*/
	PrintADJ(&G1);

}

#endif
#endif
#endif
#endif