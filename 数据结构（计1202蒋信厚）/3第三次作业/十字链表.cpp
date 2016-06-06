//ϡ������ʮ�������ʾ
#include<iostream>
using namespace std;
typedef int valuetype;//Ԫ��ֵ������
#define length 4//����Ľ�

struct node{
	node *LEFT;//��ָ����
	node *UP;//��ָ����
	int ROW;//��
	int COL;//��
	valuetype VAL;//ֵ
};

node *BASEROW=new node[length];//�б�ͷ�������
node *BASECOL=new node[length];//�б�ͷ�������

void init(node BASEROW[],node BASECOL[])//��ʼ����ͷ�������
{
	for(int i=0;i<4;i++)
	{
		BASEROW[i].COL=-1;
		BASEROW[i].LEFT=NULL;

		BASECOL[i].ROW=-1;
		BASECOL[i].UP=NULL;            
	}
}

void create()//�û�����ʮ������ϡ�����
{
	while(1)
	{
		node *temp=new node;
		cout<<"�밴����������ϡ��������Ԫ�ص��С��С�ֵ������-1,-1,-1��������"<<endl;
		int r,c,v;
		cin>>r>>c>>v;
		if(r==-1) break;
		temp->ROW=r;
		temp->COL=c;
		temp->VAL=v;

		//����LEFTָ������
		if(!BASEROW[r].LEFT){//��ͷ���Ϊ��ʱ
			BASEROW[r].LEFT=temp;
			temp->LEFT= &BASEROW[r];
		}
		else{
			temp->LEFT=BASEROW[r].LEFT;
			BASEROW[r].LEFT=temp;
		}

		//����UPָ������
		if(!BASECOL[c].UP){
			BASECOL[c].UP=temp;
			temp->UP= &BASECOL[c];
		}
		else{
			temp->UP=BASECOL[c].UP;
			BASECOL[c].UP=temp;
		}
	}
}//tempʲôʱ���ͷŵ��ˣ�
void print()//���ʮ�������ʾ������
{
	int array[length][length];//����洢ʮ�������б����������Ϣ
	//��ʼ������
	for(int i=0;i<length;i++)
		for(int j=0;j<length;j++)
			array[i][j]=0;

	node *p=NULL;
	for(i=0;i<length;i++)
	{
		p=BASEROW[i].LEFT;
		while(p->COL!=-1)
		{
			int r=p->ROW;
			int c=p->COL;
			array[r][c]=p->VAL;//p->VALΪʲôû��ֵ�ˣ�
			p=p->LEFT;
		}
	}

	for(i=0;i<length;i++)
	{
		for(int j=0;j<length;j++)
			cout<<array[i][j]<<'\t';
		cout<<endl;
	}
		
}

void main()
{
	init(BASEROW,BASECOL);
	create();
	print();
}