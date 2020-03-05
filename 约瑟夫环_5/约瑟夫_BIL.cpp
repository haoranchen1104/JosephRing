#include "stdafx.h"
#include "Func_header.h"

void Joseph_BIL_Init(int** Joseph, int n)
{
	srand((unsigned)time(NULL));

	int layer = (int)log2(n - 1) + 1; bool odds;//计算层数
	Joseph[layer] = new int[n];//最后一层有n元素 
	for (int i = 0; i < n; i++) {//构造基本层
		Joseph[layer][i] = 1;//初始化最后一层为1
	}
	odds = n % 2; n = (n - 1) / 2 + 1; layer--;//上一层元素为下一层元素的一半
	for (; layer >= 0; layer--) {//在下层的基础上构造上层
		Joseph[layer] = new int[n];//此层元素为下一层的一半
		for (int i = 0; i < n - 1; i++) {
			Joseph[layer][i] = Joseph[layer + 1][2 * i] + Joseph[layer + 1][2 * i + 1];
		}
		if (!odds) { Joseph[layer][n - 1] = Joseph[layer + 1][2 * n - 1] + Joseph[layer + 1][2 * n - 2]; }
		else { Joseph[layer][n - 1] = Joseph[layer + 1][2 * n - 2]; }
		//奇数个节点的小组，其母组必有一个只有左子组
		odds = n % 2; n = (n - 1) / 2 + 1;//判断奇偶
	}
}//Joseph_MTL_Init;

int Joseph_BIL_Delete(int** Joseph, int ID, int LAYER, unsigned long int range)
{
	for (int i = LAYER - 1; i >= 0; i--) {//更新每一组树节点的值
		Joseph[i][ID]--; ID /= 2;
	}
	return random(range);//返回随机密码
}

int Joseph_BIL_Traversal(int **Joseph, int m, int *n, coord *Current, int LAYER)
{
	if (m > 0) { m = -(((m - 1) % *n) - *n); }
	else { m = -(((m + 1) % *n) - 1); }//向左寻找，向右遍历
	while (Current->depth) {//从当前的位置开始，寻找目标位置在哪一个尽可能小的树枝内
		if (!(Current->distance % 2)) { Current->depth--; Current->distance /= 2; }//该小组在大组左端，则向上层寻找
		else {
			if (Joseph[Current->depth][Current->distance - 1] < m) { m -= Joseph[Current->depth][Current->distance - 1]; Current->depth--; Current->distance /= 2; }//当左兄弟节点
			else { Current->distance--; m--; break; }//目标一定在左端小组内，寻找结束
		}
	}
	if (!Current->depth) {
		Current->depth++;//顶层特殊判断
		if (Joseph[1][1] >= m) { Current->distance = 1; m--; }
		else { m -= Joseph[1][1] + 1; }//若到达顶层，则进行特殊判断
	}
	while (LAYER - 1 - Current->depth) {//向下遍历寻找位置
		if (Joseph[Current->depth][Current->distance] - Joseph[Current->depth + 1][Current->distance * 2] > m) {
			Current->distance = Current->distance * 2 + 1;
		}
		else { m -= Joseph[Current->depth][Current->distance] - Joseph[Current->depth + 1][Current->distance * 2]; Current->distance *= 2; }
		Current->depth++;//根据m的值判断目标元素在当前小组的哪个子小组
	}
	return Current->distance;//返回目标地址
}//Joseph_MTL_Traversal;

double Joseph_BIL(int N, unsigned long int range)
{
	int n = N, m;
	if (n <= 1) { return n; }//错误输入的处理
	int LAYER = (int)log2(n - 1) + 2;//计算出总层数，由具体算法退推出
	int **Joseph = new int*[LAYER];//二维数组
	m = rand() % (N - 1) + 1;//初始密码
	Joseph_BIL_Init(Joseph, N);//初始化树

	LARGE_INTEGER start;
	LARGE_INTEGER end;
	LARGE_INTEGER freq;

	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);

	m = m > 0 ? m % n - 1 : m % n + n + 1;
	coord Current; Current.depth = LAYER - 1; Current.distance = m;//记录当前节点的位置
	m = Joseph_BIL_Delete(Joseph, Current.distance, LAYER, range);//删除节点，更新树值
	while (--n) {//总元素不断减少
		m = Joseph_BIL_Delete(Joseph, Joseph_BIL_Traversal(Joseph, m, &n, &Current, LAYER), LAYER, range);//循环查找删除
	}

	for (int i = 0; i < LAYER; i++) {
		delete[]Joseph[i];
	}
	delete[]Joseph;
	QueryPerformanceCounter(&end);
	return (double)(end.QuadPart - start.QuadPart) / (double)freq.QuadPart;
}//Joseph_MTL;
