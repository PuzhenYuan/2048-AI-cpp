//1.0����־������汾���ܹ������ ��������yyds�� 
//2.0����־���޸��˽������ˡ�2244���⡢��Сд�����ӷ������ơ��޸�2��4���ָ��� ��Ŀ��M����Ϊ�Ƕ��η�
//2.1����־����getch��������ֱ�Ӷ�ȡ�����ûس�
//2.2����־���޸��˲��ƶ���ˢ�����ݵ�bug���޸�����������2244����ʧ��bug 
//3.0����־������AIģ�飬Ŭ���Ӽ�����������߷� 
//3.1����־������AI�Ĳ��Թ��ܣ�AI�����������������ų�����汾����bug�Ŀ��� 
//4.0����־�������ģʽ����(����ģʽ������ģʽ��ʱ��ģʽ��������yyds�� 
//           ����ģʽ�������Ѷ�ѡ�񣨱߳�ѡ��Ϊ3��4��5��
//		     �Ż���basicfunction��moveandadd�������㷨�����þ��󴫵ݽ��ĸ����򻯹鵽һ������Ϊ���������������
//		     GPAģʽ������ɣ������ھ���ģʽ����F��W��F����������W����������һ�������ķ��� 
//		     ʱ��ģʽ����bug������Ұ��������������ֵ�ʱ�̺ܽӽ�ʱ����Ϸ�������Ť��
//4.1����־������dyq2048AI.c��dyq2048AI.h����main.c��������computerplay2()�� computercount2()����basicfunction�������� moveandadd40���� 
//4.2����־�����������ģʽ���ӱ�����߷����Ĺ���,��������txt�ļ�����TIMEģʽ�Ľ�Ϊ���̷߳�����ʽ���� 
//5.0����־����gui����ԭ�ȵĳ���IDE����VS�������۾��ˣ�д��GPA��NUM��������ָ�뺯��
//5.1����־������ͳһ��graph����������ͼ������ʾ��������������ʤ������
//5.2����־��������������Ϸ���棬����û�м������ͼ��̵Ľ�������������console
//5.3����־��������̺����Ľ�������������console������Ϸ��
//5.4����־����ǿ���������³���ԣ�������ע����߿ɶ��ԣ���Ŀ�������п���ֱ�Ӱ��س���������ȡ��win���ܣ���ɳ�Ʒ��Ա����
//5.5����־���޸�TIMEģʽ���룬������ռ�������ٵ�1���Game Over,��ǿ��GPAmģʽ���������³���ԣ��޸���GPAģʽF��Ϊ��󼨵㵼��win��bug
//6.0����־����дdyq2048AI,��basicfunction��������moveandadd41�������������ȫ������
//6.1����־����ǿ³���ԣ�����ʧ�ܻ򿪷���Ա����ʱ���ַ��ع���


//��׼���ļ� 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h> 
#include <conio.h> 	  //����getch()��kbhit()
#include <math.h>
#include <easyx.h>
#include <graphics.h>

//�Ա���ļ� 
#include "basicfunction.h"
#include "GPAmodel.h"
#include "timemodel.h"
//2048�������ܺ����� ����ң� 

#include "2048AI.h" 
#include "dyq2048AI.h" 
//2048AI���ܵĺ����� �����ԣ� 

#include "gui.h"
//ͼ�λ�������غ�����

/************************************ȫ�ֱ���˵��**************************************/
//�������W/w-�� ��S/s-�� ��A/a-�� ��D/d-�� 

int a[4][4] = {0};
//��׼��Ϸ������4*4�����ʾ

int c[3][3] = {0};
int d[5][5] = {0};
int N = 4;//N���Ա�ʾ����ı߳�
//���������ڱ�׼ģʽѡ�����߳�ʱӦ�� 

int b = 0;
//b��ʾ������Ķ�Ӧ���֣�1��ʾ�ϣ�2��ʾ��3��ʾ�£�4��ʾ�� 

int M = 2048;
//�趨��Ϸ�ĳ�ʼĿ��

int point = 0;
//������������ɷ������ֵ֮��  

char choice;
//��Ҷ���Ϸģʽ��ѡ��

int AImodel;
//��Ҷ�AIģʽ��ѡ��

int steptime = 100;
//AI��ÿ��ʱ��

int GRID_NUM = 4;
//gui�и��ӱ߳�
int map[6][6] = { 0 };
//����ȡ����ͼ

int again = 0;
//�Ƿ��ٻص���ҳ��

//���¶�������dyq2048AI2��
int h[4][4] = { 0 };
//h���Դ洢���е�һ���������ǰ��aֵ 
int h1[4][4] = { 0 };
//h1���Դ洢���еڶ����������ǰ��aֵ 
int point1;
//point1���Դ洢pointֵ 
int r3, r2, r4;
//r3,r2,r4���Ա�ʾmoveandadd�����ķ���ֵ��������ʾ����Ƿ���Խ����ƶ�����������r3��¼���µ������r2��¼����������r4��¼���ҵ����
float move3, move2, move4;
//�������������ֱ�Ϊ��һ�����¡������ƶ������� 



/************************************��׼ģʽ����**************************************/

void classicmodel()
{
	drawJD();
	//���ƾ������

    printf("��ѡ��һ���Ѷȣ�\n");
    printf("�����Ѷȣ�3*3����: 3\n");
    printf("��׼�Ѷȣ�4*4����: 4\n");
    printf("���Ѷȣ�5*5����: 5\n");

	JDto345();
	//����ģʽģʽѡ����

    char key;
    //key��ʾ���̵����� 
    int r,s,t;
    //r��ʾmoveandadd�����ķ���ֵ��������ʾ����Ƿ���Խ����ƶ�����
    //s��ʾ����Ĳ����������ڹ���������ʵ���ƶ�
    //t��ʾnotfull�����ķ���ֵ�������ж��Ƿ��пո� 
    int win = 0; 
    //����Ƿ�������ս ,Ԥ��û��
    
	drawtarget345();
	//����345Ŀ��ѡ�����

    printf("��������Ҫƴ�յ�������֣�����32��64��128��...��2048��");
    //scanf_s("%d", &M);
   
	getJDM();
	//��ȡ����ģʽ���Ŀ��ֵ�������滭

	GRID_NUM = N;

	setbkcolor(RGB(187, 173, 160));//���ñ�����ɫ
	cleardevice();//����
	setbkmode(TRANSPARENT);
	draw345();

    //step1����ʾ��ʼ״̬ 
    srand((int)time(NULL));//�������������
    if(N == 3 || N == 4)
    {
   		randomnumber();//������ɵ�һ����
   		randomnumber();//������ɵڶ�����
    }
    if(N == 5)
    {
   		randomnumber();//ֻ�������һ�Σ��Է���һ������4���� 
    }

	acd2map();//��ֵ
    print();//��ӡ��ʼ״̬ 
	draw345();//����345��Ϸ����
   
    //step2����ҽ�����Ϸ���� 
    while(1)
    {
    	t = notfull();
    	if(t == 0 && canstillmove() == 0)
		{
		  	printf("Game Over��\n");
		  	printf("�����յĵ÷��ǣ�\n");
		    printf("%d", point); 
		  	//system("pause");
			drawover();

		  	break;
	    }
   	    s = move();//��ȡ������
	    if(s == 0)//��������������Ҽ��������¶�ȡ����
	    {
	  		continue;
	    }  
   	    r = moveandadd();//���ݷ�����ϲ����,����1��ʾ���ƶ�
   	    if(r == 1)
	    {
			acd2map();
	   	    print();//��ʾ����ƶ�֮��Ľ��� 
			draw345();
	    }
	    t = notfull(); 
        if(calculatemax() >= M && win == 0 && M > 0)//�ж��Ƿ�ʤ��
        {
            printf("��Ӯ�ˣ��������ս�ɣ�\n");
            win = 1;
			drawwin();
            system("pause"); 
        }
	    if(t == 1 && r == 1)//�п�λ�����ƶ���������һ������� 
	    {
	  	    randomnumber();//���������

			acd2map();
		    print();//��ʾ����ƶ�֮��Ľ��� 
			draw345();
	    }
	    if(t == 0 && canstillmove() == 1)//���û�пո��ӵ��ܶ������������ 
	    {
		    printf("��ѡ����һ�����򻬶���\n");	
		}
    }
}

/************************************GPAģʽ���� **************************************/

void GPAmodel()
{
	char key;
    //key��ʾ���̵����� 
    int r,s,t;
	//r��ʾmoveandadd�����ķ���ֵ��������ʾ����Ƿ���Խ����ƶ�����
	//s��ʾ����Ĳ����������ڹ���������ʵ���ƶ�
	//t��ʾnotfull�����ķ���ֵ�������ж��Ƿ��пո� 
    int win = 0; 
	//����Ƿ�������ս ,Ԥ��û��
    
	drawtargetGPA();
	//����GPAģʽĿ��ѡ��Ľ���

    char in[2] = {'\0','\0'};
    printf("���������Ŀ�꼨�㣬����C, C+��B-��B��,B+...��A+��\n");
    //scanf_s("%s", in, 2);
    //M = char2num(in);

	getGPAM();
	//��ȡGPAģʽ��Ŀ��ֵ�������ֻ滭
   
	GRID_NUM = N;

	setbkcolor(RGB(187, 173, 160));//���ñ�����ɫ
	cleardevice();//����
	setbkmode(TRANSPARENT);
	drawGPA();

    //step1����ʾ��ʼ״̬ 
    srand((int)time(NULL));//������������� 
    randomGPA();//������ɵ�һ���� 
    randomGPA();//������ɵڶ�����
	acd2map();
	drawGPA();
    printinGPA();//��ӡ��ʼ״̬ 
   
    //step2����ҽ�����Ϸ���� 
    while(1)
    {
    	t = notfullGPA();
		if(t == 0 && canstillmoveGPA() == 0)
		{
		  	printf("��������\n");
		  	printf("����ߵļ�����:");
			printGPA(calculatemaxGPA());
			printf("\n"); 
			printf("�����յľ�����: "); 
			printf("%.2f\n", averageGPA());
		  	//system("pause");
			drawover();

		  	break;
	    }
   	    s = moveGPA();//��ȡ������
	    if(s == 0)//��������������Ҽ��������¶�ȡ����
	    {
	  		continue;
	    }  
   	    r = moveandaddGPA();//���ݷ�����ϲ����,����1��ʾ���ƶ� 
   	    if(r == 1)
	    {
	   	    printinGPA();//��ʾ����ƶ�֮��Ľ���
			acd2map();
			drawGPA();
	    }
        if(calculatemaxGPA() >= M && win == 0 && M > 0)//�ж��Ƿ�ʤ��
        {
            printf("��ﵽ���Լ���Ŀ�꣡�������������ɣ�\n");
            win = 1;
			drawwin();
            system("pause"); 
        }
        t = notfullGPA();
	    if(t == 1 && r == 1) //�п�λ�����ƶ���������һ������� 
	    {
	  	    randomGPA();//��������� 
		    printinGPA();//��ʾ����ƶ�֮��Ľ��� 
			acd2map();
			drawGPA();
	    }
	    if(t == 0 && canstillmoveGPA() == 1)//���û�пո��ӣ����ж���Ϸ�Ƿ���� 
	    {
		    printf("��ѡ����һ�����򻬶���\n");	
		}
    }
}

/************************************ʱ��ģʽ���� **************************************/

void timemodel()
{
	drawtargetTIME();

    printf("ע�⣡�ڴ�ģʽ�£���Ϸ������������ζ����Ϸ��������!\n");
    printf("��������Ҫƴ�յ�������֣�����32��64��128��...��2048��");
    //scanf_s("%d", &M);

	getTIMEM();
	//��ȡʱ��ģʽ���Ŀ��ֵ���������滭
    
	GRID_NUM = N;

	setbkcolor(RGB(187, 173, 160));//���ñ�����ɫ
	cleardevice();//����
	setbkmode(TRANSPARENT);
	drawTIME();

    //��ʾ��ʼ״̬ 
    srand((int)time(NULL));//������������� 
    randomnumberTIME();//������ɵ�һ���� 
    randomnumberTIME();//������ɵڶ����� 

	acd2map();
    printTIME();//��ӡ��ʼ״̬
	drawTIME();

    char key;
	//key��ʾ���̵����� 
    int r,s,t;
	//r��ʾmoveandadd�����ķ���ֵ��������ʾ����Ƿ���Խ����ƶ�����
	//s��ʾ����Ĳ����������ڹ���������ʵ���ƶ�
	//t��ʾnotfull�����ķ���ֵ�������ж��Ƿ��пո� 
    int win = 0; 
	//����Ƿ�������ս ,Ԥ��û��

	clock_t tb = clock();
	//tb�洢�Զ��������ֵ�ʱ�� 
	
    while(1)
    {
    	if(_kbhit())//����ʵ�ַ�����ʽ���̼�����лл���̣� 
		{
	    	t = notfullTIME();
			if(t == 0 && canstillmoveTIME() == 0)
			{
			  	printf("Game Over��\n");
			  	printf("�����յĵ÷��ǣ�\n");
				printf("%d", point); 
			  	//system("pause");
				drawover();

			  	break;
		    }
			s = moveTIME();//��ȡ������
		    if(s == 0)//��������������Ҽ��������¶�ȡ����
		    {
		  		continue;
		    }  
	   	    r = moveandaddTIME();//���ݷ�����ϲ����,����1��ʾ���ƶ� 
	   	    if(r == 1)
		    {
				acd2map();
		   	    printTIME();//��ʾ����ƶ�֮��Ľ���
				drawTIME();
		    }
	        if(calculatemaxTIME() >= M && win == 0 && M > 0)//�ж��Ƿ�ʤ�� 
	        {
	            printf("��Ӯ�ˣ��������ս�ɣ�\n");
	            win = 1;
				drawwin();
	            system("pause"); 
	        }
	        t = notfullTIME();
		    if(t == 1 && r == 1) //�п�λ�����ƶ���������һ������� 
		    {
		  	    randomnumberTIME();//��������� 

				acd2map();
			    printTIME();//��ʾ����ƶ�֮��Ľ��� 
				drawTIME();
		    }
		    if(t == 0 && canstillmoveTIME() == 1)//���û�пո��ӣ����ж���Ϸ�Ƿ���� 
		    {
			    printf("��ѡ����һ�����򻬶���\n");	
			}
		}//ʵ�ַ�����ʽ���̼��� 
		{//�����������������Զ��������ֵĹ��ܣ�Ϊ�˷������ѭ����д���������� 
			float delta = 0.0;
			clock_t tn = clock();
			delta = ((float)(tn - tb))/ CLOCKS_PER_SEC;
			if(delta >= 1.0)
			{
				if (notfullTIME() == 0)
				{
					printf("Game Over��\n");
					printf("�����յĵ÷��ǣ�\n");
					printf("%d", point);
					//system("pause");
					drawover();

					break;
				}
				if(notfullTIME() == 1)
				{
					randomnumberTIME();
					acd2map();
					printTIME();
					drawTIME();
					tb = tn;
				}
		    }
		}//�����������������Զ��������ֵĹ��� 
    }
}


/************************************����AI��ս���� **************************************/

void computerplay()
{
    char key;
    int r,s,t;
    int win = 0; //�����Ƿ�������ս 

    printf("��������ϷҪƴ�յ�������֣�����32��64��128��...��2048��\n");
    //scanf_s("%d", &M);

	getAIM();
	//��ȡAI��Ŀ�꣬���ֻ���

    printf("���������ÿһ����Ӧ��ʱ�䣨ms��:\n");
	//scanf_s("%d", &steptime);

	getsteptime();
	//��ȡAIÿ����ʱ�䣬�����ֻ���
	
	GRID_NUM = N;

	setbkcolor(RGB(187, 173, 160));//���ñ�����ɫ
	cleardevice();//����
	setbkmode(TRANSPARENT);
	draw345();

    //step1����ʾ��ʼ״̬ 
    srand((int)time(NULL));//������������� 
    randomnumber();//������ɵ�һ���� 
    randomnumber();//������ɵڶ����� 

	acd2map();
    print();//��ӡ��ʼ״̬ 
	draw345();

    //step2�����Խ�����Ϸ���� 
	while(1)
	{
		b = change(AI2048());//(a, 4, 4, point));
		Sleep(steptime);
		r = moveandadd();//���ݷ�����ϲ����,����1��ʾ���ƶ� 
		//printf("%d", r);
   	    if(r == 1)
	    {
			acd2map();
	   	    print();//��ʾ�����ƶ�֮��Ľ��� 
			draw345();
	    }
        if(calculatemax() >= M && win == 0)//�ж��Ƿ�ʤ�� 
        {
            printf("���Դ��Ŀ��\n");
            win = 1;
			drawwin();
            system("pause"); 
        }
        t = notfull();
	    if(t == 1 && r == 1) //�п�λ�����ƶ���������һ������� 
	    {
	  	    randomnumber();//��������� 
			acd2map();
		    print();//��ʾ�����ƶ�֮��Ľ��� 
			draw345();
	    }
	    if(t == 0)//���û�пո��ӣ����ж���Ϸ�Ƿ���� 
	    {
	  	    if(canstillmove() == 1)//�����ƶ�����Ϸ���� 
		    {
		        printf("��ѡ����һ�����򻬶���\n");	
		    }
		    else
		    {
		  	    printf("Game Over��\n");
		  	    printf("�������յĵ÷��ǣ�\n");
			    printf("%d\n", point);
		  	    //system("pause");
				drawover();

		  	    break;
		    }
	    }
	}
}


int simpleplay(int m)
//����AI��β�ս������ֻ���ط���ֵ 
//m��ֵ��Ϊ�˲���α��������ӣ�һ��ʱ��̫���˲�����time��NULL)�� 
{
    char key;
    int r,s,t;
    point = 0;
	int i,j;//��� 
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			a[i][j] = 0;
		}
	} 
    srand(m);//��m��ֵ��Ϊseed����֤ÿ�ֲ�ͬ 
    randomnumber();
    randomnumber(); 
	while(1)
	{
		b = change(AI2048());
		r = moveandadd();//���ݷ�����ϲ����,����1��ʾ���ƶ� 
        t = notfull();
	    if(t == 1 && r == 1) //�п�λ�����ƶ���������һ������� 
	    {
	  	    randomnumber();//��������� 
	    }
	    if(t == 0)//���û�пո��ӣ����ж���Ϸ�Ƿ���� 
	    {
	  	    if(canstillmove() != 1)
		    {
		        break;
		    }
	    }
	}
	return point; 
}


void computercount()
//��������ͳ��ƽ���ֺͷ����AI�������� 
{
	int times = 100;
	int i;
	printf("��������Ҫ���е���Ϸ����(<500)��\n"); 
	scanf_s("%d", &times);
	int average = 0;
	int variance = 0;
	int p[1000] = { 0 };
	for(i=0;i<times;i++)
	{
		p[i] = simpleplay(i);
	}
	int sum1 = 0;
	long int sum2 = 0;
	for(i=0;i<times;i++)
	{
		sum1 += p[i];
	}
	average = sum1 / times;
	for(i=0;i<times;i++)
	{
		sum2 += (p[i] - average)*(p[i] - average);
	}
	variance = (int)sqrt((double)(sum2 / times));
	printf("���Ե�ƽ�����ǣ�\n");
	printf("%d\n", average);
	printf("���Է����ķ����ǣ�\n");
	printf("%d\n", variance);
}

/************************************����AI��ս���� 2 **************************************/

void computerplay2()
{
	char key;
	int h[4][4] = { 0 }; //h���Դ�����м������ǰ��a��ֵ 
	int r, s, t;
	int win = 0; //�����Ƿ�������ս 

	printf("��������ϷҪƴ�յ�������֣�����32��64��128��...��2048��\n");
	//scanf_s("%d", &M);

	getAIM();
	//��ȡAI��Ŀ�꣬���ֻ���

	printf("���������ÿһ����Ӧ��ʱ�䣨ms��:\n");
	//scanf_s("%d", &steptime);

	getsteptime();
	//��ȡAIÿ����ʱ�䣬�����ֻ���

	//step1����ʾ��ʼ״̬ 
	srand((int)time(NULL));//������������� 
	randomnumber();//������ɵ�һ���� 
	randomnumber();//������ɵڶ����� 
	print();//��ӡ��ʼ״̬ 


	setbkcolor(RGB(187, 173, 160));//���ñ�����ɫ
	cleardevice();//����
	setbkmode(TRANSPARENT);
	acd2map();
	draw345();

	//step2�����Խ�����Ϸ����
	while (1)
	{

		dyq2048AI();//�ռ����� 

		//���������������ж��ƶ�����
		if (cangodown() == 1 && cangoleft() == 1 && cangoright() == 1)//����������¡������ƶ� 
		{
			if (move3 >= move2 && move3 >= move4)//��������ͬ������£��������ȼ����� > �� > ��
			{
				b = 3;
				moveandadd();//���ݷ�����ϲ����
				print();//��ʾ�����ƶ�֮��Ľ��� 
				acd2map();
				draw345();
				Sleep(steptime);
				randomnumber();//��������� 
				print();//��ʾ�����ƶ�֮��Ľ��� 
				acd2map();
				draw345();
				Sleep(steptime);
			}
			else if (move2 >= move4)
			{
				b = 2;
				moveandadd();
				print();
				acd2map();
				draw345();
				Sleep(steptime);
				randomnumber();
				print();
				acd2map();
				draw345();
				Sleep(steptime);
			}
			else
			{
				b = 4;
				moveandadd();
				print();
				acd2map();
				draw345();
				Sleep(steptime);
				randomnumber();
				print();
				acd2map();
				draw345();
				Sleep(steptime);
			}
		}
		else if (cangodown() == 1 && cangoleft() == 1 && cangoright() == 0)//����������¡����ƶ� 
		{
			if (move3 >= move2)
			{
				b = 3;
				moveandadd();
				print();
				acd2map();
				draw345();
				Sleep(steptime);
				randomnumber();
				print();
				acd2map();
				draw345();
				Sleep(steptime);
			}
			else
			{
				b = 2;
				moveandadd();
				print();
				acd2map();
				draw345();
				Sleep(steptime);
				randomnumber();
				print();
				acd2map();
				draw345();
				Sleep(steptime);
			}
		}
		else if (cangodown() == 1 && cangoleft() == 0 && cangoright() == 1)//����������¡����ƶ� 
		{
			if (move3 >= move4)
			{
				b = 3;
				moveandadd();
				print();
				acd2map();
				draw345();
				Sleep(steptime);
				randomnumber();
				print();
				acd2map();
				draw345();
				Sleep(steptime);
			}
			else
			{
				b = 4;
				moveandadd();
				print();
				acd2map();
				draw345();
				Sleep(steptime);
				randomnumber();
				print();
				acd2map();
				draw345();
				Sleep(steptime);
			}
		}
		else if (cangodown() == 0 && cangoleft() == 1 && cangoright() == 1)//��������������ƶ� 
		{
			if (move2 >= move4)
			{
				b = 2;
				moveandadd();
				print();
				acd2map();
				draw345();
				Sleep(steptime);
				randomnumber();
				print();
				acd2map();
				draw345();
				Sleep(steptime);
			}
			else
			{
				b = 4;
				moveandadd();
				print();
				acd2map();
				draw345();
				Sleep(steptime);
				randomnumber();
				print();
				acd2map();
				draw345();
				Sleep(steptime);
			}
		}
		else if (cangodown() == 1 && cangoleft() == 0 && cangoright() == 0)//������������ƶ� 
		{
			b = 3;
			moveandadd();
			print();
			acd2map();
			draw345();
			Sleep(steptime);
			randomnumber();
			print();
			acd2map();
			draw345();
			Sleep(steptime);
		}
		else if (cangodown() == 0 && cangoleft() == 1 && cangoright() == 0)//������������ƶ� 
		{
			b = 2;
			moveandadd();
			print();
			acd2map();
			draw345();
			Sleep(steptime);
			randomnumber();
			print();
			acd2map();
			draw345();
			Sleep(steptime);
		}
		else if (cangodown() == 0 && cangoleft() == 0 && cangoright() == 1)//������������ƶ� 
		{
			b = 4;
			moveandadd();
			print();
			acd2map();
			draw345();
			Sleep(steptime);
			randomnumber();
			print();
			acd2map();
			draw345();
			Sleep(steptime);
		}
		else if (cangodown() == 0 && cangoleft() == 0 && cangoright() == 0)//����������¡������ƶ� 
		{
			b = 1;//���������ƶ�
			moveandadd();
			print();
			acd2map();
			draw345();
			Sleep(steptime);
			randomnumber();
			print();
			acd2map();
			draw345();
			Sleep(steptime);
			b = 3;//�������ƶ� 
			moveandadd();
			print();
			acd2map();
			draw345();
			Sleep(steptime);
			randomnumber();
			print();
			acd2map();
			draw345();
			Sleep(steptime);
		}

		if (calculatemax() >= M && win == 0)//�ж��Ƿ�ʤ��  
		{
			printf("���Դ��Ŀ��\n");
			win = 1;
			drawwin();
			system("pause");
		}
		t = notfull();
		if (t == 0)//���û�пո��ӣ����ж���Ϸ�Ƿ���� 
		{
			if (canstillmove() == 1)//�����ƶ�����Ϸ���� 
			{
			}
			else
			{
				printf("Game Over��\n");
				printf("�������յĵ÷��ǣ�\n");
				printf("%d\n", point);
				drawover();

				//system("pause");
				break;
			}
		}
	}
}


void computercount2()
//��������ͳ��ƽ���ֺͷ����AI�������ܣ���computercount��ȣ�computercount2ֻ�ǽ�simpleplay��Ϊsimpleplay2
{
	int times;//��Ҫ���е���Ϸ����
	int i;
	printf("��������Ҫ���е���Ϸ����(<500)��\n");
	scanf_s("%d", &times);
	int average = 0;//������ƽ��ֵ 
	int maximalpoint = 0;//���������ֵ 
	int maximalnumber = 0;//������ֵ����ֵ 
	int successfultime = 0;//��Ϸ�ɹ�������Ҳ������2048�Ĵ��� 
	int time64 = 0;//�������Ϊ 64�Ĵ���
	int time128 = 0;//�������Ϊ 128�Ĵ���
	int time256 = 0;//�������Ϊ 256�Ĵ���
	int time512 = 0;//�������Ϊ 512�Ĵ���
	int time1024 = 0;//�������Ϊ 1024�Ĵ���
	int time2048 = 0;//�������Ϊ 2048�Ĵ���
	int p[1000] = { 0 };
	for (i = 0; i < times; i++)
	{
		p[i] = simpleplay2(i);
		if (simpleplay2(i) > maximalpoint)
		{
			maximalpoint = simpleplay2(i);
		}
		if (calculatemax() > maximalnumber)
		{
			maximalnumber = calculatemax();
		}
		if (calculatemax() >= 2048)
		{
			successfultime++;
		}
		if (calculatemax() == 64)
		{
			time64++;
		}
		if (calculatemax() == 128)
		{
			time128++;
		}
		if (calculatemax() == 256)
		{
			time256++;
		}
		if (calculatemax() == 512)
		{
			time512++;
		}
		if (calculatemax() == 1024)
		{
			time1024++;
		}
		if (calculatemax() == 2048)
		{
			time2048++;
		}
	}
	int sum1 = 0;
	long int sum2 = 0;
	for (i = 0; i < times; i++)
	{
		sum1 += p[i];
	}
	average = sum1 / times;
	printf("���Ե�ƽ�����ǣ�\n");
	printf("%d\n", average);
	printf("���Է��������ֵ�ǣ�\n");
	printf("%d\n", maximalpoint);
	printf("�������ֵ����ֵ�ǣ�\n");
	printf("%d\n", maximalnumber);
	printf("���Գɹ��Ĵ����ǣ�\n");
	printf("%d\n", successfultime);
	printf("�����������Ϊ64�Ĵ����ǣ�\n");
	printf("%d\n", time64);
	printf("�����������Ϊ128�Ĵ����ǣ�\n");
	printf("%d\n", time128);
	printf("�����������Ϊ256�Ĵ����ǣ�\n");
	printf("%d\n", time256);
	printf("�����������Ϊ512�Ĵ����ǣ�\n");
	printf("%d\n", time512);
	printf("�����������Ϊ1024�Ĵ����ǣ�\n");
	printf("%d\n", time1024);
	printf("�����������Ϊ2048�Ĵ����ǣ�\n");
	printf("%d\n", time2048);
}

/************************************AIģʽѡ���� **************************************/

void AIchoose()
{
	drawAIchoose();

	printf("��ѡ��һ��AI��\n");
	printf("AI No.1: 1\n");
	printf("AI No.2: 2\n");

	AIget();
	//scanf_s("%d", &AImodel);

	if (AImodel == 1)
		computerplay();
	if (AImodel == 2)
		computerplay2();
}


/************************************��ӭ���� **************************************/

void welcome() 
{
	printf("��ӭ�����ģʽ2048��\n");
	printf("��ѡ��һ��ģʽ��\n");
	printf("����ģʽ: A\n");
	printf("GPA ģʽ: B\n");
	printf("ʱ��ģʽ: C\n");
	printf(" AI��ս : D\n");
	printf("��Ʒ��Ա: E\n");
	printf("computercount1:F\n");
	printf("computercount2:G\n");
}

/************************************��Ϸ������ *************************************/

int main()
{
	welcome();
	choice = '\0';
	initgraph(590, 700, EW_SHOWCONSOLE);
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, _T("2048++"));

	while (true) {

		b = 0;
		M = 2048;
		point = 0;
		N = 4;
		GRID_NUM = 4;
		steptime = 100;

		again = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				a[i][j] = 0;
			}
		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				c[i][j] = 0;
			}
		}
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				d[i][j] = 0;
			}
		}
		acd2map();
		drawbegin();
		begin2model();

    //scanf_s("%c", &choice, 1);

		if (choice == 'A')
			classicmodel();
		if (choice == 'B')
			GPAmodel();
		if (choice == 'C')
			timemodel();
		if (choice == 'D')
			AIchoose();
		if (choice == 'E')
			statement();
		if (choice == 'F')
			computercount();
		if (choice == 'G')
			computercount2();

		if (again == 0) break;
		
	}
	_getch();
	closegraph();
	return 0;
}

