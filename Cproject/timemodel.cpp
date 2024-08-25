/************************************ʱ��ģʽ������**************************************/
//��ģʽ�»�ÿ��1s����һ��2��������gameover
 
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "timemodel.h"

extern int a[4][4];
extern int h[4][4];
extern int b, M;
extern int point;

int u[4][4] = {0};//4*4��������� 

int pointmaxTIME()
//���ڷ���ʱ��ģʽ��ʷ��߷� 
{
	//�á�r��ģʽ���ȶ���ԭ�м�¼�����䵽�ַ������� 
	FILE* fptr1;
	errno_t err1 = fopen_s(&fptr1, "recordTIME.txt", "r");
	char pt[10] = { 0 };
	if (fptr1 != NULL){
		fgets(pt, 10, fptr1);
		fclose(fptr1);
	}
	//��������д��� 
	int maxpt = 0;
	maxpt = atoi(pt);
	if(point > maxpt)
	{
		maxpt = point;
		sprintf_s(pt, "%d\n", maxpt);
	}
	//�á�w��ģʽд���ļ� 
	FILE* fptr2;
	errno_t err2 = fopen_s(&fptr2, "recordTIME.txt", "w");
	if (fptr2 != NULL){
		fputs(pt, fptr2);
		fclose(fptr2);
	}
	return maxpt;
}


void printTIME()
//print�������ڴ�ӡ��Ϸ���� 
{
	system("CLS");//�����Ļ�����´�ӡ 
	int i,j,k;
	
	    for(k=1;k<=23;k++)//��һ�� 
	{
		printf("*");
	}
	printf("   ��ĵ÷֣�%d", point);
	printf("\n");
	for(i=0;i<4;i++)//�ڶ������� 
	{
		printf("* ");
		for(j=0;j<4;j++)
		{
			if(a[i][j] != 0)
			{
				printf("%-5d",a[i][j]); 
			}
			else
			{
				printf("     ");
			}
		}
		printf("*");
		if(i == 0) printf("   ��ߵ÷֣�%d", pointmaxTIME());
		printf("\n");
	}
	for(k=1;k<=23;k++)//������ 
	{
		printf("*");
	}
	printf("\n");
}

int notfullTIME()
//notfull���������ж��Ƿ��пո��ӣ��еĻ�����1,�Ѿ���������0 
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

int randTIME()
//�涨ʱ��ģʽ��ֻ����2 
{
	int y;
	y = 2;
	return y; 
}

void randomnumberTIME()
//randomnumber������������ҽ��в����������ѡȡһ���ո��ӣ���������2��4 
{
	int x;//x��ʾ��Ҫ���ɵ�����
	x = randTIME();//xֻ��Ϊ2
	int i,j;
	do
	{
		i = rand()%4;
		j = rand()%4;
	}while(a[i][j] != 0);
	a[i][j] = x;
}


int calculatemaxTIME()
//calculatemax�������ڻ�ȡ��ǰ�����е��������
{
	int maxnumber = 2;
	int i,j;
	
		for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(a[i][j] > maxnumber)
			{
				maxnumber = a[i][j];
			}
		}
	}
	
	return maxnumber;
}


int moveTIME()
//move���������ĸ����򰴼�����Ӧ���ƶ� 
{
	char key = _getch(), k = 0;//k=0��ʾû�а��������k=1��ʾ��ȷ���˷���� 
	if(key == 'w' || key == 'W')//�� 
	{
		b = 1;
		k = 1;
	}
	if(key == 'a' || key == 'A')//�� 
	{
		b = 2;
		k = 1;
	}
	if(key == 's' || key == 'S')//�� 
	{
		b = 3;
		k = 1;
	}
	if(key == 'd' || key == 'D')//�� 
	{
		b = 4;
		k = 1;
	}
	return k;
}

int canstillmoveTIME()
//canstillmove���������жϵ�û�пո��ʱ���Ƿ񻹿����ٽ����ƶ�
//��Ȼ�����ƶ�����1����Ϸ�������������ƶ�����0����Ϸ���� 
{
	int k = 0;//k��Ԥ�践��ֵ
	int i,j;
	
	    for(i=0;i<4;i++)//��������Ƿ������ڵ���ͬ���� 
	{
		for(j=0;j<3;j++)
		{
			if(a[i][j] == a[i][j+1])
			{
				k = 1;
			}
		}
	}
	for(j=0;j<4;j++)//��������Ƿ������ڵ���ͬ���� 
	{
		for(i=0;i<3;i++)
		{
			if(a[i][j] == a[i+1][j])
			{
				k = 1;
			}
		}
	}
	
	return k;
}


int moveandaddTIME()
//moveandadd�������ڽ����ƶ���������ӵĲ���
//����1��ʾ�������ƶ�������0��ʾδ�����ƶ� 
{
	int k = 0;//k��Ԥ�践��ֵ
	int i,j,pass,m;//i��ʾ��ʽ�����У�j��ʾ��ʽ�����У�pass��ʾ��������,m��ʾ�Ƿ�����˺ϲ� 
	
	    if(b == 1)//���ϵ��ƶ����� 
	{
		for(i = 0;i < 4;i++)
		{
			for(j = 0;j < 4;j++)
			{
				u[i][j] = a[i][j];			
			}
		}
		
		for(j=0;j<4;j++)
		{
			m = 0;//m=0��ʾû�н��кϲ���m��Ϊ���ʾ������ͬ�����ֺϲ�ǰ����һ����ʲô������ʾ�ϲ������ͣ��������2222�����κϲ��������������224�ĺϲ��ٺϲ���
			if(u[0][j] == u[1][j] && u[2][j] == u[3][j] && u[0][j] != 0 && u[2][j] != 0)//����2244�������ԭ�ȵĴ������228
			{
				u[0][j] = 2*u[0][j]; point += u[0][j];
				u[1][j] = 2*u[2][j]; point += u[1][j];
				u[2][j] = 0;
				u[3][j] = 0;
				k = 1;
			 } 
			else
			{
				for(pass=1;pass<=3;pass++)
				{
					for(i=1;i<4;i++)
					{
						if(u[i-1][j] == 0 && u[i][j] != 0)//�п�λ������ 
						{
							u[i-1][j] = u[i][j];
							u[i][j] = 0;
							k = 1;
						}
						if(u[i-1][j] != 0 && u[i-1][j] == u[i][j] && m == 0)//�޿�λ����û�н��й��ϲ���������ͬ���ϲ���Ӳ���¼�ϲ������� 
						{
							m = u[i][j];
							u[i-1][j] = 2*u[i][j]; point += u[i-1][j];
							u[i][j] = 0;
							k = 1;
						}
						if(u[i-1][j] != 0 && u[i-1][j] == u[i][j] && m != 0 && u[i][j] == m)//�޿�λ���Ѿ����й��ϲ���������ͬ
						{
							u[i-1][j] = 2*u[i][j]; point += u[i-1][j]; 
							u[i][j] = 0;
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
				a[i][j] = u[i][j];			
			}
		}
     }
	
	if(b == 2)//������ƶ����� 
	{
        for(i = 0;i < 4;i++)
		{
			for(j = 0;j < 4;j++)
			{
				u[i][j] = a[j][i];			
			}
		}
		
		for(j=0;j<4;j++)
		{
			m = 0;//m=0��ʾû�н��кϲ���m��Ϊ���ʾ������ͬ�����ֺϲ�ǰ����һ����ʲô������ʾ�ϲ������ͣ��������2222�����κϲ��������������224�ĺϲ��ٺϲ���
			if(u[0][j] == u[1][j] && u[2][j] == u[3][j] && u[0][j] != 0 && u[2][j] != 0)//����2244�������ԭ�ȵĴ������228
			{
				u[0][j] = 2*u[0][j]; point += u[0][j];
				u[1][j] = 2*u[2][j]; point += u[1][j];
				u[2][j] = 0;
				u[3][j] = 0;
				k = 1;
			 } 
			else
			{
				for(pass=1;pass<=4;pass++)
				{
					for(i=1;i<4;i++)
					{
						if(u[i-1][j] == 0 && u[i][j] != 0)//�п�λ������ 
						{
							u[i-1][j] = u[i][j];
							u[i][j] = 0;
							k = 1;
						}
						if(u[i-1][j] != 0 && u[i-1][j] == u[i][j] && m == 0)//�޿�λ����û�н��й��ϲ���������ͬ���ϲ���Ӳ���¼�ϲ������� 
						{
							m = u[i][j];
							u[i-1][j] = 2*u[i][j]; point += u[i-1][j];
							u[i][j] = 0;
							k = 1;
						}
						if(u[i-1][j] != 0 && u[i-1][j] == u[i][j] && m != 0 && u[i][j] == m)//�޿�λ���Ѿ����й��ϲ���������ͬ
						{
							u[i-1][j] = 2*u[i][j]; point += u[i-1][j]; 
							u[i][j] = 0;
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
				a[i][j] = u[j][i];			
			}
		}
	}
	if(b == 3)//���µ��ƶ����� 
	{
	    for(i = 0;i < 4;i++)
		{
			for(j = 0;j < 4;j++)
			{
				u[i][j] = a[3-i][j];			
			}
		}
		
		for(j=0;j<4;j++)
		{
			m = 0;//m=0��ʾû�н��кϲ���m��Ϊ���ʾ������ͬ�����ֺϲ�ǰ����һ����ʲô������ʾ�ϲ������ͣ��������2222�����κϲ��������������224�ĺϲ��ٺϲ���
			if(u[0][j] == u[1][j] && u[2][j] == u[3][j] && u[0][j] != 0 && u[2][j] != 0)//����2244�������ԭ�ȵĴ������228
			{
				u[0][j] = 2*u[0][j]; point += u[0][j];
				u[1][j] = 2*u[2][j]; point += u[1][j];
				u[2][j] = 0;
				u[3][j] = 0;
				k = 1;
			 } 
			else
			{
				for(pass=1;pass<=4;pass++)
				{
					for(i=1;i<4;i++)
					{
						if(u[i-1][j] == 0 && u[i][j] != 0)//�п�λ������ 
						{
							u[i-1][j] = u[i][j];
							u[i][j] = 0;
							k = 1;
						}
						if(u[i-1][j] != 0 && u[i-1][j] == u[i][j] && m == 0)//�޿�λ����û�н��й��ϲ���������ͬ���ϲ���Ӳ���¼�ϲ������� 
						{
							m = u[i][j];
							u[i-1][j] = 2*u[i][j]; point += u[i-1][j];
							u[i][j] = 0;
							k = 1;
						}
						if(u[i-1][j] != 0 && u[i-1][j] == u[i][j] && m != 0 && u[i][j] == m)//�޿�λ���Ѿ����й��ϲ���������ͬ
						{
							u[i-1][j] = 2*u[i][j]; point += u[i-1][j]; 
							u[i][j] = 0;
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
				a[i][j] = u[3-i][j];			
			}
		}
	}
	
	if(b == 4)//���ҵ��ƶ����� 
	{
	    for(i = 0;i < 4;i++)
		{
			for(j = 0;j < 4;j++)
			{
				u[i][j] = a[j][3-i];			
			}
		}
		
		for(j=0;j<4;j++)
		{
			m = 0;//m=0��ʾû�н��кϲ���m��Ϊ���ʾ������ͬ�����ֺϲ�ǰ����һ����ʲô������ʾ�ϲ������ͣ��������2222�����κϲ��������������224�ĺϲ��ٺϲ���
			if(u[0][j] == u[1][j] && u[2][j] == u[3][j] && u[0][j] != 0 && u[2][j] != 0)//����2244�������ԭ�ȵĴ������228
			{
				u[0][j] = 2*u[0][j]; point += u[0][j];
				u[1][j] = 2*u[2][j]; point += u[1][j];
				u[2][j] = 0;
				u[3][j] = 0;
				k = 1;
			 } 
			else
			{
				for(pass=1;pass<=4;pass++)
				{
					for(i=1;i<4;i++)
					{
						if(u[i-1][j] == 0 && u[i][j] != 0)//�п�λ������ 
						{
							u[i-1][j] = u[i][j];
							u[i][j] = 0;
							k = 1;
						}
						if(u[i-1][j] != 0 && u[i-1][j] == u[i][j] && m == 0)//�޿�λ����û�н��й��ϲ���������ͬ���ϲ���Ӳ���¼�ϲ������� 
						{
							m = u[i][j];
							u[i-1][j] = 2*u[i][j]; point += u[i-1][j];
							u[i][j] = 0;
							k = 1;
						}
						if(u[i-1][j] != 0 && u[i-1][j] == u[i][j] && m != 0 && u[i][j] == m)//�޿�λ���Ѿ����й��ϲ���������ͬ
						{
							u[i-1][j] = 2*u[i][j]; point += u[i-1][j]; 
							u[i][j] = 0;
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
				a[i][j] = u[3-j][i];			
			}
		}
	}
	return k;
}

int changeTIME(char c)
{
	if(c == 'w' || c == 'W') return 1;
	if(c == 'a' || c == 'A') return 2;
	if(c == 's' || c == 'S') return 3;
	if(c == 'd' || c == 'D') return 4;
}

