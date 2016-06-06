//��������ȫ������
#include<iostream.h> 
#define Maxsize 200 //���ѵ�����+1

typedef struct
{
     int data;
}elementtype;

typedef struct
{ 
    elementtype elements[Maxsize];
	int n;//Ԫ�ظ���
}HEAP;

void MaxHeap(HEAP &heap) //����һ���ն�
{ 
	heap.n = 0; 
} 

bool HeapEmpty(HEAP heap) //�ж϶��Ƿ�Ϊ�� 
{  
	if ( !(heap.n) )
		return true;
	else
		return false; 
} 

bool HeapFull(HEAP heap) //�ж϶��Ƿ�Ϊ�� 
{
	if ( heap.n == Maxsize - 1 )
		return true;
	else
		return false;
} 

void Insert(HEAP &heap, elementtype element) //�ڶ�heap�в���Ԫ��ֵΪelement�Ľ��
{
	int i;
	if( !HeapFull(heap) )//�Ѳ���
	{
		i = ++heap.n;
		while( (i!=1) && (element.data>heap.elements[i/2].data) )
		{
			heap.elements[i] = heap.elements[i/2];
			i /= 2;
		}
		heap.elements[i] = element; 
	} 
} 
//�����������H[0]�Ŀռ���˷ѵ���

elementtype DeleteMax(HEAP &heap) //ɾ�����е����Ԫ��
 {
	int paraent = 1, child = 2;
	elementtype element, tmp;
	if ( !HeapEmpty(heap) )
	{
		element = heap.elements[1];
		tmp = heap.elements[heap.n--];
		while ( child <= heap.n )
		{ 
            if( (child<heap.n)&&(heap.elements[child].data<heap.elements[child+1].data) )
				child++;
            if ( tmp.data >= heap.elements[child].data )
				break;
            heap.elements[paraent] = heap.elements[child];
            paraent = child;
            child *= 2;
		}
  heap.elements[paraent] = tmp;  
  return element;
	} 
} 

//���Ҷ��е�Ԫ��,������ڷ���Ԫ�ص�λ�ã���������ڷ���0
/*
int Find(HEAP H, int x)
 { 
    int p = 1; //��p��ʱ��ʾx�������е�λ��
	for(;p<=H.n;)
	{
		if(H.elements[p].data==x)
			return p;
		p++;
	}
	return 0;
 }
 */
//ע�����������ǰѶ�������Ԫ�ر�����һ�飬����ʱ�临�Ӷ�ΪO��n����nΪԪ�ظ���

//�������ѵ��ص�����Ż�Find����,����ʱ�临�Ӷȣ�ʵ��������������ƽ�������ʱ�併���ˣ�
/*
int Find(HEAP H,int x)
{
	int p=1;
	for(;p<=H.n;)
	{
		if(H.elements[p].data==x)
			return p;
		else if(x>H.elements[2*p].data&&x<=H.elements[2*p+1].data)//���x������������Ԫ�ز�������������Ԫ�أ�ֱ�Ӵ�������������x
		{
			p=2*p+1;
			if(x==H.elements[p].data)
				return p;
		}
		else if(x<=H.elements[2*p].data&&x>H.elements[2*p+1].data)//���x������������Ԫ�ز�������������Ԫ�أ�ֱ�Ӵ�������������x
		{
			p*=2;
			if(x==H.elements[p].data)
				return p;
		}
		else if(x>H.elements[2*p].data&&x>H.elements[2*p+1].data)//���x��������������Ԫ�أ�ֱ�ӷ���0
			return 0;
		else//���x�Ȳ�����������Ҳ������������
			p++;
	}
}
*/
//��bug����x�����ҽڵ㶼Сʱ�����������������Ե�

//�ݹ鷽���Ż���xΪҪ���ҵ�Ԫ�أ�hΪ�������
int Find(HEAP H,int x,int h)
{
	int i=h;
	int y=0;
	if(H.elements[h].data==x)
		return i;
	if(H.elements[2*i].data>=x)
		y=Find(H,x,i*2);
	if(y==0&&H.elements[i*2+1].data>=x)
		y=Find(H,x,i*2+1);
	return y;
}


 void main()
 {
	 HEAP H; //����һ����
     elementtype element;//����һ����Ԫ�� 
     int data[] = {1, 3, 5, 7, 9, 11, 13};//���е�Ԫ��ֵ����
	 MaxHeap(H);//�ն�
	 //����в���Ԫ�ع������ѣ�����H[0]�ռ�û������
     for ( int i = 0; i < 7; i++ )
	 {
		 element.data = data[i];
		 Insert(H, element);
	 }
	 cout<<"����Ԫ��Ϊ��"<<endl;
	 for (i = 1; i <= H.n; i++ )
		 cout << H.elements[i].data << ' ';
	 cout << endl;
	 if(!HeapEmpty(H))
		 cout<<"�öѲ�Ϊ�գ�"<<endl;
	 if(!HeapFull(H))
		 cout<<"�öѲ�����"<<endl;
	// cout<<H.elements[1].key<<endl;
cout<<"��������ҵ�Ԫ�أ�";
int x;
cin>>x;
cout <<"��Ԫ���ڶ��е�λ��Ϊ��"<< Find(H,x,1) << endl;
cout<<"ɾ�����е����Ԫ��Ϊ��"<<endl;
cout<<DeleteMax(H).data<<endl;
cout<<"��������ҵ�Ԫ�أ�";
cin>>x;
cout <<"��Ԫ���ڶ��е�λ��Ϊ��"<< Find(H,x,1) << endl;
}