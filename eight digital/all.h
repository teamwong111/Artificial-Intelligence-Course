#define CLOCKS_PER_SEC ((clock_t)1000)
#include<iostream>
#include<cstdio>
#include<ctime>
#include<queue>
#include<map>
#include<graphics.h>
using namespace std;
void swap(char* ch, int a, int b);
void bfsHash(int start, int zeroPos, int target, int& extend, int& generate, int choice);
void solvable();
void dynamic(int extend, int generate);
struct node
{
	int num, step, cost, zeroPos, choice;
	bool operator<(const node& a)const;
	node(int n, int s, int p, int c);
	void setCost(int choice);
};
extern char arr[10], brr[10];//初始和目标
extern map<int, bool>mymap;
extern priority_queue<node> que;//优先队列 
extern int change[9][4];//每个数上下左右情况
extern char dyna[1000][10];//用于动态展示
struct paint//用于画搜索树
{
	int d;//评估函数值
	int deep;//深度
	int ch;//八数码情况
};
extern paint dynapaint[1000];