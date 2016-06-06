#include "index.h"

#ifdef _LIST_EXAMPLE_

struct polynode
{
	double coef;
	int exp;
	polynode *link;
};

typedef polynode *polypointer;

polypointer Attach(double c, int e, polypointer d)
{
	polypointer x;
	x=new polynode;
	x->coef=c;
	x->exp=e;
	x->link=NULL;
	d->link=x;
	return x;
}

char Compare(int a, int b)
{
	if(a==b)
		return '=';
	else if(a>b)
		return '>';
	else
		return '<';
}

polypointer PolyAdd(polypointer a, polypointer b)
{
	polypointer p, q, d, c;
	double x;
	p=a, q=b;
	c=new polynode, d=c;;
	while((p!=NULL)&&(q!=NULL))
	{
		switch(Compare(p->exp, q->exp))
		{
		case '=':
			x=p->coef+q->coef;
			if(x!=0)
				d=Attach(x, p->exp, d);
			p=p->link; 
			q=q->link;
			break;
		case '>':
			d=Attach(p->coef, p->exp, d);
			p=p->link;
			break;
		case '<':
			d=Attach(q->coef, q->exp, d);
			q=q->link;
			break;
		}
	}
		while(p!=NULL)
		{
			d=Attach(p->coef, p->exp, d);
			p=p->link;
		}
		while(q!=NULL)
		{
			d=Attach(q->coef, q->exp, d);
			q=q->link;
		}		
	
	d->link=NULL;
	p=c;
	c=c->link;
	delete p;
	return c;
}

void Output(polypointer p)
{
	int flag=0;
	p=p->link;
	while(p!=NULL)
	{
		if(p->coef<0)
			cout<<'-'<<p->coef;
		else if(p->coef>0)
		{
			if(!flag)
			{
				if(p->coef!=1)
					cout<<p->coef;
				flag=1;
			}
			else
			{
				if(p->coef!=1 || p->exp==0)
					cout<<'+'<<p->coef;
				else
					cout<<'+';
			}

		}
		if(p->exp!=0)
		{
			if(p->exp==1)
				cout<<'x';
			else
				cout<<'x'<<'^'<<p->exp;
		}
		p=p->link;
	}
	cout<<endl;
}

void main()
{
	polypointer a, b, c;
	a=new polynode;
	c=Attach(2, 1, a);
	c=Attach(1, 0, c);
	Output(a);
	b=new polynode;
	c=Attach(1, 2, b);
	c=Attach(2, 1, c);
	c=Attach(5, 0, c);
	Output(b);

	c=PolyAdd(a, b);
	Output(c);
}
#endif