#include"all.h"
void dynamic(int extend, int generate)
{
	int deepnum[5] = { 0 };
	for (int i = 0; i <= generate; i++)
		deepnum[dynapaint[i].deep]++;
	Sleep(5000);//����5��
	initgraph(1440, 720);
	setbkcolor(WHITE); //���ñ���ɫ
	settextstyle(30, 30, _T("Courier"));// ��������
	settextcolor(BLACK);//��������ɫ
	setlinecolor(BLACK);//��������ɫ
	setlinestyle(PS_SOLID, 3);//��������
	for (int i = 0; i <= extend; i++)
	{
		char c = i + '1';
		TCHAR s[] = _T("����չ");//������չ���
		outtextxy(500, 180, s);
		outtextxy(700, 180, c);
		outtextxy(750, 180, _T("��"));
		for (int j = 0; j < 9; j++)////��̬չʾ
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
		cleardevice();//��յ�ǰ��ͼ�豸
	}
	Sleep(5000);
	settextstyle(15, 15, _T("Courier"));
	int linepointx[10] = { 0 };//��չ�ڵ���߶˵�
	int linepointy[10] = { 0 };
	int count = 0;
	for (int i = 0; i <= generate; i++)
	{
		if (dynapaint[i].deep > 3)//����ǰ�Ĳ�
			break;
		int width = 1440 / deepnum[dynapaint[i].deep];//ÿ��ÿ��ռ�ݿ��
		int y = 60 + 200* dynapaint[i].deep;//ÿ�����
		for (int j = 0; j < deepnum[dynapaint[i].deep]; j++)
		{
			int x = width/2+width*j;
			rectangle(x - 45, y - 60, x + 45, y + 60);//������
			char temp[10];
			sprintf_s(temp, "%09d", dynapaint[i+j].ch);
			if(dynapaint[i].deep>0)
				line(x, y - 60, linepointx[dynapaint[i].deep-1], linepointy[dynapaint[i].deep-1]);//����
			for (int k = 0; k <= extend; k++)//����ɫ��
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
			//����ÿ����d=? �Լ����������
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