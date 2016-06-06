#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#include "index.h"

#ifdef _HUFFMAN_

#define n 5  // 叶子数
#define m 2*(n)-1   // 结点总数

typedef struct{
	double weight;   // 权值
	int lchild;
	int rchild;
	int parent;
}HTNODE;

typedef HTNODE HuffmanT[m];  // 哈夫曼树的静态三叉链表表示


void SelectMin(HuffmanT , int, int &, int &);
void CreatHT(HuffmanT);
void InitHT(HuffmanT);


#endif 
#endif