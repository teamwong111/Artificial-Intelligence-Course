#include"all.h"
EVALUATION evaluate(int board[board_length][board_length])//评估函数
{
	//各棋型权重
	int weight[17] = { 0,10000000,-10000000,50000,-100000,400,-100000,400,-8000,20,-50,20,-50,1,-3,1,-3 };
	int i, j, type;
	int stat[4][17];//统计4个方向上每种棋型的个数
	memset(stat, 0, sizeof(stat));
	int STAT[17];//存在这种棋型的方向的个数
	memset(STAT, 0, sizeof(STAT));
	int A[17][17];//包括边界的虚拟大棋盘,board[i][j]=A[i-1][j-1],3表示边界
	for (int i = 0; i < 17; ++i)A[i][0] = 3;
	for (int i = 0; i < 17; ++i)A[i][16] = 3;
	for (int j = 0; j < 17; ++j)A[0][j] = 3;
	for (int j = 0; j < 17; ++j)A[16][j] = 3;
	for (int i = 0; i < 15; ++i)
		for (int j = 0; j < 15; ++j)
			A[i + 1][j + 1] = board[i][j] + 1;

	//判断横向棋型
	for (i = 1; i <= 15; ++i) {
		for (j = 0; j < 12; ++j) {
			type = tuple6type[A[i][j]][A[i][j + 1]][A[i][j + 2]][A[i][j + 3]][A[i][j + 4]][A[i][j + 5]];
			stat[0][type]++;
		}
	}
	//判断竖向棋型
	for (j = 1; j <= 15; ++j) {
		for (i = 0; i < 12; ++i) {
			type = tuple6type[A[i][j]][A[i + 1][j]][A[i + 2][j]][A[i + 3][j]][A[i + 4][j]][A[i + 5][j]];
			stat[1][type]++;
		}
	}
	//判断左上至右下棋型
	for (i = 0; i < 12; ++i) {
		for (j = 0; j < 12; ++j) {
			type = tuple6type[A[i][j]][A[i + 1][j + 1]][A[i + 2][j + 2]][A[i + 3][j + 3]][A[i + 4][j + 4]][A[i + 5][j + 5]];
			stat[2][type]++;
		}
	}
	//判断右上至左下棋型
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
		score += (stat[0][i] + stat[1][i] + stat[2][i] + stat[3][i]) * weight[i];//初步计分

		int count = stat[0][i] + stat[1][i] + stat[2][i] + stat[3][i];//统计所有方向上部分棋型的个数
		if (i == WIN)eval.STAT[WIN] = count;
		else if (i == LOSE)eval.STAT[LOSE] = count;
		else if (i == FLEX4)eval.STAT[FLEX4] = count;
		else if (i == BLOCK4)eval.STAT[BLOCK4] = count;
		else if (i == FLEX3)eval.STAT[FLEX3] = count;
	}
	eval.result = -1;
	//白赢或输
	if (eval.STAT[LOSE] > 0)
		eval.result = 0;
	else if (eval.STAT[WIN] > 0)
		eval.result = 1;
	eval.score = score;
	return eval;
}
pos seekPoints(int board[board_length][board_length], int who, int deep, bool choice)//局部搜索
{
	while (!que.empty())//清空队列
		que.pop();
	int B[board_length][board_length];//局部搜索标记数组
	memset(B, 0, sizeof(B));
	for (int i = 0; i < board_length; ++i)//每个非空点附近8个方向延伸3个深度,若不越界则标记为可走
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
	for (int i = 0; i < board_length; ++i)//根据可走点走，并评估，并放入队列
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
				if (result == 1 && who == 1 && deep == 2 && choice == 1)//迭代加深2层时
					return a;
				que.push(a);

			}
		}
	}
	return { 0,0,0 };
}
int maxmin(int board[board_length][board_length], int deep, int alpha, int beta, pos& ans)//极大极小搜索
{
	pos result = seekPoints(board, (deep + 1) % 2, deep, 1);//局部搜索
	if (result.x + result.y + result.worth != 0)//迭代加深2层的情况
	{
		return result.worth;
	}
	int k = 0;
	pos t[20] = { 0 };
	if (deep % 2 == 0)//队列转数组
	{
		while (!que.empty() && k < 20)
		{
			t[k] = que.top();
			que.pop();
			k++;
		}
	}
	else//队列先转栈再转数组
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
	if (deep == 0)//深度归0
	{
		return t[0].worth;
	}
	else if (deep % 2 == 0)//max层,AI决策 
	{
		for (int i = 0; i < 10; ++i)
		{
			int a = 0;
			board[t[i].y][t[i].x] = 1;//模拟AI落子
			a = maxmin(board, deep - 1, alpha, beta, ans);
			board[t[i].y][t[i].x] = -1;//还原落子
			if (a > alpha)
			{
				alpha = a;
				if (deep == maxmin_deep)//4是自己设立的深度(可以改为6,8,但必须为偶数),用来找最佳落子
				{
					ans.y = t[i].y;
					ans.x = t[i].x;
					ans.worth = a;
				}
			}
			if (beta <= alpha)//剪枝
				break;
		}
		return alpha;
	}
	else //min层,人决策
	{
		for (int i = 0; i < 10; ++i)
		{
			int a = 0;
			board[t[i].y][t[i].x] = 0;//模拟人落子
			a = maxmin(board, deep - 1, alpha, beta, ans);
			board[t[i].y][t[i].x] = -1;//还原落子
			if (a < beta)
				beta = a;
			if (beta <= alpha)
				break;//剪枝
		}
		return beta;
	}
}
void seek_kill_points(int board[board_length][board_length])//算杀点搜索
{
	int newboard[board_length][board_length];//找白棋的连5,活4,冲4,活3的杀棋位置
	for (int i = 0; i < 15; ++i)
		for (int j = 0; j < 15; ++j)
			newboard[i][j] = board[i][j];
	seekPoints(board, whoplay, 0, 0);//一般来说,能冲4或者活3的必在评分前20的点内
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
		newboard[t[i].y][t[i].x] = 1;//模拟落子
		if (evaluate(newboard).STAT[WIN] > 0)
		{//产生连5
			kill.push(t[i]);
		}
		else if (evaluate(newboard).STAT[FLEX4] > evaluate(board).STAT[FLEX4])
		{//产生新活4
			kill.push(t[i]);
		}
		else if (evaluate(newboard).STAT[BLOCK4] > evaluate(board).STAT[BLOCK4])
		{//产生新冲4
			kill.push(t[i]);
		}
		else if (evaluate(newboard).STAT[FLEX3] > evaluate(board).STAT[FLEX3])
		{//产生新活3
			kill.push(t[i]);
		}
		newboard[t[i].y][t[i].x] = -1;//还原落子
	}
}
bool analyse_kill(int board[board_length][board_length], int deep, int who, pos& ans)//算杀搜索
{
	seekPoints(board, who, deep, 0);//局部搜索
	int k = 0;
	pos t[20] = { 0 };
	if (deep % 2 == 0)//队列转数组
	{
		while (!que.empty() && k < 20)
		{
			t[k] = que.top();
			que.pop();
			k++;
		}
	}
	else//队列转栈再转数组
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
		if (EVAL.result == 1)//找到白棋杀棋
			return true;
		else if (EVAL.result == 0)//白棋输
			return false;
		else if (deep == 0)//若抵达最深层,走一步对白棋的最好位置,若白棋还没赢则返回false
		{
			board[t[0].y][t[0].x] = 1;
			int result = evaluate(board).result;
			if (result == 1)
				return true;
			else
				return false;
		}
		else if (EVAL.result == 1)
			return true;//找到白棋杀棋
		else
			return false;//白棋输
	}
	else if (deep % 2 == 0)//max层,AI决策
	{
		seek_kill_points(board);
		if (kill.empty())//没有杀棋点
			return false;
		while (!kill.empty())
		{
			pos a = kill.top();
			kill.pop();
			board[a.y][a.x] = 1;//模拟AI落子
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
	else //min层,人决策只下对自己最好的棋
	{
		board[t[0].y][t[0].x] = 0;//无需剪枝
		return analyse_kill(board, deep - 1, 1, ans);
	}
}