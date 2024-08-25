/************************************电脑AI参战函数库**************************************/

#include "2048AI.h"

extern int a[4][4];
extern int b, M;
extern int point;

int cangodown()
//可以向下则输出1，否则输出0
{
	int i, j;
	int k = 0;
	for(j=0;j<4;j++)
	{
		for(i=0;i<3;i++)
		{
			if(a[i][j] != 0 && a[i+1][j] == 0) k = 1;
			if(a[i][j] == a[i+1][j] && a[i][j] != 0) k = 1;
		}
	}
	return k;
} 


int cangoleft()
//可以向左则输出1，否则输出0
{
	int i, j;
	int k = 0;
	for(i=0;i<4;i++)
	{
		for(j=0;j<3;j++)
		{
			if(a[i][j+1] != 0 && a[i][j] == 0) k = 1;
			if(a[i][j] == a[i][j+1] && a[i][j] != 0) k = 1;
		}
	}
	return k;
} 


int cangoright()
//可以向右则输出1，否则输出0
{
	int i, j;
	int k = 0;
	for(i=0;i<4;i++)
	{
		for(j=0;j<3;j++)
		{
			if(a[i][j] != 0 && a[i][j+1] == 0) k = 1;
			if(a[i][j] == a[i][j+1] && a[i][j] != 0) k = 1;
		}
	}
	return k;
} 


int cangoup()
//可以向上则输出1，否则输出0
{
	int i, j;
	int k = 0;
	for(j=0;j<4;j++)
	{
		for(i=0;i<3;i++)
		{
			if(a[i+1][j] != 0 && a[i][j] == 0) k = 1;
			if(a[i][j] == a[i+1][j] && a[i][j] != 0) k = 1;
		}
	}
	return k;
} 


int bottomnotempty()
//底层非空返回1，空返回0 
{
	int j;
	int k = 0;
	for(j=0;j<4;j++)
	{
		if(a[3][j] != 0) k = 1;
	}
	return k;
}


int bottomcanleft()
//底层可以向左则输出1，否则输出0
{
	int j;
	int k = 0;
	for(j=0;j<3;j++)
	{
		if(a[3][j+1] != 0 && a[3][j] == 0) k = 1;
		if(a[3][j] == a[3][j+1] && a[3][j] != 0) k = 1;
	}

	return k;
} 


int bottomcanright()
//底层可以向右则输出1，否则输出0
{
	int j;
	int k = 0;
	for(j=0;j<3;j++)
	{
		if(a[3][j] != 0 && a[3][j+1] == 0) k = 1;
		if(a[3][j] == a[3][j+1] && a[3][j] != 0) k = 1;
	}

	return k;
} 


int pointchange(char k)
//下一步移动增加的分数
{
	int a0[4][4];//对a的copy 
	int n = 0;//n是预设返回值
	int i,j,pass,m;//i表示行，j表示列，pass表示检测的轮数,m表示是否进行了合并 
	for (i=0; i<4; i++)
	{
		for (j=0; j<4; j++)
		{
			a0[i][j]=a[i][j];
		}
	}
	if(k == 'w')//向上的移动操作 
	{
		for(j=0;j<4;j++)
		{
			m = 0;//m=0表示没有进行合并，m不为零表示两个相同的数字合并前其中一个是什么（即表示合并的类型，允许出现2222的两次合并，但不允许出现224的合并再合并）
			if(a0[0][j] == a0[1][j] && a0[2][j] == a0[3][j] && a0[0][j] != 0 && a0[2][j] != 0)//考虑2244的情况，原先的代码会变成228
			{
				a0[0][j] = 2*a0[0][j]; n += a0[0][j];
				a0[1][j] = 2*a0[2][j]; n += a0[1][j];
				a0[2][j] = 0;
				a0[3][j] = 0;
			 } 
			else
			{
				for(pass=1;pass<=4;pass++)
				{
					for(i=1;i<4;i++)
					{
						if(a0[i-1][j] == 0 && a0[i][j] != 0)//有空位，上移 
						{
							a0[i-1][j] = a0[i][j];
							a0[i][j] = 0;
						}
						if(a0[i-1][j] != 0 && a0[i-1][j] == a0[i][j] && m == 0)//无空位，还没有进行过合并，数字相同，合并相加并记录合并的类型 
						{
							m = a0[i][j];
							a0[i-1][j] = 2*a0[i][j]; n += a0[i-1][j];
							a0[i][j] = 0;
						}
						if(a0[i-1][j] != 0 && a0[i-1][j] == a0[i][j] && m != 0 && a0[i][j] == m)//无空位，已经进行过合并，数字相同
						{
							a0[i-1][j] = 2*a0[i][j]; n += a0[i-1][j]; 
							a0[i][j] = 0;
						}
					}
				}
			}
		}
	}
	if(k == 'a')//向左的移动操作 
	{
		for(i=0;i<4;i++)
		{
			m = 0;//m=0表示没有进行合并，m不为零表示两个相同的数字合并前其中一个是什么（即表示合并的类型，允许出现2222的两次合并，但不允许出现224的合并再合并）
			if(a0[i][0] == a0[i][1] && a0[i][2] == a0[i][3] && a0[i][0] != 0 && a0[i][2] != 0)//考虑2244的情况，原先的代码会变成228 
			{
				a0[i][0] = 2*a0[i][0]; n += a0[i][0];
				a0[i][1] = 2*a0[i][2]; n += a0[i][1];
				a0[i][2] = 0;
				a0[i][3] = 0;
			 } 
			else
			{
				for(pass=1;pass<=4;pass++)
				{
					for(j=1;j<4;j++)
					{
						if(a0[i][j-1] == 0 && a0[i][j] != 0)//有空位，左移 
						{
							a0[i][j-1] = a0[i][j];
							a0[i][j] = 0;
						}
						if(a0[i][j-1] != 0 && a0[i][j-1] == a0[i][j] && m == 0)//无空位，还没有进行过合并，数字相同，合并相加并记录合并的类型 
						{
							m = a0[i][j];
							a0[i][j-1] = 2*a0[i][j]; n += a0[i][j-1];
							a0[i][j] = 0;
						}
						if(a0[i][j-1] != 0 && a0[i][j-1] == a0[i][j] && m != 0 && a0[i][j] == m)//无空位，已经进行过合并，数字相同
						{
							a0[i][j-1] = 2*a0[i][j]; n += a0[i][j-1];
							a0[i][j] = 0;
						}
					}
				}
			}
		}
	}
	if(k == 's')//向下的移动操作 
	{
		for(j=0;j<4;j++)
		{
			m = 0;//m=0表示没有进行合并，m不为零表示两个相同的数字合并前其中一个是什么（即表示合并的类型，允许出现2222的两次合并，但不允许出现224的合并再合并） 
			if(a0[0][j] == a0[1][j] && a0[2][j] == a0[3][j] && a0[0][j] != 0 && a0[2][j] != 0)//考虑2244的情况，原先的代码会变成228 
			{
				a0[2][j] = 2*a0[0][j]; n += a0[2][j];
				a0[3][j] = 2*a0[2][j]; n += a0[3][j];
				a0[0][j] = 0;
				a0[1][j] = 0;
			 } 
			else
			{
				for(pass=1;pass<=4;pass++)
				{
					for(i=2;i>=0;i--)
					{
						if(a0[i+1][j] == 0 && a0[i][j] != 0)//有空位，下移 
						{
							a0[i+1][j] = a0[i][j];
							a0[i][j] = 0;
						}
						if(a0[i+1][j] != 0 && a0[i+1][j] == a0[i][j] && m == 0)//无空位，还没有进行过合并，数字相同，合并相加并记录合并的类型 
						{
							m = a0[i][j];
							a0[i+1][j] = 2*a0[i][j]; n += a0[i+1][j];
							a0[i][j] = 0;
						}
						if(a0[i+1][j] != 0 && a0[i+1][j] == a0[i][j] && m != 0 && a0[i][j] == m)//无空位，已经进行过合并，数字相同
						{
							a0[i+1][j] = 2*a0[i][j]; n += a0[i+1][j];
							a0[i][j] = 0;
						}
					}
				}
			}
		}
	}
	if(k == 'd')//向右的移动操作 
	{
		for(i=0;i<4;i++)
		{
			m = 0;//m=0表示没有进行合并，m不为零表示两个相同的数字合并前其中一个是什么（即表示合并的类型，允许出现2222的两次合并，但不允许出现224的合并再合并）
			if(a0[i][0] == a0[i][1] && a0[i][2] == a0[i][3] && a0[i][0] != 0 && a0[i][2] != 0)//考虑2244的情况，原先的代码会变成228 
			{
				a0[i][2] = 2*a0[i][0]; n += a0[i][2];
				a0[i][3] = 2*a0[i][2]; n += a0[i][3];
				a0[i][0] = 0;
				a0[i][1] = 0;
			 } 
			else
			{
				for(pass=1;pass<=4;pass++)
				{
					for(j=2;j>=0;j--)
					{
						if(a0[i][j+1] == 0 && a0[i][j] != 0)//有空位，右移 
						{
							a0[i][j+1] = a0[i][j];
							a0[i][j] = 0;
						}
						if(a0[i][j+1] != 0 && a0[i][j+1] == a0[i][j] && m == 0)//无空位，还没有进行过合并，数字相同，合并相加并记录合并的类型 
						{
							m = a0[i][j];
							a0[i][j+1] = 2*a0[i][j]; n += a0[i][j+1];
							a0[i][j] = 0;
						}
						if(a0[i][j+1] != 0 && a0[i][j+1] == a0[i][j] && m != 0 && a0[i][j] == m)//无空位，已经进行过合并，数字相同
						{
							a0[i][j+1] = 2*a0[i][j]; n += a0[i][j+1];
							a0[i][j] = 0;
						}
					}
				}
			}
		}
	}
	return n;
}


char pointprefer()
//下左右哪个分特别高返回哪个字符 
{
	int aa = pointchange('a'), 
		as = pointchange('s'),
		ad = pointchange('d');
	if(aa >= 2*as+1 && aa >= 2*ad+1)
		return 'a';
	else if(as >= 2*aa+1 && aa >= 2*ad+1)
		return 's';
	else if(ad >= 2*aa+1 && aa >= 2*as+1) 
		return 'd';
	else return '\0';
}


char AI2048()
//AI反应函数
//根据16个数字方块以及分数来输出一个方向字符 
{
	char k = 's';
	if(bottomnotempty() == 0)
	{
		k = 's';
	}
	else if(bottomcanleft() == 1)
	{
		k = 'a';
	}
	else if(bottomcanright() == 1 && cangodown() == 1)
	{
		k = 's';
	}
	else if(bottomcanright() == 1 && cangodown() != 1)
	{
		k = 'd';
	}
	else if(bottomcanright() != 1 && bottomcanleft() != 1)//底层不能动了 
	{
		if(pointprefer() != '\0')
		{
			k = pointprefer();
		}
		else if(pointprefer() == '\0')
		{
			if(cangodown() == 1)
				k = 's'; 
			else if(cangoleft() == 1)
				k = 'a'; 
			else if(cangoright() == 1)
				k = 'd';
			else
				k = 'w';
		}
	}
	return k;
	
	
	/*
    if(pointprefer() != '\0')//优先进行具有明显分数优势的步骤 
		k = pointprefer();
	else if(bottomcanleft() == 1)//若最下层能左移，则左移 
		k = 'a';   
	else if(a[3][3] == 0 || a[3][2] == 0 || a[3][1] == 0 || a[3][0] == 0)//若最下层有空格，按照's''a''d''w'优先级移动 
	{
		if(cangodown() == 1)
			k = 's'; 
		else if(cangoleft() == 1)
			k = 'a'; 
		else if(cangoright() == 1)
			k = 'd';
		else
			k = 'w';
	}
	else //若最下层已满，按照'a''s''d''w'优先级移动 
	{
		if(cangoleft() == 1)
			k = 'a'; 
		else if(cangodown() == 1)
			k = 's'; 
		else if(cangoright() == 1)
			k = 'd';
		else
			k = 'w';
	}
	*/
	
}
