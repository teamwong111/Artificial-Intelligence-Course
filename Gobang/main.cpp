#include"all.h"
int dx[8] = { 1,0,1,1,-1,0,-1,-1 };
int dy[8] = { 0,1,1,-1,0,-1,-1,1 };
int whowin = -1;//0为人，1为AI
int whoplay = -1;//0为人，1为AI
int allstep = 0;//总步数
int tuple6type[4][4][4][4][4][4];//棋型辨识数组,0无子,1黑子,2白子,3边界
priority_queue<pos> que, kill;//优先队列用于算杀和极大极小搜索
pos s[255] = { 0 };//棋盘落子全记录
BOX box[board_length][board_length];
int main()
{
	init_tuple6type();//初始化评估六元组
	while (1)//游戏
	{
		init();//初始化棋盘和全局变量等
		game();//对局
	}
	Sleep(5000);//暂停5秒
	closegraph();//关闭绘图窗口
	return 0;
}