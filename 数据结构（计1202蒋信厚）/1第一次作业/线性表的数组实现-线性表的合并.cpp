//线性表的数组实现-线性表的合并
#include<iostream>
using namespace std;

#define maxlength 100
typedef int position;//位置类型
typedef int Elementtype;//下标类型

struct LIST
{
	Elementtype elements[maxlength];
	int last;//最后一个元素的下标
};

position End(LIST L)//线性表的长度
{
	return (L.last+1);
}

void Insert(Elementtype x,position p,LIST &L)
//在表L的位置p处插入x
{
	position q;
	if(L.last>=maxlength-1)
		cout<<"list is full"<<endl; 
	else if((p>L.last+1) || (p<1))
		cout<<"position does not exist"<<endl;
	else
	{
		for(q=L.last;q>=p;q--)
			L.elements[q+1]=L.elements[q];
		L.last=L.last+1;
		L.elements[p]=x;
	}
}

void Delete(position p,LIST &L)
//删除位置p处的元素
{
	position q;
	if((p>L.last+1) || (p<1))
		cout<<"position does not exist"<<endl; 
	else
	{
		L.last=L.last-1;
		for(q=p;q<=L.last;q++)
			L.elements[q]=L.elements[q+1];
	}
}

position Locate(Elementtype x,LIST L)
//返回x在表L中的位置
{
	position q;
	for(q=0;q<L.last;q++)
		if(L.elements[q]==x)
			return q;
	return (L.last+1);	//x不存在
}

Elementtype Retrive(position p,LIST L)
//返回L中位置为p的元素
{
	if((p<1) || (p>L.last+1))
	{
		cout<<"position does not exist"<<endl;
		return -1;
	}
	return L.elements[p];
}
//======================================================
//将两个线性表合并
void Merge(LIST &L,LIST L1,LIST L2)
{
	position p,p1,p2;
	position len1=End(L1);//L1的长度
	position len2=End(L2);//L2的长度
	L.last=len1+len2-1;//合并后L的最后一个元素的位置
	p=p1=p2=0;
	for(;p1<len1;)//将L1的元素写进L
	{
		L.elements[p]=L1.elements[p1];
		p++;
		p1++;
	}
	for(;p2<len2;)//继续将L2的元素写进L
	{
		L.elements[p]=L2.elements[p2];
		p++;
		p2++;
	}
}

void Read(LIST &L,int i)
//输入线性表
{
	cout<<"请输入第"<<i<<"个线性表的长度：";
	cin>>L.last;
	L.last--;
	cout<<"请输入第"<<i<<"个线性表的元素："<<endl;
	for(position p=0;p<=L.last;p++)
		cin>>L.elements[p];
}

void Write(LIST L)
//输出线性表
{
	cout<<"线性表的长度为："<<End(L)<<endl;
	cout<<"线性表的元素为："<<endl;
	for(position p=0;p<=L.last;p++)
		cout<<L.elements[p]<<'\t';
	cout<<endl;
}


void main()
{
	cout<<"本次测试的类型为int"<<endl;
	LIST L,L1,L2;
	Read(L1,1);
	Read(L2,2);
	Merge(L,L1,L2);
	Write(L);
}