#include"all.h"
void BOX::draw()//画出棋子
{
	COLORREF thefillcolor = getfillcolor();//备份填充颜色
	setlinestyle(PS_SOLID, 2);//线样式设置
	setwritemode(R2_XORPEN);//设置XOR绘图模式
	setlinecolor(LIGHTGRAY);
	if (whoplay == 0)
	{
		line(x + 1, y + 2, x + 8, y + 2);
		line(x + 2, y + 1, x + 2, y + 8);
		line(x + 29, y + 2, x + 22, y + 2);
		line(x + 29, y + 1, x + 29, y + 8);
		line(x + 2, y + 29, x + 8, y + 29);
		line(x + 2, y + 22, x + 2, y + 29);
		line(x + 29, y + 29, x + 22, y + 29);
		line(x + 29, y + 22, x + 29, y + 29);
	}
	setwritemode(R2_COPYPEN);
	if (value == 0)//黑棋
	{
		setfillcolor(BLACK);
		fillcircle(x + 15, y + 15, 13);
	}
	else if (value == 1)//白棋
	{
		setfillcolor(WHITE);
		fillcircle(x + 15, y + 15, 13);
	}
	setfillcolor(thefillcolor); //还原填充色
}
bool isend()//是否结束
{
	for (int i = 0; i < board_length; i++)//遍历每个可能的位置
	{
		for (int j = 0; j < board_length; j++)
		{
			if (box[i][j].value == whoplay)
			{
				int length[8] = { 0,0,0,0,0,0,0,0 };//八个方向的长度
				for (int k = 0; k < 8; k++)
				{
					int nowi = i;
					int nowj = j;
					while (nowi <= 14 && nowj <= 14 && nowi >= 0 && nowj >= 0 && box[nowi][nowj].value == whoplay)
					{
						length[k]++;
						nowj += dx[k];
						nowi += dy[k];
						if (length[k] >= 5)
						{
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}
void retract(int i, int j)//悔棋
{
	if (box[i][j].value == 0)//黑棋
	{
		setfillcolor(BLACK);
		fillcircle(box[i][j].x + 15, box[i][j].y + 15, 13);
	}
	else if (box[i][j].value == 1)//白棋
	{
		setfillcolor(WHITE);
		fillcircle(box[i][j].x + 15, box[i][j].y + 15, 13);
	}
}
void game()//对局
{
	int oldi = -1, oldj = -1;//上一个鼠标停的坐标
	//box[oldi][oldj].draw();
	while (1)
	{
		bool retraction = false;//还没有悔棋
		if (whoplay == 0)// 玩家下棋
		{
			MOUSEMSG mouse = GetMouseMsg();//获取鼠标信息
			for (int i = 0; i < board_length; i++)
			{
				for (int j = 0; j < board_length; j++)
				{
					//重新开始
					if (mouse.x < 150 && mouse.x>0 && mouse.y < 500 && mouse.y> 450)
					{
						setfillcolor(RGB(150, 150, 150));
						solidrectangle(25, 460, 125, 490);
						outtextxy(27, 460, _T("重新开始"));
						if (mouse.uMsg == WM_LBUTTONUP)
						{
							mouse.uMsg = WM_MOUSEMOVE;
							return;
						}					
					}
					//退出
					if (mouse.x < 300 && mouse.x>150 && mouse.y < 500 && mouse.y> 450)
					{
						setfillcolor(RGB(150, 150, 150));
						solidrectangle(175, 460, 275, 490);
						outtextxy(200, 460, _T("退出"));
						if (mouse.uMsg == WM_LBUTTONUP)
						{
							mouse.uMsg = WM_MOUSEMOVE;
							exit(0);
						}					
					}
					//悔棋
					if (mouse.x < 450 && mouse.x>300 && mouse.y < 500 && mouse.y> 450 && allstep > 2)
					{
						setfillcolor(RGB(150, 150, 150));
						solidrectangle(325, 460, 425, 490);
						outtextxy(350, 460, _T("悔棋"));
						if (mouse.uMsg == WM_LBUTTONUP)
						{
							mouse.uMsg = WM_MOUSEMOVE;
							IMAGE img;//重新把之前的棋盘情况生成一遍
							loadimage(&img, _T("2.jpg"));
							putimage(0, 0, &img);
							allstep--;
							box[s[allstep].y][s[allstep].x].value = -1;
							allstep--;
							box[s[allstep].y][s[allstep].x].value = -1;
							for (int i = 0; i < allstep; i++)
							{
								retract(s[i].y, s[i].x);
							}
							retraction = true;
							oldi = -1;
							oldj = -1;
							break;
						}
					}
					//判断位置
					if (mouse.x > box[i][j].x && mouse.x<box[i][j].x + 30 && mouse.y>box[i][j].y && mouse.y < box[i][j].y + 30 && box[i][j].value == -1)
					{
						if (oldi >= 0 && oldj >= 0)
						{						
							box[oldi][oldj].isnew = false;//如果停在某一个空位置上面,更新选择框
							box[oldi][oldj].draw();
						}
						box[i][j].isnew = true;
						box[i][j].draw();
						if (mouse.mkLButton)// 如果按下了
						{
							pos my;//放入棋盘数组
							my.x = j;
							my.y = i;
							s[allstep] = my;
							box[i][j].value = 0; //下棋
							box[i][j].draw();//画出棋子
							if (isend())//判断结束
							{
								outtextxy(225, 250, _T("玩家胜"));
								Sleep(5000);
								return;
							}
							else if (allstep == 255)//判断平局
							{
								outtextxy(225, 250, _T("平局"));
								Sleep(5000);
								return;
							}
							oldi = -1;
							oldj = -1;
							allstep++;//总步数+1
							whoplay = 1;//转到AI
							break;
						}
						oldi = i;//旧位置更新
						oldj = j;
					}
				}			
				if (whoplay == 1 || retraction == true)//跳出循环
					break;
			}
		}
		else//AI下棋
		{
			pos best = { 0,0,0 };
			int board[board_length][board_length];
			for (int i = 0; i < board_length; i++)
			{
				for (int j = 0; j < board_length; j++)
				{
					board[i][j] = box[i][j].value;
				}
			}
			while (!kill.empty())//清空算杀队列
				kill.pop();
			if (!analyse_kill(board, kill_deep, 1, best))//算杀搜索并判断
			{
				for (int i = 0; i < board_length; i++)
				{
					for (int j = 0; j < board_length; j++)
					{
						board[i][j] = box[i][j].value;
					}
				}
				maxmin(board, maxmin_deep, -MAX, MAX, best);//极大极小搜索
			}
			box[best.y][best.x].value = 1;//下在最佳位置
			box[best.y][best.x].isnew = true;
			s[allstep] = best;
			box[best.y][best.x].draw();
			if (isend())
			{
				outtextxy(225, 250, _T("AI胜"));
				Sleep(5000);
				return;
			}
			allstep++;
			whoplay = 0;
		}
	}
}