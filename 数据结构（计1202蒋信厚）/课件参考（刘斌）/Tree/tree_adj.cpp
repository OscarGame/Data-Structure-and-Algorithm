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
	cout<<"输入结点个数:";
	cin>>n;
	if(n>0)
	{
		cout<<"根结点的编号为:";
		cin>>T.root;
	}
	for(int i=0; i<n; i++)
	{
		cout<<"输入第"<<i+1<<"个结点: ";		
		cin>>d;
		T.data[i+1]=d;
		T.header[i+1]=new celltypeTA;
		p1=T.header[i+1];
		p1->next=NULL;
		cout<<"输入第"<<i+1<<"个结点的孩子结点的个数: ";
		cin>>m;
		for(int j=0; j<m; j++)
		{
			cout<<"第"<<i+1<<"个结点的第"<<j+1<<"个孩子结点为(从左到右):";
			p=new celltypeTA;
			cin>>p->element;
			p->next=NULL;
			p1->next=p;
			p1=p;						
		}
	}
}

//创建树，d为树的各节点的信息，p为各结点所对应的父节点的序号，n为结点的个数
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