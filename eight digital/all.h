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
extern char arr[10], brr[10];//��ʼ��Ŀ��
extern map<int, bool>mymap;
extern priority_queue<node> que;//���ȶ��� 
extern int change[9][4];//ÿ���������������
extern char dyna[1000][10];//���ڶ�̬չʾ
struct paint//���ڻ�������
{
	int d;//��������ֵ
	int deep;//���
	int ch;//���������
};
extern paint dynapaint[1000];