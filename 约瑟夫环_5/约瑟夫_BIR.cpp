// 约瑟夫环_5.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Func_header.h"

double Joseph_BIR(long int n, unsigned long int range)
{
	srand((unsigned)time(NULL));

	int Password = random(range);
	int ** Joseph_Bitree = Joseph_BIR_Init(n);
	int LAYER = (int)log2(n - 1) + 2;
	Position Current;

	LARGE_INTEGER start;
	LARGE_INTEGER end;
	LARGE_INTEGER freq;

	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);


	Password = (Password - 1) % n + 1;
	Current.index = Password - 1;
	Current.layer = LAYER - 1;
	Password = Joseph_BIR_Delete(Joseph_Bitree, LAYER, Current.index,range);

	while (--n) {
		Password = Joseph_BIR_Delete(Joseph_Bitree, LAYER, Joseph_BIR_Search(Joseph_Bitree, &Current, Password, n, LAYER), range);
	}
	QueryPerformanceCounter(&end);
	return (double)(end.QuadPart - start.QuadPart) / (double)freq.QuadPart;
}

int ** Joseph_BIR_Init(long int N)
{
	int tree_depth = (int)log2(N - 1) + 2;
	int ** Joseph_Bitree = new int*[tree_depth];
	Joseph_Bitree[tree_depth - 1] = new int[(int)pow(2, tree_depth - 1)];
	for (int i = 0; i < N; i++) {
		Joseph_Bitree[tree_depth - 1][i] = 1;
	}
	for (int i = N; i < pow(2, tree_depth - 1); i++) {
		Joseph_Bitree[tree_depth - 1][i] = 0;
	}
	for (int layer = tree_depth - 2; layer >= 0; layer--) {
		Joseph_Bitree[layer] = new int[(int)pow(2, layer)];
		for (int i = 0; i < pow(2, layer); i++) {
			Joseph_Bitree[layer][i] = Joseph_Bitree[layer + 1][2 * i] + Joseph_Bitree[layer + 1][2 * i + 1];
		}
	}
	return Joseph_Bitree;
}

void Display_BIR_Joseph(int N, int ** Joseph_Bitree) {
	int tree_depth = (int)log2(N - 1) + 2;
	for (int i = 0; i < tree_depth; i++) {
		for (int j = 0; j < pow(2, i); j++) {
			printf("%d ", Joseph_Bitree[i][j]);
		}
		printf("\n");
	}
}

int Joseph_BIR_Delete(int ** Joseph_Bitree, int layer, int index, unsigned long int range) {//index有0
	for (int i = layer - 1; i >= 0; i--) {
		Joseph_Bitree[i][index]--;
		index /= 2;
	}
	return random(range);
}

int Joseph_BIR_Search(int ** Joseph_Bitree, Position * Current, int Password, int N, int LAYER) {
	Password = (Password - 1) % N + 1;
	while (Current->layer) {
		if ((Current->index % 2)) {
			Current->index /= 2;
			Current->layer--;
		}
		else {
			if (Joseph_Bitree[Current->layer][Current->index + 1] >= Password) {
				Current->index += 1;
				Password--;
				break;
			}
			else {
				Password -= Joseph_Bitree[Current->layer][Current->index + 1];
				Current->index /= 2;
				Current->layer--;
			}
		}
	}
	if (!Current->layer) {
		Current->layer++;
		if (Joseph_Bitree[1][0] >= Password) {
			Current->index = 0;
			Password--;
		}
		else {
			Current->index = 1;
			Password -= Joseph_Bitree[1][0] + 1;
		}
	}
	while (LAYER - 1 - Current->layer) {
		if (Joseph_Bitree[Current->layer + 1][Current->index * 2] > Password) {
			Current->layer++;
			Current->index *= 2;
		}
		else {
			Current->layer++;
			Password -= Joseph_Bitree[Current->layer][Current->index * 2];
			Current->index = Current->index * 2 + 1;
		}
	}
	return Current->index;
}

unsigned long int random(unsigned long int range) {
	if (range<=100000) {
		return rand() % 100000 + 1;
	}
	else {
		return (rand() % (range / 100000)) * 100000 + (rand() % 100000 + 1);
	}
}