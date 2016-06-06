#ifndef _ADJGRAPH_H_
#define _ADJGRAPH_H_

#include "index.h"

#ifdef _ADJGRAPH_

#define NumVertices 10 			//�������
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

// ���º�������������ͼ
void CreateADJGraph(AdjGraph *G); 				//����ͼ
void CreateADJGraph(AdjGraph *G, VertexData [], EdgeData [][NumVertices], int n); //�Ӹ�����ͼ�ľ����ʾ����ͼ��nΪ����ĸ���
void DelNode(AdjGraph *, int m);				//ɾ����m������
BOOLEAN SetSucc(AdjGraph *G, int v1, int v2, EdgeData w);   // ����v1��v2֮���һ����,Ȩ��Ϊw
void DelSucc(AdjGraph *G, int v1, int v2);		// ɾ��v1��v2֮���һ����
BOOLEAN IsEdge(AdjGraph *G, int v1, int v2);	// �ж�v1��v2֮���Ƿ��б�����

// ���º�������������ͼ
void CreateADJGraph_directed(AdjGraph *G); 				//����ͼ
void CreateADJGraph_directed(AdjGraph *G, VertexData [], EdgeData [][NumVertices], int n); //�Ӹ�����ͼ�ľ����ʾ����ͼ��nΪ����ĸ���
void DelNode_directed(AdjGraph *, int m);				//ɾ����m������
BOOLEAN SetSucc_directed(AdjGraph *G, int v1, int v2, EdgeData w);   // ����v1��v2��һ����,Ȩ��Ϊw
void DelSucc_directed(AdjGraph *G, int v1, int v2);		// ɾ��v1��v2��һ����
BOOLEAN IsEdge_directed(AdjGraph *G, int v1, int v2);	// �ж�v1��v2�Ƿ��б�����

//���º�������������ͼ������ͼ
void IniADJGraph(AdjGraph *);						// ��ʼ��ͼ
BOOLEAN NewNode(AdjGraph *, VertexData);			// ����һ������
void PrintADJ(AdjGraph *G);

#endif

#endif