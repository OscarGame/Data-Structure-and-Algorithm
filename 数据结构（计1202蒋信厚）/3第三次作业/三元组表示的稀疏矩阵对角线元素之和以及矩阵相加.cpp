//��Ԫ���ʾ��ϡ�����Խ���Ԫ����ӣ��Լ�ϡ��������
#include<iostream>
using namespace std;

#define NumVertices 6//ϡ��������Ԫ�ظ���

struct node{
    int row;//��
    int col;//��
    int data;//ֵ
};
typedef node triple;//��Ԫ��

void Input(triple a[])//������Ԫ��
{
	cout<<"������ϵ��������С������ͷ���Ԫ�ظ�����"<<endl;
	cin>>a[0].row>>a[0].col>>a[0].data;
	if(a[0].row != a[0].col)
		cout<<"��ע���������ϵ��������n�׾����޷���Խ�Ԫ�صĺͣ�"<<endl;
	for(int i=1;i<=a[0].data;i++)
	{
	cout<<"���԰������ȵĹ������������<<i<<������Ԫ�ص��±��ֵ��"<<endl;
	cin>>a[i].row>>a[i].col>>a[i].data;
	}
}

void Init(triple a[])//��ʼ����Ԫ��
{
	a[0].row = 4; a[0].col = 4; a[0].data = 6;
	a[1].row = 0; a[1].col = 0; a[1].data = 50;
	a[2].row = 1; a[2].col = 0; a[2].data = 10;
	a[3].row = 1; a[3].col = 2; a[3].data = 20;
	a[4].row = 3; a[4].col = 0; a[4].data = -30;
	a[5].row = 3; a[5].col = 2; a[5].data = -60;
	a[6].row = 3; a[6].col = 3; a[6].data = 5;
}

int Find(triple a[],int row,int col)//�ж���Ԫ��A����ʾ��ϡ������Ƿ�����±�[row][col]�ķ���Ԫ��,���ڵĻ����ظ÷���Ԫ��
{
	for(int i=1;i<=a[0].data;i++){
		if(a[i].row == row && a[i].col == col)
			return a[i].data;
	}
		return 0;
}

int Sum(triple a[])//��ԽǾ���Խ�Ԫ�صĺ�
{
    int sum=0;//�Խ���Ԫ���ۼ�
    if (a[0].row!=a[0].col)
        cout<<"��ϡ�������n*n�����޷���Խ�Ԫ�غ�"<<endl;
    else
        for (int i=1; i<=a[0].data; i++)
            if (a[i].row==a[i].col ||a[i].row+a[i].col == a[0].row-1)//�ڶԽ�����
                sum+=a[i].data;
			return sum;
}

void Print(triple *a)//�����Ԫ��
{
		for(int j=0;j<=a[0].data;j++)
			cout<<a[j].row<<'\t'<<a[j].col<<'\t'<<a[j].data<<endl;
}

void PrintMT(triple *a)//�����Ԫ������ʾ��ϡ�����
{
	for(int i=0;i<a[0].row;i++)
	{
		for(int j=0;j<a[0].col;j++)
			cout<<Find(a,i,j)<<'\t';
		cout<<endl;
	}
}

 void Combine(triple a[],triple b[],triple c[])//��Ԫ���ʾ��ϡ��������
{
	c[0].row = a[0].row;
	c[0].col = a[0].col;
	int cdata = a[0].data+b[0].data;//c����ʱ����Ԫ�ظ���
	int cmark = 1;
	for(int i = 0;i<c[0].row;i++)
		for(int j = 0;j<c[0].col;j++)
		{
			if(Find(a,i,j) && Find(b,i,j))//a��b����[i][j]����ķ���Ԫ��
			{
				c[cmark].row = i;
				c[cmark].col = j;
				c[cmark].data = Find(a,i,j)+Find(b,i,j);
				cdata--;
				cmark++;
			//	cout<<c[cmark].row<<'\t'<<c[cmark].col<<'\t'<<c[cmark].data<<endl;
			}
			else if(Find(a,i,j))//a��[i][j]����ķ���Ԫ�أ�bû��
			{
				c[cmark].row = i;
				c[cmark].col = j;
				c[cmark].data = Find(a,i,j);
				cmark++;
			}
			else if(Find(b,i,j))//b��[i][j]����ķ���Ԫ�أ�aû��
			{
				c[cmark].row = i;
				c[cmark].col = j;
				c[cmark].data = Find(b,i,j);
				cmark++;
			}
		}
		c[0].data = cdata;//����c�ķ���Ԫ�ظ���
}

void main(){
	triple a[NumVertices+1];
	Init(a);
	cout<<"���������Ԫ�飺"<<endl;
	Print(a);
	cout<<"���������Ԫ���ʾ��ϡ�����"<<endl;
	PrintMT(a);
	cout<<"ϡ�����Խ�Ԫ��֮��Ϊ��"<<Sum(a)<<endl;
	cout<<"a��a��ӣ�"<<endl;
	triple c[20];
    Combine(a,a,c);//��a��a��ӷŽ�c����
	cout<<"��Ӻ�c��Ԫ��Ϊ��"<<endl;
	Print(c);
	cout<<"��Ӻ��ϡ�����Ϊ��"<<endl;
	PrintMT(c);
}