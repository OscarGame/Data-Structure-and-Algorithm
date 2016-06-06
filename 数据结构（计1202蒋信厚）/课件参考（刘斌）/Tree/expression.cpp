#include "expression.h"

#ifdef _EXPRESSION_


TREEEX CreateT(datatype1 d, TREEEX lchild, TREEEX rchild)
{
	TREEEX t=new node;
	t->data=d;
	if(d==logicaltrue)
		t->value=TRUE;
	else if(d==logicalfalse)
		t->value=FALSE;
	t->lchild=lchild;
	t->rchild=rchild;
	return t;	
}

void PostOrderEval(TREEEX T)
{
	if(T!=NULL)
	{
		PostOrderEval(T->lchild);
		PostOrderEval(T->rchild);
		switch(T->data)
		{
		case logicalnot: T->value=BOOLEAN(!T->rchild->value); break;
		case logicaland: T->value=BOOLEAN(T->rchild->value && T->lchild->value); break;
		case logicalor: T->value=BOOLEAN(T->rchild->value || T->lchild->value); break;
		case logicaltrue: T->value=TRUE; break;
		case logicalfalse: T->value=FALSE; break;
		}

	}
}

void main()
{
	datatype1 d1, d2, d3, d4;
	TREEEX t1, t2,t3, t4;
	d1=logicaltrue;
	t1=CreateT(d1, NULL, NULL);
	
	d2=logicalfalse;
	t2=CreateT(d2, NULL, NULL);
	
	d1=logicalnot;
	t2=CreateT(d1, NULL, t2);
	
	d3=logicaland;
	t3=CreateT(d3, t1, t2);
	
	d1=logicaltrue;
	t1=CreateT(d1, NULL, NULL);

	d2=logicalnot;
	t2=CreateT(d2, NULL, t1);

	d4=logicalfalse;
	t4=CreateT(d4, NULL, NULL);

	d1=logicaland;
	t1=CreateT(d1, t2, t4);

	d2=logicalor;
	t2=CreateT(d2, t3, t1);

	d1=logicaltrue;
	t1=CreateT(d1, NULL, NULL);

	d1=logicalnot;
	t1=CreateT(d1, NULL, t1);

	d3=logicalor;
	t3=CreateT(d3, t2, t1);

	PostOrderEval(t3);
	cout<<t3->value<<endl;

	
}
#endif