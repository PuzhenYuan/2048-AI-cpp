#ifndef DYQ2048AI_H
#define DYQ2048AI_H 

void dyq2048AI();
//数据处理函数 
int dataCollection();
//数据收集函数 
int monotony();
//单调性数据收集函数 

int emptyCells();
//用于计算空格数，空格数越少越有利
void a2h();
//将a的值赋给h 
void h2a();
//将h的值赋给a
void a2h1();
//将a的值赋给h1
void h12a();
//将h1的值赋给a

int simpleplay2(int m);
//电脑dyqAI多次参战函数，返回分数值 

#endif 
