//�����������ʵ��
#include <iostream>
using namespace std;
#include <Math.h>

#define size 8//�������εĹ�ģ4x4
#define maxStep 100000//���Ĳ�����������������

struct node{
	bool visited;//����Ƿ񱻷��ʹ���false��ʾnew��true��ʾold
	int num;//���ʱ�ţ������ߵĵڼ���
	//int symbol;//Ϊÿһ�����ض����
};
int static step = 0;//����ȷ�ߵĲ���
int static sumStep = 0;//�ܹ��ߵĲ����������ߴ�ġ����˵�
node chessBoard[size+1][size+1];//������������,��һ�С���һ�в���

void initChess()//��ʼ�����̣�ʹÿһ���㶼��ʶnewû�����ʹ�������Ϊ��
{
	//int sym = 1;
        for(int i=1;i<=size;i++)
			for(int j=1;j<=size;j++){
				chessBoard[i][j].visited = false;
				chessBoard[i][j].num = 0;
			//	chessBoard[i][j].symbol = sym;//�������α��
				//sym++;
			}
}

void printChess()//һ��һ�е����
{
        for(int i=1;i<=size;i++)
        {
                for(int j=1;j<=size;j++)
                        cout << chessBoard[i][j].num<<'\t';
                cout << endl;
        }
}

int searchX(int step)//����ĳһ����������x���꣩
{
        for(int i=0;i<size;i++)
                for(int j = 0;j<size;j++)
                        if(chessBoard[j][i].num == step)
							return i;
        return 0;
}

int searchY(int step)//����ĳһ��������y���꣩
{
        for(int i=0;i<size;i++)
                for(int j = 0;j<size;j++)
                        if(chessBoard[j][i].num == step)
							return j;
        return 0;
}

bool isSun(int x1,int y1,int x2,int y2)//�жϣ�x1,y1���ͣ�x2,y2��֮��ĸ����Ƿ���ƴ�ɡ��ա���
{
	if(abs(x1-x2)==2&&abs(y1-y2)==1||abs(x1-x2)==1&&abs(y1-y2)==2)
		return true;
	else
		return false;
}

bool jumpRule(int a,int b,int x,int y)//���ǰ�������жϿɲ����Դӣ�a,b��������x,y����
{
        if(x>=1 && x<=size && y>=1 && y<=size && (chessBoard[x][y].visited == false) && isSun(a,b,x,y))
                return true;
        else
                return false;
}

void jump(int x,int y)//��������(x,y)
{
	++step;//������1
	chessBoard[x][y].num = step;//Ϊ��ǰ���ڵĵ���
	chessBoard[x][y].visited = true;//���Ϊold
	sumStep++;
}

void retreat(int x,int y)//��(x,y)����һ��
{
	chessBoard[x][y].visited = false;
	chessBoard[x][y].num = 0;
	--step;
	sumStep++;
}
//������(x,y)Ϊ���ĵ�5x5����ı߽��±�
int leftOrUp(int x)
{
	if(x-1>=1)
	{
		if(x-2>=1)
			return x-2;
		return x-1;
	}
	return x;
}
int rightOrDown(int x)
{
	if(x+1<=size)
	{
		if(x+2<=size)
			return x+2;
		return x+1;
	}
		return x;
}
//��ؼ�������*********************?????
void selectToJump(int x,int y)//��(x,y)�Լ�ѡ��������һ�����еĵ㣬�ݹ���ȥ
{ 
	//����(x,y)Ϊ���ĵ�5x5�����ڵĵ�����ѡ��,�ߵ�ͨ�Ļ�����һ����Ϊ���ļ�������
	//Ҫ���ܱ����ظ����Ѿ������еĵ����
	for(int i = leftOrUp(x);i<=rightOrDown(x);i++)//x����/��
		for(int j = leftOrUp(y);i<=rightOrDown(y);j++)//y����/��
		{
			if(!(j==x&&i==y))//�ų����ĵ㱾��
			{
			jump(j,i);
			if(step==size*size || sumStep>=maxStep)//�����ɹ�������ʧ�ܽ���
				return;
			if(jumpRule(x,y,j,i))
				selectToJump(j,i);//����һ����Ϊ���ļ�������
			else
				retreat(j,i);
			}
		}
		retreat(x,y);
		if(chessBoard[x][y].visited==false)
		{
			cout<<"����ʧ�ܣ�"<<endl;
			return;
		}
}
//*********************************
void main()
{
	int x,y;//�������
	cout<<"�������������(x,y):"<<endl;
	cin>>x>>y;
	//������㣺
	++step;//�������Ϊ��һ��
	chessBoard[x][y].num = step;//Ϊ��ǰ���ڵĵ���
	chessBoard[x][y].visited = true;//���Ϊold
    //selectToJump(x,y);
	//if(step == size)
		printChess();
	//else
		cout<<"����ʧ�ܣ������ԣ�"<<endl;
	//�������ԣ�
cout<<leftOrUp(1)<<'\t'<<rightOrDown(1)<<endl;
}