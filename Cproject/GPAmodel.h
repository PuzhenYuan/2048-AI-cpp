#ifndef GPA_H
#define GPA_H

#define numW -19  //��������Ҫ2�ı������໥���� 
#define numF +17  //��������Ҫ2�ı������໥����

float GPAmax();
//���ڷ�����ʷ��߼��� 

void printGPA(int n);
//��ʾ������ַ�

int char2num(char *p);
//������ļ���Ŀ�껻��2048����

char *num2char(int n);
//��2048����ת��Ϊ����

float averageGPA();
//����ɼ����ϵľ��� 

void printinGPA();
//�˺������ڴ�ӡ��Ϸ���� 

int notfullGPA();
//�����ո�û��������1�����˷���0 

int randGPA();
//�ٷ�֮10�Ĺ������4���ٷ�֮90�ĸ������2 

void randomGPA();
//���һ���ո����2����4 

int calculatemaxGPA();
//���������� 

int moveGPA();
//��ȡ�������ֵ��b�����ƶ�����1��û�з���0 

int canstillmoveGPA();
//�����ƶ�����1�������ƶ�����0 

int moveandaddGPA();
//moveandadd�������ڽ����ƶ���������ӵĲ���
//����1��ʾ�������ƶ�������0��ʾδ�����ƶ�

int changeinGPA(char c);
//��������ַ�ת��Ϊ��Ӧ���� 

#endif
