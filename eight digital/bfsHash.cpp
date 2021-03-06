#include"all.h"
void swap(char* ch, int a, int b)//����ch[]��a,b��λ�õ���
{
	char c = ch[a];
	ch[a] = ch[b];
	ch[b] = c;
}
void bfsHash(int start, int zeroPos, int target, int& extend, int& generate, int choice)
{
	char temp[10];
	node A(start, 0, zeroPos, choice);//����һ���ڵ� 
	que.push(A);//ѹ�����ȶ��� 
	++generate;//���ɽڵ���+1
	dynapaint[generate - 1].d = A.cost;
	dynapaint[generate - 1].ch = A.num;
	dynapaint[generate - 1].deep = A.step;
	mymap[start] = 1;//��ǽڵ㱻���ʹ� 
	while (!que.empty())
	{
		A = que.top();
		que.pop();
		++extend;//��չ�ڵ���+1
		sprintf_s(temp, "%09d", A.num);
		strcpy_s(dyna[extend - 1], temp);
		int pos = A.zeroPos, k;
		for (int i = 0; i < 4; i++)
		{
			if (change[pos][i] != -1)
			{
				swap(temp, pos, change[pos][i]);
				sscanf_s(temp, "%d", &k);
				if (k == target)
				{
					strcpy_s(dyna[extend], temp);
					dynapaint[generate].d = A.step+1;
					dynapaint[generate].ch = k;
					dynapaint[generate].deep = A.step + 1;
					return;
				}
				if (mymap.count(k) == 0)
				{
					node B(k, A.step + 1, change[pos][i], choice);//����һ���½ڵ㲢ѹ����� 
					que.push(B);
					++generate;
					dynapaint[generate - 1].d = B.cost;
					dynapaint[generate - 1].ch = B.num;
					dynapaint[generate - 1].deep = B.step;
					mymap[k] = 1;
				}
				swap(temp, pos, change[pos][i]);
			}
		}
	}
	return;
}