#ifndef GPA_H
#define GPA_H

#define numW -19  //负数，不要2的倍数，相互互素 
#define numF +17  //正数，不要2的倍数，相互互素

float GPAmax();
//用于返回历史最高绩点 

void printGPA(int n);
//显示绩点的字符

int char2num(char *p);
//将输入的绩点目标换成2048数字

char *num2char(int n);
//将2048数字转换为绩点

float averageGPA();
//计算成绩单上的均绩 

void printinGPA();
//此函数用于打印游戏界面 

int notfullGPA();
//遍历空格，没有满返回1，满了返回0 

int randGPA();
//百分之10的规律输出4，百分之90的概率输出2 

void randomGPA();
//随机一个空格输出2或者4 

int calculatemaxGPA();
//计算最大的数 

int moveGPA();
//获取方向键传值给b，有移动返回1，没有返回0 

int canstillmoveGPA();
//可以移动返回1，不能移动返回0 

int moveandaddGPA();
//moveandadd函数用于进行移动和数字相加的操作
//返回1表示进行了移动，返回0表示未进行移动

int changeinGPA(char c);
//将方向键字符转换为对应数字 

#endif
