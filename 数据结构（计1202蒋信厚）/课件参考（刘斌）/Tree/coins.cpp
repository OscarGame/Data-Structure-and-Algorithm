#include "index.h"

//�ж���

#ifdef _COINS_

char Compare(int a, int b)
{
	if(a>b)
		return '>';
	else if(a==b)
		return '=';
	else
		return '<';
}

// ����x>y����x���׼��z���бȽ�
void comp(int x, int y, int z)
{
	if(x>z) cout<<x<<" heavy"<<endl;
	else cout<<y<<" light"<<endl;
}

void eightcoins()
{
	int a, b, c, d, e, f, g, h;
	cin>>a>>b>>c>>d>>e>>f>>g>>h;

	switch(Compare(a+b+c, d+e+f))
	{
	case '=': 
		if(g>h) comp(g, h, a);
		else comp(h, g, a);
		break;
	case '>':
		switch( Compare(a+d, b+e))
		{
		case '=': comp(c, f, a); break;
		case '>': comp(a, e, b); break;
		case '<': comp(b, d, a); break;
		}
		break;
	case '<':
		switch( Compare(a+d, b+e))
		{
		case '=': comp(f, c, a); break;
		case '>': comp(d, b, a); break;
		case '<': comp(e, a, b); break;
		}
		break;
	}
}

void main()
{
	eightcoins();
}

#endif