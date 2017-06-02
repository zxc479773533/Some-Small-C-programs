//----------------------------------------//
//           ����ʱ�䣺2017.2.9��          //
//                                        //
//                ̰������Ϸ               //
//----------------------------------------// 
#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>

/*�ṹ������*/
struct snk//�����ߵ�����
{
	int x;
	int y;
	struct snk *link;
};

/*ȫ�ֱ���*/
int food[2];
int life;
int model;
int point;
int level;

/*����������*/
void goto_xy(int x, int y);//��λ���λ�õ�ָ������
void creatFood(struct snk *L);//����ʳ��
void drawPoint(int x, int y);//��ĳ�����ߵ�����
void drawFood(int x, int y);//��ĳ����ʳ��
void drawMap(struct snk *L, int *food);//���Ƶ�ͼ���ߺ�ʳ��
int keydown(int z);//��ȡ��������
void move(struct snk *L, int *food, int z);//�ƶ��ߵ�λ��

/*������д��*/
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
	printf("���ķ�����");
	goto_xy(50, 5);
	printf("%d", point);
	goto_xy(45, 11);
	printf("��ǰ�ȼ���");
	goto_xy(48, 13);
	if (model == 1) {
		printf("��ͨģʽ");
		goto_xy(45, 15);
		printf("�ƶ��ٶȣ�");
		goto_xy(48, 17);
		printf("����");
	}
	else {
		printf("�� %d ��", level);
		goto_xy(45, 15);
		printf("�ƶ��ٶȣ�");
		goto_xy(48, 17);
		switch (level) {
		case 1 :
			printf("����");
			break;
		case 2:
			printf("����");
			break;
		case 3:
			printf("����");
			break;
		case 4:
			printf("�ɿ�");
			break;
		case 5:
			printf("���");
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

/*������*/
int main(void) {

	system("mode con cols=62 lines=32");//���ô����С

	/*��Ϸ��ʼ����*/

	int j;
	printf("##############################################################\n");
	printf("##############################################################\n");
	for (j = 2; j <= 26; j++)
		printf("##                                                          ##\n");
	printf("##  tip:�뽫���뷨�л���Ӣ�Ľ�����Ϸ��By:��Խ               ##\n");
	printf("##############################################################\n");
	printf("##############################################################\n");
		/*��ӡ����ȵ�*/
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
	printf("������ƣ�"), goto_xy(20, 19);
	printf("  w �� s �� a �� d ��"), goto_xy(20, 21);
	printf("��1��2ѡ��ģʽ��"), goto_xy(20, 23);
	printf("    1 �� һ��ģʽ"), goto_xy(20, 24);
	printf("    2 �� ��սģʽ"), goto_xy(20, 25);
	printf("����ѡ�� ");
	scanf("%d", &model);
	char t = 'y';
	/*��Ϸ��ѭ��*/
	while (t == 'y' || t == 'Y') {
		/*��Ϸ��ʼ��*/

		life = 1;//����ֵ
		point = 0;//����
		level = 1;//�ȼ�
		int z = 4;//��ʼ�������ƶ�
		struct snk *snake;//������ͷ
		struct snk *body;//�����ߵ�������
		snake = (struct snk *)malloc(sizeof(struct snk));
		snake->x = 21, snake->y = 11;
		snake->link = (struct snk *)malloc(sizeof(struct snk));
		snake->link->x = 20, snake->link->y = 11;
		snake->link->link = (struct snk *)malloc(sizeof(struct snk));
		snake->link->link->x = 19, snake->link->link->y = 11;
		snake->link->link->link = (struct snk *)malloc(sizeof(struct snk));
		snake->link->link->link->x = 18, snake->link->link->link->y = 11;
		snake->link->link->link->link = NULL;//����Ϊ4�ĳ�ʼ����
		creatFood(snake);

		/*��Ϸ��ѭ��*/

		while (1) {
			system("cls");
			drawMap(snake, food);//����ͼ��
			z = keydown(z);//��ȡ����
			move(snake, food, z);//�ƶ�����
			if (snake->x == 0 || snake->x == 42 || snake->y == 0 || snake->y == 22)
				life = 0;//�ж����Ƿ�ײǽ
			body = snake->link;
			while (body) {
				if (body->x == snake->x && body->y == snake->y)
					life = 0;
				body = body->link;
			}//�ж����Ƿ�ײ���Լ�
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

		/*��Ϸ��ѭ��*/

		goto_xy(0, 23);
		printf("�����ˣ���������սһ����-----------Y/N  ");
		char ch;
		while ((ch = getchar()) != '\n' && ch != EOF);
		scanf("%c", &t);//��ȡ��һ�εľ���
	}
	return 0;
}