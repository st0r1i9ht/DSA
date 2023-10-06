#include <stdio.h>
#include <stdlib.h>
#include "DataStructure.h"

//�������Ա�
#define MAXSIZE 100 // ���Ա�洢�ռ�ĳ�ʼ������
typedef struct
{
	ElemType* elem;
	int length;// ��ǰ����
}SqList;

//// ����ʽ
//#define MAXSIZE 1000 // ����ʽ���ܴﵽ����󳤶�
//
//typedef struct // ����ʽ������Ķ���
//{
//	float* p; // ϵ��
//	int e; // ָ��
//}Polynomial;
//
//typedef struct
//{
//	Polynomial* elem; // �洢�ռ�Ļ���ַ
//	int length;// ����ʽ�е�ǰ��ĸ���
//}SqList;// ����ʽ��˳��洢�ṹ����ΪSqList
//
// //ͼ���
//#define MAXSIZE 10000 // ͼ�����ܴﵽ����󳤶�
//
//typedef struct
//{
//	// ͼ����Ϣ����
//	char no[20]; // ͼ��ISBN
//	char name[50]; // ͼ������
//	float price; // ͼ��۸�
//}Book;
//
//typedef struct
//{
//	Book* elem; // �洢�ռ�Ļ���ַ
//	int length; // ͼ����е�ǰͼ�����
//}SqList; // ͼ����˳��洢�ṹ����ΪSqList


 //���Ա����������ʵ��
 //���Ա�ĳ�ʼ��(����������)
Status InitList_Sq(SqList *L)
{
	// ����һ���յ�˳���L
	L->elem = (ElemType*)malloc(MAXSIZE * sizeof(ElemType)); // Ϊ˳������ռ�
	if (!L->elem) exit(OVERFLOW); // ˳�����ʧ��
	L->length = 0; // �ձ���Ϊ0
	return OK;
}

 //�������Ա�
void DestroyList(SqList* L)
{
	if (L->elem)
		free(L->elem); // �ͷŴ洢�ռ�
}

 //������Ա�L
void ClearList(SqList* L)
{
	L->length = 0; // �����Ա�ĳ�����Ϊ0
}

 //�����Ա�L�ĳ���
int GetLength(SqList L)
{
	return(L.length);
}

 //�ж����Ա�L�Ƿ�Ϊ��
int IsEmpty(SqList L)
{
	if (L.length == 0)
		return 1;
	else return 0;
}

 //˳����ȡֵ������λ��i��ȡ��Ӧλ������Ԫ�ص����ݣ�
int GetElem(SqList L, int i, ElemType* e)
{
	if (i < 1 || i > L.length)
		return ERROR; // �ж�iֵ�Ƿ���� �������� ����ERROR
	*e = L.elem[i - 1]; // ��i-1�ĵ�Ԫ�洢�ŵ�i������
	return OK;
}
 //�����ȡ Ч�ʸ� �㷨���Ӷ�O(1)

 //˳���Ĳ��� ��ֵ����
int LocateElem(SqList L, ElemType e)
{
	// �����Ա�L�в���ֵΪe������Ԫ�� ��������ţ��ǵڼ���Ԫ�أ�
	for (int i = 0; i < L.length; i++)
	{
		if (L.elem[i] == e)
			return i + 1; // ���ҳɹ� �������
	}
	return 0; // ����ʧ�� ����0
}
 //ƽ�����ҳ��� ASL(Average Search Length)
 //ASL = (n + 1)/2

 //˳���Ĳ���
 //�㷨˼�룺
 //1. �жϲ���λ��i�Ƿ�Ϸ�
 //2. �ж�˳���Ĵ洢�ռ��Ƿ����� ����������ERROR
 //3. ����n����iλ��Ԫ����������ƶ�һ��λ�� �ճ���i��λ��
 //4. ��Ҫ�������Ԫ��e�����i��λ��
 //5. ����1 ����ɹ�����OK
Status ListInsert_Sq(SqList* L, int i, ElemType e)
{
	if (i < 1 || i > L->length + 1)
		return ERROR;// iֵ���Ϸ�
	if (L->length == MAXSIZE)
		return ERROR;// ��ǰ�洢�ռ�����
	for (int j = L->length - 1; j >= i - 1; j--)
		L->elem[j + 1] = L->elem[j]; // ����λ�ü�֮���Ԫ�غ���
	L->elem[i - 1] = e; // ����Ԫ��e�����i��λ��
	L->length++; // ����1
	return OK;
}
 //�㷨����
 //ƽ���ƶ�����n/2
 //O(n)

 //˳����ɾ��
 //1. �ж�ɾ��λ��i�Ƿ�Ϸ� 1 <= i <= n
 //2. ��Ҫɾ����Ԫ�ر�����e��
 //3. ����i + 1����nλ��Ԫ��һ����ǰ�ƶ�һ��λ��
 //4. ����1 ɾ���ɹ�����OK
Status ListDelete_Sq(SqList* L, int i)
{
	if ((i < 1) || (i > L->length)) return ERROR; // iֵ���Ϸ�
	for (int j = i; j <= L->length - 1; j++)
		L->elem[j - 1] = L->elem[j]; // ��ɾ��Ԫ��֮���Ԫ��ǰ��
	L->length--; // ����1
	return OK;
}
 //O(n)

 //������ı�ʾ�Ͷ���
 //��㶨��
typedef struct LNode
{ // �����������ͺ�ָ��ڵ��ָ������
	ElemType data; // ������
	struct LNode* next; // ָ����
}LNode, * LinkList; // LinkListΪָ��ṹ��LNode��ָ������

//LinkList L; // ��������
//LNode* p; // ������

//// ���� �洢ѧ����Ϣ
//typedef struct
//{
//	char num[8];
//	char name[8];
//	int score;
//}ElemType;
//
//typedef struct student
//{
//	ElemType data; // ������
//	struct student* next; // ָ����
//}LNode, *LinkList;

// ������ĳ�ʼ�� ����һ���ձ� ��ͷ���
// 1. �����½����Ϊͷ��� ��ͷָ��Lָ��ͷ�ڵ�
// 2. ��ͷ����ָ���ÿ�
Status InitList_L(LinkList L)
{
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;
	return OK;
}

// �ж������Ƿ�Ϊ��
// �ж�ͷ���ָ�����Ƿ�Ϊ��
int ListEmpty(LinkList L) // ��LΪ�ձ� �򷵻�1 ���򷵻�0
{
	if (L->next) // �ǿ�
		return 0;
	else
		return 1;
}

// ����������
// ��ͷָ�뿪ʼ �����ͷ����н��
Status DestroyList(LinkList L) // ���ٵ�����L
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

 //�������
 //�����ͷ����н�� ����ͷ���ָ��������Ϊ��
Status ClearList(LinkList L) // ��L����Ϊ�ձ�
{
	LNode* p, * q;
	p = L->next;
	while (p)
	{
		q = p->next;
		free(p);
		p = q;
	}
	L->next = NULL; // ͷ���ָ����Ϊ��
	return OK;
}

 //������ı�
 //����Ԫ��㿪ʼ ���μ������н��
int ListLength_L(LinkList L) // ����L������Ԫ�ظ���
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

 //ȡֵ
 //˳���ȡ
Status GetElem_L(LinkList L, int i, ElemType *e) // ��ȡ���Ա�L�е�ĳ������Ԫ�ص����� ͨ������e����
{
	LNode* p = L->next; int j = 1;
	while (p && j < i)
	{
		p = p->next; ++j;
	}
	if (!p || j > i) return ERROR; // ��i��Ԫ�ز�����
	e = p->data; // ȡ��i��Ԫ��
	return OK;
}

 //��ֵ����
LNode* LocateElem_L(LinkList L, ElemType e) // �����Ա�L�в���ֵΪe������Ԫ��
{
	// �ҵ��򷵻�L��ֵΪe������Ԫ�صĵ�ַ ����ʧ�ܷ���NULL
	LNode* p = L->next;
	while (p && p->data != e)
		p = p->next;
	return p;
}

int LocateElem_L(LinkList L, ElemType e) // �����Ա�L�в���ֵΪe������Ԫ�ص�λ�����
{
	// ����L��ֵΪe������Ԫ�ص�λ����� ����ʧ�ܷ���0
	LNode* p = L->next; int j = 1;
	while (p && p->data != e)
	{
		p = p->next; j++;
	}
	if (p) return j;
	else return 0;
}

 //����
 //��L�е�i��Ԫ��֮ǰ��������Ԫ��e
Status ListInsert_L(LinkList L, int i, ElemType e)
{
	LNode* p = L; // ��ʼ��ָ��
    int j = 0; // ��¼ָ��λ��
	while (p && j < i - 1) // Ѱ�ҵ�i - 1��� p ָ��i - 1���
	{
		p = p->next;
		++j;
	}
	if (!p || j > i - 1) return ERROR; // i���ڱ�+1����С��1 ����λ�÷Ƿ�
	LNode* s = (LNode*)malloc(MAXSIZE * sizeof(LNode));
	s->data = e; // �����½��s �����s����������Ϊe
	s->next = p->next;
	p->next = s;
	return OK;
}

 //ɾ��
 //�����Ա�L�еĵ�i������Ԫ��ɾ��
Status ListDelete_L(LinkList L, int i, ElemType* e)
{
	LNode* p = L;
	int j = 0;
	while (p->next && j < i - 1) // Ѱ�ҵ�i����� ����pָ����ǰ��
	{
		p = p->next;
		++j;
	}
	if (!(p->next) || j > i - 1) return ERROR; // ɾ��λ�ò�����
	LNode* q = p->next; // ��ʱ���汻ɾ���Ľ���Ա��ͷ�
	p->next = q->next; // �ı�ɾ���ڵ�ǰ���ڵ��ָ����
	e = q->data; // ����ɾ���ڵ��������
	free(q); // �ͷ�ɾ�����Ŀռ�
	return OK;
}

 //����O(n) �����ɾ��O(1)

 //����������
 //ͷ�巨 ǰ�巨 O(n)
void CreateList_H(LinkList L, int n)
{
	L = (LinkList)malloc(MAXSIZE * sizeof(LNode));
	L->next = NULL; // �Ƚ���һ����ͷ���ĵ�����
	for (int i = n; i > 0; --i)
	{
		LNode* p = (LNode*)malloc(MAXSIZE * sizeof(LNode));
		scanf("%d", &p->data); // ����Ԫ��ֵ
		p->next = L->next; // ���뵽��ͷ
		L->next = p;
	}
}

 //β�巨 O(n)
void CreatList_R(LinkList L, int n)
{
	L = (LinkList)malloc(MAXSIZE * sizeof(LNode));
	L->next = NULL;
	LNode* r = L; // βָ��rָ��ͷ���
	for (int i = 0; i < n; ++i)
	{
		LNode* p = (LNode*)malloc(MAXSIZE * sizeof(LNode));
		scanf("%d", &p->data);
		p->next = NULL;
		r->next = p; // ���뵽��β
		r = p; // rָ���µ�β���
	}
}

 //ѭ������
 //�ϲ�βָ��ѭ������
LinkList Connect(LinkList Ta, LinkList Tb) // Ta Tb���Ƿǿյĵ�ѭ������
{
	LNode* p = Ta->next; // p���ͷ���
	Ta->next = Tb->next->next; // Tb��ͷ����Ta��β
	free(Tb->next); // �ͷ�Tb��ͷ���
	Tb->next = p; // �޸�ָ��
	return Tb;
}

 //˫������
 //����
typedef struct DuLNode
{
	ElemType data;
	struct DuLNode* prior, * next;
}DuLNode, * DuLinkList;

 //˫��ѭ������Ĳ���
void ListInsert_DuL(DuLinkList L, int i, ElemType e) // �ڴ�ͷ����˫��ѭ������L�е�i��λ��֮ǰ����Ԫ��e
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

 //˫������ɾ�� O(n)
void ListDelete_DuL(DuLinkList L, int i, ElemType* e) // ɾ����ͷ����˫��ѭ������L�ĵ�i��Ԫ�� ����e����
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

// //���Ա�ϲ� ���� O(n^2)
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

 //�����ĺϲ� ˳���ʵ�� ʱ��O(n) �ռ�O(n)
void MergeList_Sq(SqList LA, SqList LB, SqList* LC)
{
	ElemType* pa = LA.elem;
	ElemType* pb = LB.elem; // ָ��pa��pb�ĳ�ֵ�ֱ�ָ��������ĵ�һ��Ԫ��
	LC->length = LA.length + LB.length; // �±���Ϊ���ϲ�����ĳ���֮��
	LC->elem = (ElemType*)malloc(LC->length * sizeof(ElemType));// Ϊ�ϲ�����±����һ������ռ�
	ElemType* pc = LC->elem; // ָ��pcָ���±��һ��Ԫ��
	ElemType* pa_last = LA.elem + LA.length - 1; // ָ��pa_lastָ��LA������һ��Ԫ��
	ElemType* pb_last = LB.elem + LB.length - 1; // ָ��pb_lastָ��LB������һ��Ԫ��
	while (pa <= pa_last && pb <= pb_last) // �������ǿ�
	{
		if (*pa <= *pb) // ���Ρ�ժȡ��������ֵ��С�Ľ��
			*pc++ = *pa++;
		else
			*pc++ = *pb++;
	}
	while (pa <= pa_last) // LB���ѵ����β ��ʣ��Ԫ�ؼ���LC
		*pc++ = *pa++;
	while (pb <= pb_last) // LA���ѵ����β ��ʣ��Ԫ�ؼ���LC
		*pc++ = *pb++;
}

 //�����ĺϲ� ����ʵ�� ʱ��O(n) �ռ�O(1)
void MergeList_L(LinkList La, LinkList Lb, LinkList Lc)
{
	LNode* pa = La->next;
	LNode* pb = Lb->next;
	LNode* pc = Lc = La; // ��La��ͷ�����ΪLc��ͷ���
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
	pc->next = pa ? pa : pb; // ����ʣ���
	free(Lb); // �ͷ�Lb��ͷ���
}