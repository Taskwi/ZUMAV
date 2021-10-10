#ifndef _LINKLIST_H_
#define _LINKLIST_H_

#include "ball.h"


#define X -10.0
#define Y 100.0

//typedef int DataType;
typedef ball DataType;
//重构成双向链表
typedef struct Node
{
    DataType data;
    struct Node* prior;
    struct Node *next;
} Node;


//下为双向链表的操作
Node* CreateEmptyList();

Node* CreateList(DataType *addr, unsigned int n);

void DestroyList(Node *head);

void ListInsert(Node *head, unsigned int index, DataType data);

//下为新增函数
Node* get(Node* head, int index);//提取给定序号结点的指针

void Nodedelete(Node* p, Node* head, int& score);//删除给定结点

bool exam1(Node* temp, Node* head, int& score);//检验插入后是否进行第一次消除

void exam2(Node* temp, Node* head, int& score);//检测消除后是否需要继续消除

Node* lexam(Node* temp, Node* head, int& score); //检测左边是否需要

Node* rexam(Node* temp, Node* head, int& score); //检测右边是否需要

int listcount(Node* temp, Node* head);//编译中，希望实现3个起消

int listlength(Node* head);

#endif
