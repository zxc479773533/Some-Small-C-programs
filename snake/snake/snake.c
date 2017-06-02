//----------------------------------------//
//           制作时间：2017.2.9晚          //
//                                        //
//                贪吃蛇游戏               //
//----------------------------------------// 
#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>

/*结构定义区*/
struct snk//定义蛇的身体
{
	int x;
	int y;
	struct snk *link;
};

/*全局变量*/
int food[2];
int life;
int model;
int point;
int level;

/*函数定义区*/
void goto_xy(int x, int y);//定位光标位置到指定坐标
void creatFood(struct snk *L);//创建食物
void drawPoint(int x, int y);//在某处画蛇的身子
void drawFood(int x, int y);//在某处画食物
void drawMap(struct snk *L, int *food);//绘制地图，蛇和食物
int keydown(int z);//获取键盘输入
void move(struct snk *L, int *food, int z);//移动蛇的位置

/*函数编写区*/
void goto_xy(int x, int y) {
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x,y };
	SetConsoleCursorPosition(hOut, pos);
}

void creatFood(struct snk *L) {
	int flag = 0;
	struct snk *p;
	srand(clock(NULL));
	p = L;
	while (flag != 1) {
		food[0] = rand() % 40 + 1;
		food[1] = rand() % 20 + 1;
		flag = 1;
		while (p) {
			if (p->x == food[0] && p->y == food[1]) {
				flag = 0;
			}
			p = p->link;
		}
	}
}

void drawPoint(int x, int y) {
	goto_xy(x, y);
	printf("#");
}

void drawFood(int x, int y) {
	goto_xy(x, y);
	printf("@");
	goto_xy(0, 23);
}

void drawMap(struct snk *L, int *food) {
	int i;
	struct snk *p;
	p = L;
	printf("##############################################################\n");
	for (i = 2; i <= 8; i++)
		printf("#                                        #                   #\n");
	printf("#                                        #####################\n");
	for (i = 10; i <= 21; i++)
		printf("#                                        #                   #\n");
	printf("##############################################################\n");
	goto_xy(45, 3);
	printf("您的分数：");
	goto_xy(50, 5);
	printf("%d", point);
	goto_xy(45, 11);
	printf("当前等级：");
	goto_xy(48, 13);
	if (model == 1) {
		printf("普通模式");
		goto_xy(45, 15);
		printf("移动速度：");
		goto_xy(48, 17);
		printf("正常");
	}
	else {
		printf("第 %d 级", level);
		goto_xy(45, 15);
		printf("移动速度：");
		goto_xy(48, 17);
		switch (level) {
		case 1 :
			printf("慢速");
			break;
		case 2:
			printf("正常");
			break;
		case 3:
			printf("快速");
			break;
		case 4:
			printf("飞快");
			break;
		case 5:
			printf("疯狂");
			break;
		}
	}
	while (p) {
		drawPoint(p->x, p->y);
		p = p->link;
	}
	drawFood(food[0], food[1]);
}

int keydown(int z) {
	char ch;
	if (_kbhit()) {
		ch = getch();
		switch (ch) {
		case 'w':
			if (z != 2)
				z = 1;
			break;
		case 's':
			if (z != 1)
				z = 2;
			break;
		case 'a':
			if (z != 4)
				z = 3;
			break;
		case 'd':
			if (z != 3)
				z = 4;
			break;
		default:
			break;
		}
	}
	return z;
}

void move(struct snk *L, int *food, int z) {
	struct snk *p, *q;
	p = (struct snk *)malloc(sizeof(struct snk));
	p->x = L->x, p->y = L->y;
	p->link = L->link;
	switch (z) {
	case 1:
		L->y -= 1;
		break;
	case 2:
		L->y += 1;
		break;
	case 3:
		L->x -= 1;
		break;
	case 4:
		L->x += 1;
		break;
	default:
		break;
	}
	L->link = p;
	if (L->x == food[0] && L->y == food[1]) {
		point += 100;
		int flag = 0;
		struct snk *r;
		srand(clock(NULL));
		r = L;
		while (flag != 1) {
			food[0] = rand() % 40 + 1;
			food[1] = rand() % 20 + 1;
			flag = 1;
			while (r) {
				if (r->x == food[0] && r->y == food[1]) {
					flag = 0;
				}
				r =r->link;
			}
		}
	}
	else {
		q = L;
		while (q->link->link)
			q = q->link;
		free(q->link);
		q->link = NULL;
	}
}

/*主函数*/
int main(void) {

	system("mode con cols=62 lines=32");//设置窗体大小

	/*游戏开始界面*/

	int j;
	printf("##############################################################\n");
	printf("##############################################################\n");
	for (j = 2; j <= 26; j++)
		printf("##                                                          ##\n");
	printf("##  tip:请将输入法切换成英文进行游戏。By:潘越               ##\n");
	printf("##############################################################\n");
	printf("##############################################################\n");
		/*打印标题等等*/
	goto_xy(0, 4);
	printf("##         #                 #                     #        ##\n");
	printf("##       #   #              #             #        #        ##\n");
	printf("##     #  ###  #           # #####        #     #######     ##\n");
	printf("##         #        ##### #             #####   #     #     ##\n");
	printf("##       #####      #   #    #####     #  #  #     #        ##\n");
	printf("##      #  #  #     #   #       #      #  #  #     #  #     ##\n");
	printf("##      #  #  #     #   #      #       #  #  #     # #      ##\n");
	printf("##      #  #  #     #####     #         #####      ##       ##\n");
	printf("##        # #                #            #        #        ##\n");
	printf("##       #   #              #     #       #  #     #    #   ##\n");
	printf("##      #     #              #####     #######     #####    ##\n");
	goto_xy(20, 17);
	printf("方向控制："), goto_xy(20, 19);
	printf("  w 上 s 下 a 左 d 右"), goto_xy(20, 21);
	printf("按1或2选择模式："), goto_xy(20, 23);
	printf("    1 → 一般模式"), goto_xy(20, 24);
	printf("    2 → 挑战模式"), goto_xy(20, 25);
	printf("您的选择： ");
	scanf("%d", &model);
	char t = 'y';
	/*游戏大循环*/
	while (t == 'y' || t == 'Y') {
		/*游戏初始化*/

		life = 1;//生命值
		point = 0;//分数
		level = 1;//等级
		int z = 4;//开始蛇向右移动
		struct snk *snake;//定义蛇头
		struct snk *body;//遍历蛇的身体用
		snake = (struct snk *)malloc(sizeof(struct snk));
		snake->x = 21, snake->y = 11;
		snake->link = (struct snk *)malloc(sizeof(struct snk));
		snake->link->x = 20, snake->link->y = 11;
		snake->link->link = (struct snk *)malloc(sizeof(struct snk));
		snake->link->link->x = 19, snake->link->link->y = 11;
		snake->link->link->link = (struct snk *)malloc(sizeof(struct snk));
		snake->link->link->link->x = 18, snake->link->link->link->y = 11;
		snake->link->link->link->link = NULL;//长度为4的初始蛇身
		creatFood(snake);

		/*游戏主循环*/

		while (1) {
			system("cls");
			drawMap(snake, food);//绘制图形
			z = keydown(z);//获取输入
			move(snake, food, z);//移动蛇身
			if (snake->x == 0 || snake->x == 42 || snake->y == 0 || snake->y == 22)
				life = 0;//判定蛇是否撞墙
			body = snake->link;
			while (body) {
				if (body->x == snake->x && body->y == snake->y)
					life = 0;
				body = body->link;
			}//判定蛇是否撞到自己
			if (!life)
				break;
			if (point >= 600 && point < 1200)
				level = 2;
			else if (point >= 1200 && point < 2000)
				level = 3;
			else if (point >= 2000 && point < 2800)
				level = 4;
			else if (point >= 2800)
				level = 5;
			if (model == 1)
				level = 2;
			switch (level) {
			case 1:
				Sleep(400);
				break;
			case 2:
				Sleep(300);
				break;
			case 3:
				Sleep(200);
				break;
			case 4:
				Sleep(100);
				break;
			case 5:
				Sleep(50);
				break;
			}
		}

		/*游戏主循环*/

		goto_xy(0, 23);
		printf("你输了！你想再挑战一次吗？-----------Y/N  ");
		char ch;
		while ((ch = getchar()) != '\n' && ch != EOF);
		scanf("%c", &t);//读取下一次的决定
	}
	return 0;
}