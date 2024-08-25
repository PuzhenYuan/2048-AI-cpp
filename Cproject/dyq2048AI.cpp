/************************************* ����AI2��ս������**************************************/

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
	a2h();//������е�һ���������ǰ��aֵ 
	b = 3;//�����һ�������ƶ� 
	r3 = moveandadd40();//ע���ʱa��ֵ�ѱ仯�������ı�pointֵ��point1ֵ 
	if (r3 == 1)
	{
		a2h1();//������е�һ������������aֵ
		move3 = dataCollection();//move3�����һ�������ƶ������� 
	}
	h2a();//ʹaֵ�ص����е�һ���������ǰ��ֵ 
	b = 2;//�����һ�������ƶ� 
	r2 = moveandadd40();
	if (r2 == 1)
	{
		a2h1();//��������������������aֵ
		move2 = dataCollection();//move2�����һ�������ƶ������� 
	}

	h2a();//ʹaֵ�ص����е�һ���������ǰ��ֵ
	b = 4;//���������ƶ� 
	r4 = moveandadd40();
	if (r4 == 1)
	{
		a2h1();//����������Ҽ���������aֵ
		move4 = dataCollection();//move4�����һ�������ƶ������� 
	}
	h2a();//ʹaֵ�ص����е�һ���������ǰ��ֵ
}


int emptyCells()
//emptyCells�������ڼ���ո������ո���Խ��Խ��������������ֵΪ a�Ŀո��� 
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
//�ú��������ռ�����a������ 
{
	int point1 = 0;
	//point1��¼����������point 
	int i, j, k = 0;
	//kΪ����if(a[i][j] == 0)��ѭ��������Ҳ���ڿո��� 
	int X3 = 0, X2 = 0, X4 = 0, X = 0;
	//X3��¼ ���ڶ����������Ϊ���� ��ʱ�Ŀո���
	//X2��¼ ���ڶ����������Ϊ���� ��ʱ�Ŀո���
	//X4��¼ ���ڶ����������Ϊ���� ��ʱ�Ŀո���
	//X��¼ ���ڶ���������� ����Ŀո��������ֵ�����ڶ�����ȡ ������ ���߷���Ŀո��� 
	int P3 = 0, P2 = 0, P4 = 0, P = 0;
	//P3��¼ ���ڶ����������Ϊ���� ��ʱ�ķ�����ֵ 
	//P2��¼ ���ڶ����������Ϊ���� ��ʱ�ķ�����ֵ 
	//P4��¼ ���ڶ����������Ϊ���� ��ʱ�ķ�����ֵ 
	//P��¼ ���ڶ���������� ����ķ�����ֵ�����ֵ�����ڶ�����ȡ ������ ���߷���ķ�����ֵ 
	int M3 = 0, M2 = 0, M4 = 0, M = 0;
	//M3��¼ ���ڶ����������Ϊ���� ��ʱ�ĵ��������� 
	//M2��¼ ���ڶ����������Ϊ���� ��ʱ�ĵ���������
	//M4��¼ ���ڶ����������Ϊ���� ��ʱ�ĵ���������
	//M��¼ ���ڶ���������� ����ĵ��������ݵ����ֵ�����ڶ�����ȡ ������ ���߷���ĵ��������� 
	float x2 = 0, x4 = 0;
	//x2Ϊ���µ���������Ϊ 2ʱ�Ŀո�����ƽ��ֵ
	//x4Ϊ���µ���������Ϊ 4ʱ�Ŀո�����ƽ��ֵ
	float p2 = 0, p4 = 0;
	//p2Ϊ���µ���������Ϊ 2ʱ�ķ�����ֵ��ƽ��ֵ 
	//p4Ϊ���µ���������Ϊ 4ʱ�ķ�����ֵ��ƽ��ֵ 
	float m2 = 0, m4 = 0;
	//m2Ϊ���µ���������Ϊ 2ʱ�ĵ��������ݵ�ƽ��ֵ 
	//m4Ϊ���µ���������Ϊ 4ʱ�ĵ��������ݵ�ƽ��ֵ 
	float data = 0;
	//data��Ϊ�����ķ���ֵ���� AI�ĺ����ж����� 
	float A1 = 0.1001,//A1Ϊ������ֵȨ����ƽ��ֵȨ�صı�ֵ���ñ�ֵͨ��ѧϰ�õ� 
		A2 = 0.0051;//A2Ϊ����������Ȩ����ƽ��ֵȨ�صı�ֵ���ñ�ֵͨ��ѧϰ�õ�

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (a[i][j] == 0)
			{
				//����ѭ����ʾ������е�������������� 
				k++;//k��¼����if(a[i][j] == 0)��ѭ��������Ҳ���ڿո���

				h12a();//�� a��ֵ�ָ�Ϊ h1�������е�һ������������ aֵ 
				a[i][j] = 2;//�����λ��Ϊ2 
				b = 3;//����ڶ�������Ϊ�����ƶ� 
				point1 = point;//��¼pointֵ 
				point1 = moveandadd41();//�˴��ı� aֵ�����ı� pointֵ ,�ı� point1ֵ 
				X3 = emptyCells();//��¼��ʱʣ��ո��� 
				P3 = point1 - point;//P3��¼ ���ڶ����������Ϊ���� ��ʱ�ķ�����ֵ 
				M3 = monotony();//M3��¼ ���ڶ����������Ϊ���� ��ʱ�ĵ��������� 

				h12a();
				a[i][j] = 2;
				b = 2;//����ڶ�������Ϊ�����ƶ�
				point1 = point;
				point1 = moveandadd41();
				X2 = emptyCells();
				P2 = point1 - point;
				M2 = monotony();

				h12a();
				a[i][j] = 2;
				b = 4;//����ڶ�������Ϊ�����ƶ�
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
				}//X��¼ ���ڶ���������� ����Ŀո��������ֵ�����ڶ�����ȡ ������ ���߷���Ŀո���

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
				}//P��¼ ���ڶ���������� ����ķ�����ֵ�����ֵ�����ڶ�����ȡ ������ ���߷���ķ�����ֵ

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
				}//M��¼ ���ڶ���������� ����ĵ��������ݵ����ֵ�����ڶ�����ȡ ������ ���߷���ĵ��������� 

				x2 = (x2 * (k - 1) + X) / k;//x2Ϊ���µ���������Ϊ 2ʱ�Ŀո�����ƽ��ֵ
				p2 = (p2 * (k - 1) + P) / k;//p2Ϊ���µ���������Ϊ 2ʱ�ķ�����ֵ��ƽ��ֵ 
				m2 = (m2 * (k - 1) + P) / k;//m2Ϊ���µ���������Ϊ 2ʱ�ĵ��������ݵ�ƽ��ֵ


				h12a();
				a[i][j] = 4;//�����λ��Ϊ 4
				b = 3;//����ڶ�������Ϊ�����ƶ� 
				point1 = point;
				point1 = moveandadd41();
				X3 = emptyCells();
				P3 = point1 - point;
				M3 = monotony();

				h12a();
				a[i][j] = 2;
				b = 2;//����ڶ�������Ϊ�����ƶ�
				point1 = point;
				point1 = moveandadd41();
				X2 = emptyCells();
				P2 = point1 - point;
				M2 = monotony();

				h12a();
				a[i][j] = 2;
				b = 4;//����ڶ�������Ϊ�����ƶ�
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

	h12a();//�� a��ֵ�ָ�Ϊ h1�������е�һ������������ aֵ 

	data = 0.9 * x2 + 0.1 * x4 + A1 * (0.9 * p2 + 0.1 * p4) + A2 * (0.9 * m2 + 0.1 * m4);//data��Ϊ AI�ĺ����ж�����,ͨ��������Ѱ�ҵ�һ���������߷� 
	return data;
}


int monotony()//�����������ռ���������������ֵΪ���������� 
{
	int i, j;
	//��4*4�ľ����Ϊ�������򣬷ֱ���� a��b��c��d��e��f 
	int ma = 0, mb = 0, mc = 0, md = 0, me = 0, mf = 0;
	//��Ӧ��������ĵ��������� 
	float A = 1, B = 1, C = 1, D = 3, E = 3, F = 3;
	//��Ӧ��������ĵ��������ݵ�Ȩ�� 
	float m;
	//mΪ�������ۺ����ݣ���Ϊ��������ֵ
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
//��a��ֵ����h 
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
//��h��ֵ����a
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
//��a��ֵ����h1
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
//��h1��ֵ����a
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
//����AI��β�ս������ֻ���ط���ֵ 
//m��ֵ��Ϊ�˲���α��������ӣ�һ��ʱ��̫���˲�����time��NULL)�� 
//��ע���ú���ʵ���Ͼ���main.c�е� computerplay2()������ȥprint��sleep����������һ��AI���еķ���ֵ 
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
	srand(m);//��m��ֵ��Ϊseed����֤ÿ�ֲ�ͬ 
	randomnumber();
	randomnumber();

	while (1)
	{

		dyq2048AI();//�ռ����� 

		//���������������ж��ƶ�����
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
		if (t == 0)//���û�пո��ӣ����ж���Ϸ�Ƿ���� 
		{
			if (canstillmove() == 1)//�����ƶ�����Ϸ���� 
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

