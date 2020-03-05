#include "stdafx.h"
#include "Func_header.h"
#include <windows.h>

void init_Joseph_MD3(int &ID, multiD &Joseph, int n, int layer, unsigned long int range)
{
	if (layer <= 1) {
		Joseph.len = 0;
		for (int i = 0; i < 3; i++) {
			Joseph.layer = 1;
			if (ID > n) {
				Joseph.floor.ID[i] = 0;
				Joseph.floor.code[i] = 0;
			}
			else {
				Joseph.floor.ID[i] = ID++;
				Joseph.floor.code[i] = random(range);
				Joseph.len++;
			}
		}
	}

	else
	{
		for (int i = 0; i < 3; i++) {
			Joseph.branch[i] = new multiD;
		}

		init_Joseph_MD3(ID, *(Joseph.branch[0]), n, layer - 1, range);
		init_Joseph_MD3(ID, *(Joseph.branch[1]), n, layer - 1, range);
		init_Joseph_MD3(ID, *(Joseph.branch[2]), n, layer - 1, range);

		Joseph.layer = layer;
		Joseph.len = Joseph.branch[0]->len + Joseph.branch[1]->len + Joseph.branch[2]->len;
	}
}

int delete_Joseph_MD3(multiD &Joseph, int code, int &n, int &position)
{
	position = (position - 1 + code) % n;
	if (position == 0)position = n;

	multiD *prt = &Joseph;
	int i, tempPos = position;
	int layer = Joseph.layer;

	while (layer>1)
	{
		for (i = 0; i < 3; i++) {
			if (prt->branch[i]->len >= tempPos) {
				prt->branch[i]->len--;
				break;
			}
			else
			{
				tempPos -= prt->branch[i]->len;
			}
		}

		prt = prt->branch[i];
		layer--;
	}

	code = prt->floor.code[tempPos - 1];
	n--;

	for (i = tempPos - 1; i < 2; i++) {
		prt->floor.ID[i] = prt->floor.ID[i + 1];
		prt->floor.code[i] = prt->floor.code[i + 1];
	}

	return code;
}

double Joseph_MD3(int n, unsigned long int range)
{
	multiD Joseph;

	int i = 1, layer, code;
	int pos = 1;

	code = 5;
	layer = (int)(log(n - 1) / log(3)) + 1;
	init_Joseph_MD3(i, Joseph, n, layer, range);

	LARGE_INTEGER start;
	LARGE_INTEGER end;
	LARGE_INTEGER freq;

	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);

	while (n) {
		code = delete_Joseph_MD3(Joseph, code, n, pos);
	}
	QueryPerformanceCounter(&end);
	return (double)(end.QuadPart - start.QuadPart) / (double)freq.QuadPart;

}