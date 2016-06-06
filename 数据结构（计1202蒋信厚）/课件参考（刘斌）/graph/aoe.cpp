#include "aov.h"

#ifdef _AOE_

//AOE���ڱߵĻ������ؼ�·����������緢��ʱ�䣬��ٷ���ʱ�䣩
void aoe(AdjGraph G, int start)// ����startΪ��ʼ����±�
{
	int i, j;
	EdgeData E[NumVertices][NumVertices], VE[NumVertices], L[NumVertices][NumVertices], VL[NumVertices];
	int aov[NumVertices];
	EdgeNode *tmp;
	
	//�������¼�����������������������������aov��
	Topologicalsort( G, aov);
	
	for(i=0; i<G.n; i++)
		for(j=0; j<G.n; j++)
		{
			E[i][j]=-1;
			L[i][j]=-1;
		}

	// ��VE[i]�¼�i�����緢��ʱ��
	VE[aov[0]-1]=0;//���
	for(i=1; i<G.n; i++)    // �����������Ķ���aov[i]������
	{	
		VE[aov[i]-1]=0;
		for(j=0; j<i; j++)  // ��������aov[i]������ǰ������
		{
			tmp=G.vexlist[aov[j]].firstedge;  // �ڽӱ��ʾ��ͼ�Ķ�����±��Ǵ�1��ʼ��
			while(1)
			{
				if(tmp==NULL)
					break;
				else if(tmp->adjvex==aov[i])
				{
					if(tmp->cost+VE[aov[j]-1]>VE[aov[i]-1])	// ������������ǰ��������ǰ�����VE
						VE[aov[i]-1]=tmp->cost+VE[aov[j]-1];					
				}
				tmp=tmp->next;
			}
		}
	}
	cout<<"v3�����緢��ʱ�䣺"<<VE[3]<<endl;
	// ��E[i][j]
	for(i=0; i<G.n; i++)
	{	
		tmp=G.vexlist[i+1].firstedge;   //������i+1������ĳ���
		while(1)
		{
			if(tmp==NULL)
				break;
			else
			{
				E[i][tmp->adjvex-1]=VE[aov[i]-1];
			}
			tmp=tmp->next;
		}
	}	

	//��VL[i]�¼�i����ٷ���ʱ�䣬ת��Ϊ�����緢��ʱ������
	VL[aov[G.n-1]-1]=VE[aov[G.n-1]-1];
	for(i=G.n-2; i>=0; i--)       // �����������Ķ���aov[i]��������
	{
		VL[aov[i]-1]=VE[aov[G.n-1]-1];
		tmp=G.vexlist[aov[i]].firstedge;  // �ڽӱ��ʾ��ͼ�Ķ�����±��Ǵ�1��ʼ��
		while(1)   // ��������aov[i]�����к�̽ڵ�
		{
			if(tmp==NULL)
				break;
			else 
			{
				if(VL[aov[i]-1]>VL[tmp->adjvex -1]-tmp->cost)				
					VL[aov[i]-1]=VL[tmp->adjvex -1]-tmp->cost;					
			}
			tmp=tmp->next;
		}
		
	}

	// ��L[i][j]
	for(i=0; i<G.n; i++)
	{	
		tmp=G.vexlist[i+1].firstedge; // ������i+1������ĳ���
		while(1)
		{
			if(tmp==NULL)
				break;
			else
			{
				L[i][tmp->adjvex-1]=VL[aov[tmp->adjvex-1]-1]-tmp->cost;
			}
			tmp=tmp->next;
		}		
	}	

	//����ؼ��
	cout<<"�ؼ��Ϊ: "<<endl;
	for(i=0; i<G.n; i++)
		for(j=0; j<G.n; j++)
		{
			if(E[i][j]!=-1 && L[i][j]!=-1 && E[i][j]==L[i][j])
				cout<<i+1<<"->"<<j+1<<endl;
		}
}

void main()
{
	AdjGraph G1;
	IniADJGraph(&G1);
	// ����һ������ͼ
  	VertexData v1[9]={'v1', 'v2', 'v3', 'v4', 'v5','v6'};
	EdgeData e1[9][NumVertices]={{0, 6, 0, 4, 0, 0},
								{0, 0, 7, 0, 0, 0},
								{0, 0, 0, 0, 9, 11},
								{0, 0, 8, 0, 0, 21},
								{0, 0, 0, 0, 0, 3},
								{0, 0, 0, 0, 0, 0}};
	CreateADJGraph_directed(&G1, v1, e1, 6);

	aoe(G1, 0);
}

#endif