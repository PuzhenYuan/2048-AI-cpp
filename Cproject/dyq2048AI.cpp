/************************************* 电脑AI2参战函数库**************************************/

#include "dyq2048AI.h"
#include "2048AI.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "basicfunction.h" 


extern int a[4][4];
extern int h[4][4], h1[4][4];
extern int b, M;
extern int point;
extern int point1;
extern int r3, r2, r4;
extern float move3, move2, move4;
extern int A1, A2;


void dyq2048AI()
{
	a2h();//储存进行第一步假设操作前的a值 
	b = 3;//假设第一步向下移动 
	r3 = moveandadd40();//注意此时a的值已变化，但不改变point值与point1值 
	if (r3 == 1)
	{
		a2h1();//储存进行第一步假设操作后的a值
		move3 = dataCollection();//move3储存第一步向下移动的数据 
	}
	h2a();//使a值回到进行第一步假设操作前的值 
	b = 2;//假设第一步向左移动 
	r2 = moveandadd40();
	if (r2 == 1)
	{
		a2h1();//储存进行向左假设操作后的a值
		move2 = dataCollection();//move2储存第一步向左移动的数据 
	}

	h2a();//使a值回到进行第一步假设操作前的值
	b = 4;//假设向右移动 
	r4 = moveandadd40();
	if (r4 == 1)
	{
		a2h1();//储存进行向右假设操作后的a值
		move4 = dataCollection();//move4储存第一步向右移动的数据 
	}
	h2a();//使a值回到进行第一步假设操作前的值
}


int emptyCells()
//emptyCells函数用于计算空格数，空格数越多越有利，函数返回值为 a的空格数 
{
	int i, j, k = 0;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (a[i][j] == 0)
			{
				k++;
				break;
			}
		}
	}
	return k;
}


int dataCollection()
//该函数用以收集关于a的数据 
{
	int point1 = 0;
	//point1记录假设操作后的point 
	int i, j, k = 0;
	//k为进入if(a[i][j] == 0)的循环次数，也等于空格数 
	int X3 = 0, X2 = 0, X4 = 0, X = 0;
	//X3记录 “第二步假设操作为向下 ”时的空格数
	//X2记录 “第二步假设操作为向左 ”时的空格数
	//X4记录 “第二步假设操作为向右 ”时的空格数
	//X记录 “第二步假设操作 ”后的空格数的最大值，即第二步采取 “最优 ”走法后的空格数 
	int P3 = 0, P2 = 0, P4 = 0, P = 0;
	//P3记录 “第二步假设操作为向下 ”时的分数增值 
	//P2记录 “第二步假设操作为向左 ”时的分数增值 
	//P4记录 “第二步假设操作为向右 ”时的分数增值 
	//P记录 “第二步假设操作 ”后的分数增值的最大值，即第二步采取 “最优 ”走法后的分数增值 
	int M3 = 0, M2 = 0, M4 = 0, M = 0;
	//M3记录 “第二步假设操作为向下 ”时的单调性数据 
	//M2记录 “第二步假设操作为向左 ”时的单调性数据
	//M4记录 “第二步假设操作为向右 ”时的单调性数据
	//M记录 “第二步假设操作 ”后的单调性数据的最大值，即第二步采取 “最优 ”走法后的单调性数据 
	float x2 = 0, x4 = 0;
	//x2为当新的生成数字为 2时的空格数的平均值
	//x4为当新的生成数字为 4时的空格数的平均值
	float p2 = 0, p4 = 0;
	//p2为当新的生成数字为 2时的分数增值的平均值 
	//p4为当新的生成数字为 4时的分数增值的平均值 
	float m2 = 0, m4 = 0;
	//m2为当新的生成数字为 2时的单调性数据的平均值 
	//m4为当新的生成数字为 4时的单调性数据的平均值 
	float data = 0;
	//data作为函数的返回值，即 AI的核心判定数据 
	float A1 = 0.1001,//A1为分数增值权重与平均值权重的比值，该比值通过学习得到 
		A2 = 0.0051;//A2为单调性数据权重与平均值权重的比值，该比值通过学习得到

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (a[i][j] == 0)
			{
				//以上循环表示穷举所有的新数字生成情况 
				k++;//k记录进入if(a[i][j] == 0)的循环次数，也等于空格数

				h12a();//将 a的值恢复为 h1，即进行第一步假设操作后的 a值 
				a[i][j] = 2;//假设空位变为2 
				b = 3;//假设第二步操作为向下移动 
				point1 = point;//记录point值 
				point1 = moveandadd41();//此处改变 a值，不改变 point值 ,改变 point1值 
				X3 = emptyCells();//记录此时剩余空格数 
				P3 = point1 - point;//P3记录 “第二步假设操作为向下 ”时的分数增值 
				M3 = monotony();//M3记录 “第二步假设操作为向下 ”时的单调性数据 

				h12a();
				a[i][j] = 2;
				b = 2;//假设第二步操作为向左移动
				point1 = point;
				point1 = moveandadd41();
				X2 = emptyCells();
				P2 = point1 - point;
				M2 = monotony();

				h12a();
				a[i][j] = 2;
				b = 4;//假设第二步操作为向右移动
				point1 = point;
				point1 = moveandadd41();
				X4 = emptyCells();
				P4 = point1 - point;
				M4 = monotony();

				if (X3 >= X2 && X3 >= X4)
				{
					X = X3;
				}
				else if (X2 >= X4)
				{
					X = X2;
				}
				else
				{
					X = X4;
				}//X记录 “第二步假设操作 ”后的空格数的最大值，即第二步采取 “最优 ”走法后的空格数

				if (P3 >= P2 && P3 >= P4)
				{
					P = P3;
				}
				else if (P2 >= P4)
				{
					P = P2;
				}
				else
				{
					P = P4;
				}//P记录 “第二步假设操作 ”后的分数增值的最大值，即第二步采取 “最优 ”走法后的分数增值

				if (M3 >= M2 && M3 >= M4)
				{
					M = M3;
				}
				else if (M2 >= M4)
				{
					M = M2;
				}
				else
				{
					M = M4;
				}//M记录 “第二步假设操作 ”后的单调性数据的最大值，即第二步采取 “最优 ”走法后的单调性数据 

				x2 = (x2 * (k - 1) + X) / k;//x2为当新的生成数字为 2时的空格数的平均值
				p2 = (p2 * (k - 1) + P) / k;//p2为当新的生成数字为 2时的分数增值的平均值 
				m2 = (m2 * (k - 1) + P) / k;//m2为当新的生成数字为 2时的单调性数据的平均值


				h12a();
				a[i][j] = 4;//假设空位变为 4
				b = 3;//假设第二步操作为向下移动 
				point1 = point;
				point1 = moveandadd41();
				X3 = emptyCells();
				P3 = point1 - point;
				M3 = monotony();

				h12a();
				a[i][j] = 2;
				b = 2;//假设第二步操作为向左移动
				point1 = point;
				point1 = moveandadd41();
				X2 = emptyCells();
				P2 = point1 - point;
				M2 = monotony();

				h12a();
				a[i][j] = 2;
				b = 4;//假设第二步操作为向右移动
				point1 = point;
				point1 = moveandadd41();
				X4 = emptyCells();
				P4 = point1 - point;
				M4 = monotony();

				if (X3 >= X2 && X3 >= X4)
				{
					X = X3;
				}
				else if (X2 >= X4)
				{
					X = X2;
				}
				else
				{
					X = X4;
				}

				if (P3 >= P2 && P3 >= P4)
				{
					P = P3;
				}
				else if (P2 >= P4)
				{
					P = P2;
				}
				else
				{
					P = P4;
				}

				if (M3 >= M2 && M3 >= M4)
				{
					M = M3;
				}
				else if (M2 >= M4)
				{
					M = M2;
				}
				else
				{
					M = M4;
				}

				x4 = (x4 * (k - 1) + X) / k;
				p4 = (p4 * (k - 1) + P) / k;
				m4 = (m4 * (k - 1) + P) / k;
			}
		}
	}

	h12a();//将 a的值恢复为 h1，即进行第一步假设操作后的 a值 

	data = 0.9 * x2 + 0.1 * x4 + A1 * (0.9 * p2 + 0.1 * p4) + A2 * (0.9 * m2 + 0.1 * m4);//data作为 AI的核心判定数据,通过该数据寻找第一步的最优走法 
	return data;
}


int monotony()//单调性数据收集函数，函数返回值为单调性数据 
{
	int i, j;
	//将4*4的矩阵分为六个区域，分别记作 a、b、c、d、e、f 
	int ma = 0, mb = 0, mc = 0, md = 0, me = 0, mf = 0;
	//对应六个区域的单调性数据 
	float A = 1, B = 1, C = 1, D = 3, E = 3, F = 3;
	//对应六个区域的单调性数据的权重 
	float m;
	//m为单调性综合数据，作为函数返回值
	for (i = 1; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{

			if ((i == 1 && j == 0) || (i == 2 && j == 0))
			{
				if (a[i][j] != 0 && a[i - 1][j] != 0)
				{
					if (a[i][j] >= a[i - 1][j])
					{
						ma++;
					}
				}
				if (a[i][j] != 0 && a[i + 1][j] != 0)
				{
					if (a[i][j] <= a[i + 1][j])
					{
						ma++;
					}
				}
			}

			if ((i == 1 && j == 3) || (i == 2 && j == 3))
			{
				if (a[i][j] != 0 && a[i - 1][j] != 0)
				{
					if (a[i][j] >= a[i - 1][j])
					{
						mb++;
					}
				}
				if (a[i][j] != 0 && a[i + 1][j] != 0)
				{
					if (a[i][j] <= a[i + 1][j])
					{
						mb++;
					}
				}
			}

			if ((i == 1 && j == 1) || (i == 1 && j == 2) || (i == 2 && j == 1) || (i == 2 && j == 2))
			{
				if (a[i][j] != 0 && a[i - 1][j] != 0)
				{
					if (a[i][j] >= a[i - 1][j])
					{
						mc++;
					}
				}
				if (a[i][j] != 0 && a[i + 1][j] != 0)
				{
					if (a[i][j] <= a[i + 1][j])
					{
						mc++;
					}
				}
			}

			if ((i == 3 && j == 1) || (i == 3 && j == 2))
			{
				if (a[i][j] != 0 && a[i - 1][j] != 0)
				{
					if (a[i][j] >= a[i - 1][j])
					{
						md++;
					}
				}
			}

			if (i == 3 && j == 0)
			{
				if (a[i][j] != 0 && a[i - 1][j] != 0)
				{
					if (a[i][j] >= a[i - 1][j])
					{
						me++;
					}
				}
			}

			if (i == 3 && j == 3)
			{
				if (a[i][j] != 0 && a[i - 1][j] != 0)
				{
					if (a[i][j] >= a[i - 1][j])
					{
						mf++;
					}
				}
			}
		}
	}
	m = ma * A + mb * B + mc * C + md * D + me * E + mf * F;
	return m;
}


void a2h()
//将a的值赋给h 
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			h[i][j] = a[i][j];
		}
	}
}

void h2a()
//将h的值赋给a
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			a[i][j] = h[i][j];
		}
	}
}

void a2h1()
//将a的值赋给h1
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			h1[i][j] = a[i][j];
		}
	}
}

void h12a()
//将h1的值赋给a
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			a[i][j] = h1[i][j];
		}
	}
}


int simpleplay2(int m)
//电脑AI多次参战函数，只返回分数值 
//m的值是为了播下伪随机数种子，一把时间太快了不能用time（NULL)了 
//备注：该函数实际上就是main.c中的 computerplay2()函数除去print和sleep，函数返回一次AI运行的分数值 
{
	char key;
	int r, s, t;
	int h[4][4] = { 0 };
	int win = 0;
	point = 0;

	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			a[i][j] = 0;
		}
	}
	srand(m);//用m的值作为seed，保证每局不同 
	randomnumber();
	randomnumber();

	while (1)
	{

		dyq2048AI();//收集数据 

		//接下来根据数据判定移动方向
		if (cangodown() == 1 && cangoleft() == 1 && cangoright() == 1)
		{
			if (move3 >= move2 && move3 >= move4)
			{
				b = 3;
				moveandadd();
				randomnumber();
			}
			else if (move2 >= move4)
			{
				b = 2;
				moveandadd();
				randomnumber();
			}
			else
			{
				b = 4;
				moveandadd();
				randomnumber();
			}
		}
		else if (cangodown() == 1 && cangoleft() == 1 && cangoright() == 0)
		{
			if (move3 >= move2)
			{
				b = 3;
				moveandadd();
				randomnumber();
			}
			else
			{
				b = 2;
				moveandadd();
				randomnumber();
			}
		}
		else if (cangodown() == 1 && cangoleft() == 0 && cangoright() == 1)
		{
			if (move3 >= move4)
			{
				b = 3;
				moveandadd();
				randomnumber();
			}
			else
			{
				b = 4;
				moveandadd();
				randomnumber();
			}
		}
		else if (cangodown() == 0 && cangoleft() == 1 && cangoright() == 1)
		{
			if (move2 >= move4)
			{
				b = 2;
				moveandadd();
				randomnumber();
			}
			else
			{
				b = 4;
				moveandadd();
				randomnumber();
			}
		}
		else if (cangodown() == 1 && cangoleft() == 0 && cangoright() == 0)
		{
			b = 3;
			moveandadd();
			randomnumber();
		}
		else if (cangodown() == 0 && cangoleft() == 1 && cangoright() == 0)
		{
			b = 2;
			moveandadd();
			randomnumber();
		}
		else if (cangodown() == 0 && cangoleft() == 0 && cangoright() == 1)
		{
			b = 4;
			moveandadd();
			randomnumber();
		}
		else if (cangodown() == 0 && cangoleft() == 0 && cangoright() == 0)
		{
			b = 1;
			moveandadd();
			randomnumber();
			b = 3;
			moveandadd();
			randomnumber();
		}

		t = notfull();
		if (t == 0)//如果没有空格子，则判断游戏是否结束 
		{
			if (canstillmove() == 1)//仍能移动，游戏继续 
			{
			}
			else
			{
				break;
			}
		}
	}
	return point;
}

