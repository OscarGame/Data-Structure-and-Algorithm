#include<iostream>
using namespace std;

struct node
{
	int father;//ָ�򸸽ڵ����
	int count;//��������
};

typedef node MFSET[101];//�Ƚ�������һ
//�鲢�����ڵ������Խ�С�����鲢���������϶������
void Union(int A,int B,MFSET a)
{
	if(a[A].count>a[B].count)
	{
		a[B].father=A;
		a[A].count=a[A].count+a[B].count;
	}
	else
	{
		a[A].father=B;
		a[B].count=a[A].count+a[B].count;
	}
}

int Find(int x,MFSET a)//���ظ��ڵ㣬�����ĸ���Ϊ0
{
	while(a[x].father!=0)
	{
		x=a[x].father;
	}
	return x;
}

void Initial(int A,MFSET a)//����ȼ��ࡣ
{
	a[A].father=0;
	a[A].count=1;
}

//�ȼ۷��ຯ��
void Equivalence(MFSET a,int y)//y�Ǹü��ϵ��ܸ���
{
	int m,n;
	for(int i=1;i<y+1;i++)
		Initial(i,a);//��ʼ��
	while(1)
	{
		cout<<"������ȼ���(����0��ʾ�ȼ۹�ϵ�������)"<<endl;
		cin>>n;
		if(n==0)
			break;
		cin>>m;
		n=Find(n,a);
		m=Find(m,a);
		if(m!=n)
			Union(n,m,a);//�鲢�ȼ���
	}

}
//����ȼ���ĸ�
void Showup(MFSET a)
{
	int i=1;
	while(1)
	{
		if(a[i].father!=0)
		{
			cout<<Find(i,a)<<endl;
		}
		i++;
		if(i>9)
			break;
		if(a[i].father==0)
			cout<<i<<endl;
	}
}
int main()
{
	MFSET a;
	Equivalence(a,9);// 1��5��6��8��7��2��9��8��3��7��4��2��9��3
	Showup(a);
	return 0;
}