#include"all.h"
void solvable()//������״̬����������ż����ͬ���н�
{
	int sum_a = 0, sum_b = 0;
	for (int i = 0; i < 9; i++)
	{
		if (arr[i] != '0')
		{
			for (int j = i + 1; j < 9; j++)
				if (arr[j] < arr[i] && arr[j] != '0')
					sum_a++;
		}
	}
	for (int i = 0; i < 9; i++)
	{
		if (brr[i] != '0')
		{
			for (int j = i + 1; j < 9; j++)
				if (brr[j] < brr[i] && brr[j] != '0')
					sum_b++;
		}
	}
	if (sum_a % 2 != sum_b % 2)
	{
		cout << "�޽�" << endl;
		exit(1);
	}
}