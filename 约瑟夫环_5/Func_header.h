#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

//使用的结构体
/*--二叉右搜索结构--*/
typedef struct POSITION {
	int layer;
	int index;
}Position;

/*--二叉左搜索结构--*/
typedef struct Nodetype {
	int depth;
	int distance;
}coord;

/*--链表未优化结构--*/
typedef struct node {
	int password;
	int prior;
	int next;
}Node;

/*--二维数组结构--*/
typedef struct group {
	int EleNum;
	int prior;
	int next;
	int head;
	Node *NodeArray;
}Group;
typedef struct POSITION_1 {
	int No_Group;
	int No_Node;
}Position_1;

/*--三叉树结构--*/
typedef struct
{
	int ID[3];
	int code[3];
}ground;
typedef struct multiD {
	int len, layer;
	union {
		struct multiD *branch[3];
		ground floor;
	};
}multiD;

//使用的函数
/*--随机函数生成函数--*/
unsigned long int random(unsigned long int range);

/*--链表未优化函数--*/
double Joseph_LDL(long int n, unsigned long int range);
Node *Joseph_LDL_Init(long int n, unsigned long int range);
int Joseph_LDL_Delete(Node Joseph[], int Current);
int Joseph_LDL_Traversal(Node Joseph[], int m, int n, int Current);

/*--二叉右搜索函数--*/
double Joseph_BIR(long int n, unsigned long int range);
int ** Joseph_BIR_Init(long int n);
void Display_BIR_Joseph(int N, int ** Joseph_Bitree);
int Joseph_BIR_Delete(int ** Joseph_Bitree, int layer, int index, unsigned long int range);
int Joseph_BIR_Search(int ** Joseph_Bitree, Position * Current, int Password, int N, int LAYER);

/*--二叉左搜索函数--*/
double Joseph_BIL(int N, unsigned long int range);
void Joseph_BIL_Init(int** Joseph, int n);
int Joseph_BIL_Delete(int** Joseph, int ID, int LAYER, unsigned long int range);
int Joseph_BIL_Traversal(int **Joseph, int m, int *n, coord *Current, int LAYER);

/*--二维数组搜索函数--*/
double Joseph_2D(int n, unsigned long int range);
Group *Joseph_2D_Init(int n, int GroupNum, int NodeNum, unsigned long int range);
int Joseph_2D_Delete(Group Joseph[], Position_1 Current);
Position_1 Joseph_2D_Travarsal(Group Joseph[], int m, int n, Position_1 Current);

/*--三叉搜索--*/
double Joseph_MD3(int n, unsigned long int range);
int delete_Joseph_MD3(multiD &Joseph, int code, int &n, int &position);
void init_Joseph_MD3(int &ID, multiD &Joseph, int n, int layer, unsigned long int range);
