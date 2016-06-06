//ջ������ʵ��
//�˴���ջ�׹涨������ĵײ�������maxlength-1ָ��ջ�׵ĵ�һ��Ԫ�أ�topָ��ָ��ջ��Ԫ��
#include <iostream>
using namespace std;

#define maxlength 100//ջ������
typedef int Elementtype;//����ת����Ԫ������Ϊint
//typedef char Elementtype;//����ƥ����Ԫ������Ϊ�ַ���char
enum Boolean{TRUE,FALSE};

struct STACK//����������������ջ
{
	int top;
	Elementtype elements[maxlength];
};

bool isEmpty(STACK S)//ջ�Ƿ�Ϊ��
{
	if(S.top>=maxlength)
		return true;
	else
		return false;
}

void makeNull(STACK &S)//ջ�ÿ�
{
	S.top = maxlength;
}

Elementtype top(STACK S)//����ջ��Ԫ��
{
	if(isEmpty(S))
		return NULL;
	else
		return(S.elements[S.top]);
}

void pop(STACK &S)//��ջ,ɾ��ջ��Ԫ��
{
	if(isEmpty(S))
		cout<<"ջΪ�գ�"<<endl;
	else
		S.top++;
}

void push(STACK &S, Elementtype x)//��ջ
{
	if(S.top == 0)
		cout<<"ջ������"<<endl;
	else
	{
		--S.top;
		S.elements[S.top] = x;
	}
}
//=====================================================����ת��
void convert(int num,STACK &S,int n)//����ת������
{
	while(num!=0)
	{
		push(S,num%n);
		num/=n;
	}
}

void print(STACK S)//���ת��Ľ��
{
	while(!isEmpty(S))
	{
		cout<<S.elements[S.top];
		++S.top;
	}
	cout<<endl;
}
//====================================================����ƥ��
Boolean check(char *s)
{
	//�㷨˼·�������ַ�����s�����������������ջ����������������ջ�����Ž���ƥ�䣬
	//ƥ��ʧ����������FALSE��ƥ��ɹ���ջ����ջ����������
	STACK S;
	makeNull(S);
	int j=0;
	while(s[j]!='\0')
	{
		switch(s[j])
		{
		case '(':
			push(S,'(');
			break;
		case ')':
			if(top(S) == '(')
				pop(S);
			else
				return FALSE;
			break;

		case '[':
			push(S,'[');
			break;
		case ']':
			if(top(S) == '[')
				pop(S);
			else
				return FALSE;
			break;

	    case '{':
			push(S,'{');
			break;
		case '}':
			if(top(S) == '{')
				pop(S);
			else
				return FALSE;
			break;
		}
		j++;

	}
	if(isEmpty(S))
		return TRUE;
	else
		return FALSE;
}
void main()
{
	STACK S;
	makeNull(S);
	int num = 1024;
	int n = 2;
	cout<<"ת��ǰ��ʮ������Ϊ��"<<num<<endl;
	cout<<"ת�����"<<n<<"������Ϊ��";
	convert(num,S,n);
	print(S);
	
	/*
	char *s = "{((ab)b[cf])}";
	char *p = "{{(sd)asdf{}]";
	if(check(s) == TRUE)
		cout<<"{((ab)b[cf])}����ƥ�䣡"<<endl;
	else
		cout<<"{((ab)b[cf])}���Ų�ƥ�䣡"<<endl;

	if(check(p) == TRUE)
		cout<<"{{(sd)asdf{}]����ƥ�䣡"<<endl;
	else
		cout<<"{{(sd)asdf{}]���Ų�ƥ�䣡"<<endl;
		*/
}