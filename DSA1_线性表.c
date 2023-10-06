#include <stdio.h>
#include <stdlib.h>
#include "DataStructure.h"

//定义线性表
#define MAXSIZE 100 // 线性表存储空间的初始分配量
typedef struct
{
	ElemType* elem;
	int length;// 当前长度
}SqList;

//// 多项式
//#define MAXSIZE 1000 // 多项式可能达到的最大长度
//
//typedef struct // 多项式非零项的定义
//{
//	float* p; // 系数
//	int e; // 指数
//}Polynomial;
//
//typedef struct
//{
//	Polynomial* elem; // 存储空间的基地址
//	int length;// 多项式中当前项的个数
//}SqList;// 多项式的顺序存储结构类型为SqList
//
// //图书表
//#define MAXSIZE 10000 // 图书表可能达到的最大长度
//
//typedef struct
//{
//	// 图书信息定义
//	char no[20]; // 图书ISBN
//	char name[50]; // 图书名字
//	float price; // 图书价格
//}Book;
//
//typedef struct
//{
//	Book* elem; // 存储空间的基地址
//	int length; // 图书表中当前图书个数
//}SqList; // 图书表的顺序存储结构类型为SqList


 //线性表基本操作的实现
 //线性表的初始化(参数用引用)
Status InitList_Sq(SqList *L)
{
	// 构造一个空的顺序表L
	L->elem = (ElemType*)malloc(MAXSIZE * sizeof(ElemType)); // 为顺序表分配空间
	if (!L->elem) exit(OVERFLOW); // 顺序分配失败
	L->length = 0; // 空表长度为0
	return OK;
}

 //销毁线性表
void DestroyList(SqList* L)
{
	if (L->elem)
		free(L->elem); // 释放存储空间
}

 //清空线性表L
void ClearList(SqList* L)
{
	L->length = 0; // 将线性表的长度置为0
}

 //求线性表L的长度
int GetLength(SqList L)
{
	return(L.length);
}

 //判断线性表L是否为空
int IsEmpty(SqList L)
{
	if (L.length == 0)
		return 1;
	else return 0;
}

 //顺序表的取值（根据位置i获取相应位置数据元素的内容）
int GetElem(SqList L, int i, ElemType* e)
{
	if (i < 1 || i > L.length)
		return ERROR; // 判断i值是否合理 若不合理 返回ERROR
	*e = L.elem[i - 1]; // 低i-1的单元存储着第i个数据
	return OK;
}
 //随机存取 效率高 算法复杂度O(1)

 //顺序表的查找 按值查找
int LocateElem(SqList L, ElemType e)
{
	// 在线性表L中查找值为e的数据元素 返回其序号（是第几个元素）
	for (int i = 0; i < L.length; i++)
	{
		if (L.elem[i] == e)
			return i + 1; // 查找成功 返回序号
	}
	return 0; // 查找失败 返回0
}
 //平均查找长度 ASL(Average Search Length)
 //ASL = (n + 1)/2

 //顺序表的插入
 //算法思想：
 //1. 判断插入位置i是否合法
 //2. 判断顺序表的存储空间是否已满 若已满返回ERROR
 //3. 将第n至第i位的元素依次向后移动一个位置 空出第i个位置
 //4. 将要插入的新元素e放入第i个位置
 //5. 表长加1 插入成功返回OK
Status ListInsert_Sq(SqList* L, int i, ElemType e)
{
	if (i < 1 || i > L->length + 1)
		return ERROR;// i值不合法
	if (L->length == MAXSIZE)
		return ERROR;// 当前存储空间已满
	for (int j = L->length - 1; j >= i - 1; j--)
		L->elem[j + 1] = L->elem[j]; // 插入位置及之后的元素后移
	L->elem[i - 1] = e; // 将新元素e放入第i个位置
	L->length++; // 表长增1
	return OK;
}
 //算法分析
 //平均移动次数n/2
 //O(n)

 //顺序表的删除
 //1. 判断删除位置i是否合法 1 <= i <= n
 //2. 将要删除的元素保存在e中
 //3. 将第i + 1至第n位的元素一次向前移动一个位置
 //4. 表长减1 删除成功返回OK
Status ListDelete_Sq(SqList* L, int i)
{
	if ((i < 1) || (i > L->length)) return ERROR; // i值不合法
	for (int j = i; j <= L->length - 1; j++)
		L->elem[j - 1] = L->elem[j]; // 被删除元素之后的元素前移
	L->length--; // 表长减1
	return OK;
}
 //O(n)

 //单链表的表示和定义
 //结点定义
typedef struct LNode
{ // 声明结点的类型和指向节点的指针类型
	ElemType data; // 数据域
	struct LNode* next; // 指针域
}LNode, * LinkList; // LinkList为指向结构体LNode的指针类型

//LinkList L; // 定义链表
//LNode* p; // 定义结点

//// 例如 存储学生信息
//typedef struct
//{
//	char num[8];
//	char name[8];
//	int score;
//}ElemType;
//
//typedef struct student
//{
//	ElemType data; // 数据域
//	struct student* next; // 指针域
//}LNode, *LinkList;

// 单链表的初始化 构造一个空表 带头结点
// 1. 生成新结点作为头结点 用头指针L指向头节点
// 2. 将头结点的指针置空
Status InitList_L(LinkList L)
{
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;
	return OK;
}

// 判断链表是否为空
// 判断头结点指针域是否为空
int ListEmpty(LinkList L) // 若L为空表 则返回1 否则返回0
{
	if (L->next) // 非空
		return 0;
	else
		return 1;
}

// 单链表销毁
// 从头指针开始 依次释放所有结点
Status DestroyList(LinkList L) // 销毁单链表L
{
	LNode* p; // LinkList p;
	while (L)
	{
		p = L;
		L = L->next;
		free(p);
	}
	return OK;
}

 //清空链表
 //依次释放所有结点 并将头结点指针域设置为空
Status ClearList(LinkList L) // 将L重置为空表
{
	LNode* p, * q;
	p = L->next;
	while (p)
	{
		q = p->next;
		free(p);
		p = q;
	}
	L->next = NULL; // 头结点指针域为空
	return OK;
}

 //求单链表的表长
 //从首元结点开始 依次计数所有结点
int ListLength_L(LinkList L) // 返回L中数据元素个数
{
	LinkList p;
	p = L->next;
	int i = 0;
	while (p)
	{
		i++;
		p = p->next;
	}
	return i;
}

 //取值
 //顺序存取
Status GetElem_L(LinkList L, int i, ElemType *e) // 获取线性表L中的某个数据元素的内容 通过变量e返回
{
	LNode* p = L->next; int j = 1;
	while (p && j < i)
	{
		p = p->next; ++j;
	}
	if (!p || j > i) return ERROR; // 第i个元素不存在
	e = p->data; // 取第i个元素
	return OK;
}

 //按值查找
LNode* LocateElem_L(LinkList L, ElemType e) // 在线性表L中查找值为e的数据元素
{
	// 找到则返回L中值为e的数据元素的地址 查找失败返回NULL
	LNode* p = L->next;
	while (p && p->data != e)
		p = p->next;
	return p;
}

int LocateElem_L(LinkList L, ElemType e) // 在线性表L中查找值为e的数据元素的位置序号
{
	// 返回L中值为e的数据元素的位置序号 查找失败返回0
	LNode* p = L->next; int j = 1;
	while (p && p->data != e)
	{
		p = p->next; j++;
	}
	if (p) return j;
	else return 0;
}

 //插入
 //在L中第i个元素之前插入数据元素e
Status ListInsert_L(LinkList L, int i, ElemType e)
{
	LNode* p = L; // 初始化指针
    int j = 0; // 记录指针位置
	while (p && j < i - 1) // 寻找第i - 1结点 p 指向i - 1结点
	{
		p = p->next;
		++j;
	}
	if (!p || j > i - 1) return ERROR; // i大于表长+1或者小于1 插入位置非法
	LNode* s = (LNode*)malloc(MAXSIZE * sizeof(LNode));
	s->data = e; // 生成新结点s 将结点s的数据域置为e
	s->next = p->next;
	p->next = s;
	return OK;
}

 //删除
 //将线性表L中的第i个数据元素删除
Status ListDelete_L(LinkList L, int i, ElemType* e)
{
	LNode* p = L;
	int j = 0;
	while (p->next && j < i - 1) // 寻找第i个结点 并令p指向其前驱
	{
		p = p->next;
		++j;
	}
	if (!(p->next) || j > i - 1) return ERROR; // 删除位置不合理
	LNode* q = p->next; // 临时保存被删除的结点以备释放
	p->next = q->next; // 改变删除节点前驱节点的指针域
	e = q->data; // 保存删除节点的数据域
	free(q); // 释放删除结点的空间
	return OK;
}

 //查找O(n) 插入和删除O(1)

 //建立单链表
 //头插法 前插法 O(n)
void CreateList_H(LinkList L, int n)
{
	L = (LinkList)malloc(MAXSIZE * sizeof(LNode));
	L->next = NULL; // 先建立一个带头结点的单链表
	for (int i = n; i > 0; --i)
	{
		LNode* p = (LNode*)malloc(MAXSIZE * sizeof(LNode));
		scanf("%d", &p->data); // 输入元素值
		p->next = L->next; // 插入到表头
		L->next = p;
	}
}

 //尾插法 O(n)
void CreatList_R(LinkList L, int n)
{
	L = (LinkList)malloc(MAXSIZE * sizeof(LNode));
	L->next = NULL;
	LNode* r = L; // 尾指针r指向头结点
	for (int i = 0; i < n; ++i)
	{
		LNode* p = (LNode*)malloc(MAXSIZE * sizeof(LNode));
		scanf("%d", &p->data);
		p->next = NULL;
		r->next = p; // 插入到表尾
		r = p; // r指向新的尾结点
	}
}

 //循环链表
 //合并尾指针循环链表
LinkList Connect(LinkList Ta, LinkList Tb) // Ta Tb都是非空的单循环链表
{
	LNode* p = Ta->next; // p存表头结点
	Ta->next = Tb->next->next; // Tb表头连结Ta表尾
	free(Tb->next); // 释放Tb表头结点
	Tb->next = p; // 修改指针
	return Tb;
}

 //双向链表
 //定义
typedef struct DuLNode
{
	ElemType data;
	struct DuLNode* prior, * next;
}DuLNode, * DuLinkList;

 //双向循环链表的插入
void ListInsert_DuL(DuLinkList L, int i, ElemType e) // 在带头结点的双向循环链表L中第i个位置之前插入元素e
{
	DuLNode* p;
	if (!(p = GetElemP_DuL(L, i)))
		return ERROR;
	DuLNode* s = (DuLNode*)malloc(MAXSIZE * sizeof(DuLNode));
	s->data = e;
	s->prior = p->prior;
	p->prior->next = s;
	s->next = p;
	p->prior = s;
	return OK;
}

 //双向链表删除 O(n)
void ListDelete_DuL(DuLinkList L, int i, ElemType* e) // 删除带头结点的双向循环链表L的第i个元素 并用e返回
{
	DuLNode* p;
	if (!(p == GetElemP_DuL(L, i)))
		return ERROR; // O(n)
	e = p->data;
	p->prior->next = p->next; // O(1)
	p->next->prior = p->prior;
	free(p);
	return OK;
}

// //线性表合并 集合 O(n^2)
//void Union(List& La, List Lb)
//{
//	La_len = ListLength(La);
//	Lb_len = ListLength(Lb);
//	for (i = 1; i <= Lb_len; i++)
//	{
//		GetElem(Lb, i, e);
//		if (!LocateElem(La, e))
//			ListInsert(*La, ++La_len, e);
//	}
//}

 //有序表的合并 顺序表实现 时间O(n) 空间O(n)
void MergeList_Sq(SqList LA, SqList LB, SqList* LC)
{
	ElemType* pa = LA.elem;
	ElemType* pb = LB.elem; // 指针pa和pb的初值分别指向两个表的第一个元素
	LC->length = LA.length + LB.length; // 新表长度为待合并两表的长度之和
	LC->elem = (ElemType*)malloc(LC->length * sizeof(ElemType));// 为合并后的新表分配一个数组空间
	ElemType* pc = LC->elem; // 指针pc指向新表第一个元素
	ElemType* pa_last = LA.elem + LA.length - 1; // 指针pa_last指向LA表的最后一个元素
	ElemType* pb_last = LB.elem + LB.length - 1; // 指针pb_last指向LB表的最后一个元素
	while (pa <= pa_last && pb <= pb_last) // 两个表都非空
	{
		if (*pa <= *pb) // 依次“摘取”两表中值较小的结点
			*pc++ = *pa++;
		else
			*pc++ = *pb++;
	}
	while (pa <= pa_last) // LB表已到达表尾 将剩余元素加入LC
		*pc++ = *pa++;
	while (pb <= pb_last) // LA表已到达表尾 将剩余元素加入LC
		*pc++ = *pb++;
}

 //有序表的合并 链表实现 时间O(n) 空间O(1)
void MergeList_L(LinkList La, LinkList Lb, LinkList Lc)
{
	LNode* pa = La->next;
	LNode* pb = Lb->next;
	LNode* pc = Lc = La; // 用La的头结点作为Lc的头结点
	while (pa && pb)
	{
		if (pa->data <= pb->data)
		{
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}
		else
		{
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	}
	pc->next = pa ? pa : pb; // 插入剩余段
	free(Lb); // 释放Lb的头结点
}