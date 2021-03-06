#include"all.h"
EVALUATION evaluate(int board[board_length][board_length])//��������
{
	//������Ȩ��
	int weight[17] = { 0,10000000,-10000000,50000,-100000,400,-100000,400,-8000,20,-50,20,-50,1,-3,1,-3 };
	int i, j, type;
	int stat[4][17];//ͳ��4��������ÿ�����͵ĸ���
	memset(stat, 0, sizeof(stat));
	int STAT[17];//�����������͵ķ���ĸ���
	memset(STAT, 0, sizeof(STAT));
	int A[17][17];//�����߽�����������,board[i][j]=A[i-1][j-1],3��ʾ�߽�
	for (int i = 0; i < 17; ++i)A[i][0] = 3;
	for (int i = 0; i < 17; ++i)A[i][16] = 3;
	for (int j = 0; j < 17; ++j)A[0][j] = 3;
	for (int j = 0; j < 17; ++j)A[16][j] = 3;
	for (int i = 0; i < 15; ++i)
		for (int j = 0; j < 15; ++j)
			A[i + 1][j + 1] = board[i][j] + 1;

	//�жϺ�������
	for (i = 1; i <= 15; ++i) {
		for (j = 0; j < 12; ++j) {
			type = tuple6type[A[i][j]][A[i][j + 1]][A[i][j + 2]][A[i][j + 3]][A[i][j + 4]][A[i][j + 5]];
			stat[0][type]++;
		}
	}
	//�ж���������
	for (j = 1; j <= 15; ++j) {
		for (i = 0; i < 12; ++i) {
			type = tuple6type[A[i][j]][A[i + 1][j]][A[i + 2][j]][A[i + 3][j]][A[i + 4][j]][A[i + 5][j]];
			stat[1][type]++;
		}
	}
	//�ж���������������
	for (i = 0; i < 12; ++i) {
		for (j = 0; j < 12; ++j) {
			type = tuple6type[A[i][j]][A[i + 1][j + 1]][A[i + 2][j + 2]][A[i + 3][j + 3]][A[i + 4][j + 4]][A[i + 5][j + 5]];
			stat[2][type]++;
		}
	}
	//�ж���������������
	for (i = 0; i < 12; ++i) {
		for (j = 5; j < 17; ++j) {
			type = tuple6type[A[i][j]][A[i + 1][j - 1]][A[i + 2][j - 2]][A[i + 3][j - 3]][A[i + 4][j - 4]][A[i + 5][j - 5]];
			stat[3][type]++;
		}
	}
	EVALUATION eval;
	memset(eval.STAT, 0, sizeof(eval.STAT));

	int score = 0;
	for (i = 1; i < 17; ++i) {
		score += (stat[0][i] + stat[1][i] + stat[2][i] + stat[3][i]) * weight[i];//�����Ʒ�

		int count = stat[0][i] + stat[1][i] + stat[2][i] + stat[3][i];//ͳ�����з����ϲ������͵ĸ���
		if (i == WIN)eval.STAT[WIN] = count;
		else if (i == LOSE)eval.STAT[LOSE] = count;
		else if (i == FLEX4)eval.STAT[FLEX4] = count;
		else if (i == BLOCK4)eval.STAT[BLOCK4] = count;
		else if (i == FLEX3)eval.STAT[FLEX3] = count;
	}
	eval.result = -1;
	//��Ӯ����
	if (eval.STAT[LOSE] > 0)
		eval.result = 0;
	else if (eval.STAT[WIN] > 0)
		eval.result = 1;
	eval.score = score;
	return eval;
}
pos seekPoints(int board[board_length][board_length], int who, int deep, bool choice)//�ֲ�����
{
	while (!que.empty())//��ն���
		que.pop();
	int B[board_length][board_length];//�ֲ������������
	memset(B, 0, sizeof(B));
	for (int i = 0; i < board_length; ++i)//ÿ���ǿյ㸽��8����������3�����,����Խ������Ϊ����
	{
		for (int j = 0; j < board_length; ++j)
		{
			if (board[i][j] != -1)
			{
				for (int l = 0; l < 8; l++)
				{
					int nowi = i;
					int nowj = j;
					for (int k = 1; k <= search_deep; ++k)
					{
						nowi += dy[l];
						nowj += dx[l];
						if (nowi <= 14 && nowj <= 14 && nowi >= 0 && nowj >= 0)
						{
							B[nowi][nowj] = 1;
						}
					}
				}

			}
		}
	}
	for (int i = 0; i < board_length; ++i)//���ݿ��ߵ��ߣ������������������
	{
		for (int j = 0; j < board_length; ++j)
		{
			if (board[i][j] == -1 && B[i][j] == 1)
			{
				board[i][j] = who;
				pos a;
				a.x = j;
				a.y = i;
				EVALUATION t = evaluate(board);
				board[i][j] = -1;
				a.worth = t.score;
				int result = t.result;
				if (result == 1 && who == 1 && deep == 2 && choice == 1)//��������2��ʱ
					return a;
				que.push(a);

			}
		}
	}
	return { 0,0,0 };
}
int maxmin(int board[board_length][board_length], int deep, int alpha, int beta, pos& ans)//����С����
{
	pos result = seekPoints(board, (deep + 1) % 2, deep, 1);//�ֲ�����
	if (result.x + result.y + result.worth != 0)//��������2������
	{
		return result.worth;
	}
	int k = 0;
	pos t[20] = { 0 };
	if (deep % 2 == 0)//����ת����
	{
		while (!que.empty() && k < 20)
		{
			t[k] = que.top();
			que.pop();
			k++;
		}
	}
	else//������תջ��ת����
	{
		stack<pos> q;
		while (!que.empty())
		{
			q.push(que.top());
			que.pop();
		}
		while (!q.empty() && k < 20)
		{
			t[k] = q.top();
			q.pop();
			k++;
		}
	}
	if (deep == 0)//��ȹ�0
	{
		return t[0].worth;
	}
	else if (deep % 2 == 0)//max��,AI���� 
	{
		for (int i = 0; i < 10; ++i)
		{
			int a = 0;
			board[t[i].y][t[i].x] = 1;//ģ��AI����
			a = maxmin(board, deep - 1, alpha, beta, ans);
			board[t[i].y][t[i].x] = -1;//��ԭ����
			if (a > alpha)
			{
				alpha = a;
				if (deep == maxmin_deep)//4���Լ����������(���Ը�Ϊ6,8,������Ϊż��),�������������
				{
					ans.y = t[i].y;
					ans.x = t[i].x;
					ans.worth = a;
				}
			}
			if (beta <= alpha)//��֦
				break;
		}
		return alpha;
	}
	else //min��,�˾���
	{
		for (int i = 0; i < 10; ++i)
		{
			int a = 0;
			board[t[i].y][t[i].x] = 0;//ģ��������
			a = maxmin(board, deep - 1, alpha, beta, ans);
			board[t[i].y][t[i].x] = -1;//��ԭ����
			if (a < beta)
				beta = a;
			if (beta <= alpha)
				break;//��֦
		}
		return beta;
	}
}
void seek_kill_points(int board[board_length][board_length])//��ɱ������
{
	int newboard[board_length][board_length];//�Ұ������5,��4,��4,��3��ɱ��λ��
	for (int i = 0; i < 15; ++i)
		for (int j = 0; j < 15; ++j)
			newboard[i][j] = board[i][j];
	seekPoints(board, whoplay, 0, 0);//һ����˵,�ܳ�4���߻�3�ı�������ǰ20�ĵ���
	int k = 0;
	pos t[20] = { 0 };
	while (!que.empty() && k < 20)
	{
		t[k] = que.top();
		que.pop();
		k++;
	}
	for (int i = 0; i < 20; ++i)
	{
		newboard[t[i].y][t[i].x] = 1;//ģ������
		if (evaluate(newboard).STAT[WIN] > 0)
		{//������5
			kill.push(t[i]);
		}
		else if (evaluate(newboard).STAT[FLEX4] > evaluate(board).STAT[FLEX4])
		{//�����»�4
			kill.push(t[i]);
		}
		else if (evaluate(newboard).STAT[BLOCK4] > evaluate(board).STAT[BLOCK4])
		{//�����³�4
			kill.push(t[i]);
		}
		else if (evaluate(newboard).STAT[FLEX3] > evaluate(board).STAT[FLEX3])
		{//�����»�3
			kill.push(t[i]);
		}
		newboard[t[i].y][t[i].x] = -1;//��ԭ����
	}
}
bool analyse_kill(int board[board_length][board_length], int deep, int who, pos& ans)//��ɱ����
{
	seekPoints(board, who, deep, 0);//�ֲ�����
	int k = 0;
	pos t[20] = { 0 };
	if (deep % 2 == 0)//����ת����
	{
		while (!que.empty() && k < 20)
		{
			t[k] = que.top();
			que.pop();
			k++;
		}
	}
	else//����תջ��ת����
	{
		stack<pos> q;
		while (!que.empty())
		{
			q.push(que.top());
			que.pop();
		}
		while (!q.empty() && k < 20)
		{
			t[k] = q.top();
			q.pop();
			k++;
		}
	}
	EVALUATION EVAL = evaluate(board);
	if (deep == 0 || EVAL.result != -1)
	{
		if (EVAL.result == 1)//�ҵ�����ɱ��
			return true;
		else if (EVAL.result == 0)//������
			return false;
		else if (deep == 0)//���ִ������,��һ���԰�������λ��,�����廹ûӮ�򷵻�false
		{
			board[t[0].y][t[0].x] = 1;
			int result = evaluate(board).result;
			if (result == 1)
				return true;
			else
				return false;
		}
		else if (EVAL.result == 1)
			return true;//�ҵ�����ɱ��
		else
			return false;//������
	}
	else if (deep % 2 == 0)//max��,AI����
	{
		seek_kill_points(board);
		if (kill.empty())//û��ɱ���
			return false;
		while (!kill.empty())
		{
			pos a = kill.top();
			kill.pop();
			board[a.y][a.x] = 1;//ģ��AI����
			if (analyse_kill(board, deep - 1, 0, ans))
			{
				if (deep == kill_deep)
				{
					ans = a;
				}
				return true;
			}
		}
		return false;
	}
	else //min��,�˾���ֻ�¶��Լ���õ���
	{
		board[t[0].y][t[0].x] = 0;//�����֦
		return analyse_kill(board, deep - 1, 1, ans);
	}
}