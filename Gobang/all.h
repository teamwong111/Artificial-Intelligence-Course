#pragma once
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <graphics.h>
#include<queue>
#include<stack>
#include <map>
using namespace std;
#define MAX 100000000//极大极小算法的初始化
#define board_length 15//棋盘长度
#define search_deep 3//局部搜索的深度
#define kill_deep 16//算杀搜索的深度
#define maxmin_deep 4//极大极小搜索的深度
#define C_NONE 0//棋子：黑子,白子,无子
#define C_BLACK 1
#define C_WHITE 2
//棋型代号 下标 权重
#define OTHER 0//0,其他棋型不考虑
#define WIN 1//10000000,白赢
#define LOSE 2//-10000000
#define FLEX4 3//10000,白活4
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
//八个方向
extern int dx[8];
extern int dy[8];
extern int whowin;//0为人，1为AI
extern int whoplay;//0为人，1为AI
extern int allstep;//总步数
extern int tuple6type[4][4][4][4][4][4];//棋型辨识数组,0无子,1黑子,2白子,3边界
//评估
struct EVALUATION 
{
	int score;
	int result;//算杀判断输赢
	int STAT[8];//储存部分棋形的个数(杀棋棋型),下标WIN=1为白连5,LOSE=2为黑连5,FLEX4=3为白活4,BLOCK4=5为白冲4,FLEX3=7为白活3
};
//落子
struct pos
{
	int x;
	int y;
	int worth;//评估值
	bool operator<(const pos& b)const
	{
		return worth < b.worth;
	}
};
extern priority_queue<pos> que, kill;//优先队列用于算杀和极大极小搜索
extern pos s[255];
//棋盘
struct BOX
{
	int x;
	int y;
	int value;//0为人，1为AI
	int isnew;//是否滑到新框
	void draw();//画出棋子
};
extern BOX box[board_length][board_length];

void init_tuple6type();//初始化评估六元组
void init();//初始化棋盘和全局变量等
bool isend();//判断对局结束
void retract(int i, int j);//悔棋
EVALUATION evaluate(int board[board_length][board_length]);//评估函数
pos seekPoints(int board[board_length][board_length], int who, int deep, bool choice);//局部搜索
int maxmin(int board[board_length][board_length], int deep, int alpha, int beta, pos& ans);//极大极小搜索
void seek_kill_points(int board[board_length][board_length]);//算杀点搜索
bool analyse_kill(int board[board_length][board_length], int deep, int who, pos& ans);//算杀搜索
void game();//对局