#include<iostream>
using namespace std;
//��Ԫ��Ķ�ά�����ʾʵ����Ԫ���ʾ�ľ������
int Find(int arry[10][3],int row,int col)//�ж���Ԫ��A����ʾ��ϡ������Ƿ�����±�[row][col]�ķ���Ԫ��,���ڵĻ����ظ÷���Ԫ��
{
for(int i=1;i<10;i++)
	if(arry[i][0]==row&&arry[i][1]==col)
		return arry[i][2];
	return 0;
}
int main()
{
    int Row,Col,Num1,Num2;
    //ȷ���μ�����ľ���Ĺ�ģ
	cout<<"������μӼ���ľ����������������"<<endl;
	cin>>Row>>Col;
	//������һ��ϡ��������Ԫ��
    cout << "�����һ��ϡ�����ķ���Ԫ�ظ���(<10)��";
	cin>>Num1;
	int A[10][3];
	A[0][0]=Row;
	A[0][1]=Col;
	A[0][2]=Num1;
    for (int i=0;i<Num1;i++)
    {
        cout <<"����ϡ������" << i+1 << "������Ԫ�ص��С��м�Ԫ��ֵ��";
        cin >> A[i][0] >> A[i][1] >> A[i][2];
    }
	//�����ڶ���ϡ��������Ԫ��
	cout << "����ڶ���ϡ�����ķ���Ԫ�ظ���(<10)��";
	cin>>Num2;
	int B[10][3];
	B[0][0]=Row;
	B[0][1]=Col;
	B[0][2]=Num2;
    for (i=0;i<Num2;i++)
    {
        cout <<"����ϡ������" << i+1 << "������Ԫ�ص��С��м�Ԫ��ֵ��";
        cin >> B[i][0] >> B[i][1] >> B[i][2];
    }
	//��A��B��ӽ������C��
	int Num=Num1+Num2;//C��ʾ��ϡ�����ķ���Ԫ�ظ���
	int C[20][3];
	int col=1;//C�Ķ�̬���±�
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