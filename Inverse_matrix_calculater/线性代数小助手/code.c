#include <stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<math.h>

/*全局变量*/
int A = 0;//行列式的结果
int sum = 0;//行列式的值

/*函数定义*/
void goto_xy(int x, int y);//移动光标
void exchange(int *a, int *b);//交换两个数的值
void clean(int *p);//清空数组
int getp(int *p, int n);//计算p的逆序数
void getA(int *matrix, int * p, int counter, int n, int k);//计算行列式的值
void getAij(int *matrix,int *B, int i, int j, int n);//计算aij的代数余子式对应的行列式

/*函数编写*/
void goto_xy(int x, int y) {//移动光标
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x,y };
	SetConsoleCursorPosition(hOut, pos);
}

void exchange(int *a, int *b)  //交换两个数的值  
{
	int m = *a;
	*a = *b;
	*b = m;
}

void clean(int *p) {//清空数组
	int i = 0;
	for (i = 0; i < 6; i++)
		p[i] = 0;
}

int getp(int *p, int n) {//计算p的逆序数
	int i, j, k = 0;
	for (i = 0; i < n; i++) {
		for (j = 0; j < i; j++) {
			if (p[j] > p[i])//逆序数的定义
				k++;
		}
	}
	if ((k % 2) == 0)
		return 1;
	else
		return -1;
}

void getA(int *matrix, int *p, int counter, int n, int k) {//计算行列式的值
	int i, j;
	if (counter == n) {
		int ans = 1;
		for (i = 0; i < n; i++)
			ans *= *(matrix + i * k + p[i] - 1);
		sum += ans * getp(p, n);//将所有组合加起来
	}
	else {
		for (i = 1; i <= n; i++) {
			int ok = 1;
			for (j = 0; j < counter && ok; j++) {
				if (p[j] == i)//检测i是否出现
					ok = 0;
			}
			if (ok) {
				p[counter] = i;//对数的排列赋值
				getA(matrix, p, counter + 1, n, k);
			}
		}
	}
}

void getAij(int *matrix, int *B, int i, int j, int n) {//计算aij的代数余子式对应的行列式
	double Aij;
	int x, y, k = 0, l = 0;
	double c;//暂时储存
	for (x = 0; x < i; x++) {//左上方保留
		for (y = 0; y < j; y++) {
			c = *(matrix + x * 6 + y);
			*(B + x * 5 +y) = c;
		}
	}
	for (x = i; x < n - 1; x++) {//左下方向上移动一行
		for (y = 0; y < j; y++) {
			c = *(matrix + (x + 1) * 6 + y);
			*(B + x * 5 + y) = c;
		}
	}
	for (x = 0; x < i; x++) {//右上方向左移动一列
		for (y = j; y < n - 1; y++) {
			c = *(matrix + x * 6 + y + 1);
			*(B + x * 5 + y) = c;
		}
	}
	for (x = i; x < n - 1; x++) {//右下方向左上方移动
		for (y = j; y < n - 1; y++) {
			c = *(matrix + (x + 1) * 6 + y + 1);
			*(B + x * 5 + y) = c;
		}
	}
}

int main(void) {
	char re = 'Y';
	while (re == 'y' || re == 'Y') {
		/*介绍界面*/
		printf("##########################################\n");
		printf("## 欢迎使用线性代数小助手               ##\n");
		printf("##                                      ##\n");
		printf("## 它可以帮你解决作业中常见的令人头疼的 ##\n");
		printf("## 逆矩阵计算和行列式的问题             ##\n");
		printf("##                                      ##\n");
		printf("## 作者：潘越                           ##\n");
		printf("##########################################\n");
		/*常量定义*/
		int n;//n阶矩阵
		int i, j;
		int matrix[6][6];//原矩阵
		double partnermatrix[6][6];//伴随矩阵
		double antimatrix[6][6];//逆矩阵
		int p[6];//辅助行列式计算
		int B[5][5];//储存代数余子式对应的行列式
		int A;//储存行列式的值
		printf("请选择您要计算的矩阵阶数（2~6）: ");
		scanf_s("%d", &n);
		printf("\n请输入您要计算的矩阵A");

		/*程序运行*/

		for (i = 0; i < n; i++) {//输入矩阵
			for (j = 0; j < n; j++) {
				goto_xy(j * 4 + 1, 12 + i * 2);
				scanf_s("%d", &matrix[i][j]);
			}
		}
		printf("\n");
		getA(matrix, p, 0, n, 6);
		printf("以矩阵A中的元素构成的行列式的值是： ");
		printf("%d\n\n", sum);
		A = sum;//用A来储存行列式的值

				//给伴随矩阵赋值
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				getAij(matrix, B, i, j, n);
				sum = 0;
				clean(p);
				getA(B, p, 0, n - 1, 5);
				partnermatrix[j][i] = sum * pow(-1, i + j);
			}
		}
		goto_xy(0, 14 + n * 2);
		printf("矩阵A的伴随矩阵是：\n");
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				goto_xy(j * 6 + 1, 16 + (n + i) * 2);
				printf("%.0lf", partnermatrix[i][j]);
			}
		}
		printf("\n\n");
		goto_xy(0, 23 + n * 3);
		if (A != 0) {
			printf("矩阵A的逆矩阵是：\n");
			for (i = 0; i < n; i++) {
				for (j = 0; j < n; j++) {
					goto_xy(j * 6 + 1, 25 + n * 3 + i * 2);
					printf("%.2lf", partnermatrix[i][j] / A);
				}
			}
		}
		else
			printf("该矩阵不可逆！");
		printf("\n\n");
		printf("请问您想继续计算吗？-------Y/N ");
		char ch;
		while ((ch = getchar()) != '\n' && ch != EOF);
		scanf_s("%c", &re);//读取下一次的决定
		if (re == 'Y' || re == 'y') {
			sum = 0;
			clean(p);
			system("cls");
		}
	}
	printf("\n");
	system("pause");
	return 0;
}