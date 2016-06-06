#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#include "index.h"

#ifdef _HUFFMAN_

#define n 5  // Ҷ����
#define m 2*(n)-1   // �������

typedef struct{
	double weight;   // Ȩֵ
	int lchild;
	int rchild;
	int parent;
}HTNODE;

typedef HTNODE HuffmanT[m];  // ���������ľ�̬���������ʾ


void SelectMin(HuffmanT , int, int &, int &);
void CreatHT(HuffmanT);
void InitHT(HuffmanT);


#endif 
#endif