#ifndef _MTGRAPH_H_
#define _MTGRAPH_H_

//#include "index.h"

#ifdef _MTGRAPH_	

#define NumEdges 50 			//����
//#define NumVertices 10 			//�������

typedef char VertexData; 		//������������
typedef int EdgeData;			//����Ȩֵ����

typedef struct{
    VertexData vexlist[NumVertices]; 	//�����
    EdgeData edge[NumVertices][NumVertices];
            		//�ڽӾ��󡪱߱�, ����Ϊ��֮��Ĺ�ϵ
    int n;			//ͼ�е�ǰ�Ķ������
	int e; 			//ͼ�е�ǰ�ı���
} MTGraph;

// ���º�������������ͼ
void CreateMGraph (MTGraph *G); 			//����(����)ͼ���ڽӾ���
void CreateMGraph(MTGraph *G, VertexData [], EdgeData [][NumVertices], int n);   // ͨ�����������鹹������ͼ��nΪ����ĸ���
void IniMGraph(MTGraph *);					// ��ʼ��ͼ
void NewNode(MTGraph *, VertexData);  // ����һ������,(����)ͼ
void DelNode(MTGraph *, int m);				//ɾ����m������,(����)ͼ
void SetSucc(MTGraph *G, int v1, int v2, EdgeData w);   // ����v1��v2֮���һ����,Ȩ��Ϊw
void DelSucc(MTGraph *G, int v1, int v2);   // ɾ��v1��v2֮���һ����,Ȩ��Ϊw
BOOLEAN IsEdge(MTGraph *G, int v1, int v2); // �ж�v1��v2֮���Ƿ��б�����


// ���º�������������ͼ

void CreateMGraph_directed (MTGraph *G); 			//����ͼ���ڽӾ���
void CreateMGraph_directed(MTGraph *G, VertexData [], EdgeData [][NumVertices], int n);   // ͨ�����������鹹������ͼͼ��nΪ����ĸ���
void IniMGraph_directed(MTGraph *);					// ��ʼ��ͼ
void NewNode_directed(MTGraph *, VertexData);  // ����һ������,����ͼ
void DelNode_directed(MTGraph *, int m);				//ɾ����m������,����ͼ
void SetSucc_directed(MTGraph *G, int v1, int v2, EdgeData w);   // ����v1��v2֮���һ����,Ȩ��Ϊw
void DelSucc_directed(MTGraph *G, int v1, int v2);   // ɾ��v1��v2֮���һ����,Ȩ��Ϊw
BOOLEAN IsEdge_directed(MTGraph *G, int v1, int v2); // �ж�v1��v2֮���Ƿ��б�����


// ���º���ʹ��������ͼ������ͼ
void PrintMT(MTGraph *G);



#endif

#endif