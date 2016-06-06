#include "index.h"

#ifdef _STRING_INDEX_

#define maxlength 100

typedef char STRING[maxlength];

int Index(STRING S, STRING T) {
   // 返回子串T在主串S中的位置。若不存在，则函数值为-1。其中，T非空。
    int i =1 , j = 1;
    while (i < strlen(S) && j < strlen(T) ) {
      if (S[i] == T[j])  // 继续比较后继字符
	  { 
		  ++i;  
		  ++j; 
	  }  
      else 
	  { 
		  i = i-j+2;   
		  j = 1; 
	  }     // 指针后退重新开始匹配
    }
   if (j >= strlen(T) )  
	   return  i-j+1;
   else 
	   return -1;
} // Index

void get_next(STRING T, int next[] ) // 求模式串T的next函数值并存入数组next
{     
	int i = 1,  j = 0;
	next[1] = 0; 
	while (i < strlen(T)) {
		if (j == 0 || T[i] == T[j])
		{
			++i;  
			++j; 
			next[i] = j; 
		}
		else 
		{
			j = next[j];
   
		}
	}
 } // get_next


void get_nextval(STRING T, int nextval[]) 
{
	int i = 1, j = 0;
	nextval[1] = 0;
	while (i < strlen(T)) 
	{
		if (j == 0 || T[i] == T[j]) 
		{
			++i;  
			++j;
			if (T[i] != T[j])  
				nextval[i] = j;
			else  
				nextval[i] = nextval[j];
		}
		else  
			j = nextval[j];
	}
} // get_nextval

int Index_KMP(STRING S, STRING T) 
{    
	int next[maxlength];
	get_next(T, next);
	
	int i = 1, j = 1;
	while (i < strlen(S) && j < strlen(T)) {
		if (j == 0 || S[i] == T[j]) 
		{ 
			++i;  
			++j; 
		}										   // 继续比较后继字符
		else  
			j = next[j];         // 模式串向右移动
	}
	if (j >= strlen(T))  
		return  i-strlen(T)+1;    // 匹配成功
	else 
		return -1;
} // Index_KMP



int main()
{
	STRING S1="0ababababababbaab", S2="0abababb", S3="0abaabcac", S4="0abcaababc";

	int next[20];
	get_nextval(S4, next);
	for(int i=1; i<strlen(S4); i++)
		cout<<next[i]<<' ';
	cout<<endl;

	cout<<Index(S1, S2)<<endl;

	cout<<Index_KMP(S1, S2)<<endl;

	return 0;
}


#endif