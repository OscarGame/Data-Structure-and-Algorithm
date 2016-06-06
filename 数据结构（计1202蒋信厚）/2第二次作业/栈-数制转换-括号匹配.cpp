//栈的数组实现
//此处将栈底规定在数组的底部，即让maxlength-1指向栈底的第一个元素，top指针指向栈顶元素
#include <iostream>
using namespace std;

#define maxlength 100//栈的容量
typedef int Elementtype;//数制转换中元素类型为int
//typedef char Elementtype;//括号匹配中元素类型为字符型char
enum Boolean{TRUE,FALSE};

struct STACK//定义整型线性数组栈
{
	int top;
	Elementtype elements[maxlength];
};

bool isEmpty(STACK S)//栈是否为空
{
	if(S.top>=maxlength)
		return true;
	else
		return false;
}

void makeNull(STACK &S)//栈置空
{
	S.top = maxlength;
}

Elementtype top(STACK S)//返回栈顶元素
{
	if(isEmpty(S))
		return NULL;
	else
		return(S.elements[S.top]);
}

void pop(STACK &S)//出栈,删除栈顶元素
{
	if(isEmpty(S))
		cout<<"栈为空！"<<endl;
	else
		S.top++;
}

void push(STACK &S, Elementtype x)//进栈
{
	if(S.top == 0)
		cout<<"栈已满！"<<endl;
	else
	{
		--S.top;
		S.elements[S.top] = x;
	}
}
//=====================================================数制转换
void convert(int num,STACK &S,int n)//进制转换函数
{
	while(num!=0)
	{
		push(S,num%n);
		num/=n;
	}
}

void print(STACK S)//输出转后的结果
{
	while(!isEmpty(S))
	{
		cout<<S.elements[S.top];
		++S.top;
	}
	cout<<endl;
}
//====================================================括号匹配
Boolean check(char *s)
{
	//算法思路：遍历字符数组s，如果是左括号则入栈，如果是右括号则跟栈顶符号进行匹配，
	//匹配失败立即返回FALSE，匹配成功将栈顶出栈，继续运行
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
	cout<<"转化前的十进制数为："<<num<<endl;
	cout<<"转化后的"<<n<<"进制数为：";
	convert(num,S,n);
	print(S);
	
	/*
	char *s = "{((ab)b[cf])}";
	char *p = "{{(sd)asdf{}]";
	if(check(s) == TRUE)
		cout<<"{((ab)b[cf])}括号匹配！"<<endl;
	else
		cout<<"{((ab)b[cf])}括号不匹配！"<<endl;

	if(check(p) == TRUE)
		cout<<"{{(sd)asdf{}]括号匹配！"<<endl;
	else
		cout<<"{{(sd)asdf{}]括号不匹配！"<<endl;
		*/
}