#include "LinkList.h"


/*
Args:
	* None.
Return:
	* Pointer of the head node.
Description:
	* Create an empty linked list with a head node.
	* The "next" field of the head node should point to NULL.
*/
Node* CreateEmptyList()//双向链表
{
	Node* head;

	head = (Node*)malloc(sizeof(Node));
	head->prior = NULL;
	head->next = NULL;

	return head;
}


/*
Args:
	* addr: pointer of an array.
	* n: length of the array.
Return:
	* Pointer of the head node.
Description:
	* Initialize a linked list with an array.
*/
Node* CreateList(DataType* addr, unsigned int n)
{
	Node* head;

	head = (Node*)malloc(sizeof(Node));
	//便于碰撞 给头结点赋予一个不画球的初始位置，后续可利用内积进行插入
	head->data.x = X;
	head->data.y = Y;
	head->prior = NULL;
	head->next = NULL;

	for (unsigned int i = 0; i < n; i++)
	{
		ListInsert(head, i, addr[i]);
	}

	return head;
}


/*
Args:
	* head: pointer of the head node.
Returns:
	* None
Description:
	* Destroy the linked list.
	* Release all allocated memory.
*/
void DestroyList(Node* head)
{
	Node* p;


	while (head->next != NULL)
	{
		p = head->next;
		free(head);
		head = p;
	}
	free(head);

}


/*
Args:
	* head: pointer of the head node.
	* index: index of the inserted data.
	* data: the inserted data.
Returns:
	* None.
Description:
	*   If the linked list is "head->3->5->2",
	* when you call (head, 0, 6), the linked
	* list will be "head->6->3->5->2".
*/
void ListInsert(Node* head, unsigned int index, DataType data)
{
	unsigned int j = 0;
	Node* p = head;

	while (p && j < index)
	{
		p = p->next;
		++j;
	}
	if (p == NULL)
		return;

	Node* s = (Node*)malloc(sizeof(Node));
	s->data = data;
	s->next = p->next;
	if (p->next) p->next->prior = s;
	p->next = s;
	s->prior = p;
}


//new

void Nodedelete(Node* p, Node* head,int &score)//删除给定结点
{
	Node* end = head;
	if (!p) return;
	score++;
	for (; end->next;)end = end->next;//end指向链表末尾
	if (p->prior == head) {
		head->next = p->next;
		if (p->next) p->next->prior = head;
		free(p);
		return;
	}//第一个元素
	if (p == end) {
		p->prior->next = NULL;
		free(p);
		return;
	}//最后一个元素
	p->prior->next = p->next;
	p->next->prior = p->prior;
	free(p);
	return;
}

Node* get(Node* head, int index)
{
	int j = 0;
	Node* p = head;

	while (p->next && j < index)
	{
		p = p->next;
		++j;
	}
	return p->next;
}

bool exam1(Node* temp, Node* head, int& score)//此函数旨在检验是否需要删除结点周围的球，若是则返回true进行下一步检测
{
	Node* left = NULL;
	Node* right = NULL;
	bool t = false;
	if (temp->prior != head) {
		left = temp->prior;
		while (left != head && left->data.c == temp->data.c) {
			Nodedelete(left, head,score);
			left = temp->prior;
			t = true;
		}
	}
	if (temp->next != NULL) {
		right = temp->next;
		while (right != NULL && right->data.c == temp->data.c) {
			Nodedelete(right, head,score);
			right = temp->next;
			t = true;
		}
	}
	return t;
}

void exam2(Node* temp, Node* head, int& score)//此为检测2，检测待删除结点在消除后两侧是否仍为同色，若是则消除，继续运行到两侧无同色为止
{
	int count;
	if (temp->prior == head || temp->next == NULL) {
		Nodedelete(temp, head,score);
		return;
	}
	Node* tleft, * tright;
	tleft = temp->prior;
	tright = temp->next;
	Nodedelete(temp, head,score);
	count = listcount(tleft, head);
	for (; count>=3&&tleft != head && tright != NULL;) {
		tleft = lexam(tleft, head,score);
		tright = rexam(tright, head,score);
		count = listcount(tleft, head);
	}
}

Node* lexam(Node* temp,Node *head, int& score)//检测左边是否需要
{
	Node* left;
	if (temp->prior != head) {
		left = temp->prior;
		while (left != head && left->data.c == temp->data.c) {
			Nodedelete(left, head,score);
			left = temp->prior;
		}
		Node* temp2;
		temp2 = temp->prior;
		Nodedelete(temp, head,score);
		return temp2;
	}
	else {
		Nodedelete(temp, head,score);
			return head;
	}
}

Node* rexam(Node *temp,Node*head, int& score)//检测右边是否需要
{
	Node* right;
	if (temp->next != NULL) {
		right = temp->next;
		while (right != NULL && right->data.c == temp->data.c) {
			Nodedelete(right, head,score);
			right = temp->next;
		}
		Node* temp2;
		temp2 = temp->next;
		Nodedelete(temp, head,score);
		return temp2;
	}
	else {
		Nodedelete(temp, head,score);
		return NULL;
	}
}

int listcount(Node* temp, Node* head)//计数，3个起消
{
	if (temp== head || temp == NULL) return -1;
	Node* left, * right;
	int count=1;
	left = temp->prior;
	right = temp->next;
	for (; left != head && left->data.c == temp->data.c; count++) left = left->prior;
	for (; right != NULL && right->data.c == temp->data.c; count++) right = right->next;
	return count;
}

int listlength(Node *head)
{
	Node* p = head;
	int count=0;
	for (; p->next; p = p->next) count++;
	return count;
}
