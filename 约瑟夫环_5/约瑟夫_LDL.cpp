#include "stdafx.h"
#include "Func_header.h"

double Joseph_LDL(long int n, unsigned long int range)
{
	srand((unsigned)time(NULL));

	LARGE_INTEGER start;
	LARGE_INTEGER end;
	LARGE_INTEGER freq;

	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);

	int m, Current;
	m = random(range);

	Node * Joseph = Joseph_LDL_Init(n,range);

	Current = Joseph_LDL_Traversal(Joseph, m, n, 0);
	m = Joseph_LDL_Delete(Joseph, Current);

	n--;
	for (; n > 1; n--) {
		Current = Joseph_LDL_Traversal(Joseph, m, n, Current);
		m = Joseph_LDL_Delete(Joseph, Current);
	}

	Current = Joseph[Current].next;


	QueryPerformanceCounter(&end);
	return (double)(end.QuadPart - start.QuadPart) / (double)freq.QuadPart;
}

Node * Joseph_LDL_Init(long int n, unsigned long int range)
{

	Node * Joseph = new Node[n];

	int i;
	for (i = 0; i < n; i++) {
		Joseph[i].password = random(range);
		Joseph[i].prior = i - 1;
		Joseph[i].next = i + 1;
	}
	Joseph[0].prior = n - 1;
	Joseph[n - 1].next = 0;

	return Joseph;
}

int Joseph_LDL_Traversal(Node Joseph[], int m, int n, int Current)
{
	int direction;

	if (m > 0) {
		m = m % n;

		if (m == 0) {
			return Joseph[Current].prior;
		}

		direction = 1;
		if (2 * m > n) {
			m = n - m + 1;
			direction = 0;
		}
	}

	if (m < 0) {
		m = (-m) % n;

		if (m == 0) {
			return Joseph[Current].next;
		}

		direction = 0;
		if (2 * m > n) {
			m = n - m + 1;
			direction = 1;
		}
	}

	if (direction) {
		while (m != 0) {
			Current = Joseph[Current].next;
			m--;
		}
	}
	else {
		while (m != 0) {
			Current = Joseph[Current].prior;
			m--;
		}
	}

	return Current;
}

int Joseph_LDL_Delete(Node Joseph[], int Current)
{
	Joseph[Joseph[Current].prior].next = Joseph[Current].next;
	Joseph[Joseph[Current].next].prior = Joseph[Current].prior;

	return Joseph[Current].password;
}