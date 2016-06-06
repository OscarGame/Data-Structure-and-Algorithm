//���������⣡
//������ԭ��Ԫ�صĸ���
#include <iostream>
using namespace std;

//�����ṹ����
struct listnode{
    listnode *link;
    bool tag;//false��ʾ�ý��Ϊԭ�ӣ�true��ʾ���Ϊָ���ӱ��ָ��
    union{
        char data;
        listnode *dlink;
    }element;//������
};

typedef listnode *listpointer;

//��ͷ
listpointer Cal(listpointer S){
    if (S==NULL)
        return NULL;
    else
    {
        listpointer temp;
		temp->tag=S->tag;
        temp->link=S->link;
		temp->element=S->element;
		/*
		if(!temp->tag)
			temp->element.data=S->element.data;
		else
			temp->element.dlink=S->element.dlink;
			*/
        return temp;
    }
}

//��β
listpointer Cdr(listpointer S){
    if (S->link==NULL)
        return NULL;
    else
    {
        listpointer temp;
        temp->tag=S->link->tag;
        temp->link=S->link->link;
        temp->element=S->link->element;
        return temp;
    }
}

//������ԭ��Ԫ�صĸ���
int elements(listpointer L){
    //��������Ϊ�գ�����ԭ�Ӹ���Ϊ��
    if(L==NULL) 
		return 0; 
	//���������һ�������ԭ�ӷ�����������ԭ�Ӹ���+1  
	if(Cal(L)->tag==false) //��ͷΪԭ��   
		return(elements(Cdr(L))+1); 
	else //��ͷΪ�����
		return(elements(Cdr(L))); 
}

void main(){    
//���������a,(b,c),d,e��
  listpointer A= new listnode;
  A->tag=false;  
  A->element.data='a';  
  A->link=NULL;
  cout<<Cal(A)->element.data<<endl;
  /*
  listpointer B;  
  B->tag=false; 
  B->element.data='b'; 
  listpointer C;   
  C->tag=false;  
  C->link=NULL; 
  C->element.data='c'; 
  B->element.dlink=C; 
  listpointer F;
  F->tag = true;
  A->link=F;
  listpointer D;  
  D->tag=false;  
  D->element.data='d'; 
  F->link = D;
  listpointer E;  
  E->tag=false; 
  E->element.data='e';  
  E->link=NULL;  
  B->link=D; 
  D->link=E; 
  */
  //cout<<"������ԭ��Ԫ�ظ���Ϊ��"<<elements(A)<<endl; 
 
}


/*
//�ж�����������Ƿ��ͬ
bool Equal(listpointer S,listpointer T)
{    bool x,y;
    y=false;
    if ((S==NULL)&&(T==NULL))
        y=true;
    else if((S!=NULL)&&(T!=NULL))
        if (S->tag==T->tag)
        {
            if (S->tag==false)
            {
                if (S->element.data==T->element.data)
                    x=true;
                else
                    x=false;
            }
            else
                x=Equal(S->element.dlink,T->element.dlink);
            if (x==true)
                y=Equal(S->link, T->link);
        }
		return y;
}
*/
/*
//������ԭ��Ԫ�ع����
listpointer *create(char e[],int n)//������eΪԭ��Ԫ�����飬nΪԪ�ظ���
{
   listpointer *p;
   listpointer *p0 = NULL;
   listpointer *p1;
    for (int i=0; i<n; i--)
    {
		p=new listpointer;
        p->element.data=e[i];
        p->link=NULL;
		if(!p0){
		p0=p;
		p1=p0;
		}
		else{
			p0->link=p;
			p0=p0->link;
		}
    }
    return p1;
}
*/