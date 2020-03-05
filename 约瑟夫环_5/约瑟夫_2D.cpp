// Joseph20.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Func_header.h"

double Joseph_2D(int n, unsigned long int range)
{
	srand((unsigned)time(NULL));

	int m;
	Position_1 Current;
	m = random(range);
	Current.No_Group = 0;
	Current.No_Node = 0;

	int GroupNum = (int)(sqrt(n) * 2);
											 
	int NodeNum = n / GroupNum + (n % GroupNum ? 1 : 0);
	Group *Joseph = Joseph_2D_Init(n, GroupNum, NodeNum, range);

	LARGE_INTEGER start;
	LARGE_INTEGER end;
	LARGE_INTEGER freq;

	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);

	for (; n > 0; n--) {
		Current = Joseph_2D_Travarsal(Joseph, m, n, Current);
		m = Joseph_2D_Delete(Joseph, Current);
	}

	QueryPerformanceCounter(&end);
	return (double)(end.QuadPart - start.QuadPart) / (double)freq.QuadPart;
}

Group *Joseph_2D_Init(int n, int GroupNum, int NodeNum, unsigned long int range)
{
	Group * Joseph = new Group[GroupNum];

	int i, j;
	for (i = 0; i < GroupNum - 1; i++) {

		Joseph[i].NodeArray = new Node[NodeNum];

		for (j = 0; j < NodeNum; j++) {
			Joseph[i].NodeArray[j].password = random(range);
			Joseph[i].NodeArray[j].prior = j - 1;
			Joseph[i].NodeArray[j].next = j + 1;

		}
		Joseph[i].NodeArray[0].prior = -1;
		Joseph[i].NodeArray[NodeNum - 1].next = -1;

		Joseph[i].EleNum = NodeNum;
		Joseph[i].prior = i - 1;
		Joseph[i].next = i + 1;
		Joseph[i].head = 0;

	}

	Joseph[i].NodeArray = new Node[NodeNum];
	for (j = 0; j < n - (GroupNum - 1)*NodeNum; j++) {

		Joseph[i].NodeArray[j].password = random(range);
		Joseph[i].NodeArray[j].prior = j - 1;
		Joseph[i].NodeArray[j].next = j + 1;
	}
	Joseph[i].NodeArray[0].prior = -1;
	Joseph[i].NodeArray[j - 1].next = -1;

	Joseph[i].EleNum = j;
	Joseph[i].prior = i - 1;
	Joseph[i].next = i + 1;
	Joseph[i].head = 0;

	Joseph[0].prior = GroupNum - 1;
	Joseph[GroupNum - 1].next = 0;

	return Joseph;
}

int Joseph_2D_Delete(Group Joseph[], Position_1 Current)
{

	if (Joseph[Current.No_Group].EleNum > 2) {
		if (Joseph[Current.No_Group].head == Current.No_Node) {
			Joseph[Current.No_Group].head = Joseph[Current.No_Group].NodeArray[Current.No_Node].next;
			Joseph[Current.No_Group].NodeArray[Joseph[Current.No_Group].NodeArray[Current.No_Node].next].prior = -1;

			Joseph[Current.No_Group].EleNum--;
			return Joseph[Current.No_Group].NodeArray[Current.No_Node].password;
		}

		if (Joseph[Current.No_Group].NodeArray[Current.No_Node].next == -1) {
			Joseph[Current.No_Group].NodeArray[Joseph[Current.No_Group].NodeArray[Current.No_Node].prior].next = -1;

			Joseph[Current.No_Group].EleNum--;
			return Joseph[Current.No_Group].NodeArray[Current.No_Node].password;
		}

		Joseph[Current.No_Group].NodeArray[Joseph[Current.No_Group].NodeArray[Current.No_Node].prior].next
			= Joseph[Current.No_Group].NodeArray[Current.No_Node].next;
		Joseph[Current.No_Group].NodeArray[Joseph[Current.No_Group].NodeArray[Current.No_Node].next].prior
			= Joseph[Current.No_Group].NodeArray[Current.No_Node].prior;

	}


	else if (Joseph[Current.No_Group].EleNum == 2) {
		if (Joseph[Current.No_Group].head == Current.No_Node) {
			Joseph[Current.No_Group].head = Joseph[Current.No_Group].NodeArray[Current.No_Node].next;
			Joseph[Current.No_Group].NodeArray[Joseph[Current.No_Group].head].prior = -1;
		}
		else {
			Joseph[Current.No_Group].NodeArray[Joseph[Current.No_Group].head].next = -1;
		}
	}
	Joseph[Current.No_Group].EleNum--;
	return Joseph[Current.No_Group].NodeArray[Current.No_Node].password;

}

Position_1 Joseph_2D_Travarsal(Group Joseph[], int m, int n, Position_1 Current)
{
	int direction;

	if (m > 0) {
		m = m % n;
		if (m == 0) {
			m = n;
		}
		direction = 1;
		if (2 * m > n) {
			m = n - m + 1;
			direction = 0;
		}
	}
	else if (m < 0) {
		m = (-m) % n;

		if (m == 0) {
			m = n;
		}

		direction = 0;
		if (2 * m > n) {
			m = n - m + 1;
			direction = 1;
		}
	}
	if (direction == 1) {

		while (Joseph[Current.No_Group].NodeArray[Current.No_Node].next != -1) {
			Current.No_Node = Joseph[Current.No_Group].NodeArray[Current.No_Node].next;
			m--;

			if (m == 0) {
				return Current;
			}
		}
		Current.No_Group = Joseph[Current.No_Group].next;
		while (m > Joseph[Current.No_Group].EleNum) {
			m -= Joseph[Current.No_Group].EleNum;
			Current.No_Group = Joseph[Current.No_Group].next;
		}
		m--;
		Current.No_Node = Joseph[Current.No_Group].head;
		while (m > 0) {
			Current.No_Node = Joseph[Current.No_Group].NodeArray[Current.No_Node].next;
			m--;
		}
	}
	else {
		if (Joseph[Current.No_Group].NodeArray[Current.No_Node].prior != -1) {
			while (Current.No_Node != Joseph[Current.No_Group].head) {
				Current.No_Node = Joseph[Current.No_Group].NodeArray[Current.No_Node].prior;
				m--;
				if (m == 0) {
					return Current;
				}
			}
		}
		Current.No_Group = Joseph[Current.No_Group].prior;
		while (m > Joseph[Current.No_Group].EleNum) {
			m -= Joseph[Current.No_Group].EleNum;
			Current.No_Group = Joseph[Current.No_Group].prior;
		}
		m = Joseph[Current.No_Group].EleNum - m; // 小组内正序查找
		Current.No_Node = Joseph[Current.No_Group].head;
		while (m > 0) {
			Current.No_Node = Joseph[Current.No_Group].NodeArray[Current.No_Node].next;
			m--;
		}
	}
	return Current;
}