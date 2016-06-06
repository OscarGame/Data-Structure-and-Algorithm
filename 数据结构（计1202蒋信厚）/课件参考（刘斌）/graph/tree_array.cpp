#include "tree_array.h"

#ifdef _TREE_ARRAY_

void visit(elementtype_tree_array e)
{
	cout<<e;
}

elementtype_tree_array Data(TREE_ARRAY t, int n )
{
	return t[n].data;
}

// ������T�е�n��Ԫ�ص������ӵ��±꣬��������ڣ��򷵻�0
int LeftMostChild(TREE_ARRAY T, int n)
{
	int i;
	for(i=n+1; i<MAX_TREE_ARRAY; i++)
	{
		if(T[i].parent==n)
			return i;
	}
	return 0;
}

// ������T�е�n��Ԫ�ص����ֵܵ��±꣬��������ڣ��򷵻�0
int RightSibling(TREE_ARRAY T, int n)
{
	int i;
	for(i=n+1; i<MAX_TREE_ARRAY; i++)
	{
		if(T[i].parent==T[n].parent)
			return i;
	}
	return 0;
}

int Parent(TREE_ARRAY T, int n)
{
	return T[n].parent;
}

int Root(TREE_ARRAY T)
{
	int t;
	for(int i=1; i<MAX_TREE_ARRAY; i++)
	{
		if(T[i].data!=' ')
		{
			t=i;
			while(1)
			{
				if(T[t].parent==0)
					return t;
				t=T[t].parent;

			}
		}

	}
}

//�ӵ�n��Ԫ�ؿ�ʼ�ȸ�������n��
void PreOrder(TREE_ARRAY T, int n)
{
	int c;
	visit(Data(T, n));
	c=LeftMostChild(T, n);
	while(c!=0)
	{
		PreOrder(T, c);
		c=RightSibling(T, c);
	}
}

// ͨ������t��������n��������T
void CreateTreeArray(TREE_ARRAY &T, nodeTR t[], int n)
{
	if(n>=MAX_TREE_ARRAY)
		return;
	for(int i=1; i<=n; i++)
	{
		T[i].parent=t[i].parent;
		T[i].data=t[i].data;
	}
}

#ifndef _MTGRAPH_

void main()
{
	nodeTR t[10]={{0, ' '}, {0, 'a'}, {1, 'b'}, {1, 'c'}, {2, 'd'}, {2, 'e'}, 
					{5, 'f'}, {5, 'g'}, {3, 'h'}, {3, 'i'}};
	TREE_ARRAY T;
	CreateTreeArray(T, t, 9);
	PreOrder(T, 1);
	cout<<endl;
}

#endif
#endif