#include<stdio.h>			
#include<time.h>			
#include<windows.h>			
#include<stdlib.h>			
#include<conio.h>			
#include<mmsystem.h>
#define U 1
#define D 2
#define L 3 
#define R 4    
#define High 58                                         //��Ϸ��ͼ�ĸ� 
#define Width 26										//��Ϸ��ͼ�Ŀ� 

typedef struct snake 									//�ṹ�� 
{
    int x;				
    int y;					
    struct snake *next;		
}snake; 
int pattern;                                            //��Ϸģʽ 
int score=0,score1=0,score2=0;          				//����ģʽ�÷֣�˫��ģʽ���1�����2�÷� 
int add=10;			             						//ʳ��÷�
int HighScore = 0,HighScore1=0,HighScore2=0;			//����ģʽ��ʷ��¼��˫��ģʽ���1�����2��ʷ��¼ 
int status,status2;										//���1�����2��С�ߵ�ǰ��״̬
int musicStatus=1;										//���ֲ���״̬ 
int endgamestatus=0;									//��Ϸ���������
int sleeptime=200;										//ÿ�����е�ʱ����
snake *head,*head2;										//��ͷָ��
snake *food;											//ʳ��ָ��
snake *q,*p;											//�����ߵ�ʱ���õ���ָ��
HANDLE hOut;											//����̨���

void gotoxy(int x,int y);   
int color(int c);           
void draw();
void menu();          
void map();          
void grade();		
void snakebody();           
void createfood();          
void biteself();             
void knockwall();      
void speedup();				
void speeddown();			
void move();           
void control();     
void Lostdraw();            
void endgame();             
void choose();				
void File_out();
void File1_out();
void File2_out();            
void File_in();  
void File1_in();              
void File2_in();                         	
void explation();  
void about();        
void go(struct snake *nexthead,struct snake *food,struct snake *p,int pattern);

int main()                         							//������ 
{
	mciSendString("open 1.mp3 alias music1", NULL, 0, NULL);    //������ 
	mciSendString("play music1 repeat", NULL, 0, NULL); 		//�������� 
	system("mode con cols=120 lines=30");						//���ÿ���̨���
	draw();							        					//��ʼ�˵� 												
	menu();														//��ʼ�˵� 
	return 0;
}

void gotoxy(int x,int y)                                   //�ƶ����λ�� 
{
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

int color(int c)                                       	  //�ı�������ɫ 
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);        
	return 0;
}

void draw()                                               //���ƿ�ʼ�˵� 
{
	int i,j;
	color(14);
	printf("                            __                                                                           \n");
	printf("                    _______|  |________                             ___                                  \n");
	printf("                   |_______|  |________|                           |   |                                 \n");
	printf("                  _________|  |__________                          |   |                                 \n");
	printf("                 |   _________________   |                         |   |                                 \n");
	printf("                 |  |    __    __     |  |             ____________|   |____________                     \n");
	printf("                 |  |   |__/  /__|    |  |            |                             |                    \n");
	printf("                 |  |    ________     |  |            |___________        __________|                    \n");
	printf("                 |  |   |________|    |  |                        |      |                               \n");
	printf("                 |  |    __|__|__     |  |                       /   |    |                              \n");
	printf("                 |  |   |________|    |  |                      /   /  |    |                            \n");
	printf("                 |  |      |__|       |  |                    /    /    |    |                           \n");
	printf("                 |  |              __ |  |                 /     /        |    |                         \n");
	printf("                 |  |              | |   |              /     /              |     |                     \n");
	printf("                 |__|               |____|           /______/                  |______|                  \n");		
	gotoxy(43,18);
	color(10);
	printf("̰  ��  ��");
	color(14);          			
	for (i = 20; i <= 28; i++)   	                                    //���ƿ�� 
	{
		for (j = 27; j <= 74; j++) 
		{
			gotoxy(j, i);
			if (i == 20 || i == 28)
			{
				printf("-");
    		}
			else if (j == 27 || j == 74)
			{
				printf("|");
    		}
		}
	}
	color(7);
	gotoxy(35, 22);
	printf("1.����ģʽ");
	gotoxy(55, 22);
	printf("2.˫��ģʽ");
	gotoxy(35, 24);
	printf("3.����");
	gotoxy(55,24);
	printf("4.����");
	gotoxy(35,26);
	printf("5.�ر�����");
	gotoxy(55,26);
	printf("6.�˳���Ϸ"); 
	gotoxy(67,29);
	color(3);
	printf("̰���ߣ����ˡ�˫�˰棩  2.0.1  Copyright 2022 �߿���");
	color(7);
	gotoxy(29,29);
}

void menu()												  //��ʼ�˵�	 
{
	int n;     
	n=getch();          
	switch (n)
    {
    	case '1':										//����ģʽ 
			pattern=1;									
    		system("cls");
			map(); 	          
			snakebody();
			createfood();	
			control();
        	break;
    	case '2':										//˫��ģʽ 
			pattern=2;
			system("cls");
			map(); 	          
			snakebody();
			createfood();	
			control();
        	break;
    	case '3':					    				//��Ϸ���� 
  			explation();
		    break;
        case '4':										//���ڳ��� 
			about();
			break;
		case '5':										//���ֿ��� 
			if(musicStatus==1)
			{
				mciSendString("stop music1", NULL, 0, NULL);	
				musicStatus=0;
				gotoxy(35, 26);
				printf("5.������");	
				menu();
			} 
			if(musicStatus==0)
			{
				mciSendString("open 1.mp3 alias music1", NULL, 0, NULL);
				mciSendString("play music1 repeat", NULL, 0, NULL);	
				musicStatus=1;
				gotoxy(35, 26);
				printf("5.�ر�����");
				menu();
			}
			break;
		case '6':										//�˳���Ϸ 
			exit(0);
			break; 
		default:				
			system("cls");	
			draw();
			if(musicStatus==1)
			{
				gotoxy(35, 26);
				printf("5.�ر�����");	
			} 
			if(musicStatus==0)
			{
				gotoxy(35, 26);
				printf("5.������");
			}
			menu();
    }		
}

void map()                                               //���Ƶ�ͼ 
{
    int i,j;
    for(i=0;i<High;i+=2)	
    {
        gotoxy(i,0);
		color(12);		
        printf("��");
        gotoxy(i,26);
        printf("��");
    }
    for(i=1;i<Width;i++)		
    {
        gotoxy(0,i);
        printf("��");                        
        gotoxy(56,i);
        printf("��");        
    }
	for(i = 2;i<High-2;i+=2)
	{
		for(j = 1;j<Width;j++)
		{
			gotoxy(i,j);
			color(0);
			printf("��\n\n");
		}
	}			    				
	if(pattern==1)
	{
		File_out();	
		color(6);	
		gotoxy(63,3);
		printf("------------------");
		gotoxy(63,5);
		printf("------------------");
		gotoxy(63,4);
		printf("|");
		gotoxy(80,4);
		printf("|");	 
		gotoxy(64,4);			
		color(11);				
		printf("��ʷ��¼  %d",HighScore);	
		gotoxy(64,16);
		printf("�á� �� �� ���ֱ�����ߵ��ƶ�");
	}
	if(pattern==2)
	{
		File1_out();
		File2_out();
		color(6);	
		gotoxy(63,3);
		printf("--------------------------------------");
		gotoxy(63,5);
		printf("--------------------------------------");
		gotoxy(63,4);
		printf("|");
		gotoxy(100,4);
		printf("|");	 
		gotoxy(64,4);			
		color(11);				
		printf("��ʷ��¼  ���һ %d   ��Ҷ� %d",HighScore1,HighScore2);
		gotoxy(64,16);
		printf("������W A S D�ƶ��������á� �� �� ���ƶ�");
	}
	gotoxy(60,13);
	color(6);
	printf("------------------------------------");
	gotoxy(60,25);
	printf("------------------------------------");
	gotoxy(64,18);
	color(7);
	printf("����ײǽ������ҧ���Լ�");
	gotoxy(64,20);
	printf("Shift���٣�Ctrl����");
	gotoxy(64,22);
	printf("�ո����ͣ");
	gotoxy(64,24);
	printf("Esc���˳�");
}

void grade()                                              //��ͼ�Ҳ�ɼ� 
{
	if(pattern==1)
	{
		gotoxy(64,8);
		color(14);
		printf("��ǰ�÷�  %d  ",score);	
	}
	if(pattern==2)
	{
		gotoxy(64,8);
		color(14);
		printf("��ǰ�÷�  ���һ %d   ��Ҷ� %d",score1,score2);				
	}	
	color(3);
	gotoxy(64,14);
	printf("�Ե�ʳ��÷�  %d��",add);
}

void snakebody()                                         //������������� 
{
    snake *tail,*tail2;
    int i;
    tail=(snake*)malloc(sizeof(snake));		
	tail->x=24;				                                            //���ߵĳ�ʼλ�ã�24,5��
    tail->y=5;
    tail->next=NULL;
    for(i=1;i<=4;i++)                                                   //������������Ϊ5
    {
        head=(snake*)malloc(sizeof(snake)); 
        head->next=tail;    
        head->x=24+2*i;     
        head->y=5;
        tail=head;           	      
    }
    while(tail!=NULL)
    {
        gotoxy(tail->x,tail->y);
		color(7);
        printf("��");      
        tail=tail->next; 
    }
    
    if(pattern==2)
	{	
		tail2=(snake*)malloc(sizeof(snake));	
	    tail2->x=24;												//���ߵĳ�ʼλ�ã�24,10��
    	tail2->y=10;
		tail2->next=NULL;
		for(i=1;i<=4;i++)
		{	
			head2=(snake*)malloc(sizeof(snake)); 
			head2->next=tail2;    
			head2->x=24+2*i;     
			head2->y=10;
			tail2=head2;
		}
		while(tail2!=NULL&&pattern==2)
		{
        	gotoxy(tail2->x,tail2->y);
			color(10);
    		printf("��");      
			tail2=tail2->next; 
	   	}
    }
}

void createfood()                                       //����ʳ�� 
{
    snake *food_1;
    srand((unsigned)time(NULL));        	
flag:
	food_1=(snake*)malloc(sizeof(snake));   
    food_1->x=rand()%52+2;
	while((food_1->x%2)!=0)    				                           //��֤��Ϊż����ʹ��ʳ��������ͷ���룬Ȼ��ʳ����������������
    {
        food_1->x=rand()%52+2;              
    }
    food_1->y=rand()%24+1;					
    q=head;
    while(q!=NULL)
    {
        if(q->x==food_1->x && q->y==food_1->y)                          //�ж������Ƿ���ʳ���غ�
        {
            goto flag;      
        }
        q=q->next;
    }
    if(pattern==2)
	{
		p=head2;
    	while(p!=NULL)
    	{
        	if(p->x==food_1->x && p->y==food_1->y)                       //�ж������Ƿ���ʳ���غ�
        	{
            	goto flag;      
        	}
        	p=p->next;
    	}
	}
    gotoxy(food_1->x,food_1->y);
    food=food_1;
	color(14);
    printf("��"); 
}

void knockwall()                                        //�ж��Ƿ�ײǽ 
{
    if(head->x==0 || head->x==High-2 ||head->y==0 || head->y==Width) 
    {
        endgamestatus=1;        
        endgame();              
    }
    if(pattern==2)
	{
		if(head2->x==0 || head2->x==High-2 ||head2->y==0 || head2->y==Width) 
	    {
	    	endgamestatus=1;        
	        endgame();              
	    }
	}
}

void biteself()                                         //�ж��Ƿ�ҧ���Լ� 
{
    snake *self,*self2;            
    if(pattern==1)
	{
		self=head->next;        
    	while(self!=NULL)
    	{
        	if(self->x==head->x && self->y==head->y)    
        	{
            	endgamestatus=2; 
				endgame();      
       	 	}
        	self=self->next;
    	}
	}	
    if(pattern==2)
	{
		self=head->next;
		self2=head2->next;
    	while(self2!=NULL)
    	{
        	if((self2->x==head2->x && self2->y==head2->y)||(head->x==self2->x && head->y==self2->y))    
        	{
            	endgamestatus=2; 
				endgame();      
        	}
        	self2=self2->next;
    	}
    	while(self!=NULL)
	    {
	        if((self->x==head2->x && self->y==head2->y)||(head->x==self->x && head->y==self->y))    
	        {
	            endgamestatus=2; 
				endgame();      
	        }
	        self=self->next;
		}	
	}
}

void speedup()                                          //���� 
{
	if(add<30)
	{
		sleeptime=sleeptime-10;
		add=add+2;
    }
}

void speeddown()                                        //���� 
{
	if(add>10)               
    {
        sleeptime=sleeptime+30;     
        add=add-2;                  
    }
}

void go(struct snake *nexthead,struct snake *food,struct snake *q,int pattern)        //���ƶ� 
{
	if(nexthead->x==food->x && nexthead->y==food->y)	//�����һ��λ����ʳ�� 
	{
	   while(q!=NULL)
		{
			gotoxy(q->x,q->y);
			if(pattern==1)
			{
				color(7);
			}			
			if(pattern==2)
			{
				color(10);
			}
	    	printf("��");                               //ԭ��ʳ���λ�ã��ӡ񻻳ɡ�
			q=q->next;          		
		}
        score=score+add;
		if(pattern==1)
		{
			score2+=add;
		}
		if(pattern==2)
		{
			score1+=add;
		}        
	    createfood();
	}
	else                                                 //�����һ��λ��û��ʳ��
	{
	    while(q->next->next!=NULL)	
	    {
	    	gotoxy(q->x,q->y);
			if(pattern==1)
			{
				color(7);
			}			
			if(pattern==2)
			{
				color(10);
			}
	        printf("��");                                 //�����һλ�õ�����
	        q=q->next;              
	    }
	    gotoxy(q->next->x,q->next->y);
		color(0);
	    printf("��");                                    //��ԭ������β�ڵ� 
	    free(q->next);			
	    q->next=NULL;
	}
} 

void move()	                                           //�߸�������ƶ� 
{
    knockwall();
    biteself();
    snake * nexthead,*nexthead2;
    nexthead=(snake*)malloc(sizeof(snake));		
	if(status==U)
    {
        nexthead->x=head->x;        
        nexthead->y=head->y-1;						//����ǰ��ʱ��x���겻����y���������ƶ�-1 
        nexthead->next=head;
        head=nexthead;
        q=head;		
		go(nexthead,food,q,1);
    }
    else if(status==D)
    {
        nexthead->x=head->x;        
        nexthead->y=head->y+1;						//����ǰ��ʱ��x���겻����y���������ƶ�+1 
        nexthead->next=head;
        head=nexthead;
        q=head;
        go(nexthead,food,q,1);
    }
    else if(status==L)
    {
        nexthead->x=head->x-2;        				//����ǰ��ʱ��x���������ƶ�-2��y���겻��
        nexthead->y=head->y;
        nexthead->next=head;
        head=nexthead;
        q=head;
        go(nexthead,food,q,1);
    }
    else if(status==R)
    {
        nexthead->x=head->x+2;        				//����ǰ��ʱ��x���������ƶ�+2��y���겻��
        nexthead->y=head->y;
        nexthead->next=head;
        head=nexthead;
        q=head;
        go(nexthead,food,q,1);
    }
  	if(pattern==2)  
    {
    	nexthead2=(snake*)malloc(sizeof(snake));	
   		if(status2==U)
		{
			nexthead2->x=head2->x;        
			nexthead2->y=head2->y-1;
			nexthead2->next=head2;
			head2=nexthead2;
			p=head2;		
			go(nexthead2,food,p,2);				
	    }
	    else if(status2==D)
	    {
	        nexthead2->x=head2->x;        
	        nexthead2->y=head2->y+1;
	        nexthead2->next=head2;
	        head2=nexthead2;
	        p=head2;		
			go(nexthead2,food,p,2);	
	    }
	    else if(status2==L)
	    {
	        nexthead2->x=head2->x-2;        
	        nexthead2->y=head2->y;
	        nexthead2->next=head2;
			head2=nexthead2;
			p=head2;		
			go(nexthead2,food,p,2);	
	    }
	    else if(status2==R)
	    {
	        nexthead2->x=head2->x+2;        
			nexthead2->y=head2->y;
	        nexthead2->next=head2;
	        head2=nexthead2;
	        p=head2;		
			go(nexthead2,food,p,2);	
	    }
    }
}

void control()                                          //���̿��� 
{
	status=R;       									//��ʼ�������ƶ�
	status2=R;
    while(1)
    {
		grade();   
		if(GetAsyncKeyState(VK_UP) && status!=D)            //GetAsyncKeyState���������жϺ�������ʱָ���������״̬
	    {
            status=U;           							//����߲�������ǰ����ʱ�򣬰��ϼ���ִ������ǰ������    
		}
        else if(GetAsyncKeyState(VK_DOWN) && status!=U)     //����߲�������ǰ����ʱ�򣬰��¼���ִ������ǰ������
	    {
	        status=D;
	    }
	    else if(GetAsyncKeyState(VK_LEFT)&& status!=R)      //����߲�������ǰ����ʱ�򣬰������ִ������ǰ��
	    {
	        status=L;
	    }
	    else if(GetAsyncKeyState(VK_RIGHT)&& status!=L)     //����߲�������ǰ����ʱ�򣬰��Ҽ���ִ������ǰ��
	    {
	  	    status=R;
	    }
	    if(pattern==2)
	    {
	    	if(GetAsyncKeyState('W') && status2!=D)            
			{
			    status2=U;               
			}
			else if(GetAsyncKeyState('S') && status2!=U)     
		    {
		        status2=D;
			}
			else if(GetAsyncKeyState('A')&& status2!=R)      
			{
			    status2=L;
			}
			else if(GetAsyncKeyState('D')&& status2!=L)     
			{
				status2=R;
			}
	    }
        if(GetAsyncKeyState(VK_SPACE))						//���ո���ͣ
        {
            while(1)
			{
				Sleep(300); 
				if(GetAsyncKeyState(VK_SPACE))      		//�ٰ��ո�������ͣ
				{
					break;
				}
				if(GetAsyncKeyState(VK_ESCAPE))				//��Esc���˳� 
				{
					endgamestatus=3;
					endgame();
				}
			}       
        }
        else if(GetAsyncKeyState(VK_ESCAPE))
        {
            endgamestatus=3;    							//��esc����ֱ�ӵ���������
            endgame();
        }
        else if(GetAsyncKeyState(VK_SHIFT))    				//��shift��������
        {
            speedup();
        }
        else if(GetAsyncKeyState(VK_CONTROL))    			//��ctrl��������
        {
        	speeddown();
        }
        Sleep(sleeptime);
        move();
    }
}

void File_in()                                         	//����ģʽ���ݴ洢 
{
	FILE *fp;
	fp = fopen("����ģʽ.txt", "w+");       
	fprintf(fp, "%d", score);           
	fclose(fp);                         
}

void File1_in()                                         //˫��ģʽ���һ���ݴ洢 
{
	FILE *fp;
	fp = fopen("˫��ģʽ���һ.txt", "w+");       
	fprintf(fp, "%d", score1);           
	fclose(fp);                         
}

void File2_in()                                         //˫��ģʽ��Ҷ����ݴ洢 
{
	FILE *fp;
	fp = fopen("˫��ģʽ��Ҷ�.txt", "w+");       
	fprintf(fp, "%d", score2);           
	fclose(fp);                         
}

void File_out()                                         //����ģʽ���ݶ�ȡ 
{
	FILE *fp;
	fp = fopen("����ģʽ.txt", "a+");       
	fscanf(fp, "%d", &HighScore);       
	fclose(fp);                         
}
void File1_out()                                        //˫��ģʽ���һ���ݶ�ȡ 
{
	FILE *fp;
	fp = fopen("˫��ģʽ���һ.txt", "a+");       
	fscanf(fp, "%d", &HighScore1);       
	fclose(fp);                         
}
void File2_out()                                        //˫��ģʽ��Ҷ����ݶ�ȡ 
{
	FILE *fp;
	fp = fopen("˫��ģʽ��Ҷ�.txt", "a+");       
	fscanf(fp, "%d", &HighScore2);       
	fclose(fp);                         
}

void about()                                            //������Ϸ 
{
	int i,j;
	system("cls");
	color(14);
	for (i = 6; i <= 22; i++)   
	{
		for (j = 20; j <= 76; j++) 
		{
			gotoxy(j, i);
			if (i == 6 || i == 22) printf("-");
			else if (j == 20 || j == 75) printf("|");
		}
	}
	color(10);
	gotoxy(30,8);
	printf("�������ƣ�̰���߶��˰�");
	gotoxy(30,11);
	printf("�汾��Ϣ��2.0.1");
    gotoxy(30,14);
    printf("����ʱ�䣺2021��12��-2022��1��");
	gotoxy(30,17);
	printf("�����ߣ��߿���  8008121291");
	gotoxy(30,20);
	printf("        ���������  2110��");
	gotoxy(20,23);
	printf("�����������������"); 
	getch();              
	system("cls");
    draw();
	menu();
}
void explation()                                        //��Ϸ˵�� 
{
	int i,j;
    system("cls");
    color(15);
    gotoxy(44,3);
    printf("��Ϸ˵��");
    color(14);
    for (i = 6; i <= 22; i++)   
	{
		for (j = 20; j <= 76; j++)  
		{
			gotoxy(j, i);
			if (i == 6 || i == 22) printf("-");
			else if (j == 20 || j == 75) printf("|");
		}
	}
    color(10);
    gotoxy(30,8);
    printf("tip1: �����á������������ƶ�");
    gotoxy(30,9);
	printf("      ������W S A D �����ƶ�"); 
	color(7);
    gotoxy(30,11);
    printf("tip2: ��Shift�����٣���Ctrl������");
    color(3);
    gotoxy(30,14);
    printf("tip3: ��Ҫײ��ǽ����Ҫҧ���Լ�");
    color(11);
    gotoxy(30,17);
    printf("tip4: ���ո����ͣ��Ϸ���ٰ��ո������");
    color(4);
    gotoxy(30,20);
    printf("tip5: ��Esc���˳���Ϸ");
    color(14);
	gotoxy(20,23);
	printf("�����������������"); 
	getch();               
    system("cls");
    draw();
	menu();
}

void endgame()                                          //��Ϸ���� 
{
    system("cls");
    if(endgamestatus==1)
    {
		Lostdraw();
		gotoxy(39,9);
    	color(7);
		if(pattern==1)printf("��ײ��ǽ��  ��Ϸ������");
		else if(pattern==2)printf("����ײ��ǽ��  ��Ϸ������"); 
		mciSendString("close music1", NULL, 0, NULL);
		mciSendString("open 3.mp3 alias music3", NULL, 0, NULL);      
		mciSendString("play music3", NULL, 0, NULL);
    }
    if(endgamestatus==2)
    {
        Lostdraw();
        gotoxy(39,9);
    	color(7);
        if(pattern==1)printf("��ҧ���Լ���  ��Ϸ������");
        gotoxy(37,9);
		if(pattern==2)printf("����ҧ���Է���  ��Ϸ������"); 
       	mciSendString("close music1", NULL, 0, NULL);
		mciSendString("open 3.mp3 alias music3", NULL, 0, NULL);      
		mciSendString("play music3", NULL, 0, NULL);
    }
    if(endgamestatus==3)
    {
		Lostdraw();
		gotoxy(45,9);
    	color(7);
        printf("��Ϸ������");
        mciSendString("close music1", NULL, 0, NULL);
		mciSendString("open 3.mp3 alias music3", NULL, 0, NULL);      
		mciSendString("play music3", NULL, 0, NULL);
    }
    gotoxy(43,12);
    color(14);
    if(pattern==1)
	{
		printf("�����ֵ÷�Ϊ %d",score);
		if(score > HighScore)
		{
			color(10);
			gotoxy(43,16);
			printf("��ϲ������˼�¼��");
			File_in();
			mciSendString("close music3", NULL, 0, NULL);
			mciSendString("open 2.mp3 alias music2", NULL, 0, NULL);      
			mciSendString("play music2", NULL, 0, NULL);			
		}	    
	}
	if(pattern==2)
	{
		gotoxy(37,12);
		printf("���ֵ÷�  ���һ %d  ��Ҷ� %d",score1,score2);
		if(score1>HighScore1)
		{
			color(10);
			gotoxy(41,16);
			printf("��ϲ���һ�����˼�¼��");
			File1_in();
		}
		if(score2>HighScore2)
		{
			color(10);
			gotoxy(41,16);
			printf("��ϲ��Ҷ������˼�¼��");
			File2_in();
		}
		if(score1>HighScore1||score2>HighScore2)
		{
			mciSendString("close music3", NULL, 0, NULL);
			mciSendString("open 2.mp3 alias music2", NULL, 0, NULL);      
			mciSendString("play music2", NULL, 0, NULL);
		} 
	}
	choose();
}

void choose()                                          	//�������ѡ�� 
{
	int n;
	gotoxy(30,23);
	color(12);
	printf("����һ�� [1]");
	gotoxy(55,23);
	printf("�˳���Ϸ [2]");
	n=getch(); 
    switch (n)
    {
	case '1':
		system("cls");
		mciSendString("close music2", NULL, 0, NULL);
		mciSendString("close music3", NULL, 0, NULL);
		score=0,score1=0,score2=0;                			//��������
		sleeptime=200;			
		add = 10;				
		draw();                 
		if(musicStatus==1)
		{
			mciSendString("open 1.mp3 alias music1", NULL, 0, NULL);
			mciSendString("play music1 repeat", NULL, 0, NULL); 
			gotoxy(35, 26);
			printf("5.�ر�����");	
		}
		if(musicStatus==0)
		{
			gotoxy(35, 26);
			printf("5.������");	
		}
		menu();
		break;
	case '2':
		exit(0);                							//�˳���Ϸ
		break;
	default:
		choose();
		break;
		
	}
}

void Lostdraw()                                       	//�������� 
{
	system("cls");
	int i;
	gotoxy(17,5);
	color(15);
	printf("******************************************************************");	
	for(i = 6;i<=19;i++)													
	{
		gotoxy(17,i);
		printf("*");
		gotoxy(82,i);
		printf("*");
	}
	gotoxy(17,20);
	printf("******************************************************************");	
}
