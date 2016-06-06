//三元组表示的稀疏矩阵对角线元素相加，以及稀疏矩阵相加
#include<iostream>
using namespace std;

#define NumVertices 6//稀疏矩阵非零元素个数

struct node{
    int row;//行
    int col;//列
    int data;//值
};
typedef node triple;//三元组

void Input(triple a[])//输入三元组
{
	cout<<"请输入系数矩阵的行、列数和非零元素个数："<<endl;
	cin>>a[0].row>>a[0].col>>a[0].data;
	if(a[0].row != a[0].col)
		cout<<"请注意您输入的系数矩阵不是n阶矩阵，无法求对角元素的和！"<<endl;
	for(int i=1;i<=a[0].data;i++)
	{
	cout<<"请以按行优先的规则依次输入第<<i<<个非零元素的下标和值："<<endl;
	cin>>a[i].row>>a[i].col>>a[i].data;
	}
}

void Init(triple a[])//初始化三元祖
{
	a[0].row = 4; a[0].col = 4; a[0].data = 6;
	a[1].row = 0; a[1].col = 0; a[1].data = 50;
	a[2].row = 1; a[2].col = 0; a[2].data = 10;
	a[3].row = 1; a[3].col = 2; a[3].data = 20;
	a[4].row = 3; a[4].col = 0; a[4].data = -30;
	a[5].row = 3; a[5].col = 2; a[5].data = -60;
	a[6].row = 3; a[6].col = 3; a[6].data = 5;
}

int Find(triple a[],int row,int col)//判断三元组A所标示的稀疏矩阵是否存在下标[row][col]的非零元素,存在的话返回该非零元素
{
	for(int i=1;i<=a[0].data;i++){
		if(a[i].row == row && a[i].col == col)
			return a[i].data;
	}
		return 0;
}

int Sum(triple a[])//求对角矩阵对角元素的和
{
    int sum=0;//对角线元素累加
    if (a[0].row!=a[0].col)
        cout<<"此稀疏矩阵不是n*n矩阵，无法求对角元素和"<<endl;
    else
        for (int i=1; i<=a[0].data; i++)
            if (a[i].row==a[i].col ||a[i].row+a[i].col == a[0].row-1)//在对角线上
                sum+=a[i].data;
			return sum;
}

void Print(triple *a)//输出三元组
{
		for(int j=0;j<=a[0].data;j++)
			cout<<a[j].row<<'\t'<<a[j].col<<'\t'<<a[j].data<<endl;
}

void PrintMT(triple *a)//输出三元组所表示的稀疏矩阵
{
	for(int i=0;i<a[0].row;i++)
	{
		for(int j=0;j<a[0].col;j++)
			cout<<Find(a,i,j)<<'\t';
		cout<<endl;
	}
}

 void Combine(triple a[],triple b[],triple c[])//三元组表示的稀疏矩阵相加
{
	c[0].row = a[0].row;
	c[0].col = a[0].col;
	int cdata = a[0].data+b[0].data;//c的临时非零元素个数
	int cmark = 1;
	for(int i = 0;i<c[0].row;i++)
		for(int j = 0;j<c[0].col;j++)
		{
			if(Find(a,i,j) && Find(b,i,j))//a和b都有[i][j]坐标的非零元素
			{
				c[cmark].row = i;
				c[cmark].col = j;
				c[cmark].data = Find(a,i,j)+Find(b,i,j);
				cdata--;
				cmark++;
			//	cout<<c[cmark].row<<'\t'<<c[cmark].col<<'\t'<<c[cmark].data<<endl;
			}
			else if(Find(a,i,j))//a有[i][j]坐标的非零元素，b没有
			{
				c[cmark].row = i;
				c[cmark].col = j;
				c[cmark].data = Find(a,i,j);
				cmark++;
			}
			else if(Find(b,i,j))//b有[i][j]坐标的非零元素，a没有
			{
				c[cmark].row = i;
				c[cmark].col = j;
				c[cmark].data = Find(b,i,j);
				cmark++;
			}
		}
		c[0].data = cdata;//最终c的非零元素个数
}

void main(){
	triple a[NumVertices+1];
	Init(a);
	cout<<"您输入的三元组："<<endl;
	Print(a);
	cout<<"您输入的三元组表示的稀疏矩阵："<<endl;
	PrintMT(a);
	cout<<"稀疏矩阵对角元素之和为："<<Sum(a)<<endl;
	cout<<"a和a相加："<<endl;
	triple c[20];
    Combine(a,a,c);//将a和a相加放进c里面
	cout<<"相加后c三元组为："<<endl;
	Print(c);
	cout<<"相加后的稀疏矩阵为："<<endl;
	PrintMT(c);
}