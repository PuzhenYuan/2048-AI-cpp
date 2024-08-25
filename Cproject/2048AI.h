#ifndef C2048AI_H
#define C2048AI_H 

char AI2048();//(int a[4][4], int n, int m, int point);
//AI反应函数
//根据16个数字方块以及分数来输出一个方向字符 

int cangodown();
int cangoleft();
int cangoright();
int cangoup();
//如果可以上下左右则返回1，否则0；

int bottomcanleft();
//底层可以向左则输出1，否则输出0
int bottomcanright();
//底层可以向右则输出1，否则输出0
int bottomnotempty();
//底层非空返回1，空返回0  

int pointchange(char k);
//返回下一步移动增加的分数
char pointprefer(); 
//下左右哪个分特别高返回哪个字符 

 
#endif 
