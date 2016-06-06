#include "index.h"

#ifdef _STRING_INDEX_

#define maxlength 100

typedef char STRING[maxlength];

int Index(STRING S, STRING T) {
   // �����Ӵ�T������S�е�λ�á��������ڣ�����ֵΪ-1�����У�T�ǿա�
    int i =1 , j = 1;
    while (i < strlen(S) && j < strlen(T) ) {
      if (S[i] == T[j])  // �����ȽϺ���ַ�
	  { 
		  ++i;  
		  ++j; 
	  }  
      else 
	  { 
		  i = i-j+2;   
		  j = 1; 
	  }     // ָ��������¿�ʼƥ��
    }
   if (j >= strlen(T) )  
	   return  i-j+1;
   else 
	   return -1;
} // Index

void get_next(STRING T, int next[] ) // ��ģʽ��T��next����ֵ����������next
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
		}										   // �����ȽϺ���ַ�
		else  
			j = next[j];         // ģʽ�������ƶ�
	}
	if (j >= strlen(T))  
		return  i-strlen(T)+1;    // ƥ��ɹ�
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