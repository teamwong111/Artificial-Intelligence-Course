#pragma once
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <graphics.h>
#include<queue>
#include<stack>
#include <map>
using namespace std;
#define MAX 100000000//����С�㷨�ĳ�ʼ��
#define board_length 15//���̳���
#define search_deep 3//�ֲ����������
#define kill_deep 16//��ɱ���������
#define maxmin_deep 4//����С���������
#define C_NONE 0//���ӣ�����,����,����
#define C_BLACK 1
#define C_WHITE 2
//���ʹ��� �±� Ȩ��
#define OTHER 0//0,�������Ͳ�����
#define WIN 1//10000000,��Ӯ
#define LOSE 2//-10000000
#define FLEX4 3//10000,�׻�4
#define flex4 4//-100000
#define BLOCK4 5//400
#define block4 6//-100000
#define FLEX3 7//400
#define flex3 8//-10000
#define BLOCK3 9//20
#define block3 10//-40
#define FLEX2 11//20
#define flex2 12//-40
#define BLOCK2 13//1
#define block2 14//-2
#define FLEX1 15//1
#define flex1 16//-2
//�˸�����
extern int dx[8];
extern int dy[8];
extern int whowin;//0Ϊ�ˣ�1ΪAI
extern int whoplay;//0Ϊ�ˣ�1ΪAI
extern int allstep;//�ܲ���
extern int tuple6type[4][4][4][4][4][4];//���ͱ�ʶ����,0����,1����,2����,3�߽�
//����
struct EVALUATION 
{
	int score;
	int result;//��ɱ�ж���Ӯ
	int STAT[8];//���沿�����εĸ���(ɱ������),�±�WIN=1Ϊ����5,LOSE=2Ϊ����5,FLEX4=3Ϊ�׻�4,BLOCK4=5Ϊ�׳�4,FLEX3=7Ϊ�׻�3
};
//����
struct pos
{
	int x;
	int y;
	int worth;//����ֵ
	bool operator<(const pos& b)const
	{
		return worth < b.worth;
	}
};
extern priority_queue<pos> que, kill;//���ȶ���������ɱ�ͼ���С����
extern pos s[255];
//����
struct BOX
{
	int x;
	int y;
	int value;//0Ϊ�ˣ�1ΪAI
	int isnew;//�Ƿ񻬵��¿�
	void draw();//��������
};
extern BOX box[board_length][board_length];

void init_tuple6type();//��ʼ��������Ԫ��
void init();//��ʼ�����̺�ȫ�ֱ�����
bool isend();//�ж϶Ծֽ���
void retract(int i, int j);//����
EVALUATION evaluate(int board[board_length][board_length]);//��������
pos seekPoints(int board[board_length][board_length], int who, int deep, bool choice);//�ֲ�����
int maxmin(int board[board_length][board_length], int deep, int alpha, int beta, pos& ans);//����С����
void seek_kill_points(int board[board_length][board_length]);//��ɱ������
bool analyse_kill(int board[board_length][board_length], int deep, int who, pos& ans);//��ɱ����
void game();//�Ծ�