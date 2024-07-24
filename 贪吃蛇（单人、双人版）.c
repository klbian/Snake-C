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
#define High 58                                         //游戏地图的高 
#define Width 26										//游戏地图的宽 

typedef struct snake 									//结构体 
{
    int x;				
    int y;					
    struct snake *next;		
}snake; 
int pattern;                                            //游戏模式 
int score=0,score1=0,score2=0;          				//单人模式得分，双人模式玩家1、玩家2得分 
int add=10;			             						//食物得分
int HighScore = 0,HighScore1=0,HighScore2=0;			//单人模式历史记录，双人模式玩家1、玩家2历史记录 
int status,status2;										//玩家1、玩家2的小蛇的前进状态
int musicStatus=1;										//音乐播放状态 
int endgamestatus=0;									//游戏结束的情况
int sleeptime=200;										//每次运行的时间间隔
snake *head,*head2;										//蛇头指针
snake *food;											//食物指针
snake *q,*p;											//遍历蛇的时候用到的指针
HANDLE hOut;											//控制台句柄

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

int main()                         							//主函数 
{
	mciSendString("open 1.mp3 alias music1", NULL, 0, NULL);    //打开音乐 
	mciSendString("play music1 repeat", NULL, 0, NULL); 		//播放音乐 
	system("mode con cols=120 lines=30");						//设置控制台宽高
	draw();							        					//开始菜单 												
	menu();														//开始菜单 
	return 0;
}

void gotoxy(int x,int y)                                   //移动光标位置 
{
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

int color(int c)                                       	  //改变字体颜色 
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);        
	return 0;
}

void draw()                                               //绘制开始菜单 
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
	printf("贪  吃  蛇");
	color(14);          			
	for (i = 20; i <= 28; i++)   	                                    //绘制框框 
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
	printf("1.单人模式");
	gotoxy(55, 22);
	printf("2.双人模式");
	gotoxy(35, 24);
	printf("3.帮助");
	gotoxy(55,24);
	printf("4.关于");
	gotoxy(35,26);
	printf("5.关闭音乐");
	gotoxy(55,26);
	printf("6.退出游戏"); 
	gotoxy(67,29);
	color(3);
	printf("贪吃蛇（单人、双人版）  2.0.1  Copyright 2022 边凯伦");
	color(7);
	gotoxy(29,29);
}

void menu()												  //开始菜单	 
{
	int n;     
	n=getch();          
	switch (n)
    {
    	case '1':										//单人模式 
			pattern=1;									
    		system("cls");
			map(); 	          
			snakebody();
			createfood();	
			control();
        	break;
    	case '2':										//双人模式 
			pattern=2;
			system("cls");
			map(); 	          
			snakebody();
			createfood();	
			control();
        	break;
    	case '3':					    				//游戏帮助 
  			explation();
		    break;
        case '4':										//关于程序 
			about();
			break;
		case '5':										//音乐控制 
			if(musicStatus==1)
			{
				mciSendString("stop music1", NULL, 0, NULL);	
				musicStatus=0;
				gotoxy(35, 26);
				printf("5.打开音乐");	
				menu();
			} 
			if(musicStatus==0)
			{
				mciSendString("open 1.mp3 alias music1", NULL, 0, NULL);
				mciSendString("play music1 repeat", NULL, 0, NULL);	
				musicStatus=1;
				gotoxy(35, 26);
				printf("5.关闭音乐");
				menu();
			}
			break;
		case '6':										//退出游戏 
			exit(0);
			break; 
		default:				
			system("cls");	
			draw();
			if(musicStatus==1)
			{
				gotoxy(35, 26);
				printf("5.关闭音乐");	
			} 
			if(musicStatus==0)
			{
				gotoxy(35, 26);
				printf("5.打开音乐");
			}
			menu();
    }		
}

void map()                                               //绘制地图 
{
    int i,j;
    for(i=0;i<High;i+=2)	
    {
        gotoxy(i,0);
		color(12);		
        printf("■");
        gotoxy(i,26);
        printf("■");
    }
    for(i=1;i<Width;i++)		
    {
        gotoxy(0,i);
        printf("■");                        
        gotoxy(56,i);
        printf("■");        
    }
	for(i = 2;i<High-2;i+=2)
	{
		for(j = 1;j<Width;j++)
		{
			gotoxy(i,j);
			color(0);
			printf("■\n\n");
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
		printf("历史记录  %d",HighScore);	
		gotoxy(64,16);
		printf("用↑ ↓ ← →分别控制蛇的移动");
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
		printf("历史记录  玩家一 %d   玩家二 %d",HighScore1,HighScore2);
		gotoxy(64,16);
		printf("青蛇用W A S D移动，白蛇用↑ ↓ ← →移动");
	}
	gotoxy(60,13);
	color(6);
	printf("------------------------------------");
	gotoxy(60,25);
	printf("------------------------------------");
	gotoxy(64,18);
	color(7);
	printf("不能撞墙，不能咬到自己");
	gotoxy(64,20);
	printf("Shift加速，Ctrl减速");
	gotoxy(64,22);
	printf("空格键暂停");
	gotoxy(64,24);
	printf("Esc键退出");
}

void grade()                                              //地图右侧成绩 
{
	if(pattern==1)
	{
		gotoxy(64,8);
		color(14);
		printf("当前得分  %d  ",score);	
	}
	if(pattern==2)
	{
		gotoxy(64,8);
		color(14);
		printf("当前得分  玩家一 %d   玩家二 %d",score1,score2);				
	}	
	color(3);
	gotoxy(64,14);
	printf("吃到食物得分  %d分",add);
}

void snakebody()                                         //用链表绘制蛇身 
{
    snake *tail,*tail2;
    int i;
    tail=(snake*)malloc(sizeof(snake));		
	tail->x=24;				                                            //白蛇的初始位置（24,5）
    tail->y=5;
    tail->next=NULL;
    for(i=1;i<=4;i++)                                                   //设置蛇身，长度为5
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
        printf("■");      
        tail=tail->next; 
    }
    
    if(pattern==2)
	{	
		tail2=(snake*)malloc(sizeof(snake));	
	    tail2->x=24;												//青蛇的初始位置（24,10）
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
    		printf("■");      
			tail2=tail2->next; 
	   	}
    }
}

void createfood()                                       //创造食物 
{
    snake *food_1;
    srand((unsigned)time(NULL));        	
flag:
	food_1=(snake*)malloc(sizeof(snake));   
    food_1->x=rand()%52+2;
	while((food_1->x%2)!=0)    				                           //保证其为偶数，使得食物能与蛇头对齐，然后食物会出现在网格线上
    {
        food_1->x=rand()%52+2;              
    }
    food_1->y=rand()%24+1;					
    q=head;
    while(q!=NULL)
    {
        if(q->x==food_1->x && q->y==food_1->y)                          //判断蛇身是否与食物重合
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
        	if(p->x==food_1->x && p->y==food_1->y)                       //判断蛇身是否与食物重合
        	{
            	goto flag;      
        	}
        	p=p->next;
    	}
	}
    gotoxy(food_1->x,food_1->y);
    food=food_1;
	color(14);
    printf("●"); 
}

void knockwall()                                        //判断是否撞墙 
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

void biteself()                                         //判断是否咬到自己 
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

void speedup()                                          //加速 
{
	if(add<30)
	{
		sleeptime=sleeptime-10;
		add=add+2;
    }
}

void speeddown()                                        //减速 
{
	if(add>10)               
    {
        sleeptime=sleeptime+30;     
        add=add-2;                  
    }
}

void go(struct snake *nexthead,struct snake *food,struct snake *q,int pattern)        //蛇移动 
{
	if(nexthead->x==food->x && nexthead->y==food->y)	//如果下一个位置有食物 
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
	    	printf("■");                               //原来食物的位置，从●换成◆
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
	else                                                 //如果下一个位置没有食物
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
	        printf("■");                                 //输出下一位置的蛇身
	        q=q->next;              
	    }
	    gotoxy(q->next->x,q->next->y);
		color(0);
	    printf("■");                                    //把原来的蛇尾遮掉 
	    free(q->next);			
	    q->next=NULL;
	}
} 

void move()	                                           //蛇各方向的移动 
{
    knockwall();
    biteself();
    snake * nexthead,*nexthead2;
    nexthead=(snake*)malloc(sizeof(snake));		
	if(status==U)
    {
        nexthead->x=head->x;        
        nexthead->y=head->y-1;						//向上前进时，x坐标不动，y坐标向上移动-1 
        nexthead->next=head;
        head=nexthead;
        q=head;		
		go(nexthead,food,q,1);
    }
    else if(status==D)
    {
        nexthead->x=head->x;        
        nexthead->y=head->y+1;						//向下前进时，x坐标不动，y坐标向下移动+1 
        nexthead->next=head;
        head=nexthead;
        q=head;
        go(nexthead,food,q,1);
    }
    else if(status==L)
    {
        nexthead->x=head->x-2;        				//向左前进时，x坐标向左移动-2，y坐标不动
        nexthead->y=head->y;
        nexthead->next=head;
        head=nexthead;
        q=head;
        go(nexthead,food,q,1);
    }
    else if(status==R)
    {
        nexthead->x=head->x+2;        				//向右前进时，x坐标向右移动+2，y坐标不动
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

void control()                                          //键盘控制 
{
	status=R;       									//初始蛇向右移动
	status2=R;
    while(1)
    {
		grade();   
		if(GetAsyncKeyState(VK_UP) && status!=D)            //GetAsyncKeyState函数用来判断函数调用时指定虚拟键的状态
	    {
            status=U;           							//如果蛇不是向下前进的时候，按上键，执行向上前进操作    
		}
        else if(GetAsyncKeyState(VK_DOWN) && status!=U)     //如果蛇不是向上前进的时候，按下键，执行向下前进操作
	    {
	        status=D;
	    }
	    else if(GetAsyncKeyState(VK_LEFT)&& status!=R)      //如果蛇不是向右前进的时候，按左键，执行向左前进
	    {
	        status=L;
	    }
	    else if(GetAsyncKeyState(VK_RIGHT)&& status!=L)     //如果蛇不是向左前进的时候，按右键，执行向右前进
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
        if(GetAsyncKeyState(VK_SPACE))						//按空格暂停
        {
            while(1)
			{
				Sleep(300); 
				if(GetAsyncKeyState(VK_SPACE))      		//再按空格键解除暂停
				{
					break;
				}
				if(GetAsyncKeyState(VK_ESCAPE))				//按Esc键退出 
				{
					endgamestatus=3;
					endgame();
				}
			}       
        }
        else if(GetAsyncKeyState(VK_ESCAPE))
        {
            endgamestatus=3;    							//按esc键，直接到结束界面
            endgame();
        }
        else if(GetAsyncKeyState(VK_SHIFT))    				//按shift键，加速
        {
            speedup();
        }
        else if(GetAsyncKeyState(VK_CONTROL))    			//按ctrl键，减速
        {
        	speeddown();
        }
        Sleep(sleeptime);
        move();
    }
}

void File_in()                                         	//单人模式数据存储 
{
	FILE *fp;
	fp = fopen("单人模式.txt", "w+");       
	fprintf(fp, "%d", score);           
	fclose(fp);                         
}

void File1_in()                                         //双人模式玩家一数据存储 
{
	FILE *fp;
	fp = fopen("双人模式玩家一.txt", "w+");       
	fprintf(fp, "%d", score1);           
	fclose(fp);                         
}

void File2_in()                                         //双人模式玩家二数据存储 
{
	FILE *fp;
	fp = fopen("双人模式玩家二.txt", "w+");       
	fprintf(fp, "%d", score2);           
	fclose(fp);                         
}

void File_out()                                         //单人模式数据读取 
{
	FILE *fp;
	fp = fopen("单人模式.txt", "a+");       
	fscanf(fp, "%d", &HighScore);       
	fclose(fp);                         
}
void File1_out()                                        //双人模式玩家一数据读取 
{
	FILE *fp;
	fp = fopen("双人模式玩家一.txt", "a+");       
	fscanf(fp, "%d", &HighScore1);       
	fclose(fp);                         
}
void File2_out()                                        //双人模式玩家二数据读取 
{
	FILE *fp;
	fp = fopen("双人模式玩家二.txt", "a+");       
	fscanf(fp, "%d", &HighScore2);       
	fclose(fp);                         
}

void about()                                            //关于游戏 
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
	printf("程序名称：贪吃蛇多人版");
	gotoxy(30,11);
	printf("版本信息：2.0.1");
    gotoxy(30,14);
    printf("开发时间：2021年12月-2022年1月");
	gotoxy(30,17);
	printf("开发者：边凯伦  8008121291");
	gotoxy(30,20);
	printf("        计算机Ⅱ类  2110班");
	gotoxy(20,23);
	printf("按任意键返回主界面"); 
	getch();              
	system("cls");
    draw();
	menu();
}
void explation()                                        //游戏说明 
{
	int i,j;
    system("cls");
    color(15);
    gotoxy(44,3);
    printf("游戏说明");
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
    printf("tip1: 白蛇用↑↓←→控制移动");
    gotoxy(30,9);
	printf("      青蛇用W S A D 控制移动"); 
	color(7);
    gotoxy(30,11);
    printf("tip2: 按Shift键加速，按Ctrl键减速");
    color(3);
    gotoxy(30,14);
    printf("tip3: 不要撞到墙，不要咬到自己");
    color(11);
    gotoxy(30,17);
    printf("tip4: 按空格键暂停游戏，再按空格键继续");
    color(4);
    gotoxy(30,20);
    printf("tip5: 按Esc键退出游戏");
    color(14);
	gotoxy(20,23);
	printf("按任意键返回主界面"); 
	getch();               
    system("cls");
    draw();
	menu();
}

void endgame()                                          //游戏结束 
{
    system("cls");
    if(endgamestatus==1)
    {
		Lostdraw();
		gotoxy(39,9);
    	color(7);
		if(pattern==1)printf("您撞到墙了  游戏结束！");
		else if(pattern==2)printf("你们撞到墙了  游戏结束！"); 
		mciSendString("close music1", NULL, 0, NULL);
		mciSendString("open 3.mp3 alias music3", NULL, 0, NULL);      
		mciSendString("play music3", NULL, 0, NULL);
    }
    if(endgamestatus==2)
    {
        Lostdraw();
        gotoxy(39,9);
    	color(7);
        if(pattern==1)printf("您咬到自己了  游戏结束！");
        gotoxy(37,9);
		if(pattern==2)printf("你们咬到对方了  游戏结束！"); 
       	mciSendString("close music1", NULL, 0, NULL);
		mciSendString("open 3.mp3 alias music3", NULL, 0, NULL);      
		mciSendString("play music3", NULL, 0, NULL);
    }
    if(endgamestatus==3)
    {
		Lostdraw();
		gotoxy(45,9);
    	color(7);
        printf("游戏结束！");
        mciSendString("close music1", NULL, 0, NULL);
		mciSendString("open 3.mp3 alias music3", NULL, 0, NULL);      
		mciSendString("play music3", NULL, 0, NULL);
    }
    gotoxy(43,12);
    color(14);
    if(pattern==1)
	{
		printf("您本轮得分为 %d",score);
		if(score > HighScore)
		{
			color(10);
			gotoxy(43,16);
			printf("恭喜你打破了记录！");
			File_in();
			mciSendString("close music3", NULL, 0, NULL);
			mciSendString("open 2.mp3 alias music2", NULL, 0, NULL);      
			mciSendString("play music2", NULL, 0, NULL);			
		}	    
	}
	if(pattern==2)
	{
		gotoxy(37,12);
		printf("本轮得分  玩家一 %d  玩家二 %d",score1,score2);
		if(score1>HighScore1)
		{
			color(10);
			gotoxy(41,16);
			printf("恭喜玩家一打破了记录！");
			File1_in();
		}
		if(score2>HighScore2)
		{
			color(10);
			gotoxy(41,16);
			printf("恭喜玩家二打破了记录！");
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

void choose()                                          	//结束后的选择 
{
	int n;
	gotoxy(30,23);
	color(12);
	printf("再来一局 [1]");
	gotoxy(55,23);
	printf("退出游戏 [2]");
	n=getch(); 
    switch (n)
    {
	case '1':
		system("cls");
		mciSendString("close music2", NULL, 0, NULL);
		mciSendString("close music3", NULL, 0, NULL);
		score=0,score1=0,score2=0;                			//分数归零
		sleeptime=200;			
		add = 10;				
		draw();                 
		if(musicStatus==1)
		{
			mciSendString("open 1.mp3 alias music1", NULL, 0, NULL);
			mciSendString("play music1 repeat", NULL, 0, NULL); 
			gotoxy(35, 26);
			printf("5.关闭音乐");	
		}
		if(musicStatus==0)
		{
			gotoxy(35, 26);
			printf("5.打开音乐");	
		}
		menu();
		break;
	case '2':
		exit(0);                							//退出游戏
		break;
	default:
		choose();
		break;
		
	}
}

void Lostdraw()                                       	//结束界面 
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
