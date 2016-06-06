#include "tree_adj.h"

#ifdef _TREE_ADJ_


void visit(datatypeTA e)
{
	cout<<e;
}

datatypeTA Data(TREETA t, int n )
{
	return t.data[n];
}

void initTA(TREETA &T)
{
	for(int i=1; i< maxtanodes; i++)
	{
		T.data[i]='#';
		T.header[i]=NULL;
		T.root=0;
	}
}

BOOLEAN Empty(LISTTA L)
{
	if(L->next==NULL)
		return TRUE;
	return FALSE;
}

nodeTA LeftMostChild(TREETA T, nodeTA n)
{
	LISTTA L;
	L=T.header[n];
	if(Empty(L))
		return 0;
	else
		return L->next->element;
}

nodeTA RightSibling(TREETA T, nodeTA n)
{
	for(nodeTA i=1; i<maxtanodes; i++)
	{
		LISTTA L;
		L=T.header[i];
		while(L!=NULL)
		{
			if(L->element==n && L->next!=NULL)
				return L->next->element;
			L=L->next;
		}
	}
	return 0;
}

void PreOrder(TREETA T, nodeTA n)
{
	nodeTA c;
	visit(Data(T, n));
	c=LeftMostChild(T, n);
	while(c!=0)
	{
		PreOrder(T, c);
		c=RightSibling(T, c);
	}
}

void CreateTreeTA(TREETA &T)
{
	int m, n;
	positionta p, p1;
	datatypeTA d;
	cout<<"���������:";
	cin>>n;
	if(n>0)
	{
		cout<<"�����ı��Ϊ:";
		cin>>T.root;
	}
	for(int i=0; i<n; i++)
	{
		cout<<"�����"<<i+1<<"�����: ";		
		cin>>d;
		T.data[i+1]=d;
		T.header[i+1]=new celltypeTA;
		p1=T.header[i+1];
		p1->next=NULL;
		cout<<"�����"<<i+1<<"�����ĺ��ӽ��ĸ���: ";
		cin>>m;
		for(int j=0; j<m; j++)
		{
			cout<<"��"<<i+1<<"�����ĵ�"<<j+1<<"�����ӽ��Ϊ(������):";
			p=new celltypeTA;
			cin>>p->element;
			p->next=NULL;
			p1->next=p;
			p1=p;						
		}
	}
}

//��������dΪ���ĸ��ڵ����Ϣ��pΪ���������Ӧ�ĸ��ڵ����ţ�nΪ���ĸ���
void CreateTreeTA(TREETA &T, datatypeTA d[], nodeTA p[], int n)
{
	positionta p1;

	for(int i=0; i<n; i++)
	{
		T.data[i+1]=d[i];
		T.header[i+1]=new celltypeTA;
		T.header[i+1]->next=NULL;
		if(p[i]==0)
			T.root=i+1;
	}
	for(i=n-1; i>=0; i--)
	{
		if(p[i]!=0)
		{		
			p1=new celltypeTA;
			p1->element=i+1;
			p1->next=T.header[p[i]]->next;
			T.header[p[i]]->next=p1;
		}
	}
}

void main()
{
	TREETA T;
	initTA(T);
	CreateTreeTA(T);
	/*datatypeTA d[]="abcdehijfg";
	nodeTA p[]={0, 1, 1, 2, 2, 5, 5, 5, 3, 3};
	CreateTreeTA(T, d, p, 10);*/

	PreOrder(T, T.root);
	cout<<endl;
}

#endif