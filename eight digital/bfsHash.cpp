#include"all.h"
void swap(char* ch, int a, int b)//交换ch[]中a,b两位置的数
{
	char c = ch[a];
	ch[a] = ch[b];
	ch[b] = c;
}
void bfsHash(int start, int zeroPos, int target, int& extend, int& generate, int choice)
{
	char temp[10];
	node A(start, 0, zeroPos, choice);//创建一个节点 
	que.push(A);//压入优先队列 
	++generate;//生成节点数+1
	dynapaint[generate - 1].d = A.cost;
	dynapaint[generate - 1].ch = A.num;
	dynapaint[generate - 1].deep = A.step;
	mymap[start] = 1;//标记节点被访问过 
	while (!que.empty())
	{
		A = que.top();
		que.pop();
		++extend;//扩展节点数+1
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
					node B(k, A.step + 1, change[pos][i], choice);//创建一个新节点并压入队列 
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