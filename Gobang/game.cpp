#include"all.h"
void BOX::draw()//��������
{
	COLORREF thefillcolor = getfillcolor();//���������ɫ
	setlinestyle(PS_SOLID, 2);//����ʽ����
	setwritemode(R2_XORPEN);//����XOR��ͼģʽ
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
	if (value == 0)//����
	{
		setfillcolor(BLACK);
		fillcircle(x + 15, y + 15, 13);
	}
	else if (value == 1)//����
	{
		setfillcolor(WHITE);
		fillcircle(x + 15, y + 15, 13);
	}
	setfillcolor(thefillcolor); //��ԭ���ɫ
}
bool isend()//�Ƿ����
{
	for (int i = 0; i < board_length; i++)//����ÿ�����ܵ�λ��
	{
		for (int j = 0; j < board_length; j++)
		{
			if (box[i][j].value == whoplay)
			{
				int length[8] = { 0,0,0,0,0,0,0,0 };//�˸�����ĳ���
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
void retract(int i, int j)//����
{
	if (box[i][j].value == 0)//����
	{
		setfillcolor(BLACK);
		fillcircle(box[i][j].x + 15, box[i][j].y + 15, 13);
	}
	else if (box[i][j].value == 1)//����
	{
		setfillcolor(WHITE);
		fillcircle(box[i][j].x + 15, box[i][j].y + 15, 13);
	}
}
void game()//�Ծ�
{
	int oldi = -1, oldj = -1;//��һ�����ͣ������
	//box[oldi][oldj].draw();
	while (1)
	{
		bool retraction = false;//��û�л���
		if (whoplay == 0)// �������
		{
			MOUSEMSG mouse = GetMouseMsg();//��ȡ�����Ϣ
			for (int i = 0; i < board_length; i++)
			{
				for (int j = 0; j < board_length; j++)
				{
					//���¿�ʼ
					if (mouse.x < 150 && mouse.x>0 && mouse.y < 500 && mouse.y> 450)
					{
						setfillcolor(RGB(150, 150, 150));
						solidrectangle(25, 460, 125, 490);
						outtextxy(27, 460, _T("���¿�ʼ"));
						if (mouse.uMsg == WM_LBUTTONUP)
						{
							mouse.uMsg = WM_MOUSEMOVE;
							return;
						}					
					}
					//�˳�
					if (mouse.x < 300 && mouse.x>150 && mouse.y < 500 && mouse.y> 450)
					{
						setfillcolor(RGB(150, 150, 150));
						solidrectangle(175, 460, 275, 490);
						outtextxy(200, 460, _T("�˳�"));
						if (mouse.uMsg == WM_LBUTTONUP)
						{
							mouse.uMsg = WM_MOUSEMOVE;
							exit(0);
						}					
					}
					//����
					if (mouse.x < 450 && mouse.x>300 && mouse.y < 500 && mouse.y> 450 && allstep > 2)
					{
						setfillcolor(RGB(150, 150, 150));
						solidrectangle(325, 460, 425, 490);
						outtextxy(350, 460, _T("����"));
						if (mouse.uMsg == WM_LBUTTONUP)
						{
							mouse.uMsg = WM_MOUSEMOVE;
							IMAGE img;//���°�֮ǰ�������������һ��
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
					//�ж�λ��
					if (mouse.x > box[i][j].x && mouse.x<box[i][j].x + 30 && mouse.y>box[i][j].y && mouse.y < box[i][j].y + 30 && box[i][j].value == -1)
					{
						if (oldi >= 0 && oldj >= 0)
						{						
							box[oldi][oldj].isnew = false;//���ͣ��ĳһ����λ������,����ѡ���
							box[oldi][oldj].draw();
						}
						box[i][j].isnew = true;
						box[i][j].draw();
						if (mouse.mkLButton)// ���������
						{
							pos my;//������������
							my.x = j;
							my.y = i;
							s[allstep] = my;
							box[i][j].value = 0; //����
							box[i][j].draw();//��������
							if (isend())//�жϽ���
							{
								outtextxy(225, 250, _T("���ʤ"));
								Sleep(5000);
								return;
							}
							else if (allstep == 255)//�ж�ƽ��
							{
								outtextxy(225, 250, _T("ƽ��"));
								Sleep(5000);
								return;
							}
							oldi = -1;
							oldj = -1;
							allstep++;//�ܲ���+1
							whoplay = 1;//ת��AI
							break;
						}
						oldi = i;//��λ�ø���
						oldj = j;
					}
				}			
				if (whoplay == 1 || retraction == true)//����ѭ��
					break;
			}
		}
		else//AI����
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
			while (!kill.empty())//�����ɱ����
				kill.pop();
			if (!analyse_kill(board, kill_deep, 1, best))//��ɱ�������ж�
			{
				for (int i = 0; i < board_length; i++)
				{
					for (int j = 0; j < board_length; j++)
					{
						board[i][j] = box[i][j].value;
					}
				}
				maxmin(board, maxmin_deep, -MAX, MAX, best);//����С����
			}
			box[best.y][best.x].value = 1;//�������λ��
			box[best.y][best.x].isnew = true;
			s[allstep] = best;
			box[best.y][best.x].draw();
			if (isend())
			{
				outtextxy(225, 250, _T("AIʤ"));
				Sleep(5000);
				return;
			}
			allstep++;
			whoplay = 0;
		}
	}
}