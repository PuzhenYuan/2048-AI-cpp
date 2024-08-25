#ifndef TIME_H
#define TIME_H

int pointmaxTIME(); 
//用于返回时间模式历史最高分 

void printTIME();
//此函数用于打印游戏界面 

int notfullTIME();
//遍历空格，没有满返回1，满了返回0 

int randTIME();
//时间模式下只能规定只能生成2 

void randomnumberTIME();
//随机一个空格输出2或者4 

int calculatemaxTIME();
//计算最大的数 

int moveTIME();
//获取方向键传值给b，有移动返回1，没有返回0 

int canstillmoveTIME();
//可以移动返回1，不能移动返回0 

int moveandaddTIME();
//moveandadd函数用于进行移动和数字相加的操作
//返回1表示进行了移动，返回0表示未进行移动

int changeTIME(char c);
//将方向键字符转换为对应数字 

#endif
