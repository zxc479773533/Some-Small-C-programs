#include <stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<math.h>

/*ȫ�ֱ���*/
int A = 0;//����ʽ�Ľ��
int sum = 0;//����ʽ��ֵ

/*��������*/
void goto_xy(int x, int y);//�ƶ����
void exchange(int *a, int *b);//������������ֵ
void clean(int *p);//�������
int getp(int *p, int n);//����p��������
void getA(int *matrix, int * p, int counter, int n, int k);//��������ʽ��ֵ
void getAij(int *matrix,int *B, int i, int j, int n);//����aij�Ĵ�������ʽ��Ӧ������ʽ

/*������д*/
void goto_xy(int x, int y) {//�ƶ����
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x,y };
	SetConsoleCursorPosition(hOut, pos);
}

void exchange(int *a, int *b)  //������������ֵ  
{
	int m = *a;
	*a = *b;
	*b = m;
}

void clean(int *p) {//�������
	int i = 0;
	for (i = 0; i < 6; i++)
		p[i] = 0;
}

int getp(int *p, int n) {//����p��������
	int i, j, k = 0;
	for (i = 0; i < n; i++) {
		for (j = 0; j < i; j++) {
			if (p[j] > p[i])//�������Ķ���
				k++;
		}
	}
	if ((k % 2) == 0)
		return 1;
	else
		return -1;
}

void getA(int *matrix, int *p, int counter, int n, int k) {//��������ʽ��ֵ
	int i, j;
	if (counter == n) {
		int ans = 1;
		for (i = 0; i < n; i++)
			ans *= *(matrix + i * k + p[i] - 1);
		sum += ans * getp(p, n);//��������ϼ�����
	}
	else {
		for (i = 1; i <= n; i++) {
			int ok = 1;
			for (j = 0; j < counter && ok; j++) {
				if (p[j] == i)//���i�Ƿ����
					ok = 0;
			}
			if (ok) {
				p[counter] = i;//���������и�ֵ
				getA(matrix, p, counter + 1, n, k);
			}
		}
	}
}

void getAij(int *matrix, int *B, int i, int j, int n) {//����aij�Ĵ�������ʽ��Ӧ������ʽ
	double Aij;
	int x, y, k = 0, l = 0;
	double c;//��ʱ����
	for (x = 0; x < i; x++) {//���Ϸ�����
		for (y = 0; y < j; y++) {
			c = *(matrix + x * 6 + y);
			*(B + x * 5 +y) = c;
		}
	}
	for (x = i; x < n - 1; x++) {//���·������ƶ�һ��
		for (y = 0; y < j; y++) {
			c = *(matrix + (x + 1) * 6 + y);
			*(B + x * 5 + y) = c;
		}
	}
	for (x = 0; x < i; x++) {//���Ϸ������ƶ�һ��
		for (y = j; y < n - 1; y++) {
			c = *(matrix + x * 6 + y + 1);
			*(B + x * 5 + y) = c;
		}
	}
	for (x = i; x < n - 1; x++) {//���·������Ϸ��ƶ�
		for (y = j; y < n - 1; y++) {
			c = *(matrix + (x + 1) * 6 + y + 1);
			*(B + x * 5 + y) = c;
		}
	}
}

int main(void) {
	char re = 'Y';
	while (re == 'y' || re == 'Y') {
		/*���ܽ���*/
		printf("##########################################\n");
		printf("## ��ӭʹ�����Դ���С����               ##\n");
		printf("##                                      ##\n");
		printf("## �����԰�������ҵ�г���������ͷ�۵� ##\n");
		printf("## �������������ʽ������             ##\n");
		printf("##                                      ##\n");
		printf("## ���ߣ���Խ                           ##\n");
		printf("##########################################\n");
		/*��������*/
		int n;//n�׾���
		int i, j;
		int matrix[6][6];//ԭ����
		double partnermatrix[6][6];//�������
		double antimatrix[6][6];//�����
		int p[6];//��������ʽ����
		int B[5][5];//�����������ʽ��Ӧ������ʽ
		int A;//��������ʽ��ֵ
		printf("��ѡ����Ҫ����ľ��������2~6��: ");
		scanf_s("%d", &n);
		printf("\n��������Ҫ����ľ���A");

		/*��������*/

		for (i = 0; i < n; i++) {//�������
			for (j = 0; j < n; j++) {
				goto_xy(j * 4 + 1, 12 + i * 2);
				scanf_s("%d", &matrix[i][j]);
			}
		}
		printf("\n");
		getA(matrix, p, 0, n, 6);
		printf("�Ծ���A�е�Ԫ�ع��ɵ�����ʽ��ֵ�ǣ� ");
		printf("%d\n\n", sum);
		A = sum;//��A����������ʽ��ֵ

				//���������ֵ
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
		printf("����A�İ�������ǣ�\n");
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				goto_xy(j * 6 + 1, 16 + (n + i) * 2);
				printf("%.0lf", partnermatrix[i][j]);
			}
		}
		printf("\n\n");
		goto_xy(0, 23 + n * 3);
		if (A != 0) {
			printf("����A��������ǣ�\n");
			for (i = 0; i < n; i++) {
				for (j = 0; j < n; j++) {
					goto_xy(j * 6 + 1, 25 + n * 3 + i * 2);
					printf("%.2lf", partnermatrix[i][j] / A);
				}
			}
		}
		else
			printf("�þ��󲻿��棡");
		printf("\n\n");
		printf("�����������������-------Y/N ");
		char ch;
		while ((ch = getchar()) != '\n' && ch != EOF);
		scanf_s("%c", &re);//��ȡ��һ�εľ���
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