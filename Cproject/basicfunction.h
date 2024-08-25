#ifndef BASIC_H
#define BASIC_H

int pointmax();
//历次游戏最高得分

void print();
//此函数用于打印游戏界面 

int notfull();
//遍历空格，没有满返回1，满了返回0 

int rand10();
//百分之10的规律输出4，百分之90的概率输出2 

void randomnumber();
//随机一个空格输出2或者4 

int calculatemax();
//计算最大的数 

int move();
//获取方向键传值给b，有移动返回1，没有返回0 

int canstillmove();
//可以移动返回1，不能移动返回0 

int moveandadd();
int moveandadd3();
int moveandadd4();
int moveandadd5();

int moveandadd40();
int moveandadd41();
//moveandadd函数用于进行移动和数字相加的操作
//返回1表示进行了移动，返回0表示未进行移动
//附带3*3,4*4,5*5情况的子函数 

int change(char c);
//将方向键字符转换为对应数字 

#endif
