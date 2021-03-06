#include"all.h"
void init_tuple6type()//初始化评估六元组
{
	memset(tuple6type, 0, sizeof(tuple6type));//全部设为0
	//白连5,ai赢
	tuple6type[2][2][2][2][2][2] = WIN;
	tuple6type[2][2][2][2][2][0] = WIN;
	tuple6type[0][2][2][2][2][2] = WIN;
	tuple6type[2][2][2][2][2][1] = WIN;
	tuple6type[1][2][2][2][2][2] = WIN;
	tuple6type[3][2][2][2][2][2] = WIN;//边界考虑
	tuple6type[2][2][2][2][2][3] = WIN;
	//黑连5,ai输
	tuple6type[1][1][1][1][1][1] = LOSE;
	tuple6type[1][1][1][1][1][0] = LOSE;
	tuple6type[0][1][1][1][1][1] = LOSE;
	tuple6type[1][1][1][1][1][2] = LOSE;
	tuple6type[2][1][1][1][1][1] = LOSE;
	tuple6type[3][1][1][1][1][1] = LOSE;
	tuple6type[1][1][1][1][1][3] = LOSE;
	//白活4
	tuple6type[0][2][2][2][2][0] = FLEX4;
	//黑活4
	tuple6type[0][1][1][1][1][0] = flex4;
	//白活3
	tuple6type[0][2][2][2][0][0] = FLEX3;
	tuple6type[0][0][2][2][2][0] = FLEX3;
	tuple6type[0][2][0][2][2][0] = FLEX3;
	tuple6type[0][2][2][0][2][0] = FLEX3;
	//黑活3
	tuple6type[0][1][1][1][0][0] = flex3;
	tuple6type[0][0][1][1][1][0] = flex3;
	tuple6type[0][1][0][1][1][0] = flex3;
	tuple6type[0][1][1][0][1][0] = flex3;
	//白活2
	tuple6type[0][2][2][0][0][0] = FLEX2;
	tuple6type[0][2][0][2][0][0] = FLEX2;
	tuple6type[0][2][0][0][2][0] = FLEX2;
	tuple6type[0][0][2][2][0][0] = FLEX2;
	tuple6type[0][0][2][0][2][0] = FLEX2;
	tuple6type[0][0][0][2][2][0] = FLEX2;
	//黑活2
	tuple6type[0][1][1][0][0][0] = flex2;
	tuple6type[0][1][0][1][0][0] = flex2;
	tuple6type[0][1][0][0][1][0] = flex2;
	tuple6type[0][0][1][1][0][0] = flex2;
	tuple6type[0][0][1][0][1][0] = flex2;
	tuple6type[0][0][0][1][1][0] = flex2;
	//白活1
	tuple6type[0][2][0][0][0][0] = FLEX1;
	tuple6type[0][0][2][0][0][0] = FLEX1;
	tuple6type[0][0][0][2][0][0] = FLEX1;
	tuple6type[0][0][0][0][2][0] = FLEX1;
	//黑活1
	tuple6type[0][1][0][0][0][0] = flex1;
	tuple6type[0][0][1][0][0][0] = flex1;
	tuple6type[0][0][0][1][0][0] = flex1;
	tuple6type[0][0][0][0][1][0] = flex1;

	int p1, p2, p3, p4, p5, p6, x, y, ix, iy;//x:左5中黑个数,y:左5中白个数,ix:右5中黑个数,iy:右5中白个数
	for (p1 = 0; p1 < 4; ++p1) {
		for (p2 = 0; p2 < 3; ++p2) {
			for (p3 = 0; p3 < 3; ++p3) {
				for (p4 = 0; p4 < 3; ++p4) {
					for (p5 = 0; p5 < 3; ++p5) {
						for (p6 = 0; p6 < 4; ++p6) {
							x = y = ix = iy = 0;

							if (p1 == 1)x++;
							else if (p1 == 2)y++;

							if (p2 == 1) { x++; ix++; }
							else if (p2 == 2) { y++; iy++; }

							if (p3 == 1) { x++; ix++; }
							else if (p3 == 2) { y++; iy++; }

							if (p4 == 1) { x++; ix++; }
							else if (p4 == 2) { y++; iy++; }

							if (p5 == 1) { x++; ix++; }
							else if (p5 == 2) { y++; iy++; }

							if (p6 == 1)ix++;
							else if (p6 == 2)iy++;

							if (p1 == 3 || p6 == 3) {//有边界
								if (p1 == 3 && p6 != 3) {//左边界
									//白冲4
									if (ix == 0 && iy == 4) {//若右边有空位是活4也没关系，因为活4权重远大于冲4，再加上冲4权重变化可以不计
										if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
											tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK4;
									}
									//黑冲4
									if (ix == 4 && iy == 0) {
										if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
											tuple6type[p1][p2][p3][p4][p5][p6] = block4;
									}
									//白眠3
									if (ix == 0 && iy == 3) {
										if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
											tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK3;
									}
									//黑眠3
									if (ix == 3 && iy == 0) {
										if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
											tuple6type[p1][p2][p3][p4][p5][p6] = block3;
									}
									//白眠2
									if (ix == 0 && iy == 2) {
										if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
											tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK2;
									}
									//黑眠2
									if (ix == 2 && iy == 0) {
										if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
											tuple6type[p1][p2][p3][p4][p5][p6] = block2;
									}
								}
								else if (p6 == 3 && p1 != 3) {//右边界
								   //白冲4
									if (x == 0 && y == 4) {
										if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
											tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK4;
									}
									//黑冲4
									if (x == 4 && y == 0) {
										if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
											tuple6type[p1][p2][p3][p4][p5][p6] = block4;
									}
									//黑眠3
									if (x == 3 && y == 0) {
										if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
											tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK3;
									}
									//白眠3
									if (x == 0 && y == 3) {
										if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
											tuple6type[p1][p2][p3][p4][p5][p6] = block3;
									}
									//黑眠2
									if (x == 2 && y == 0) {
										if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
											tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK2;
									}
									//白眠2
									if (x == 0 && y == 2) {
										if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
											tuple6type[p1][p2][p3][p4][p5][p6] = block2;
									}
								}
							}
							else {//无边界
							   //白冲4
								if ((x == 0 && y == 4) || (ix == 0 && iy == 4)) {
									if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
										tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK4;
								}
								//黑冲4
								if ((x == 4 && y == 0) || (ix == 4 && iy == 0)) {
									if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
										tuple6type[p1][p2][p3][p4][p5][p6] = block4;
								}
								//白眠3
								if ((x == 0 && y == 3) || (ix == 0 && iy == 3)) {
									if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
										tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK3;
								}
								//黑眠3
								if ((x == 3 && y == 0) || (ix == 3 && iy == 0)) {
									if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
										tuple6type[p1][p2][p3][p4][p5][p6] = block3;
								}
								//白眠2
								if ((x == 0 && y == 2) || (ix == 0 && iy == 2)) {
									if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
										tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK2;
								}
								//黑眠2
								if ((x == 2 && y == 0) || (ix == 2 && iy == 0)) {
									if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
										tuple6type[p1][p2][p3][p4][p5][p6] = block2;
								}
							}
						}
					}
				}
			}
		}
	}
}
void init()//初始化棋盘和全局变量等
{
	initgraph(450, 500);//初始化绘图环境
	setbkcolor(BLACK);
	cleardevice();
	setbkmode(TRANSPARENT);//设置透明文字输出背景
	IMAGE img;
	loadimage(&img, _T("./resources/board.jpg"));//载入棋盘图片
	putimage(0, 0, &img);
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 30;
	wcscpy_s(f.lfFaceName, L"微软雅黑 Light");
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(WHITE);
	setfillcolor(RGB(100, 100, 100));
	solidrectangle(25, 460, 125, 490);//绘制边框
	solidrectangle(175, 460, 275, 490);
	solidrectangle(325, 460, 425, 490);
	outtextxy(27, 460, _T("重新开始"));
	outtextxy(200, 460, _T("退出"));
	outtextxy(350, 460, _T("悔棋"));
	//变量初始化
	whowin = -1;
	whoplay = 0;
	allstep = 0;
	memset(s, 0, sizeof(s));
	while (!que.empty())
		que.pop();
	while (!kill.empty())
		kill.pop();
	for (int i = 0; i < board_length; i++)
		for (int j = 0; j < board_length; j++)
		{
			box[i][j].value = -1;
			box[i][j].x = j * 30;
			box[i][j].y = i * 30;
		}
}