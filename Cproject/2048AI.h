#ifndef C2048AI_H
#define C2048AI_H 

char AI2048();//(int a[4][4], int n, int m, int point);
//AI��Ӧ����
//����16�����ַ����Լ����������һ�������ַ� 

int cangodown();
int cangoleft();
int cangoright();
int cangoup();
//����������������򷵻�1������0��

int bottomcanleft();
//�ײ�������������1���������0
int bottomcanright();
//�ײ�������������1���������0
int bottomnotempty();
//�ײ�ǿշ���1���շ���0  

int pointchange(char k);
//������һ���ƶ����ӵķ���
char pointprefer(); 
//�������ĸ����ر�߷����ĸ��ַ� 

 
#endif 
