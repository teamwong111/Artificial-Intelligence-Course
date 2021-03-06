#include"all.h"
char arr[10], brr[10];
bool node::operator<(const node& a)const
{
	return cost > a.cost;
}
node::node(int n, int s, int p, int c)
{
	num = n, step = s, zeroPos = p, choice = c;
	setCost(choice);
}
void node::setCost(int choice)
{
	char a[10];
	int c = 0;
	sprintf_s(a, "%09d", num);
	if (choice == 1)
	{
		for (int i = 0; i < 9; i++)
			if (a[i] != brr[i])
				c++;
		cost = c + step;
	}
	else if (choice == 2)
	{
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
			{
				if (a[i] == brr[j] && a[i] != '0')
				{
					c += int(fabs(i / 3 - j / 3) + fabs(i % 3 - j % 3));
				}
			}
		cost = c + step;
	}
}
map<int, bool>mymap;
priority_queue<node> que;//���ȶ��� 
int change[9][4] = {
	{-1,-1,3,1},
	{-1,0,4,2},
	{-1,1,5,-1},
	{0,-1,6,4},
	{1,3,7,5},
	{2,4,8,-1},
	{3,-1,-1,7},
	{4,6,-1,8},
	{5,7,-1,-1}
};
char dyna[1000][10];
paint dynapaint[1000];
int main()
{
	int start, zeropos, target, extend = 0, generate = 0, choice = 1;
	clock_t starttime, finishtime;
	double  duration;
	cout << "�������ʼ״̬��" << endl;
	for (int i = 0; i < 9; i++)
		cin >> arr[i];
	cout << "������Ŀ��״̬��" << endl;
	for (int i = 0; i < 9; i++)
		cin >> brr[i];
	cout << "���������ۺ���ѡ��1/2��" << endl;//���ۺ���1Ϊ���+����λ�������������ۺ���2Ϊ���+�������ӵ���Ŀ��λ�õľ����
	cin >> choice;
	cout << endl << "�����" << endl;
	solvable();
	starttime = clock();
	for (zeropos = 0; zeropos < 9; zeropos++)
		if (arr[zeropos] == '0')
			break;
	sscanf_s(arr, "%d", &start);
	sscanf_s(brr, "%d", &target);
	bfsHash(start, zeropos, target, extend, generate, choice);
	finishtime = clock();
	duration = ((double)finishtime - (double)starttime) / CLOCKS_PER_SEC;//����ʱ��
	cout << "�������ѵ�ʱ�䣺" << duration << "s" << endl;
	cout << "����չ�ڵ���Ϊ��" << extend << endl;
	cout << "�����ɽڵ���Ϊ��" << generate << endl;
	cout << "5���ʼ��̬չʾ����ͼ" << endl;
	dynamic(extend, generate);
	return 0;
}
