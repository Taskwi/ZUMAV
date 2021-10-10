#ifndef _LINKLIST_H_
#define _LINKLIST_H_

#include "ball.h"


#define X -10.0
#define Y 100.0

//typedef int DataType;
typedef ball DataType;
//�ع���˫������
typedef struct Node
{
    DataType data;
    struct Node* prior;
    struct Node *next;
} Node;


//��Ϊ˫������Ĳ���
Node* CreateEmptyList();

Node* CreateList(DataType *addr, unsigned int n);

void DestroyList(Node *head);

void ListInsert(Node *head, unsigned int index, DataType data);

//��Ϊ��������
Node* get(Node* head, int index);//��ȡ������Ž���ָ��

void Nodedelete(Node* p, Node* head, int& score);//ɾ���������

bool exam1(Node* temp, Node* head, int& score);//���������Ƿ���е�һ������

void exam2(Node* temp, Node* head, int& score);//����������Ƿ���Ҫ��������

Node* lexam(Node* temp, Node* head, int& score); //�������Ƿ���Ҫ

Node* rexam(Node* temp, Node* head, int& score); //����ұ��Ƿ���Ҫ

int listcount(Node* temp, Node* head);//�����У�ϣ��ʵ��3������

int listlength(Node* head);

#endif
