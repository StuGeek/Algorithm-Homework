#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int row;
	int col;
	int value;
} Triple;

typedef struct tmatrix{
	int rn;
	int cn;
	int tn;
	Triple data[100];
} *TMatrix;

TMatrix creat_TMatrix(int row, int col){
	TMatrix t = (TMatrix)malloc(sizeof(struct tmatrix));
	t->rn = row;
	t->cn = col;
	t->tn = 0;
	return t;
}

void add(TMatrix a, int row, int col, int val){
	a->data[a->tn].row = row;
	a->data[a->tn].col = col;
	a->data[a->tn].value = val;
	a->tn++;
}

void FastTransMatrix(TMatrix a, TMatrix b) {
	int num[100] = {0};
	int cpot[100] = {0};
	b->rn = a->cn;
	b->cn = a->rn;
	b->tn = a->tn;
	if (b->tn == 0) return;
	for (int i = 0; i < a->tn; ++i){
		num[a->data[i].col]++;
	}
	for (int i = 1; i <= a->cn; ++i){
		cpot[i] = cpot[i - 1] + num[i - 1];
	}
	for (int i = 0; i < a->tn; ++i){
		int col = a->data[i].col;
		int j = cpot[col];
		b->data[j].row = a->data[i].col;
		b->data[j].col = a->data[i].row;
		b->data[j].value = a->data[i].value;
		cpot[col]++;
	}
}

void printTMatrix(TMatrix a){
	for (int i = 0; i < a->tn; ++i){
		printf("row:%d col:%d value: %d\n", a->data[i].row, a->data[i].col, a->data[i].value);
	}
}

int main(){
	TMatrix t = creat_TMatrix(4, 5);
	add(t, 1, 2, 5);
	add(t, 2, 4, 8);
	add(t, 2, 3, 9);
	TMatrix temp = creat_TMatrix(4, 5);
	FastTransMatrix(t, temp);
	printTMatrix(t);
	printTMatrix(temp);
}