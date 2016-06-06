//最大堆是完全二叉树
#include<iostream.h> 
#define Maxsize 200 //最大堆的容量+1

typedef struct
{
     int data;
}elementtype;

typedef struct
{ 
    elementtype elements[Maxsize];
	int n;//元素个数
}HEAP;

void MaxHeap(HEAP &heap) //创建一个空堆
{ 
	heap.n = 0; 
} 

bool HeapEmpty(HEAP heap) //判断堆是否为空 
{  
	if ( !(heap.n) )
		return true;
	else
		return false; 
} 

bool HeapFull(HEAP heap) //判断堆是否为满 
{
	if ( heap.n == Maxsize - 1 )
		return true;
	else
		return false;
} 

void Insert(HEAP &heap, elementtype element) //在堆heap中插入元素值为element的结点
{
	int i;
	if( !HeapFull(heap) )//堆不满
	{
		i = ++heap.n;
		while( (i!=1) && (element.data>heap.elements[i/2].data) )
		{
			heap.elements[i] = heap.elements[i/2];
			i /= 2;
		}
		heap.elements[i] = element; 
	} 
} 
//这样插入堆中H[0]的空间就浪费掉了

elementtype DeleteMax(HEAP &heap) //删除堆中的最大元素
 {
	int paraent = 1, child = 2;
	elementtype element, tmp;
	if ( !HeapEmpty(heap) )
	{
		element = heap.elements[1];
		tmp = heap.elements[heap.n--];
		while ( child <= heap.n )
		{ 
            if( (child<heap.n)&&(heap.elements[child].data<heap.elements[child+1].data) )
				child++;
            if ( tmp.data >= heap.elements[child].data )
				break;
            heap.elements[paraent] = heap.elements[child];
            paraent = child;
            child *= 2;
		}
  heap.elements[paraent] = tmp;  
  return element;
	} 
} 

//查找堆中的元素,如果存在返回元素的位置，如果不存在返回0
/*
int Find(HEAP H, int x)
 { 
    int p = 1; //用p临时表示x在最大堆中的位置
	for(;p<=H.n;)
	{
		if(H.elements[p].data==x)
			return p;
		p++;
	}
	return 0;
 }
 */
//注：这样查找是把堆中所有元素遍历了一遍，所以时间复杂度为O（n），n为元素个数

//利用最大堆的特点可以优化Find函数,降低时间复杂度，实际上是最好情况和平均情况的时间降低了：
/*
int Find(HEAP H,int x)
{
	int p=1;
	for(;p<=H.n;)
	{
		if(H.elements[p].data==x)
			return p;
		else if(x>H.elements[2*p].data&&x<=H.elements[2*p+1].data)//如果x大于左子树的元素不大于右子树的元素，直接从右子树里面找x
		{
			p=2*p+1;
			if(x==H.elements[p].data)
				return p;
		}
		else if(x<=H.elements[2*p].data&&x>H.elements[2*p+1].data)//如果x大于右子树的元素不大于左子树的元素，直接从左子树里面找x
		{
			p*=2;
			if(x==H.elements[p].data)
				return p;
		}
		else if(x>H.elements[2*p].data&&x>H.elements[2*p+1].data)//如果x大于两个子树的元素，直接返回0
			return 0;
		else//如果x既不大于左子树也不大于右子树
			p++;
	}
}
*/
//有bug，当x比左右节点都小时会把左子树的情况忽略掉

//递归方法优化，x为要查找的元素，h为查找起点
int Find(HEAP H,int x,int h)
{
	int i=h;
	int y=0;
	if(H.elements[h].data==x)
		return i;
	if(H.elements[2*i].data>=x)
		y=Find(H,x,i*2);
	if(y==0&&H.elements[i*2+1].data>=x)
		y=Find(H,x,i*2+1);
	return y;
}


 void main()
 {
	 HEAP H; //定义一个堆
     elementtype element;//定义一个堆元素 
     int data[] = {1, 3, 5, 7, 9, 11, 13};//堆中的元素值数组
	 MaxHeap(H);//空堆
	 //向堆中插入元素构成最大堆，堆中H[0]空间没有利用
     for ( int i = 0; i < 7; i++ )
	 {
		 element.data = data[i];
		 Insert(H, element);
	 }
	 cout<<"最大堆元素为："<<endl;
	 for (i = 1; i <= H.n; i++ )
		 cout << H.elements[i].data << ' ';
	 cout << endl;
	 if(!HeapEmpty(H))
		 cout<<"该堆不为空！"<<endl;
	 if(!HeapFull(H))
		 cout<<"该堆不满！"<<endl;
	// cout<<H.elements[1].key<<endl;
cout<<"请输入查找的元素：";
int x;
cin>>x;
cout <<"该元素在堆中的位置为："<< Find(H,x,1) << endl;
cout<<"删除堆中的最大元素为："<<endl;
cout<<DeleteMax(H).data<<endl;
cout<<"请输入查找的元素：";
cin>>x;
cout <<"该元素在堆中的位置为："<< Find(H,x,1) << endl;
}