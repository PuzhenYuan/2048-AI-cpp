//1.0版日志：经典版本大框架构建完成 ，文天哥哥yyds！ 
//2.0版日志：修改了结束闪退、2244问题、大小写、增加分数机制、修改2和4出现概率 、目标M可以为非二次方
//2.1版日志：用getch函数做到直接读取，不用回车
//2.2版日志：修改了不移动就刷新数据的bug，修改了向下向右2244会消失的bug 
//3.0版日志：加入AI模块，努力从几个方向打出最高分 
//3.1版日志：加入AI的测试功能，AI制作陷入困境，不排除经典版本还有bug的可能 
//4.0版日志：增添多模式功能(经典模式，绩点模式和时间模式）文天哥哥yyds！ 
//           经典模式增添了难度选择（边长选择为3，4，5）
//		     优化了basicfunction中moveandadd函数的算法，利用矩阵传递将四个方向化归到一个方向，为此引入了替身矩阵
//		     GPA模式基本完成，区别于经典模式加入F和W，F难以消除，W可以消除第一个碰到的方块 
//		     时间模式存在bug，在玩家按按键和生成数字的时刻很接近时，游戏区域会变得扭曲
//4.1版日志：增加dyq2048AI.c、dyq2048AI.h，在main.c中增加了computerplay2()与 computercount2()，在basicfunction中增加了 moveandadd40函数 
//4.2版日志：给三个玩家模式增加保存最高分数的功能,增加三个txt文件，将TIME模式改进为单线程非阻塞式监听 
//5.0版日志：将gui合入原先的程序，IDE换成VS，不费眼睛了，写了GPA与NUM互换调用指针函数
//5.1版日志：绘制统一的graph，加入分数和绩点的显示，加入结束界面和胜利界面
//5.2版日志：绘制完所有游戏界面，但是没有加入鼠标和键盘的交互，控制依靠console
//5.3版日志：加入键盘和鼠标的交互，可以抛弃console进行游戏了
//5.4版日志：增强键盘输入的鲁棒性，增加了注释提高可读性，在目标设置中可以直接按回车，这样就取消win功能，完成出品人员链接
//5.5版日志：修改TIME模式代码，等数字占满格子再等1秒才Game Over,增强了GPAm模式键盘输入的鲁棒性，修改了GPA模式F作为最大绩点导致win的bug
//6.0版日志：重写dyq2048AI,在basicfunction中增加了moveandadd41函数，基本完成全部内容
//6.1版日志：加强鲁棒性，增加失败或开发人员名单时出现返回功能


//标准库文件 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h> 
#include <conio.h> 	  //包含getch()、kbhit()
#include <math.h>
#include <easyx.h>
#include <graphics.h>

//自编库文件 
#include "basicfunction.h"
#include "GPAmodel.h"
#include "timemodel.h"
//2048基本功能函数库 （玩家） 

#include "2048AI.h" 
#include "dyq2048AI.h" 
//2048AI功能的函数库 （电脑） 

#include "gui.h"
//图形化界面相关函数库

/************************************全局变量说明**************************************/
//方向键：W/w-上 ；S/s-下 ；A/a-左 ；D/d-右 

int a[4][4] = {0};
//标准游戏区域用4*4数组表示

int c[3][3] = {0};
int d[5][5] = {0};
int N = 4;//N用以表示数组的边长
//以上三个在标准模式选择矩阵边长时应用 

int b = 0;
//b表示方向键的对应数字，1表示上，2表示左，3表示下，4表示右 

int M = 2048;
//设定游戏的初始目标

int point = 0;
//分数，玩家生成方块的数值之和  

char choice;
//玩家对游戏模式的选择

int AImodel;
//玩家对AI模式的选择

int steptime = 100;
//AI的每步时间

int GRID_NUM = 4;
//gui中格子边长
int map[6][6] = { 0 };
//用来取数绘图

int again = 0;
//是否再回到主页面

//以下定义用在dyq2048AI2中
int h[4][4] = { 0 };
//h用以存储进行第一步假设操作前的a值 
int h1[4][4] = { 0 };
//h1用以存储进行第二步假设操作前的a值 
int point1;
//point1用以存储point值 
int r3, r2, r4;
//r3,r2,r4用以表示moveandadd函数的返回值，用来表示玩家是否可以进行移动操作，其中r3记录向下的情况，r2记录向左的情况，r4记录向右的情况
float move3, move2, move4;
//以上三个变量分别为第一步向下、左、右移动的数据 



/************************************标准模式函数**************************************/

void classicmodel()
{
	drawJD();
	//绘制经典界面

    printf("请选择一种难度：\n");
    printf("困难难度（3*3方阵）: 3\n");
    printf("标准难度（4*4方阵）: 4\n");
    printf("简单难度（5*5方阵）: 5\n");

	JDto345();
	//经典模式模式选择函数

    char key;
    //key表示键盘的输入 
    int r,s,t;
    //r表示moveandadd函数的返回值，用来表示玩家是否可以进行移动操作
    //s表示输入的操作键，用于关联按键和实际移动
    //t表示notfull函数的返回值，用于判断是否还有空格 
    int win = 0; 
    //玩家是否达成了挑战 ,预设没有
    
	drawtarget345();
	//绘制345目标选择界面

    printf("请输入想要拼凑的最大数字，例如32，64，128，...，2048：");
    //scanf_s("%d", &M);
   
	getJDM();
	//获取经典模式里的目标值并逐数绘画

	GRID_NUM = N;

	setbkcolor(RGB(187, 173, 160));//设置背景颜色
	cleardevice();//清屏
	setbkmode(TRANSPARENT);
	draw345();

    //step1：显示初始状态 
    srand((int)time(NULL));//播下随机数种子
    if(N == 3 || N == 4)
    {
   		randomnumber();//随机生成第一个数
   		randomnumber();//随机生成第二个数
    }
    if(N == 5)
    {
   		randomnumber();//只随机生成一次，以防第一次生成4个数 
    }

	acd2map();//赋值
    print();//打印初始状态 
	draw345();//绘制345游戏界面
   
    //step2：玩家进行游戏操作 
    while(1)
    {
    	t = notfull();
    	if(t == 0 && canstillmove() == 0)
		{
		  	printf("Game Over！\n");
		  	printf("你最终的得分是：\n");
		    printf("%d", point); 
		  	//system("pause");
			drawover();

		  	break;
	    }
   	    s = move();//读取操作键
	    if(s == 0)//如果不是上下左右键，则重新读取键盘
	    {
	  		continue;
	    }  
   	    r = moveandadd();//根据方向键合并相加,返回1表示有移动
   	    if(r == 1)
	    {
			acd2map();
	   	    print();//显示玩家移动之后的界面 
			draw345();
	    }
	    t = notfull(); 
        if(calculatemax() >= M && win == 0 && M > 0)//判断是否胜利
        {
            printf("你赢了！请继续挑战吧！\n");
            win = 1;
			drawwin();
            system("pause"); 
        }
	    if(t == 1 && r == 1)//有空位且有移动，再生成一个随机数 
	    {
	  	    randomnumber();//生成随机数

			acd2map();
		    print();//显示玩家移动之后的界面 
			draw345();
	    }
	    if(t == 0 && canstillmove() == 1)//如果没有空格子但能动，则提醒玩家 
	    {
		    printf("请选择另一个方向滑动！\n");	
		}
    }
}

/************************************GPA模式函数 **************************************/

void GPAmodel()
{
	char key;
    //key表示键盘的输入 
    int r,s,t;
	//r表示moveandadd函数的返回值，用来表示玩家是否可以进行移动操作
	//s表示输入的操作键，用于关联按键和实际移动
	//t表示notfull函数的返回值，用于判断是否还有空格 
    int win = 0; 
	//玩家是否达成了挑战 ,预设没有
    
	drawtargetGPA();
	//绘制GPA模式目标选择的界面

    char in[2] = {'\0','\0'};
    printf("请输入你的目标绩点，例如C, C+，B-，B，,B+...，A+：\n");
    //scanf_s("%s", in, 2);
    //M = char2num(in);

	getGPAM();
	//获取GPA模式的目标值，并逐字绘画
   
	GRID_NUM = N;

	setbkcolor(RGB(187, 173, 160));//设置背景颜色
	cleardevice();//清屏
	setbkmode(TRANSPARENT);
	drawGPA();

    //step1：显示初始状态 
    srand((int)time(NULL));//播下随机数种子 
    randomGPA();//随机生成第一个数 
    randomGPA();//随机生成第二个数
	acd2map();
	drawGPA();
    printinGPA();//打印初始状态 
   
    //step2：玩家进行游戏操作 
    while(1)
    {
    	t = notfullGPA();
		if(t == 0 && canstillmoveGPA() == 0)
		{
		  	printf("卷不动啦！\n");
		  	printf("你最高的绩点是:");
			printGPA(calculatemaxGPA());
			printf("\n"); 
			printf("你最终的均绩是: "); 
			printf("%.2f\n", averageGPA());
		  	//system("pause");
			drawover();

		  	break;
	    }
   	    s = moveGPA();//读取操作键
	    if(s == 0)//如果不是上下左右键，则重新读取键盘
	    {
	  		continue;
	    }  
   	    r = moveandaddGPA();//根据方向键合并相加,返回1表示有移动 
   	    if(r == 1)
	    {
	   	    printinGPA();//显示玩家移动之后的界面
			acd2map();
			drawGPA();
	    }
        if(calculatemaxGPA() >= M && win == 0 && M > 0)//判断是否胜利
        {
            printf("你达到了自己的目标！接下来请继续卷吧！\n");
            win = 1;
			drawwin();
            system("pause"); 
        }
        t = notfullGPA();
	    if(t == 1 && r == 1) //有空位且有移动，再生成一个随机数 
	    {
	  	    randomGPA();//生成随机数 
		    printinGPA();//显示玩家移动之后的界面 
			acd2map();
			drawGPA();
	    }
	    if(t == 0 && canstillmoveGPA() == 1)//如果没有空格子，则判断游戏是否结束 
	    {
		    printf("请选择另一个方向滑动！\n");	
		}
    }
}

/************************************时间模式函数 **************************************/

void timemodel()
{
	drawtargetTIME();

    printf("注意！在此模式下，游戏区域被填满即意味着游戏即将结束!\n");
    printf("请输入想要拼凑的最大数字，例如32，64，128，...，2048：");
    //scanf_s("%d", &M);

	getTIMEM();
	//获取时间模式里的目标值，并逐数绘画
    
	GRID_NUM = N;

	setbkcolor(RGB(187, 173, 160));//设置背景颜色
	cleardevice();//清屏
	setbkmode(TRANSPARENT);
	drawTIME();

    //显示初始状态 
    srand((int)time(NULL));//播下随机数种子 
    randomnumberTIME();//随机生成第一个数 
    randomnumberTIME();//随机生成第二个数 

	acd2map();
    printTIME();//打印初始状态
	drawTIME();

    char key;
	//key表示键盘的输入 
    int r,s,t;
	//r表示moveandadd函数的返回值，用来表示玩家是否可以进行移动操作
	//s表示输入的操作键，用于关联按键和实际移动
	//t表示notfull函数的返回值，用于判断是否还有空格 
    int win = 0; 
	//玩家是否达成了挑战 ,预设没有

	clock_t tb = clock();
	//tb存储自动生成数字的时间 
	
    while(1)
    {
    	if(_kbhit())//可以实现非阻塞式键盘监听，谢谢助教！ 
		{
	    	t = notfullTIME();
			if(t == 0 && canstillmoveTIME() == 0)
			{
			  	printf("Game Over！\n");
			  	printf("你最终的得分是：\n");
				printf("%d", point); 
			  	//system("pause");
				drawover();

			  	break;
		    }
			s = moveTIME();//读取操作键
		    if(s == 0)//如果不是上下左右键，则重新读取键盘
		    {
		  		continue;
		    }  
	   	    r = moveandaddTIME();//根据方向键合并相加,返回1表示有移动 
	   	    if(r == 1)
		    {
				acd2map();
		   	    printTIME();//显示玩家移动之后的界面
				drawTIME();
		    }
	        if(calculatemaxTIME() >= M && win == 0 && M > 0)//判断是否胜利 
	        {
	            printf("你赢了！请继续挑战吧！\n");
	            win = 1;
				drawwin();
	            system("pause"); 
	        }
	        t = notfullTIME();
		    if(t == 1 && r == 1) //有空位且有移动，再生成一个随机数 
		    {
		  	    randomnumberTIME();//生成随机数 

				acd2map();
			    printTIME();//显示玩家移动之后的界面 
				drawTIME();
		    }
		    if(t == 0 && canstillmoveTIME() == 1)//如果没有空格子，则判断游戏是否结束 
		    {
			    printf("请选择另一个方向滑动！\n");	
			}
		}//实现非阻塞式键盘监听 
		{//这个大括号里包含了自动生成数字的功能，为了方便结束循环不写进函数里了 
			float delta = 0.0;
			clock_t tn = clock();
			delta = ((float)(tn - tb))/ CLOCKS_PER_SEC;
			if(delta >= 1.0)
			{
				if (notfullTIME() == 0)
				{
					printf("Game Over！\n");
					printf("你最终的得分是：\n");
					printf("%d", point);
					//system("pause");
					drawover();

					break;
				}
				if(notfullTIME() == 1)
				{
					randomnumberTIME();
					acd2map();
					printTIME();
					drawTIME();
					tb = tn;
				}
		    }
		}//这个大括号里包含了自动生成数字的功能 
    }
}


/************************************电脑AI参战函数 **************************************/

void computerplay()
{
    char key;
    int r,s,t;
    int win = 0; //电脑是否达成了挑战 

    printf("请输入游戏要拼凑的最大数字，例如32，64，128，...，2048：\n");
    //scanf_s("%d", &M);

	getAIM();
	//获取AI的目标，逐字绘制

    printf("请输入电脑每一步反应的时间（ms）:\n");
	//scanf_s("%d", &steptime);

	getsteptime();
	//获取AI每步的时间，并逐字绘制
	
	GRID_NUM = N;

	setbkcolor(RGB(187, 173, 160));//设置背景颜色
	cleardevice();//清屏
	setbkmode(TRANSPARENT);
	draw345();

    //step1：显示初始状态 
    srand((int)time(NULL));//播下随机数种子 
    randomnumber();//随机生成第一个数 
    randomnumber();//随机生成第二个数 

	acd2map();
    print();//打印初始状态 
	draw345();

    //step2：电脑进行游戏操作 
	while(1)
	{
		b = change(AI2048());//(a, 4, 4, point));
		Sleep(steptime);
		r = moveandadd();//根据方向键合并相加,返回1表示有移动 
		//printf("%d", r);
   	    if(r == 1)
	    {
			acd2map();
	   	    print();//显示电脑移动之后的界面 
			draw345();
	    }
        if(calculatemax() >= M && win == 0)//判断是否胜利 
        {
            printf("电脑达成目标\n");
            win = 1;
			drawwin();
            system("pause"); 
        }
        t = notfull();
	    if(t == 1 && r == 1) //有空位且有移动，再生成一个随机数 
	    {
	  	    randomnumber();//生成随机数 
			acd2map();
		    print();//显示电脑移动之后的界面 
			draw345();
	    }
	    if(t == 0)//如果没有空格子，则判断游戏是否结束 
	    {
	  	    if(canstillmove() == 1)//仍能移动，游戏继续 
		    {
		        printf("请选择另一个方向滑动！\n");	
		    }
		    else
		    {
		  	    printf("Game Over！\n");
		  	    printf("电脑最终的得分是：\n");
			    printf("%d\n", point);
		  	    //system("pause");
				drawover();

		  	    break;
		    }
	    }
	}
}


int simpleplay(int m)
//电脑AI多次参战函数，只返回分数值 
//m的值是为了播下伪随机数种子，一把时间太快了不能用time（NULL)了 
{
    char key;
    int r,s,t;
    point = 0;
	int i,j;//清空 
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			a[i][j] = 0;
		}
	} 
    srand(m);//用m的值作为seed，保证每局不同 
    randomnumber();
    randomnumber(); 
	while(1)
	{
		b = change(AI2048());
		r = moveandadd();//根据方向键合并相加,返回1表示有移动 
        t = notfull();
	    if(t == 1 && r == 1) //有空位且有移动，再生成一个随机数 
	    {
	  	    randomnumber();//生成随机数 
	    }
	    if(t == 0)//如果没有空格子，则判断游戏是否结束 
	    {
	  	    if(canstillmove() != 1)
		    {
		        break;
		    }
	    }
	}
	return point; 
}


void computercount()
//用来方便统计平均分和方差的AI辅助功能 
{
	int times = 100;
	int i;
	printf("请输入想要进行的游戏局数(<500)：\n"); 
	scanf_s("%d", &times);
	int average = 0;
	int variance = 0;
	int p[1000] = { 0 };
	for(i=0;i<times;i++)
	{
		p[i] = simpleplay(i);
	}
	int sum1 = 0;
	long int sum2 = 0;
	for(i=0;i<times;i++)
	{
		sum1 += p[i];
	}
	average = sum1 / times;
	for(i=0;i<times;i++)
	{
		sum2 += (p[i] - average)*(p[i] - average);
	}
	variance = (int)sqrt((double)(sum2 / times));
	printf("电脑的平均分是：\n");
	printf("%d\n", average);
	printf("电脑分数的方差是：\n");
	printf("%d\n", variance);
}

/************************************电脑AI参战函数 2 **************************************/

void computerplay2()
{
	char key;
	int h[4][4] = { 0 }; //h用以储存进行假设操作前的a的值 
	int r, s, t;
	int win = 0; //电脑是否达成了挑战 

	printf("请输入游戏要拼凑的最大数字，例如32，64，128，...，2048：\n");
	//scanf_s("%d", &M);

	getAIM();
	//获取AI的目标，逐字绘制

	printf("请输入电脑每一步反应的时间（ms）:\n");
	//scanf_s("%d", &steptime);

	getsteptime();
	//获取AI每步的时间，并逐字绘制

	//step1：显示初始状态 
	srand((int)time(NULL));//播下随机数种子 
	randomnumber();//随机生成第一个数 
	randomnumber();//随机生成第二个数 
	print();//打印初始状态 


	setbkcolor(RGB(187, 173, 160));//设置背景颜色
	cleardevice();//清屏
	setbkmode(TRANSPARENT);
	acd2map();
	draw345();

	//step2：电脑进行游戏操作
	while (1)
	{

		dyq2048AI();//收集数据 

		//接下来根据数据判定移动方向
		if (cangodown() == 1 && cangoleft() == 1 && cangoright() == 1)//如果可以向下、左、右移动 
		{
			if (move3 >= move2 && move3 >= move4)//在数据相同的情况下，方向优先级：下 > 左 > 右
			{
				b = 3;
				moveandadd();//根据方向键合并相加
				print();//显示电脑移动之后的界面 
				acd2map();
				draw345();
				Sleep(steptime);
				randomnumber();//生成随机数 
				print();//显示电脑移动之后的界面 
				acd2map();
				draw345();
				Sleep(steptime);
			}
			else if (move2 >= move4)
			{
				b = 2;
				moveandadd();
				print();
				acd2map();
				draw345();
				Sleep(steptime);
				randomnumber();
				print();
				acd2map();
				draw345();
				Sleep(steptime);
			}
			else
			{
				b = 4;
				moveandadd();
				print();
				acd2map();
				draw345();
				Sleep(steptime);
				randomnumber();
				print();
				acd2map();
				draw345();
				Sleep(steptime);
			}
		}
		else if (cangodown() == 1 && cangoleft() == 1 && cangoright() == 0)//如果可以向下、左移动 
		{
			if (move3 >= move2)
			{
				b = 3;
				moveandadd();
				print();
				acd2map();
				draw345();
				Sleep(steptime);
				randomnumber();
				print();
				acd2map();
				draw345();
				Sleep(steptime);
			}
			else
			{
				b = 2;
				moveandadd();
				print();
				acd2map();
				draw345();
				Sleep(steptime);
				randomnumber();
				print();
				acd2map();
				draw345();
				Sleep(steptime);
			}
		}
		else if (cangodown() == 1 && cangoleft() == 0 && cangoright() == 1)//如果可以向下、右移动 
		{
			if (move3 >= move4)
			{
				b = 3;
				moveandadd();
				print();
				acd2map();
				draw345();
				Sleep(steptime);
				randomnumber();
				print();
				acd2map();
				draw345();
				Sleep(steptime);
			}
			else
			{
				b = 4;
				moveandadd();
				print();
				acd2map();
				draw345();
				Sleep(steptime);
				randomnumber();
				print();
				acd2map();
				draw345();
				Sleep(steptime);
			}
		}
		else if (cangodown() == 0 && cangoleft() == 1 && cangoright() == 1)//如果可以向左、右移动 
		{
			if (move2 >= move4)
			{
				b = 2;
				moveandadd();
				print();
				acd2map();
				draw345();
				Sleep(steptime);
				randomnumber();
				print();
				acd2map();
				draw345();
				Sleep(steptime);
			}
			else
			{
				b = 4;
				moveandadd();
				print();
				acd2map();
				draw345();
				Sleep(steptime);
				randomnumber();
				print();
				acd2map();
				draw345();
				Sleep(steptime);
			}
		}
		else if (cangodown() == 1 && cangoleft() == 0 && cangoright() == 0)//如果可以向下移动 
		{
			b = 3;
			moveandadd();
			print();
			acd2map();
			draw345();
			Sleep(steptime);
			randomnumber();
			print();
			acd2map();
			draw345();
			Sleep(steptime);
		}
		else if (cangodown() == 0 && cangoleft() == 1 && cangoright() == 0)//如果可以向左移动 
		{
			b = 2;
			moveandadd();
			print();
			acd2map();
			draw345();
			Sleep(steptime);
			randomnumber();
			print();
			acd2map();
			draw345();
			Sleep(steptime);
		}
		else if (cangodown() == 0 && cangoleft() == 0 && cangoright() == 1)//如果可以向右移动 
		{
			b = 4;
			moveandadd();
			print();
			acd2map();
			draw345();
			Sleep(steptime);
			randomnumber();
			print();
			acd2map();
			draw345();
			Sleep(steptime);
		}
		else if (cangodown() == 0 && cangoleft() == 0 && cangoright() == 0)//如果不能向下、左、右移动 
		{
			b = 1;//被迫向上移动
			moveandadd();
			print();
			acd2map();
			draw345();
			Sleep(steptime);
			randomnumber();
			print();
			acd2map();
			draw345();
			Sleep(steptime);
			b = 3;//再向下移动 
			moveandadd();
			print();
			acd2map();
			draw345();
			Sleep(steptime);
			randomnumber();
			print();
			acd2map();
			draw345();
			Sleep(steptime);
		}

		if (calculatemax() >= M && win == 0)//判断是否胜利  
		{
			printf("电脑达成目标\n");
			win = 1;
			drawwin();
			system("pause");
		}
		t = notfull();
		if (t == 0)//如果没有空格子，则判断游戏是否结束 
		{
			if (canstillmove() == 1)//仍能移动，游戏继续 
			{
			}
			else
			{
				printf("Game Over！\n");
				printf("电脑最终的得分是：\n");
				printf("%d\n", point);
				drawover();

				//system("pause");
				break;
			}
		}
	}
}


void computercount2()
//用来方便统计平均分和方差的AI辅助功能，与computercount相比，computercount2只是将simpleplay改为simpleplay2
{
	int times;//想要进行的游戏局数
	int i;
	printf("请输入想要进行的游戏局数(<500)：\n");
	scanf_s("%d", &times);
	int average = 0;//分数的平均值 
	int maximalpoint = 0;//分数的最大值 
	int maximalnumber = 0;//最高数字的最大值 
	int successfultime = 0;//游戏成功次数，也即生成2048的次数 
	int time64 = 0;//最高数字为 64的次数
	int time128 = 0;//最高数字为 128的次数
	int time256 = 0;//最高数字为 256的次数
	int time512 = 0;//最高数字为 512的次数
	int time1024 = 0;//最高数字为 1024的次数
	int time2048 = 0;//最高数字为 2048的次数
	int p[1000] = { 0 };
	for (i = 0; i < times; i++)
	{
		p[i] = simpleplay2(i);
		if (simpleplay2(i) > maximalpoint)
		{
			maximalpoint = simpleplay2(i);
		}
		if (calculatemax() > maximalnumber)
		{
			maximalnumber = calculatemax();
		}
		if (calculatemax() >= 2048)
		{
			successfultime++;
		}
		if (calculatemax() == 64)
		{
			time64++;
		}
		if (calculatemax() == 128)
		{
			time128++;
		}
		if (calculatemax() == 256)
		{
			time256++;
		}
		if (calculatemax() == 512)
		{
			time512++;
		}
		if (calculatemax() == 1024)
		{
			time1024++;
		}
		if (calculatemax() == 2048)
		{
			time2048++;
		}
	}
	int sum1 = 0;
	long int sum2 = 0;
	for (i = 0; i < times; i++)
	{
		sum1 += p[i];
	}
	average = sum1 / times;
	printf("电脑的平均分是：\n");
	printf("%d\n", average);
	printf("电脑分数的最高值是：\n");
	printf("%d\n", maximalpoint);
	printf("电脑数字的最高值是：\n");
	printf("%d\n", maximalnumber);
	printf("电脑成功的次数是：\n");
	printf("%d\n", successfultime);
	printf("电脑最高数字为64的次数是：\n");
	printf("%d\n", time64);
	printf("电脑最高数字为128的次数是：\n");
	printf("%d\n", time128);
	printf("电脑最高数字为256的次数是：\n");
	printf("%d\n", time256);
	printf("电脑最高数字为512的次数是：\n");
	printf("%d\n", time512);
	printf("电脑最高数字为1024的次数是：\n");
	printf("%d\n", time1024);
	printf("电脑最高数字为2048的次数是：\n");
	printf("%d\n", time2048);
}

/************************************AI模式选择函数 **************************************/

void AIchoose()
{
	drawAIchoose();

	printf("请选择一种AI：\n");
	printf("AI No.1: 1\n");
	printf("AI No.2: 2\n");

	AIget();
	//scanf_s("%d", &AImodel);

	if (AImodel == 1)
		computerplay();
	if (AImodel == 2)
		computerplay2();
}


/************************************欢迎函数 **************************************/

void welcome() 
{
	printf("欢迎来玩多模式2048！\n");
	printf("请选择一种模式：\n");
	printf("经典模式: A\n");
	printf("GPA 模式: B\n");
	printf("时间模式: C\n");
	printf(" AI参战 : D\n");
	printf("出品人员: E\n");
	printf("computercount1:F\n");
	printf("computercount2:G\n");
}

/************************************游戏主函数 *************************************/

int main()
{
	welcome();
	choice = '\0';
	initgraph(590, 700, EW_SHOWCONSOLE);
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, _T("2048++"));

	while (true) {

		b = 0;
		M = 2048;
		point = 0;
		N = 4;
		GRID_NUM = 4;
		steptime = 100;

		again = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				a[i][j] = 0;
			}
		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				c[i][j] = 0;
			}
		}
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				d[i][j] = 0;
			}
		}
		acd2map();
		drawbegin();
		begin2model();

    //scanf_s("%c", &choice, 1);

		if (choice == 'A')
			classicmodel();
		if (choice == 'B')
			GPAmodel();
		if (choice == 'C')
			timemodel();
		if (choice == 'D')
			AIchoose();
		if (choice == 'E')
			statement();
		if (choice == 'F')
			computercount();
		if (choice == 'G')
			computercount2();

		if (again == 0) break;
		
	}
	_getch();
	closegraph();
	return 0;
}

