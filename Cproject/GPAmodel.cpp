/************************************GPA模式函数库**************************************/
//将数字换成GPA评级输出
//增加W退课（能够消除第一个碰到的方块）
//增加F不及格（只能被W消除，或两个F合并，以增加游戏体验） 

#include <stdio.h> 
#include <stdlib.h>
#include <conio.h>
#include "GPAmodel.h"

#define numW -19  //负数，不要2的倍数，相互互素 
#define numF +17  //正数，不要2的倍数，相互互素

extern int a[4][4];
extern int b, M;
extern int point;

int v[4][4] = {0};//4*4矩阵的替身

float GPAmax()
//用于返回历史最高绩点 
{
	//用“r”模式，先读入原有记录，分配到字符数组中 
	FILE* fptr1;
	errno_t err1 = fopen_s(&fptr1, "recordGPA.txt", "r");
	char pt[10] = { 0 };
	if (fptr1 != NULL){
		fgets(pt, 10, fptr1);
		fclose(fptr1);
    }
	//对数组进行处理 
	float maxpt = 0.0;
	maxpt = atof(pt);
	if(averageGPA() > maxpt)
	{
		maxpt = averageGPA();
		sprintf_s(pt, "%.2f\n", maxpt);
	}
	//用“w”模式写进文件 
	FILE* fptr2;
	errno_t err = fopen_s(&fptr2, "recordGPA.txt", "w");
	if (fptr2 != NULL){
		fputs(pt, fptr2);
		fclose(fptr2);
	}
	return maxpt;
} 


int char2num(char *p)
//将输入的绩点目标换成2048数字
{
	int k = 0;
	if(*p == 'D' && *(p+1) == '\0')
    {
   	    k = 2;
    }
    if(*p == 'D' && *(p+1) == '+')
    {
   	    k = 4;
    }
    if(*p == 'C' && *(p+1) == '-')
    {
   	    k = 8;
    }
    if(*p == 'C' && *(p+1) == '\0')
    {
   	    k = 16;
    }
    if(*p == 'C' && *(p+1) == '+')
    {
   	    k = 32;
    }
    if(*p == 'B' && *(p+1) == '-')
    {
   	    k = 64;
    }
    if(*p == 'B' && *(p+1) == '\0')
    {
   	    k = 128;
    }
    if(*p == 'B' && *(p+1) == '+')
    {
   	    k = 256;
    }
    if(*p == 'A' && *(p+1) == '-')
    {
   	    k = 512;
    }
    if(*p == 'A' && *(p+1) == '\0')
    {
   	    k = 1024;
    }
    if(*p == 'A' && *(p+1) == '+')
    {
   	    k = 2048;
    }
	return k;
}


char* num2char(int n)
{
	static char a[5] = { 0 };
	char* ptr = a;
	if (n == 2) {
		*ptr = 'D';
		*(ptr + 1) = '\0';
		*(ptr + 2) = '\0';
	}
	if (n == 4) {
		*ptr = 'D';
		*(ptr + 1) = '+';
		*(ptr + 2) = '\0';
	}
	if (n == 8) {
		*ptr = 'C';
		*(ptr + 1) = '-';
		*(ptr + 2) = '\0';
	}
	if (n == 16) {
		*ptr = 'C';
		*(ptr + 1) = '\0';
		*(ptr + 2) = '\0';
	}
	if (n == 32) {
		*ptr = 'C';
		*(ptr + 1) = '+';
		*(ptr + 2) = '\0';
	}
	if (n == 64) {
		*ptr = 'B';
		*(ptr + 1) = '-';
		*(ptr + 2) = '\0';
	}
	if (n == 128) {
		*ptr = 'B';
		*(ptr + 1) = '\0';
		*(ptr + 2) = '\0';
	}
	if (n == 256) {
		*ptr = 'B';
		*(ptr + 1) = '+';
		*(ptr + 2) = '\0';
	}
	if (n == 512) {
		*ptr = 'A';
		*(ptr + 1) = '-';
		*(ptr + 2) = '\0';
	}
	if (n == 1024) {
		*ptr = 'A';
		*(ptr + 1) = '\0';
		*(ptr + 2) = '\0';
	}
	if (n == 2048) {
		*ptr = 'A';
		*(ptr + 1) = '+';
		*(ptr + 2) = '\0';
	}
	if (n == numW) {
		*ptr = 'W';
		*(ptr + 1) = '\0';
		*(ptr + 2) = '\0';
	}
	if (n == numF) {
		*ptr = 'F';
		*(ptr + 1) = '\0';
		*(ptr + 2) = '\0';
	}
	return ptr;
}


float averageGPA()
//计算成绩单上的均绩 
{
	float sum = 0;
	int num = 0;
	int i, j;
	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 4; j++)
		{
			if(a[i][j] == numF)  {sum += 0.0;  num++;}  //" F   "
			if(a[i][j] == 2)     {sum += 1.3;  num++;}  //" D   "
			if(a[i][j] == 4)     {sum += 1.6;  num++;}  //" D+  "
			if(a[i][j] == 8)     {sum += 2.0;  num++;}  //" C-  "
			if(a[i][j] == 16)    {sum += 2.3;  num++;}  //" C   "
			if(a[i][j] == 32)    {sum += 2.6;  num++;}  //" C+  "
			if(a[i][j] == 64)    {sum += 3.0;  num++;}  //" B-  "
			if(a[i][j] == 128)   {sum += 3.3;  num++;}  //" B   "
			if(a[i][j] == 256)   {sum += 3.6;  num++;}  //" B+  "
			if(a[i][j] == 512)   {sum += 4.0;  num++;}  //" A-  "
			if(a[i][j] == 1024)  {sum += 4.0;  num++;}  //" A   "
			if(a[i][j] == 2048)  {sum += 4.0;  num++;}  //" A+  "
			if(a[i][j] == 4096)  {sum += 4.0;  num++;}  //"满绩 "
			if(a[i][j] == 8192)  {sum += 5.0;  num++;}  //"特奖 "
		}
	}
	return (sum/(float)num);
}

void printGPA(int n)
//用于根据分数打印GPA 
{
	if(n % numW == 0) printf(" W   ");
	if(n % numF == 0) printf(" F   ");
	
	if(n == 2)    printf(" D   ");
	if(n == 4)    printf(" D+  ");
	if(n == 8)    printf(" C-  ");
	if(n == 16)   printf(" C   ");
	if(n == 32)   printf(" C+  ");
	if(n == 64)   printf(" B-  ");
	if(n == 128)  printf(" B   ");
	if(n == 256)  printf(" B+  ");
	if(n == 512)  printf(" A-  ");
	if(n == 1024) printf(" A   ");
	if(n == 2048) printf(" A+  ");
	if(n == 4096) printf("满绩 ");
	if(n == 8192) printf("特奖 ");
}

void printinGPA()
//print函数用于打印游戏界面 
{
	system("CLS");//清空屏幕，重新打印 
	int i,j,k;
	
	    for(k=1;k<=23;k++)//第一行 
	{
		printf("*");
	}
	printf("   你的均绩：%.2f", averageGPA());
	printf("\n");
	for(i=0;i<4;i++)//第二至五行 
	{
		printf("* ");
		for(j=0;j<4;j++)
		{
			if(a[i][j] != 0)
			{
				printGPA(a[i][j]); 
			}
			else
			{
				printf("     ");
			}
		}
		printf("*");
		if(i == 0) printf("   最高均绩：%.2f", GPAmax()); 
		printf("\n");
	}
	for(k=1;k<=23;k++)//第六行 
	{
		printf("*");
	}
	printf("\n");	
}

int notfullGPA()
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


int randGPA()
//开始时百分之八十的概率产生2，百分之十的概率产生4，百分之五产生W，百分之五产生F
//等到后来学生卷的多了，F概率下降，2概率上升，其余不变
{
	int y;
	y = rand();
	if ((y % 100) >= 0 && (y % 100) < (15000 / (3000 + point)))
		return numF;
	else if ((y % 100) >= 5 && (y % 100) < 10)
		return numW;
	else if ((y % 100) >= 10 && (y % 100) < 20)
		return 4;
	else return 2;
}


void randomGPA()
//random函数用于在玩家进行操作过后，随机选取一个空格子，生成数字2或4 
{
	int x;//x表示将要生成的数字
	x = randGPA();//x可以为D,D+,W,F
	int i,j;
	do
	{
		i = rand()%4;
		j = rand()%4;
	} while(a[i][j] != 0);
	a[i][j] = x;
}

	
int calculatemaxGPA()
//calculatemax函数用于获取当前数组中的最大数字
{
	int maxnumber = 2;
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(a[i][j] > maxnumber && a[i][j] != numF)
			{
				maxnumber = a[i][j];
			}
		}
	}
	return maxnumber;
}


int moveGPA()
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

int canstillmoveGPA()
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
	for (j = 0; j < 4; j++)//检查上下是否有相邻的相同数字 
	{
		for (i = 0; i < 4; i++)
		{
			if (a[i][j] == numW)
			{
				k = 1;
			}
		}
	}
	return k;
}


int moveandaddGPA()
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
				v[i][j] = a[i][j];			
			}
		}
		
		for(j=0;j<4;j++)
		{
			{//这个大括号里包装了让W退课的功能，列数未知故难以写成函数（调用指针） 
				if(v[0][j] == numW)
				{
					if(v[1][j] > 0){
						v[1][j] = 0;
						v[0][j] = 0;
						k = 1;
					}
					else if(v[2][j] > 0 && v[1][j] == 0){
						v[2][j] = 0;
						v[0][j] = 0;
						k = 1;
					}
					else if(v[3][j] > 0 && v[2][j] == 0 && v[1][j] == 0){
						 v[3][j] = 0;
						 v[0][j] = 0;
						 k = 1;
					}
				}
				if(v[1][j] == numW)
				{
					if(v[0][j] > 0){
						v[1][j] = 0;
						v[0][j] = 0;
						k = 1;						
					}
					else if(v[0][j] == 0 && v[2][j] > 0){
						v[1][j] = 0;
						v[2][j] = 0;
						k = 1;
					}
					else if(v[0][j] == 0 && v[2][j] == 0 && v[3][j] > 0){
						v[1][j] = 0;
						v[3][j] = 0;
						k = 1;
					}
				}
				if(v[2][j] == numW)
				{
					if(v[1][j] > 0){
						v[1][j] = 0;
						v[2][j] = 0;
						k = 1;
					}
					else if(v[1][j] == 0 && v[0][j] > 0){
						v[0][j] = 0;
						v[2][j] = 0;
						k = 1;
					}
					else if(v[1][j] == 0 && v[0][j] == 0 && v[3][j] > 0){
						v[3][j] = 0;
						v[2][j] = 0;
						k = 1;
					}
				}
				if(v[3][j] == numW)
				{
					if(v[2][j] > 0){
						v[2][j] = 0;
						v[3][j] = 0;
						k = 1;
					}
					else if(v[2][j] == 0 && v[1][j] > 0){
						v[1][j] = 0;
						v[3][j] = 0;
						k = 1;
					}
					else if(v[2][j] == 0 && v[1][j] == 0 && v[0][j] > 0){
						v[0][j] = 0;
						v[3][j] = 0;
						k = 1;
					}
				}
			}//这个大括号里包装了让W退课的功能 
			
			m = 0;//m=0表示没有进行合并，m不为零表示两个相同的数字合并前其中一个是什么
			if(v[0][j] == v[1][j] && v[2][j] == v[3][j] && v[0][j] != 0 && v[2][j] != 0)//考虑2244的情况，原先的代码会变成228
			{
				v[0][j] = 2*v[0][j]; point += v[0][j];
				v[1][j] = 2*v[2][j]; point += v[1][j];
				v[2][j] = 0;
				v[3][j] = 0;
				k = 1;
			} 
			else
			{
				for(pass=1;pass<=3;pass++)
				{
					for(i=1;i<4;i++)
					{
						if(v[i-1][j] == 0 && v[i][j] != 0)//有空位，上移 
						{
							v[i-1][j] = v[i][j];
							v[i][j] = 0;
							k = 1;
						}
						if(v[i-1][j] != 0 && v[i-1][j] == v[i][j] && m == 0)//无空位，还没有进行过合并，数字相同，合并相加并记录合并的类型 
						{
							m = v[i][j];
							v[i-1][j] = 2*v[i][j]; point += v[i-1][j];
							v[i][j] = 0;
							k = 1;
						}
						if(v[i-1][j] != 0 && v[i-1][j] == v[i][j] && m != 0 && v[i][j] == m)//无空位，已经进行过合并，数字相同
						{
							v[i-1][j] = 2*v[i][j]; point += v[i-1][j]; 
							v[i][j] = 0;
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
				a[i][j] = v[i][j];			
			}
		}
    }
	
	if(b == 2)//向左的移动操作 
	{
        for(i = 0;i < 4;i++)
		{
			for(j = 0;j < 4;j++)
			{
				v[i][j] = a[j][i];			
			}
		}
		
		for(j=0;j<4;j++)
		{
			{//这个大括号里包装了让W退课的功能，列数未知故难以写成函数（调用指针） 
				if(v[0][j] == numW)
				{
					if(v[1][j] > 0){
						v[1][j] = 0;
						v[0][j] = 0;
						k = 1;
					}
					else if(v[2][j] > 0 && v[1][j] == 0){
						v[2][j] = 0;
						v[0][j] = 0;
						k = 1;
					}
					else if(v[3][j] > 0 && v[2][j] == 0 && v[1][j] == 0){
						 v[3][j] = 0;
						 v[0][j] = 0;
						 k = 1;
					}
				}
				if(v[1][j] == numW)
				{
					if(v[0][j] > 0){
						v[1][j] = 0;
						v[0][j] = 0;	
						k = 1;					
					}
					else if(v[0][j] == 0 && v[2][j] > 0){
						v[1][j] = 0;
						v[2][j] = 0;
						k = 1;
					}
					else if(v[0][j] == 0 && v[2][j] == 0 && v[3][j] > 0){
						v[1][j] = 0;
						v[3][j] = 0;
						k = 1;
					}
				}
				if(v[2][j] == numW)
				{
					if(v[1][j] > 0){
						v[1][j] = 0;
						v[2][j] = 0;
						k = 1;
					}
					else if(v[1][j] == 0 && v[0][j] > 0){
						v[0][j] = 0;
						v[2][j] = 0;
						k = 1;
					}
					else if(v[1][j] == 0 && v[0][j] == 0 && v[3][j] > 0){
						v[3][j] = 0;
						v[2][j] = 0;
						k = 1;
					}
				}
				if(v[3][j] == numW)
				{
					if(v[2][j] > 0){
						v[2][j] = 0;
						v[3][j] = 0;
						k = 1;
					}
					else if(v[2][j] == 0 && v[1][j] > 0){
						v[1][j] = 0;
						v[3][j] = 0;
						k = 1;
					}
					else if(v[2][j] == 0 && v[1][j] == 0 && v[0][j] > 0){
						v[0][j] = 0;
						v[3][j] = 0;
						k = 1;
					}
				}
			}//这个大括号里包装了让W退课的功能 			
			
			m = 0;//m=0表示没有进行合并，m不为零表示两个相同的数字合并前其中一个是什么（即表示合并的类型，允许出现2222的两次合并，但不允许出现224的合并再合并）
			if(v[0][j] == v[1][j] && v[2][j] == v[3][j] && v[0][j] != 0 && v[2][j] != 0)//考虑2244的情况，原先的代码会变成228
			{
				v[0][j] = 2*v[0][j]; point += v[0][j];
				v[1][j] = 2*v[2][j]; point += v[1][j];
				v[2][j] = 0;
				v[3][j] = 0;
				k = 1;
			 } 
			else
			{
				for(pass=1;pass<=4;pass++)
				{
					for(i=1;i<4;i++)
					{
						if(v[i-1][j] == 0 && v[i][j] != 0)//有空位，上移 
						{
							v[i-1][j] = v[i][j];
							v[i][j] = 0;
							k = 1;
						}
						if(v[i-1][j] != 0 && v[i-1][j] == v[i][j] && m == 0)//无空位，还没有进行过合并，数字相同，合并相加并记录合并的类型 
						{
							m = v[i][j];
							v[i-1][j] = 2*v[i][j]; point += v[i-1][j];
							v[i][j] = 0;
							k = 1;
						}
						if(v[i-1][j] != 0 && v[i-1][j] == v[i][j] && m != 0 && v[i][j] == m)//无空位，已经进行过合并，数字相同
						{
							v[i-1][j] = 2*v[i][j]; point += v[i-1][j]; 
							v[i][j] = 0;
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
				a[i][j] = v[j][i];			
			}
		}
	}
	
	if(b == 3)//向下的移动操作 
	{
	    for(i = 0;i < 4;i++)
		{
			for(j = 0;j < 4;j++)
			{
				v[i][j] = a[3-i][j];			
			}
		}
		
		for(j=0;j<4;j++)
		{
			{//这个大括号里包装了让W退课的功能，列数未知故难以写成函数（调用指针） 
				if(v[0][j] == numW)
				{
					if(v[1][j] > 0){
						v[1][j] = 0;
						v[0][j] = 0;
						k = 1;
					}
					else if(v[2][j] > 0 && v[1][j] == 0){
						v[2][j] = 0;
						v[0][j] = 0;
						k = 1;
					}
					else if(v[3][j] > 0 && v[2][j] == 0 && v[1][j] == 0){
						v[3][j] = 0;
						v[0][j] = 0;
						k = 1;
					}
				}
				if(v[1][j] == numW)
				{
					if(v[0][j] > 0){
						v[1][j] = 0;
						v[0][j] = 0;
						k = 1;						
					}
					else if(v[0][j] == 0 && v[2][j] > 0){
						v[1][j] = 0;
						v[2][j] = 0;
						k = 1;
					}
					else if(v[0][j] == 0 && v[2][j] == 0 && v[3][j] > 0){
						v[1][j] = 0;
						v[3][j] = 0;
						k = 1;
					}
				}
				if(v[2][j] == numW)
				{
					if(v[1][j] > 0){
						v[1][j] = 0;
						v[2][j] = 0;
						k = 1;
					}
					else if(v[1][j] == 0 && v[0][j] > 0){
						v[0][j] = 0;
						v[2][j] = 0;
						k = 1;
					}
					else if(v[1][j] == 0 && v[0][j] == 0 && v[3][j] > 0){
						v[3][j] = 0;
						v[2][j] = 0;
						k = 1;
					}
				}
				if(v[3][j] == numW)
				{
					if(v[2][j] > 0){
						v[2][j] = 0;
						v[3][j] = 0;
						k = 1;
					}
					else if(v[2][j] == 0 && v[1][j] > 0){
						v[1][j] = 0;
						v[3][j] = 0;
						k = 1;
					}
					else if(v[2][j] == 0 && v[1][j] == 0 && v[0][j] > 0){
						v[0][j] = 0;
						v[3][j] = 0;
						k = 1;
					}
				}
			}//这个大括号里包装了让W退课的功能 			
			
			m = 0;//m=0表示没有进行合并，m不为零表示两个相同的数字合并前其中一个是什么（即表示合并的类型，允许出现2222的两次合并，但不允许出现224的合并再合并）
			if(v[0][j] == v[1][j] && v[2][j] == v[3][j] && v[0][j] != 0 && v[2][j] != 0)//考虑2244的情况，原先的代码会变成228
			{
				v[0][j] = 2*v[0][j]; point += v[0][j];
				v[1][j] = 2*v[2][j]; point += v[1][j];
				v[2][j] = 0;
				v[3][j] = 0;
				k = 1;
			 } 
			else
			{
				for(pass=1;pass<=4;pass++)
				{
					for(i=1;i<4;i++)
					{
						if(v[i-1][j] == 0 && v[i][j] != 0)//有空位，上移 
						{
							v[i-1][j] = v[i][j];
							v[i][j] = 0;
							k = 1;
						}
						if(v[i-1][j] != 0 && v[i-1][j] == v[i][j] && m == 0)//无空位，还没有进行过合并，数字相同，合并相加并记录合并的类型 
						{
							m = v[i][j];
							v[i-1][j] = 2*v[i][j]; point += v[i-1][j];
							v[i][j] = 0;
							k = 1;
						}
						if(v[i-1][j] != 0 && v[i-1][j] == v[i][j] && m != 0 && v[i][j] == m)//无空位，已经进行过合并，数字相同
						{
							v[i-1][j] = 2*v[i][j]; point += v[i-1][j]; 
							v[i][j] = 0;
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
				a[i][j] = v[3-i][j];			
			}
		}
	}
	
	if(b == 4)//向右的移动操作 
	{
	    for(i = 0;i < 4;i++)
		{
			for(j = 0;j < 4;j++)
			{
				v[i][j] = a[j][3-i];			
			}
		}
		
		for(j=0;j<4;j++)
		{
			{//这个大括号里包装了让W退课的功能，列数未知故难以写成函数（调用指针） 
				if(v[0][j] == numW)
				{
					if(v[1][j] > 0){
						v[1][j] = 0;
						v[0][j] = 0;
						k = 1;
					}
					else if(v[2][j] > 0 && v[1][j] == 0){
						v[2][j] = 0;
						v[0][j] = 0;
						k = 1;
					}
					else if(v[3][j] > 0 && v[2][j] == 0 && v[1][j] == 0){
						 v[3][j] = 0;
						 v[0][j] = 0;
						 k = 1;
					}
				}
				if(v[1][j] == numW)
				{
					if(v[0][j] > 0){
						v[1][j] = 0;
						v[0][j] = 0;
						k = 1;						
					}
					else if(v[0][j] == 0 && v[2][j] > 0){
						v[1][j] = 0;
						v[2][j] = 0;
						k = 1;
					}
					else if(v[0][j] == 0 && v[2][j] == 0 && v[3][j] > 0){
						v[1][j] = 0;
						v[3][j] = 0;
						k = 1;
					}
				}
				if(v[2][j] == numW)
				{
					if(v[1][j] > 0){
						v[1][j] = 0;
						v[2][j] = 0;
						k = 1;
					}
					else if(v[1][j] == 0 && v[0][j] > 0){
						v[0][j] = 0;
						v[2][j] = 0;
						k = 1;
					}
					else if(v[1][j] == 0 && v[0][j] == 0 && v[3][j] > 0){
						v[3][j] = 0;
						v[2][j] = 0;
						k = 1;
					}
				}
				if(v[3][j] == numW)
				{
					if(v[2][j] > 0){
						v[2][j] = 0;
						v[3][j] = 0;
						k = 1;
					}
					else if(v[2][j] == 0 && v[1][j] > 0){
						v[1][j] = 0;
						v[3][j] = 0;
						k = 1;
					}
					else if(v[2][j] == 0 && v[1][j] == 0 && v[0][j] > 0){
						v[0][j] = 0;
						v[3][j] = 0;
						k = 1;
					}
				}
			}//这个大括号里包装了让W退课的功能 			
			
			m = 0;//m=0表示没有进行合并，m不为零表示两个相同的数字合并前其中一个是什么（即表示合并的类型，允许出现2222的两次合并，但不允许出现224的合并再合并）
			if(v[0][j] == v[1][j] && v[2][j] == v[3][j] && v[0][j] != 0 && v[2][j] != 0)//考虑2244的情况，原先的代码会变成228
			{
				v[0][j] = 2*v[0][j]; point += v[0][j];
				v[1][j] = 2*v[2][j]; point += v[1][j];
				v[2][j] = 0;
				v[3][j] = 0;
				k = 1;
			 } 
			else
			{
				for(pass=1;pass<=4;pass++)
				{
					for(i=1;i<4;i++)
					{
						if(v[i-1][j] == 0 && v[i][j] != 0)//有空位，上移 
						{
							v[i-1][j] = v[i][j];
							v[i][j] = 0;
							k = 1;
						}
						if(v[i-1][j] != 0 && v[i-1][j] == v[i][j] && m == 0)//无空位，还没有进行过合并，数字相同，合并相加并记录合并的类型 
						{
							m = v[i][j];
							v[i-1][j] = 2*v[i][j]; point += v[i-1][j];
							v[i][j] = 0;
							k = 1;
						}
						if(v[i-1][j] != 0 && v[i-1][j] == v[i][j] && m != 0 && v[i][j] == m)//无空位，已经进行过合并，数字相同
						{
							v[i-1][j] = 2*v[i][j]; point += v[i-1][j]; 
							v[i][j] = 0;
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
				a[i][j] = v[3-j][i];			
			}
		}
	}
	//检查是否有W被退了,考虑两个以上W在并在一起 
	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 4; j++)
		{
			if(a[i][j] % numW == 0 && a[i][j] != 0)
			{
				a[i][j] = numW;
			}
		}
	}
	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 4; j++)
		{
			if(a[i][j] % numF == 0 && a[i][j] != 0)
			{
				a[i][j] = numF;
			}
		}
	} 
	return k;
}


int changeinGPA(char c)
{
	if(c == 'w' || c == 'W') return 1;
	if(c == 'a' || c == 'A') return 2;
	if(c == 's' || c == 'S') return 3;
	if(c == 'd' || c == 'D') return 4;
}

