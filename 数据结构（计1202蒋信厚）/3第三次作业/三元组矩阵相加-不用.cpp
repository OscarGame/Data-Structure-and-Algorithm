#include<iostream>
using namespace std;
//三元组的二维矩阵表示实现三元组表示的矩阵相加
int Find(int arry[10][3],int row,int col)//判断三元组A所标示的稀疏矩阵是否存在下标[row][col]的非零元素,存在的话返回该非零元素
{
for(int i=1;i<10;i++)
	if(arry[i][0]==row&&arry[i][1]==col)
		return arry[i][2];
	return 0;
}
int main()
{
    int Row,Col,Num1,Num2;
    //确定参加运算的矩阵的规模
	cout<<"请输入参加计算的矩阵的行数、列数："<<endl;
	cin>>Row>>Col;
	//创建第一个稀疏矩阵的三元组
    cout << "输入第一个稀疏矩阵的非零元素个数(<10)：";
	cin>>Num1;
	int A[10][3];
	A[0][0]=Row;
	A[0][1]=Col;
	A[0][2]=Num1;
    for (int i=0;i<Num1;i++)
    {
        cout <<"输入稀疏矩阵第" << i+1 << "个非零元素的行、列及元素值：";
        cin >> A[i][0] >> A[i][1] >> A[i][2];
    }
	//创建第二个稀疏矩阵的三元组
	cout << "输入第二个稀疏矩阵的非零元素个数(<10)：";
	cin>>Num2;
	int B[10][3];
	B[0][0]=Row;
	B[0][1]=Col;
	B[0][2]=Num2;
    for (i=0;i<Num2;i++)
    {
        cout <<"输入稀疏矩阵第" << i+1 << "个非零元素的行、列及元素值：";
        cin >> B[i][0] >> B[i][1] >> B[i][2];
    }
	//将A和B相加结果存在C中
	int Num=Num1+Num2;//C表示的稀疏矩阵的非零元素个数
	int C[20][3];
	int col=1;//C的动态列下标
    for(int r=0;r<Row;r++)
		for(int c=0;c<Col;c++)
		{
			if(Find(A,r,c)&&Find(B,r,c))
			{
				Num--;
				C[col][0]=r;
				C[col][1]=c;
				C[col][2]=Find(A,r,c)+Find(B,r,c);
				col++;
			}
			else if(Find(A,r,c))
			{
				C[col][0]=r;
				C[col][1]=c;
				C[col][2]=Find(A,r,c);
				col++;
			}
			else if(Find(B,r,c))
			{
				C[col][0]=r;
				C[col][1]=c;
				C[col][2]=Find(B,r,c);
				col++;
			}
		}
    C[0][0]=Row;
	C[0][1]=Col;
	C[0][2]=Num;
    return 0;
}