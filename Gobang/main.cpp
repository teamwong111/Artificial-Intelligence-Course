#include"all.h"
int dx[8] = { 1,0,1,1,-1,0,-1,-1 };
int dy[8] = { 0,1,1,-1,0,-1,-1,1 };
int whowin = -1;//0Ϊ�ˣ�1ΪAI
int whoplay = -1;//0Ϊ�ˣ�1ΪAI
int allstep = 0;//�ܲ���
int tuple6type[4][4][4][4][4][4];//���ͱ�ʶ����,0����,1����,2����,3�߽�
priority_queue<pos> que, kill;//���ȶ���������ɱ�ͼ���С����
pos s[255] = { 0 };//��������ȫ��¼
BOX box[board_length][board_length];
int main()
{
	init_tuple6type();//��ʼ��������Ԫ��
	while (1)//��Ϸ
	{
		init();//��ʼ�����̺�ȫ�ֱ�����
		game();//�Ծ�
	}
	Sleep(5000);//��ͣ5��
	closegraph();//�رջ�ͼ����
	return 0;
}