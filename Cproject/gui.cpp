/************************************GUI��غ�����**************************************/

#include <stdio.h>
#include <stdlib.h>
#include <easyx.h>
#include <conio.h>
#include <graphics.h>
#include <math.h>

#include "gui.h"
#include "GPAmodel.h"
#include "basicfunction.h"
#include "timemodel.h"

#define GRID_WIDTH 100//���ӿ��
#define INTERVAL 15//���

extern int a[4][4];
extern int b, M;
extern int point;
extern int N;
extern char choice;
extern int AImodel;
extern int steptime;
extern int again;

extern int c[3][3];//3*3�ķ��� 
extern int d[5][5];//5*5�ķ��� 


enum Color//ö�ٸ�����ɫ
{
	zero = RGB(205, 193, 180),//0
	twoTo1 = RGB(238, 228, 218),//2
	twoTo2 = RGB(237, 224, 200),//4
	twoTo3 = RGB(242, 177, 121),//8
	twoTo4 = RGB(243, 149, 97),//16
	twoTo5 = RGB(246, 124, 95),//32
	twoTo6 = RGB(246, 94, 59),//64
	twoTo7 = RGB(237, 206, 114),//128
	twoTo8 = RGB(237, 204, 97),//256
	twoTo9 = RGB(238, 200, 81),//512
	twoTo10 = RGB(236, 197, 62),//1024
	twoTo11 = RGB(236, 194, 47),//2048
	back = RGB(200, 173, 160),//����
};
Color colors[13] = { zero,twoTo1 ,twoTo2,twoTo3,twoTo4,twoTo5,twoTo6,twoTo7,twoTo8,twoTo9,twoTo10,twoTo11,back};


enum ColorGPA//ö�ٸ�����ɫ
{
	null  = RGB(205, 193, 180),//0
	gpaD2 = RGB(231, 46, 31),//2
	gpaD3 = RGB(240, 108, 21),//4
	gpaC1 = RGB(240, 171, 68),//8
	gpaC2 = RGB(239, 227, 82),//16
	gpaC3 = RGB(203, 232, 89),//32
	gpaB1 = RGB(195, 195, 81),//64
	gpaB2 = RGB(157, 178, 83),//128
	gpaB3 = RGB(119, 161, 85),//256
	gpaA1 = RGB(76, 106, 54),//512
	gpaA2 = RGB(76, 106, 54),//1024
	gpaA3 = RGB(76, 106, 54),//2048
	BACK  = RGB(200, 173, 160),//����
	gpaW  = RGB(150, 150, 150),//�˿�W��ɫ
	gpaF  = RGB(50, 50, 50),//������F��ɫ
};
ColorGPA colorgpa[15] = {null, gpaD2, gpaD3, gpaC1, gpaC2, gpaC3, gpaB1, gpaB2, gpaB3, gpaA1, gpaA2, gpaA3, BACK, gpaW, gpaF};


extern int map[6][6];
extern int GRID_NUM;

void draw345()
//�滭345ģʽ�Ľ���
{
	//���Ʒ���
	cleardevice();
	settextstyle(30, 0, "������κ");
	settextcolor(RGB(119, 110, 101));
	
	char str1[] = "yourpoint:";
	char str2[] = "maxpoint:";
	char strpt[10];
	char maxpt[10];
	//�ֱ��ǵ�ǰ��������߷���

	sprintf_s(strpt, "%d", point);
	sprintf_s(maxpt, "%d", pointmax());

	int horspace345 = (GRID_WIDTH - textwidth(strpt)) / 2;
	int vecspace345 = (GRID_WIDTH - textheight(strpt)) / 2;
	//λ�ü���

	outtextxy(50, INTERVAL + vecspace345, str1);
	outtextxy(200, INTERVAL + vecspace345, strpt);
	outtextxy(300, INTERVAL + vecspace345, str2);
	outtextxy(450, INTERVAL + vecspace345, maxpt);
	//��ӡ����

	//���Ƹ���
	if (N == 5) {
		for (int r = 0; r < GRID_NUM; r++)
		{
			for (int c = 0; c < GRID_NUM; c++)
			{
				int x = c * GRID_WIDTH + (c + 1) * INTERVAL;
				int y = r * GRID_WIDTH + (r + 1) * INTERVAL + GRID_WIDTH;

				int index = 0;
				if (map[r][c] == 0)
				{
					index = 0;
				}
				if (map[r][c] != 0)
				{
					index = (int)log2(map[r][c]);
					//printf("%d\n",index);
				}

				setfillcolor(colors[index]);
				solidroundrect(x, y, x + GRID_WIDTH, y + GRID_WIDTH, 10, 10);


				if (map[r][c] != 0)
					//���ӱ�����ɫ
				{
					settextcolor(RGB(119, 110, 101));
					settextstyle(50, 0, "������κ");

					char str[5] = { 0 };
					sprintf_s(str, "%d", map[r][c]);

					int horspace = (GRID_WIDTH - textwidth(str)) / 2;
					int vecspace = (GRID_WIDTH - textheight(str)) / 2;

					outtextxy(x + horspace, y + vecspace, str);
				}
			}
		}
	}
	if (N == 4) {
		for (int r = 0; r < GRID_NUM; r++)
		{
			for (int c = 0; c < GRID_NUM; c++)
			{
				int x = c * GRID_WIDTH + (c + 1) * INTERVAL + GRID_WIDTH / 2 + INTERVAL / 2;
				int y = r * GRID_WIDTH + (r + 1) * INTERVAL + GRID_WIDTH;

				int index = 0;
				if (map[r][c] == 0)
				{
					index = 0;
				}
				if (map[r][c] != 0)
				{
					index = (int)log2(map[r][c]);
					//printf("%d\n",index);
				}

				setfillcolor(colors[index]);
				solidroundrect(x, y, x + GRID_WIDTH, y + GRID_WIDTH, 10, 10);


				if (map[r][c] != 0)
					//���ӱ�����ɫ
				{
					settextcolor(RGB(119, 110, 101));
					settextstyle(50, 0, "������κ");

					char str[5] = { 0 };
					sprintf_s(str, "%d", map[r][c]);

					int horspace = (GRID_WIDTH - textwidth(str)) / 2;
					int vecspace = (GRID_WIDTH - textheight(str)) / 2;

					outtextxy(x + horspace, y + vecspace, str);
				}
			}
		}
	}
	if (N == 3) {
		for (int r = 0; r < GRID_NUM; r++)
		{
			for (int c = 0; c < GRID_NUM; c++)
			{
				int x = c * GRID_WIDTH + (c + 1) * INTERVAL + GRID_WIDTH + INTERVAL;
				int y = r * GRID_WIDTH + (r + 1) * INTERVAL + GRID_WIDTH;

				int index = 0;
				if (map[r][c] == 0)
				{
					index = 0;
				}
				if (map[r][c] != 0)
				{
					index = (int)log2(map[r][c]);
					//printf("%d\n",index);
				}

				setfillcolor(colors[index]);
				solidroundrect(x, y, x + GRID_WIDTH, y + GRID_WIDTH, 10, 10);


				if (map[r][c] != 0)
					//���ӱ�����ɫ
				{
					settextcolor(RGB(119, 110, 101));
					settextstyle(50, 0, "������κ");

					char str[5] = { 0 };
					sprintf_s(str, "%d", map[r][c]);

					int horspace = (GRID_WIDTH - textwidth(str)) / 2;
					int vecspace = (GRID_WIDTH - textheight(str)) / 2;

					outtextxy(x + horspace, y + vecspace, str);
				}
			}
		}
	}
}

void drawGPA()
//�滭GPAģʽ�Ľ���
{
	//����GPA
	cleardevice();
	settextstyle(30, 0, "������κ");
	settextcolor(RGB(119, 110, 101));

	char str1[] = "yourGPA:";
	char str2[] = "maxGPA:";
	char strpt[10];
	char maxpt[10];
	//�ֱ��ǵ�ǰGPA�����GPA

	sprintf_s(strpt, "%.2f", averageGPA());
	sprintf_s(maxpt, "%.2f", GPAmax());

	int horspaceGPA = (GRID_WIDTH - textwidth(strpt)) / 2;
	int vecspaceGPA = (GRID_WIDTH - textheight(strpt)) / 2;
	//λ�ü���

	outtextxy(50, INTERVAL + vecspaceGPA, str1);
	outtextxy(200, INTERVAL + vecspaceGPA, strpt);
	outtextxy(300, INTERVAL + vecspaceGPA, str2);
	outtextxy(450, INTERVAL + vecspaceGPA, maxpt);
	//��ӡGPA

	//���Ƹ���
	for (int r = 0; r < GRID_NUM; r++)
	{
		for (int c = 0; c < GRID_NUM; c++)
		{
			int x = c * GRID_WIDTH + (c + 1) * INTERVAL + GRID_WIDTH / 2;
			int y = r * GRID_WIDTH + (r + 1) * INTERVAL + GRID_WIDTH;

			int index = 0;
			if (map[r][c] == 0)
			{
				index = 0;
			}
			if (map[r][c] != 0 && map[r][c] != numW && map[r][c] != numF)
			{
				index = (int)log2(map[r][c]);
				//printf("%d\n",index);
			}
			if (map[r][c] == numW)
			{
				index = 13;
			}
			if (map[r][c] == numF)
			{
				index = 14;
			}

			setfillcolor(colorgpa[index]);
			solidroundrect(x, y, x + GRID_WIDTH, y + GRID_WIDTH, 10, 10);


			if (map[r][c] != 0)
				//���ӱ�����ɫ
			{
				settextcolor(RGB(119, 110, 101));
				settextstyle(50, 0, "������κ");

				char str[5] = { 0 };
				sprintf_s(str, "%s", num2char(map[r][c]));

				int horspace = (GRID_WIDTH - textwidth(str)) / 2;
				int vecspace = (GRID_WIDTH - textheight(str)) / 2;

				outtextxy(x + horspace, y + vecspace, str);
			}
		}
	}
}

void drawTIME()
//�滭ʱ��ģʽ�Ľ���
{
	//���Ʒ���
	cleardevice();
	settextstyle(30, 0, "������κ");
	settextcolor(RGB(119, 110, 101));

	char str1[] = "yourpoint:";
	char str2[] = "maxpoint:";
	char strpt[10];
	char maxpt[10];
	//�ֱ��ǵ�ǰ��������߷���

	sprintf_s(strpt, "%d", point);
	sprintf_s(maxpt, "%d", pointmaxTIME());

	int horspace345 = (GRID_WIDTH - textwidth(strpt)) / 2;
	int vecspace345 = (GRID_WIDTH - textheight(strpt)) / 2;
	//λ�ü���

	outtextxy(50, INTERVAL + vecspace345, str1);
	outtextxy(200, INTERVAL + vecspace345, strpt);
	outtextxy(300, INTERVAL + vecspace345, str2);
	outtextxy(450, INTERVAL + vecspace345, maxpt);
	//��ӡ����

	//���Ƹ���
	for (int r = 0; r < GRID_NUM; r++)
	{
		for (int c = 0; c < GRID_NUM; c++)
		{
			int x = c * GRID_WIDTH + (c + 1) * INTERVAL + GRID_WIDTH / 2 + INTERVAL / 2;
			int y = r * GRID_WIDTH + (r + 1) * INTERVAL + GRID_WIDTH;

			int index = 0;
			if (map[r][c] == 0)
			{
				index = 0;
			}
			if (map[r][c] != 0)
			{
				index = (int)log2(map[r][c]);
				//printf("%d\n",index);
			}

			setfillcolor(colors[index]);
			solidroundrect(x, y, x + GRID_WIDTH, y + GRID_WIDTH, 10, 10);

			if (map[r][c] != 0)
				//���ӱ�����ɫ
			{
				settextcolor(RGB(119, 110, 101));
				settextstyle(50, 0, "������κ");

				char str[5] = { 0 };
				sprintf_s(str, "%d", map[r][c]);

				int horspace = (GRID_WIDTH - textwidth(str)) / 2;
				int vecspace = (GRID_WIDTH - textheight(str)) / 2;

				outtextxy(x + horspace, y + vecspace, str);
			}
		}
	}
}

void drawbegin()
//�滭��ʼ��������
{
	setbkcolor(RGB(187, 173, 160));//���ñ�����ɫ
	setbkmode(TRANSPARENT);
	cleardevice();
	settextcolor(RGB(119, 110, 101));//������ɫ

	char str1[] = "2048++";
	settextstyle(100, 0, "����");
	settextcolor(RGB(119, 110, 101));//������ɫ
	int horspace1 = (590 - textwidth(str1)) / 2; //���в���
	outtextxy(horspace1, 60, str1);

	char str2[] = "����ģʽ";
	setfillcolor(twoTo3);
	solidroundrect(170, 200, 420, 270, 10, 10);
	settextstyle(50, 0, "����");
	settextcolor(RGB(119, 110, 101));//������ɫ
	int horspace2 = (590 - textwidth(str2)) / 2; //���в���
	outtextxy(horspace2, 210, str2);

	char str3[] = "GPA ģʽ";
	setfillcolor(twoTo4);
	solidroundrect(170, 290, 420, 360, 10, 10);
	settextstyle(50, 0, "����");
	settextcolor(RGB(119, 110, 101));//������ɫ
	int horspace3 = (590 - textwidth(str3)) / 2; //���в���
	outtextxy(horspace3, 300, str3);

	char str4[] = "ʱ��ģʽ";
	setfillcolor(twoTo5);
	solidroundrect(170, 380, 420, 450, 10, 10);
	settextstyle(50, 0, "����");
	settextcolor(RGB(119, 110, 101));//������ɫ
	int horspace4 = (590 - textwidth(str4)) / 2; //���в���
	outtextxy(horspace4, 390, str4);

	char str5[] = "AI��ս";
	setfillcolor(twoTo6);
	solidroundrect(170, 470, 420, 540, 10, 10);
	settextstyle(50, 0, "����");
	settextcolor(RGB(119, 110, 101));//������ɫ
	int horspace5 = (590 - textwidth(str5)) / 2; //���в���
	outtextxy(horspace5, 480, str5);

	char str6[] = "��Ʒ��Ա";
	setfillcolor(twoTo7);
	solidroundrect(170, 560, 420, 630, 10, 10);
	settextstyle(50, 0, "����");
	settextcolor(RGB(119, 110, 101));//������ɫ
	int horspace6 = (590 - textwidth(str6)) / 2; //���в���
	outtextxy(horspace6, 570, str6);
}


void drawJD()
//�滭����ģʽ����
{
	cleardevice();

	settextcolor(RGB(119, 110, 101));//������ɫ
	char strwj[] = "����ģʽ";
	settextstyle(70, 0, "����");
	//���в���
	int horspacebt = (590 - textwidth(strwj)) / 2;
	outtextxy(horspacebt, 120, strwj);

	char strnd2[] = "��ս�Ѷ�ѡ�񡪡�";
	settextstyle(20, 0, "����");
	//���в���
	int horspacend = (590 - textwidth(strnd2)) / 2;
	outtextxy(horspacend, 240, strnd2);

	char strH[] = "�����Ѷ� 3*3����";
	setfillcolor(twoTo3);
	solidroundrect(70, 280, 520, 370, 10, 10);
	settextstyle(50, 0, "����");
	//���в���
	outtextxy(300 - textwidth(strH) / 2, 300, strH);

	char strS[] = "��׼�Ѷ� 4*4����";
	setfillcolor(twoTo4);
	solidroundrect(70, 380, 520, 470, 10, 10);
	settextstyle(50, 0, "����");
	//���в���
	outtextxy(300 - textwidth(strS) / 2, 400, strS);

	char strE[] = "���Ѷ� 5*5����";
	setfillcolor(twoTo5);
	solidroundrect(70, 480, 520, 570, 10, 10);
	settextstyle(50, 0, "����");
	//���в���
	outtextxy(300 - textwidth(strE) / 2, 500, strE);
}


void drawtarget345()
//��ӡĿ����ʾ���
{
	//����͸��
	int y = 0;
	setlinecolor(RGB(230, 230, 230));
	for (y = 0; y < 700; y = y + 2)
	{
		line(0, y, 589, y);
	}
	for (y = 215; y < 275; y = y + 1)
	{
		line(0, y, 589, y);
	}
	//д����
	settextstyle(50, 0, "����");
	settextcolor(RGB(119, 110, 101));
	char str[] = "���������Ŀ�꣺";
	outtextxy(110, 220, str);
}


void drawtargetGPA()
//����GPAģʽ��˵����Ŀ����ʾ���
{
	setbkcolor(RGB(187, 173, 160));//���ñ�����ɫ
	cleardevice();
	//д����

	settextstyle(30, 0, "����");
	settextcolor(RGB(119, 110, 101));
	char str2[] = "W���������ķ���";
	char str3[] = "Fֻ�ܺ�W��F�ϲ�";
	outtextxy(170, 210, str2);
	outtextxy(170, 250, str3);

	settextstyle(50, 0, "����");
	settextcolor(RGB(119, 110, 101));
	char str1[] = "���������Ŀ�꣺";
	outtextxy(110, 300, str1);

	settextstyle(30, 0, "����");
	settextcolor(RGB(119, 110, 101));
	char str4[] = "(����B+,A-,A,A+)";
	outtextxy(170, 360, str4);
}


void drawtargetTIME()
//����ʱ��ģʽ����ʾ���
{
	setbkcolor(RGB(187, 173, 160));//���ñ�����ɫ
	cleardevice();
	//д����

	settextstyle(30, 0, "����");
	settextcolor(RGB(119, 110, 101));
	char str2[] = "�ڱ�ģʽ�·�����Զ�����";
	char str3[] = "�����������������ж�ʧ��";
	outtextxy(110, 190, str2);
	outtextxy(110, 230, str3);

	settextstyle(50, 0, "����");
	settextcolor(RGB(119, 110, 101));
	char str1[] = "���������Ŀ�꣺";
	outtextxy(110, 280, str1);
}


void drawAIchoose()
{
	setbkcolor(RGB(187, 173, 160));//���ñ�����ɫ
	cleardevice();

	//д����

	char str1[] = "��ѡ�����AI��";
	settextstyle(50, 0, "����");
	settextcolor(RGB(119, 110, 101));
	outtextxy(140, 100, str1);

	char str2[] = "AI 1.0";
	setfillcolor(twoTo3);
	solidroundrect(170, 170, 420, 240, 10, 10);
	settextstyle(50, 0, "����");
	settextcolor(RGB(119, 110, 101));//������ɫ
	int horspace2 = (590 - textwidth(str2)) / 2; //���в���
	outtextxy(horspace2, 180, str2);

	char str3[] = "AI 2.0";
	setfillcolor(twoTo4);
	solidroundrect(170, 260, 420, 330, 10, 10);
	settextstyle(50, 0, "����");
	settextcolor(RGB(119, 110, 101));//������ɫ
	int horspace3 = (590 - textwidth(str3)) / 2; //���в���
	outtextxy(horspace3, 270, str3);

	char str4[] = "���������Ŀ�꣺";
	settextstyle(50, 0, "����");
	settextcolor(RGB(119, 110, 101));
	outtextxy(120, 350, str4);

	char str5[] = "������ÿ��ʱ��(ms)��";
	settextstyle(50, 0, "����");
	settextcolor(RGB(119, 110, 101));
	outtextxy(80, 480, str5);
}


void drawwin()
//���ƴ��Ŀ��ʱ��ͼƬ
{
	//����͸��
	int y = 0;
	setlinecolor(RGB(255, 255, 160));
	for (y = 0; y < 700; y = y + 2)
	{
		line(0, y, 589, y);
	}
	//д����
	settextstyle(80, 0, "������κ");
	settextcolor(RGB(236, 194, 47));
	char str1[] = "You Win!";
	outtextxy(120, 200, str1);
}


void drawover()
//����345ģʽ��TIMEģʽ��GPAģʽ�Ľ�������
{
	//����͸��
	int y = 0;
	setlinecolor(RGB(200, 200, 200));
	for (y = 0; y < 700; y = y + 2)
	{
		line(0, y, 589, y);
	}
	//д����
	settextstyle(80, 0, "������κ");
	settextcolor(RGB(119, 110, 101));
	char str1[] = "Game Over!";
	outtextxy(100, 200, str1);

	setfillcolor(twoTo11);
	solidcircle(295, 355, 50);

	POINT pts1[] = { {263,355}, {314,325}, {314,385} };

	setfillcolor(twoTo2);
	solidpolygon(pts1, 3);

	ExMessage m;   // ������Ϣ����
	{
		// ��ȡһ�����򰴼���Ϣ
		while (true) {
			m = getmessage(EM_MOUSE | EM_KEY);
			if (m.message == WM_LBUTTONDOWN) {
				// ��������
				if (m.x >= 245 && m.x <= 345 && m.y >= 305 && m.y <= 395)
				{
					again = 1;
					break;
				}
			}
		}
	}
}


void acd2map()
//��acd���鸳ֵ��map
{
	for (int i = 0; i < GRID_NUM; i++) {
		for (int j = 0; j < GRID_NUM; j++) {
			if (N == 3) map[i][j] = c[i][j];
			if (N == 4) map[i][j] = a[i][j];
			if (N == 5) map[i][j] = d[i][j];
		}
	}
}


void begin2model()
//��ʼʱģʽѡ����
{
	ExMessage m;   // ������Ϣ����
	{
		// ��ȡһ�����򰴼���Ϣ
		while (true) {
			m = getmessage(EM_MOUSE | EM_KEY);
			if (m.message == WM_LBUTTONDOWN) {
				// ��������
				if (m.x >= 170 && m.x <= 420 && m.y >= 200 && m.y <= 270) {
					choice = 'A';
					break;
				}
				if (m.x >= 170 && m.x <= 420 && m.y >= 290 && m.y <= 360) {
					choice = 'B';
					break;
				}
				if (m.x >= 170 && m.x <= 420 && m.y >= 380 && m.y <= 450) {
					choice = 'C';
					break;
				}
				if (m.x >= 170 && m.x <= 420 && m.y >= 470 && m.y <= 540) {
					choice = 'D';
					break;
				}
				if (m.x >= 170 && m.x <= 420 && m.y >= 560 && m.y <= 630) {
					choice = 'E';
					break;
				}
			}
		}
	}
}



void JDto345()
//����ģʽģʽѡ����
{
	ExMessage m;   // ������Ϣ����
	{
		// ��ȡһ�����򰴼���Ϣ
		while (true) {
			m = getmessage(EM_MOUSE | EM_KEY);
			if (m.message == WM_LBUTTONDOWN) {
				// ��������
				if (m.x >= 70 && m.x <= 520 && m.y >= 280 && m.y <= 370) {
					N = 3;
					break;
				}
				if (m.x >= 70 && m.x <= 520 && m.y >= 380 && m.y <= 470) {
					N = 4;
					break;
				}
				if (m.x >= 70 && m.x <= 520 && m.y >= 480 && m.y <= 570) {
					N = 5;
					break;
				}
			}
		}
	}
}


void AIget()
//��ȡ�����AIchoose�����������Ϣ
{
	ExMessage m;   // ������Ϣ����
	setfillcolor(twoTo2);

	{
		// ��ȡһ�����򰴼���Ϣ
		while (true) 
		{
			m = getmessage(EM_MOUSE | EM_KEY);
			if (m.message == WM_LBUTTONDOWN) {
				// ��������
				if (m.x >= 170 && m.x <= 420 && m.y >= 170 && m.y <= 240) {
					AImodel = 1;
					POINT pt1s[] = { {100, 180}, {100, 230}, {160, 205} };
					solidpolygon(pt1s, 3);
					POINT pt2s[] = { {490, 180}, {490, 230}, {430, 205} };
					solidpolygon(pt2s, 3);
					break;
				}
				if (m.x >= 170 && m.x <= 420 && m.y >= 260 && m.y <= 330) {
					AImodel = 2;
					POINT pt3s[] = { {100, 270}, {100, 320}, {160, 295} };
					solidpolygon(pt3s, 3);
					POINT pt4s[] = { {490, 270}, {490, 320}, {430, 295} };
					solidpolygon(pt4s, 3);
					break;
				}
			}
		}
	}
}

void getJDM()
//��ȡ����ģʽ���Ŀ��ֵ���������滭
{
	settextstyle(60, 0, "����");
	settextcolor(RGB(119, 110, 101));//������ɫ
	char str[20] = { 0 };
	char c;
	int i = 0;
	while ((c = _getch()) != VK_RETURN)//�����˸�
	{
		if (c != VK_BACK && c <= '9' && c >= '0' && i < 19) {
			str[i] = c;
			i++;
			int horspace = (590 - textwidth(str)) / 2; //���в���
			cleardevice();
			drawJD();
			drawtarget345();
			outtextxy(horspace, 350, str);
		}
		if (c == VK_BACK && i > 0) {
			i--;
			str[i] = 0;
			int horspace = (590 - textwidth(str)) / 2; //���в���
			cleardevice();
			drawJD();
			drawtarget345();
			outtextxy(horspace, 350, str);
		}
	}
	M = atoi(str);
}


void getGPAM()
//��ȡGPAģʽ��Ŀ��ֵ�������ֻ滭
{
	settextstyle(60, 0, "����");
	settextcolor(RGB(119, 110, 101));//������ɫ
	char str[20] = { 0 };
	char c;
	int i = 0;
	int eng = 0;//�������³���Ե�ָ��
	int sym = 0;//�������³���Ե�ָ��
	while ((c = _getch()) != VK_RETURN)//�����˸�
	{
		if (c != VK_BACK && (c == '+' || c == '-') && i == 0) {//�����һ�������������ʾ
			//str[i] = c;
			//i++;
			int horspace = (590 - textwidth(str)) / 2; //���в���
			drawtargetGPA();
			settextstyle(60, 0, "����");
			outtextxy(horspace, 420, str);
		}
		else if (c != VK_BACK && (c <= 'D' && c >= 'A') && eng == 0) {//���������ĸ����ʾ�������eng
			str[i] = c;
			i++;
			int horspace = (590 - textwidth(str)) / 2; //���в���
			drawtargetGPA();
			settextstyle(60, 0, "����");
			outtextxy(horspace, 420, str);
			eng = 1;
		}
		else if (c != VK_BACK && (c == '+' || c == '-') && sym == 0) {//���������Ų���ʾ�������sym
			str[i] = c;
			i++;
			int horspace = (590 - textwidth(str)) / 2; //���в���
			drawtargetGPA();
			settextstyle(60, 0, "����");
			outtextxy(horspace, 420, str);
			sym = 1;
		}
		else if (c == VK_BACK && i == 1){//��������һ���ַ���س�
			i--;
			str[i] = 0;
			int horspace = (590 - textwidth(str)) / 2; //���в���
			drawtargetGPA();
			settextstyle(60, 0, "����");
			outtextxy(horspace, 420, str);
			eng = 0;
		}
		else if (c == VK_BACK && i == 2) {//�������ڶ����ַ���س�
			i--;
			str[i] = 0;
			int horspace = (590 - textwidth(str)) / 2; //���в���
			drawtargetGPA();
			settextstyle(60, 0, "����");
			outtextxy(horspace, 420, str);
			sym = 0;
		}
	}
	M = char2num(str);
}


void getTIMEM()
//��ȡʱ��ģʽ���Ŀ��ֵ���������滭
{
	settextstyle(60, 0, "����");
	settextcolor(RGB(119, 110, 101));//������ɫ
	char str[20] = { 0 };
	char c;
	int i = 0;
	while ((c = _getch()) != VK_RETURN)//�����˸�
	{
		if (c != VK_BACK && c <= '9' && c >= '0' && i < 19) {
			str[i] = c;
			i++;
			int horspace = (590 - textwidth(str)) / 2; //���в���
			drawtargetTIME();
			outtextxy(horspace, 360, str);
		}
		if (c == VK_BACK && i > 0) {
			i--;
			str[i] = 0;
			int horspace = (590 - textwidth(str)) / 2; //���в���
			drawtargetTIME();
			outtextxy(horspace, 360, str);
		}
	}
	M = atoi(str);
}


void getAIM()
//��ȡAI��Ŀ�꣬���ֻ���
{
	settextstyle(50, 0, "����");
	settextcolor(RGB(119, 110, 101));//������ɫ
	char str[20] = { 0 };
	char c;
	int i = 0, j = 0;
	while ((c = _getch()) != VK_RETURN)//�����˸�
	{
		if (c != VK_BACK && c <= '9' && c >= '0' && i < 19) {
			str[i] = c;
			i++;
			int horspace = (590 - textwidth(str)) / 2; //���в���
			setlinecolor(RGB(187, 173, 160));
			for (j = 400; j < 480; j++) {
				line(0, j, 589, j);
			}
			settextstyle(50, 0, "����");
			settextcolor(RGB(119, 110, 101));//������ɫ
			outtextxy(horspace, 410, str);
		}
		if (c == VK_BACK && i > 0) {
			i--;
			str[i] = 0;
			int horspace = (590 - textwidth(str)) / 2; //���в���
			setlinecolor(RGB(187, 173, 160));
			for (j = 400; j < 480; j++) {
				line(0, j, 589, j);
			}
			settextstyle(50, 0, "����");
			settextcolor(RGB(119, 110, 101));//������ɫ
			outtextxy(horspace, 410, str);
		}
	}
	M = atoi(str);
}


void getsteptime()
//��ȡAIÿ����ʱ�䣬�����ֻ���
{
	settextstyle(50, 0, "����");
	settextcolor(RGB(119, 110, 101));//������ɫ
	char str[20] = { 0 };
	char c;
	int i = 0, j = 0;
	while ((c = _getch()) != VK_RETURN)//�����˸�
	{
		if (c != VK_BACK && c <= '9' && c >= '0' && i < 19) {
			str[i] = c;
			i++;
			int horspace = (590 - textwidth(str)) / 2; //���в���
			setlinecolor(RGB(187, 173, 160));
			for (j = 540; j < 699; j++) {
				line(0, j, 589, j);
			}
			settextstyle(50, 0, "����");
			settextcolor(RGB(119, 110, 101));//������ɫ
			outtextxy(horspace, 540, str);
		}
		if (c == VK_BACK && i > 0) {
			i--;
			str[i] = 0;
			int horspace = (590 - textwidth(str)) / 2; //���в���
			setlinecolor(RGB(187, 173, 160));
			for (j = 540; j < 699; j++) {
				line(0, j, 589, j);
			}
			settextstyle(50, 0, "����");
			settextcolor(RGB(119, 110, 101));//������ɫ
			outtextxy(horspace, 540, str);
		}
	}
	steptime = atoi(str);
}


void statement()
//��Ʒ����
{

	cleardevice();
	settextstyle(30, 0, "����");
	settextcolor(RGB(119, 110, 101));//������ɫ
	char str1[] = "2048++��Ʒ��Ա�У�";
	char str2[] = "Ԭ����";
	char str3[] = "������";
	char str4[] = "������";
	char str5[] = "�";
	char str6[] = "��ʫ��";
	char str7[] = "��л��ʦѧ���İ�����";
	char str8[] = "���Ա���Ϸ�иĽ��뷨";
	char str9[] = "��ӭemail��";
	char str10[] = "ypz21@mails.tsinghua.edu.cn";
	outtextxy(100, 50, str1);
	outtextxy(100, 100, str2);
	outtextxy(100, 150, str3);
	outtextxy(100, 200, str4);
	outtextxy(100, 250, str5);
	outtextxy(100, 300, str6);
	outtextxy(100, 350, str7);
	outtextxy(100, 400, str8);
	outtextxy(100, 450, str9);
	outtextxy(100, 500, str10);

	setfillcolor(twoTo11);
	solidcircle(295, 605, 50);

	POINT pts1[] = { {263,605}, {314,575}, {314,635} };

	setfillcolor(twoTo2);
	solidpolygon(pts1, 3);

	ExMessage m;   // ������Ϣ����
	{
		// ��ȡһ�����򰴼���Ϣ
		while (true) {
			m = getmessage(EM_MOUSE | EM_KEY);
			if (m.message == WM_LBUTTONDOWN) {
				// ��������
				if (m.x >= 245 && m.x <= 345 && m.y >= 555 && m.y <= 645)
				{
					again = 1;
					break;
				}
			}
		}
	}

}


int show()
//δ���õĺ�����������һ��ʼʱ���ɻ���Ĺ���
{
	initgraph(GRID_NUM * GRID_WIDTH + (GRID_NUM + 1) * INTERVAL, GRID_NUM * GRID_WIDTH + (GRID_NUM + 1) * INTERVAL, EW_SHOWCONSOLE);//����ͼ�δ���
	setbkcolor(RGB(187, 173, 160));//���ñ�����ɫ
	cleardevice();//����
	setbkmode(TRANSPARENT);

	for (int i = 0; i < GRID_NUM; i++) {
		for (int j = 0; j < GRID_NUM; j++) {
			if (N == 3) map[i][j] = c[i][j];
			if (N == 4) map[i][j] = a[i][j];
			if (N == 5) map[i][j] = d[i][j];
		}
	}

	closegraph();
	return 0;
}


