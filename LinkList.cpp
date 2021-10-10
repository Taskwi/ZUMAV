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
Node* CreateEmptyList()//˫������
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
	//������ײ ��ͷ��㸳��һ��������ĳ�ʼλ�ã������������ڻ����в���
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

void Nodedelete(Node* p, Node* head,int &score)//ɾ���������
{
	Node* end = head;
	if (!p) return;
	score++;
	for (; end->next;)end = end->next;//endָ������ĩβ
	if (p->prior == head) {
		head->next = p->next;
		if (p->next) p->next->prior = head;
		free(p);
		return;
	}//��һ��Ԫ��
	if (p == end) {
		p->prior->next = NULL;
		free(p);
		return;
	}//���һ��Ԫ��
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

bool exam1(Node* temp, Node* head, int& score)//�˺���ּ�ڼ����Ƿ���Ҫɾ�������Χ���������򷵻�true������һ�����
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

void exam2(Node* temp, Node* head, int& score)//��Ϊ���2������ɾ������������������Ƿ���Ϊͬɫ���������������������е�������ͬɫΪֹ
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

Node* lexam(Node* temp,Node *head, int& score)//�������Ƿ���Ҫ
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

Node* rexam(Node *temp,Node*head, int& score)//����ұ��Ƿ���Ҫ
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

int listcount(Node* temp, Node* head)//������3������
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
