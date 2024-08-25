#ifndef GUI_H
#define GUI_H

#define GRID_WIDTH 100//格子宽度
#define INTERVAL 15//间隔

void draw345();
//绘画345模式的界面

void drawGPA();
//绘画GPA模式的界面

void drawTIME();
//绘画时间模式的界面

void drawbegin();
//绘画开始交互界面

void drawJD();
//绘画经典模式界面

void drawtarget345();
//打印目标提示语句

void drawtargetGPA();
//绘制GPA模式的说明和目标提示语句

void drawtargetTIME();
//绘制时间模式的提示语句

void drawAIchoose();
//绘画AI选择界面

void drawover();
//绘制345模式、TIME模式、GPA模式的结束界面

void drawwin();
//绘制达成目标时的图像

void acd2map();
//将acd数组赋值给map

void begin2model();
//开始时模式选择函数

void JDto345();
//经典模式模式选择函数

void AIget();
//获取玩家在AIchoose界面输入的信息

void getJDM();
//获取经典模式里的目标值并逐数绘画

void getGPAM();
//获取GPA模式的目标值，并逐字绘画

void getTIMEM();
//获取时间模式里的目标值，并逐数绘画

void getAIM();
//获取AI的目标，逐字绘制

void getsteptime();
//获取AI每步的时间，并逐字绘制

void statement();
//出品声明

int show();
//未调用的函数，保存了生成画面的功能

#endif 
