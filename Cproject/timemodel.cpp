/************************************时间模式函数库**************************************/
//该模式下会每隔1s产生一个2，填满则gameover
 
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "timemodel.h"

extern int a[4][4];
extern int h[4][4];
extern int b, M;
extern int point;

int u[4][4] = {0};//4*4矩阵的替身 

int pointmaxTIME()
//用于返回时间模式历史最高分 
{
	//用“r”模式，先读入原有记录，分配到字符数组中 
	FILE* fptr1;
	errno_t err1 = fopen_s(&fptr1, "recordTIME.txt", "r");
	char pt[10] = { 0 };
	if (fptr1 != NULL){
		fgets(pt, 10, fptr1);
		fclose(fptr1);
	}
	//对数组进行处理 
	int maxpt = 0;
	maxpt = atoi(pt);
	if(point > maxpt)
	{
		maxpt = point;
		sprintf_s(pt, "%d\n", maxpt);
	}
	//用“w”模式写进文件 
	FILE* fptr2;
	errno_t err2 = fopen_s(&fptr2, "recordTIME.txt", "w");
	if (fptr2 != NULL){
		fputs(pt, fptr2);
		fclose(fptr2);
	}
	return maxpt;
}


void printTIME()
//print函数用于打印游戏界面 
{
	system("CLS");//清空屏幕，重新打印 
	int i,j,k;
	
	    for(k=1;k<=23;k++)//第一行 
	{
		printf("*");
	}
	printf("   你的得分：%d", point);
	printf("\n");
	for(i=0;i<4;i++)//第二至五行 
	{
		printf("* ");
		for(j=0;j<4;j++)
		{
			if(a[i][j] != 0)
			{
				printf("%-5d",a[i][j]); 
			}
			else
			{
				printf("     ");
			}
		}
		printf("*");
		if(i == 0) printf("   最高得分：%d", pointmaxTIME());
		printf("\n");
	}
	for(k=1;k<=23;k++)//第六行 
	{
		printf("*");
	}
	printf("\n");
}

int notfullTIME()
//notfull函数用于判断是否有空格子，有的话返回1,已经填满返回0 
{
	int i,j,k=0;
	
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(a[i][j] == 0)
			{
				k = 1;
				break;
			}
		}
	}	
	return k;
}

int randTIME()
//规定时间模式下只产生2 
{
	int y;
	y = 2;
	return y; 
}

void randomnumberTIME()
//randomnumber函数用于在玩家进行操作过后，随机选取一个空格子，生成数字2或4 
{
	int x;//x表示将要生成的数字
	x = randTIME();//x只能为2
	int i,j;
	do
	{
		i = rand()%4;
		j = rand()%4;
	}while(a[i][j] != 0);
	a[i][j] = x;
}


int calculatemaxTIME()
//calculatemax函数用于获取当前数组中的最大数字
{
	int maxnumber = 2;
	int i,j;
	
		for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(a[i][j] > maxnumber)
			{
				maxnumber = a[i][j];
			}
		}
	}
	
	return maxnumber;
}


int moveTIME()
//move函数关联四个方向按键和相应的移动 
{
	char key = _getch(), k = 0;//k=0表示没有按方向键，k=1表示正确按了方向键 
	if(key == 'w' || key == 'W')//上 
	{
		b = 1;
		k = 1;
	}
	if(key == 'a' || key == 'A')//左 
	{
		b = 2;
		k = 1;
	}
	if(key == 's' || key == 'S')//下 
	{
		b = 3;
		k = 1;
	}
	if(key == 'd' || key == 'D')//右 
	{
		b = 4;
		k = 1;
	}
	return k;
}

int canstillmoveTIME()
//canstillmove函数用于判断当没有空格的时候，是否还可以再进行移动
//仍然可以移动返回1，游戏继续；不能再移动返回0，游戏结束 
{
	int k = 0;//k是预设返回值
	int i,j;
	
	    for(i=0;i<4;i++)//检查左右是否有相邻的相同数字 
	{
		for(j=0;j<3;j++)
		{
			if(a[i][j] == a[i][j+1])
			{
				k = 1;
			}
		}
	}
	for(j=0;j<4;j++)//检查上下是否有相邻的相同数字 
	{
		for(i=0;i<3;i++)
		{
			if(a[i][j] == a[i+1][j])
			{
				k = 1;
			}
		}
	}
	
	return k;
}


int moveandaddTIME()
//moveandadd函数用于进行移动和数字相加的操作
//返回1表示进行了移动，返回0表示未进行移动 
{
	int k = 0;//k是预设返回值
	int i,j,pass,m;//i表示形式参数行，j表示形式参数列，pass表示检测的轮数,m表示是否进行了合并 
	
	    if(b == 1)//向上的移动操作 
	{
		for(i = 0;i < 4;i++)
		{
			for(j = 0;j < 4;j++)
			{
				u[i][j] = a[i][j];			
			}
		}
		
		for(j=0;j<4;j++)
		{
			m = 0;//m=0表示没有进行合并，m不为零表示两个相同的数字合并前其中一个是什么（即表示合并的类型，允许出现2222的两次合并，但不允许出现224的合并再合并）
			if(u[0][j] == u[1][j] && u[2][j] == u[3][j] && u[0][j] != 0 && u[2][j] != 0)//考虑2244的情况，原先的代码会变成228
			{
				u[0][j] = 2*u[0][j]; point += u[0][j];
				u[1][j] = 2*u[2][j]; point += u[1][j];
				u[2][j] = 0;
				u[3][j] = 0;
				k = 1;
			 } 
			else
			{
				for(pass=1;pass<=3;pass++)
				{
					for(i=1;i<4;i++)
					{
						if(u[i-1][j] == 0 && u[i][j] != 0)//有空位，上移 
						{
							u[i-1][j] = u[i][j];
							u[i][j] = 0;
							k = 1;
						}
						if(u[i-1][j] != 0 && u[i-1][j] == u[i][j] && m == 0)//无空位，还没有进行过合并，数字相同，合并相加并记录合并的类型 
						{
							m = u[i][j];
							u[i-1][j] = 2*u[i][j]; point += u[i-1][j];
							u[i][j] = 0;
							k = 1;
						}
						if(u[i-1][j] != 0 && u[i-1][j] == u[i][j] && m != 0 && u[i][j] == m)//无空位，已经进行过合并，数字相同
						{
							u[i-1][j] = 2*u[i][j]; point += u[i-1][j]; 
							u[i][j] = 0;
							k = 1;
						}
					}
				}
			}
		}
		
		for(i = 0;i < 4;i++)
		{
			for(j = 0;j < 4;j++)
			{
				a[i][j] = u[i][j];			
			}
		}
     }
	
	if(b == 2)//向左的移动操作 
	{
        for(i = 0;i < 4;i++)
		{
			for(j = 0;j < 4;j++)
			{
				u[i][j] = a[j][i];			
			}
		}
		
		for(j=0;j<4;j++)
		{
			m = 0;//m=0表示没有进行合并，m不为零表示两个相同的数字合并前其中一个是什么（即表示合并的类型，允许出现2222的两次合并，但不允许出现224的合并再合并）
			if(u[0][j] == u[1][j] && u[2][j] == u[3][j] && u[0][j] != 0 && u[2][j] != 0)//考虑2244的情况，原先的代码会变成228
			{
				u[0][j] = 2*u[0][j]; point += u[0][j];
				u[1][j] = 2*u[2][j]; point += u[1][j];
				u[2][j] = 0;
				u[3][j] = 0;
				k = 1;
			 } 
			else
			{
				for(pass=1;pass<=4;pass++)
				{
					for(i=1;i<4;i++)
					{
						if(u[i-1][j] == 0 && u[i][j] != 0)//有空位，上移 
						{
							u[i-1][j] = u[i][j];
							u[i][j] = 0;
							k = 1;
						}
						if(u[i-1][j] != 0 && u[i-1][j] == u[i][j] && m == 0)//无空位，还没有进行过合并，数字相同，合并相加并记录合并的类型 
						{
							m = u[i][j];
							u[i-1][j] = 2*u[i][j]; point += u[i-1][j];
							u[i][j] = 0;
							k = 1;
						}
						if(u[i-1][j] != 0 && u[i-1][j] == u[i][j] && m != 0 && u[i][j] == m)//无空位，已经进行过合并，数字相同
						{
							u[i-1][j] = 2*u[i][j]; point += u[i-1][j]; 
							u[i][j] = 0;
							k = 1;
						}
					}
				}
			}
		}
		
		for(i = 0;i < 4;i++)
		{
			for(j = 0;j < 4;j++)
			{
				a[i][j] = u[j][i];			
			}
		}
	}
	if(b == 3)//向下的移动操作 
	{
	    for(i = 0;i < 4;i++)
		{
			for(j = 0;j < 4;j++)
			{
				u[i][j] = a[3-i][j];			
			}
		}
		
		for(j=0;j<4;j++)
		{
			m = 0;//m=0表示没有进行合并，m不为零表示两个相同的数字合并前其中一个是什么（即表示合并的类型，允许出现2222的两次合并，但不允许出现224的合并再合并）
			if(u[0][j] == u[1][j] && u[2][j] == u[3][j] && u[0][j] != 0 && u[2][j] != 0)//考虑2244的情况，原先的代码会变成228
			{
				u[0][j] = 2*u[0][j]; point += u[0][j];
				u[1][j] = 2*u[2][j]; point += u[1][j];
				u[2][j] = 0;
				u[3][j] = 0;
				k = 1;
			 } 
			else
			{
				for(pass=1;pass<=4;pass++)
				{
					for(i=1;i<4;i++)
					{
						if(u[i-1][j] == 0 && u[i][j] != 0)//有空位，上移 
						{
							u[i-1][j] = u[i][j];
							u[i][j] = 0;
							k = 1;
						}
						if(u[i-1][j] != 0 && u[i-1][j] == u[i][j] && m == 0)//无空位，还没有进行过合并，数字相同，合并相加并记录合并的类型 
						{
							m = u[i][j];
							u[i-1][j] = 2*u[i][j]; point += u[i-1][j];
							u[i][j] = 0;
							k = 1;
						}
						if(u[i-1][j] != 0 && u[i-1][j] == u[i][j] && m != 0 && u[i][j] == m)//无空位，已经进行过合并，数字相同
						{
							u[i-1][j] = 2*u[i][j]; point += u[i-1][j]; 
							u[i][j] = 0;
							k = 1;
						}
					}
				}
			}
		}
		
		for(i = 0;i < 4;i++)
		{
			for(j = 0;j < 4;j++)
			{
				a[i][j] = u[3-i][j];			
			}
		}
	}
	
	if(b == 4)//向右的移动操作 
	{
	    for(i = 0;i < 4;i++)
		{
			for(j = 0;j < 4;j++)
			{
				u[i][j] = a[j][3-i];			
			}
		}
		
		for(j=0;j<4;j++)
		{
			m = 0;//m=0表示没有进行合并，m不为零表示两个相同的数字合并前其中一个是什么（即表示合并的类型，允许出现2222的两次合并，但不允许出现224的合并再合并）
			if(u[0][j] == u[1][j] && u[2][j] == u[3][j] && u[0][j] != 0 && u[2][j] != 0)//考虑2244的情况，原先的代码会变成228
			{
				u[0][j] = 2*u[0][j]; point += u[0][j];
				u[1][j] = 2*u[2][j]; point += u[1][j];
				u[2][j] = 0;
				u[3][j] = 0;
				k = 1;
			 } 
			else
			{
				for(pass=1;pass<=4;pass++)
				{
					for(i=1;i<4;i++)
					{
						if(u[i-1][j] == 0 && u[i][j] != 0)//有空位，上移 
						{
							u[i-1][j] = u[i][j];
							u[i][j] = 0;
							k = 1;
						}
						if(u[i-1][j] != 0 && u[i-1][j] == u[i][j] && m == 0)//无空位，还没有进行过合并，数字相同，合并相加并记录合并的类型 
						{
							m = u[i][j];
							u[i-1][j] = 2*u[i][j]; point += u[i-1][j];
							u[i][j] = 0;
							k = 1;
						}
						if(u[i-1][j] != 0 && u[i-1][j] == u[i][j] && m != 0 && u[i][j] == m)//无空位，已经进行过合并，数字相同
						{
							u[i-1][j] = 2*u[i][j]; point += u[i-1][j]; 
							u[i][j] = 0;
							k = 1;
						}
					}
				}
			}
		}
		
		for(i = 0;i < 4;i++)
		{
			for(j = 0;j < 4;j++)
			{
				a[i][j] = u[3-j][i];			
			}
		}
	}
	return k;
}

int changeTIME(char c)
{
	if(c == 'w' || c == 'W') return 1;
	if(c == 'a' || c == 'A') return 2;
	if(c == 's' || c == 'S') return 3;
	if(c == 'd' || c == 'D') return 4;
}

