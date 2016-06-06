//深度优先搜索实现
#include <iostream>
using namespace std;
#include <Math.h>

#define size 8//定义期盼的规模4x4
#define maxStep 100000//最大的步数，超出结束运行

struct node{
	bool visited;//结点是否被访问过，false表示new，true表示old
	int num;//访问编号，即马走的第几步
	//int symbol;//为每一个点特定编号
};
int static step = 0;//已正确走的步数
int static sumStep = 0;//总共走的步数，包括走错的、后退的
node chessBoard[size+1][size+1];//定义棋盘数组,第一行、第一列不用

void initChess()//初始化棋盘，使每一个点都标识new没被访问过，编码为零
{
	//int sym = 1;
        for(int i=1;i<=size;i++)
			for(int j=1;j<=size;j++){
				chessBoard[i][j].visited = false;
				chessBoard[i][j].num = 0;
			//	chessBoard[i][j].symbol = sym;//按行依次标号
				//sym++;
			}
}

void printChess()//一行一行的输出
{
        for(int i=1;i<=size;i++)
        {
                for(int j=1;j<=size;j++)
                        cout << chessBoard[i][j].num<<'\t';
                cout << endl;
        }
}

int searchX(int step)//查找某一步的列数（x坐标）
{
        for(int i=0;i<size;i++)
                for(int j = 0;j<size;j++)
                        if(chessBoard[j][i].num == step)
							return i;
        return 0;
}

int searchY(int step)//查找某一步行数（y坐标）
{
        for(int i=0;i<size;i++)
                for(int j = 0;j<size;j++)
                        if(chessBoard[j][i].num == step)
							return j;
        return 0;
}

bool isSun(int x1,int y1,int x2,int y2)//判断（x1,y1）和（x2,y2）之间的格子是否能拼成“日”字
{
	if(abs(x1-x2)==2&&abs(y1-y2)==1||abs(x1-x2)==1&&abs(y1-y2)==2)
		return true;
	else
		return false;
}

bool jumpRule(int a,int b,int x,int y)//马的前进规则，判断可不可以从（a,b）跳到（x,y）点
{
        if(x>=1 && x<=size && y>=1 && y<=size && (chessBoard[x][y].visited == false) && isSun(a,b,x,y))
                return true;
        else
                return false;
}

void jump(int x,int y)//让马跳到(x,y)
{
	++step;//步数加1
	chessBoard[x][y].num = step;//为马当前所在的点编号
	chessBoard[x][y].visited = true;//标记为old
	sumStep++;
}

void retreat(int x,int y)//从(x,y)后退一步
{
	chessBoard[x][y].visited = false;
	chessBoard[x][y].num = 0;
	--step;
	sumStep++;
}
//返回以(x,y)为中心的5x5宫格的边界下标
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
//最关键函数：*********************?????
void selectToJump(int x,int y)//从(x,y)自己选择跳到下一个可行的点，递归下去
{ 
	//在以(x,y)为中心的5x5宫格内的点里面选择,走得通的话以下一个点为中心继续搜索
	//要是能避免重复走已经不可行的点最好
	for(int i = leftOrUp(x);i<=rightOrDown(x);i++)//x坐标/列
		for(int j = leftOrUp(y);i<=rightOrDown(y);j++)//y坐标/行
		{
			if(!(j==x&&i==y))//排除中心点本身
			{
			jump(j,i);
			if(step==size*size || sumStep>=maxStep)//搜索成功结束或失败结束
				return;
			if(jumpRule(x,y,j,i))
				selectToJump(j,i);//以下一个点为中心继续搜索
			else
				retreat(j,i);
			}
		}
		retreat(x,y);
		if(chessBoard[x][y].visited==false)
		{
			cout<<"搜索失败！"<<endl;
			return;
		}
}
//*********************************
void main()
{
	int x,y;//起点坐标
	cout<<"请输入起点坐标(x,y):"<<endl;
	cin>>x>>y;
	//访问起点：
	++step;//起点设置为第一步
	chessBoard[x][y].num = step;//为马当前所在的点编号
	chessBoard[x][y].visited = true;//标记为old
    //selectToJump(x,y);
	//if(step == size)
		printChess();
	//else
		cout<<"搜索失败，请重试！"<<endl;
	//函数测试：
cout<<leftOrUp(1)<<'\t'<<rightOrDown(1)<<endl;
}