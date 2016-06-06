//程序有问题！
//求广义表原子元素的个数
#include <iostream>
using namespace std;

//广义表结构的型
struct listnode{
    listnode *link;
    bool tag;//false表示该结点为原子，true表示结点为指向子表的指针
    union{
        char data;
        listnode *dlink;
    }element;//共用体
};

typedef listnode *listpointer;

//表头
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

//表尾
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

//求广义表原子元素的个数
int elements(listpointer L){
    //如果广义表为空，返回原子个数为零
    if(L==NULL) 
		return 0; 
	//如果广义表第一个结点是原子返回其他结点的原子个数+1  
	if(Cal(L)->tag==false) //表头为原子   
		return(elements(Cdr(L))+1); 
	else //表头为广义表
		return(elements(Cdr(L))); 
}

void main(){    
//建立广义表（a,(b,c),d,e）
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
  //cout<<"广义表的原子元素个数为："<<elements(A)<<endl; 
 
}


/*
//判断两个广义表是否等同
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
//创建纯原子元素广义表
listpointer *create(char e[],int n)//参数：e为原子元素数组，n为元素个数
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