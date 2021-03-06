#include"all.h"
void dynamic(int extend, int generate)
{
	int deepnum[5] = { 0 };
	for (int i = 0; i <= generate; i++)
		deepnum[dynapaint[i].deep]++;
	Sleep(5000);//休眠5秒
	initgraph(1440, 720);
	setbkcolor(WHITE); //设置背景色
	settextstyle(30, 30, _T("Courier"));// 设置字体
	settextcolor(BLACK);//设置字体色
	setlinecolor(BLACK);//设置线颜色
	setlinestyle(PS_SOLID, 3);//设置线形
	for (int i = 0; i <= extend; i++)
	{
		char c = i + '1';
		TCHAR s[] = _T("已扩展");//画出扩展情况
		outtextxy(500, 180, s);
		outtextxy(700, 180, c);
		outtextxy(750, 180, _T("步"));
		for (int j = 0; j < 9; j++)////动态展示
		{
			char c = dyna[i][j];
			int y = j / 3 + 1;
			int x = j % 3 + 1;
			IMAGE img;
			if (c == '0')
				loadimage(&img, _T("./resources/0.jpg"));
			if (c == '1')
				loadimage(&img, _T("./resources/1.jpg"));
			if (c == '2')
				loadimage(&img, _T("./resources/2.jpg"));
			if (c == '3')
				loadimage(&img, _T("./resources/3.jpg"));
			if (c == '4')
				loadimage(&img, _T("./resources/4.jpg"));
			if (c == '5')
				loadimage(&img, _T("./resources/5.jpg"));
			if (c == '6')
				loadimage(&img, _T("./resources/6.jpg"));
			if (c == '7')
				loadimage(&img, _T("./resources/7.jpg"));
			if (c == '8')
				loadimage(&img, _T("./resources/8.jpg"));
			putimage(100 * x, 100 * y, &img);
		}
		Sleep(3000);
		cleardevice();//清空当前绘图设备
	}
	Sleep(5000);
	settextstyle(15, 15, _T("Courier"));
	int linepointx[10] = { 0 };//扩展节点的线端点
	int linepointy[10] = { 0 };
	int count = 0;
	for (int i = 0; i <= generate; i++)
	{
		if (dynapaint[i].deep > 3)//画出前四层
			break;
		int width = 1440 / deepnum[dynapaint[i].deep];//每层每个占据宽度
		int y = 60 + 200* dynapaint[i].deep;//每层深度
		for (int j = 0; j < deepnum[dynapaint[i].deep]; j++)
		{
			int x = width/2+width*j;
			rectangle(x - 45, y - 60, x + 45, y + 60);//画矩形
			char temp[10];
			sprintf_s(temp, "%09d", dynapaint[i+j].ch);
			if(dynapaint[i].deep>0)
				line(x, y - 60, linepointx[dynapaint[i].deep-1], linepointy[dynapaint[i].deep-1]);//画线
			for (int k = 0; k <= extend; k++)//画红色线
			{
				if (strcmp(temp, dyna[k]) == 0)
				{
					linepointx[count] = x;
					linepointy[count] = y + 60;
					count++;
					setlinecolor(RED);
					if (dynapaint[i].deep > 0)
						line(x, y - 60, linepointx[dynapaint[i].deep - 1], linepointy[dynapaint[i].deep - 1]);
					setlinecolor(BLACK);
					break;
				}
			}
			//画出每个的d=? 以及八数码情况
			x += 3;
			y += 3;
			char c1 = 'd';
			char c2 = '=';
			char c3 = dynapaint[i+j].d + '0';
			outtextxy(x - 45, y - 60, c1);
			outtextxy(x - 30, y - 60, c2);
			outtextxy(x - 15, y - 60, c3);
			for (int k = 0; k < 9; k++)
			{
				int yy = k / 3;
				int xx = k % 3;
				outtextxy(x - 45+xx*30, y - 30+yy*30, temp[k]);
			}
		}
		i += (deepnum[dynapaint[i].deep] - 1);
	}
	Sleep(10000);
	closegraph();
}