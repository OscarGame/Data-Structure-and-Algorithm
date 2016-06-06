#include "heap.h"

#ifdef _HEAP_

//创建一个空堆
void MaxHeap(HEAP heap)
{
	heap.n=0;
}

//判断堆是否为空
BOOLEAN HeapEmpty(HEAP heap)
{
	if(!(heap.n))
		return TRUE;
	else
		return FALSE;
}

//判断堆是否为满
BOOLEAN HeapFull(HEAP heap)
{
	if(heap.n==Maxsize-1)
		return TRUE;
	else
		return FALSE;

}

//在堆heap中插入元素值为element的结点
void Insert(HEAP &heap, elementtype element)
{
	int i;
	if(!HeapFull(heap))
	{
		i=heap.n+1;
		while((i!=1) && (element.data>heap.elements[i/2].data))
		{
			heap.elements[i]=heap.elements[i/2];
			i/=2;
		}
		heap.n++;
		heap.elements[i]=element;
	}
	else
		return;
	
}

//删除堆中的最大元素
elementtype DeleteMax(HEAP &heap)
{
	int paraent=1, child=2;
	elementtype element, tmp;
	if(!HeapEmpty(heap))
	{
		element=heap.elements[1];
		tmp=heap.elements[heap.n--];
		while(child<=heap.n)
		{
			if((child<heap.n) && (heap.elements[child].data <heap.elements[child+1].data ))
				child++;
			if(tmp.data>=heap.elements[child].data )
				break;
			heap.elements[paraent]=heap.elements[child];
			paraent=child;
			child*=2;
		}
		heap.elements[paraent]=tmp;	

		return element;
	}
}

void main()
{
	HEAP H;
	elementtype element;
	int data[]={1, 3, 5, 7, 9, 11, 13};
	H.n=0;
	for(int i=0; i<7; i++)
	{
		element.key=i+1;
		element.data=data[i];
		Insert(H, element);
	}

	for(i=1; i<=H.n; i++)
		cout<<H.elements[i].data<<' ';
	cout<<endl;

	DeleteMax(H);
	for(i=1; i<=H.n; i++)
		cout<<H.elements[i].data<<' ';
	cout<<endl;	

}

#endif