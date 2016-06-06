//Dijikstra�㷨������ͼ�ĵ�Դ���·���Լ�ÿһ�Զ���֮������·��
#include<iostream>
#include<string>
using namespace std;
#define MaxValue 1000//�˴���1000��ʾ�����
enum BOOLEAN{FALSE, TRUE};
//�˳����е�ͼ�����ڽӾ����ʾ
#define NumEdges 50 			//����
#define NumVertices 6			//�������

typedef string VertexData; 		//������������
typedef int EdgeData;			//����Ȩֵ����

typedef struct{
    VertexData vexlist[NumVertices]; 	//�����
    EdgeData edge[NumVertices][NumVertices];
            		//�ڽӾ��󡪱߱�, ����Ϊ��֮��Ĺ�ϵ
    int n;			//ͼ�е�ǰ�Ķ������
	int e; 			//ͼ�е�ǰ�ı���
} MTGraph;

void IniMGraph_directed(MTGraph *G)//��ʼ������ͼ
{
	for(int i=0; i<NumVertices; i++)
		for(int j=0; j<NumVertices; j++)
			G->edge[i][j]=MaxValue;
	G->n=0;
	G->e=0;
}
//��������ͼ
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
//�������ͼ���ڽӾ���
void PrintMT(MTGraph *G)
{
	cout<<'\t';
	for(int i=0; i<G->n; i++)
	{
		cout<<G->vexlist[i]<<'\t';
	}
	cout<<endl;
	for(i=0; i<G->n; i++)
	{
		cout<<G->vexlist[i]<<'\t';	
		for(int j=0; j<G->n; j++)
			cout<<G->edge[i][j]<<'\t';
		cout<<endl;
	}
}
//��V-S��ʹD[w]��С��wֵ
int mincost(EdgeData D[NumVertices], BOOLEAN S[NumVertices], int n)
{   
	int w;
	EdgeData temp =MaxValue ;  //��MaxValue��ʾ�����
	w=0;
    for (int i=1 ; i<n ; i++ )
		if (!S[i] && D[i]<temp)//����D[]����С��δ����S�еĶ����Ȩ
		{   
			temp = D[i] ;
            w = i ;
        }
    return w ;
}

// ��Դ���·��-Dijkstra�㷨
void Dijkstra(MTGraph G, EdgeData D[NumVertices], int P[NumVertices])
//D[]��¼Դ�㵽��������㵱ǰ�����·������
{
	BOOLEAN S[NumVertices]={FALSE};//��Ƕ����Ƿ��Ѿ�ȷ�����·����ȷ���ı��ΪTRUE
	int i, v, w;
	EdgeData sum;

    D[0]=MaxValue;//�����һ��λ�ñ�ʾԴ�㵽����ľ��룬��ʼ��Ϊ����
//��ʼ��Ϊ��̬�����㷨�涨��һ������ΪԴ��
	for ( i=1 ; i<G.n; i++ )
    { 
		D[i]=G.edge[0][i] ; 
		S[i]=FALSE ; 
	}
    S[0]= TRUE;//��̬��Դ�����S��
    for(i=1; i<G.n; i++)
    {   
		w=mincost ( D, S, G.n );
        S[w]=TRUE ;//��w����S��
        for ( v=1 ; v<G.n ; v++ )
            if ( S[v]!=TRUE && G.edge[w][v]!=MaxValue)//����vδ���ʹ����Ҷ���v-w֮���б�
            { 
				sum=D[w] + G.edge[w][v] ;
                if (sum < D[v] ) 
					D[v] = sum ; 
				P[v]=w; //�������·����v��ֱ��ǰ�����
			}
   } 
}
/*
void Path(int P[],VertexData v[],int input)//���Դ�㵽����input�����·��
{
	cout<<"Դ�㵽����<<v[input]<<�����·��Ϊ��"<<endl;
	for(int i=0;P[i]!=input;i++)
	{
		cout<<v[P[i]]<<"-->";
	}
	cout<<v[v]<<endl;
}
*/
void main()
{
	MTGraph G;
	IniMGraph_directed(&G);
	VertexData v[6]={"v1", "v2", "v3", "v4", "v5" , "v6"};//��������
	EdgeData e[6][NumVertices]={
		{0,45,15,MaxValue,15,MaxValue},
		{MaxValue,0,MaxValue,20,15,15},
		{10,10,0,60,MaxValue,MaxValue},
		{MaxValue,30,MaxValue,0,MaxValue,20},
		{MaxValue,MaxValue,MaxValue,MaxValue,0,MaxValue},
		{MaxValue,MaxValue,MaxValue,MaxValue,MaxValue,0}
	};//�ڽӾ���
	CreateMGraph_directed(&G, v, e, 6);//����
	cout<<"����ͼ���ڽӾ���"<<endl;
	PrintMT(&G);
	cout<<endl;
	EdgeData D[6]; //��¼Դ�㵽��������㵱ǰ�����·������
	int P[6]={0};//P[v]�Ǽ�¼���·���ϵĶ���v֮ǰ�Ķ���
	Dijkstra(G, D, P);
	cout<<"��Դ���·�����ȣ�";
	for(int i=1; i<6; i++)
		cout<<D[i]<<'\t';
	cout<<endl;
	cout<<"�����㷨�Ľ���D[w]�䶯ʱ����D[w]��·�߱䶯�����"<<endl;
	for(i=1; i<6; i++)
		cout<<G.vexlist[P[i]]<<"->"<<G.vexlist[i]<<endl;
	cout<<endl;
}
