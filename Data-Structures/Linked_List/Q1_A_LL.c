//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode; // You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList; // You should not change the definition of LinkedList

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;

	// Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertSortedLL(&ll, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The value %d was added at index %d\n", i, j);
			break;
		case 3:
			printf("The resulting sorted linked list is: ");
			printList(&ll);
			// removeAllItems(&ll); 임시 주석처리
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

/**
  * item을 오름차순으로 정렬된 링크드리스트에 삽입하는 함수
  * @param ll 삽입할 링크드 리스트
  * @param item 삽입할 정수 값
  * @return 삽입된 위치의 인덱스, 중복값이면 -1
  */
int insertSortedLL(LinkedList *ll, int item)
{
	/* add your code here */

	// 시작 노드 중복 값 제외
	if (ll->head != NULL && ll->head->item == item)
	{
		return -1;
	}
	
	// 링크드리스트에 노드가 없는 경우 or 시작 노드의 item이 매개변수 item보다 큰 경우 
	if (ll->head == NULL || ll->head->item > item)
	{
		// 힙에 ListNode의 크기만큼 메모리 할당
		// int 4바이트 + pointer 8바이트
		// 자료형이 ListNode(방금 힙에서 메모리 할당받은 구조체)인 변수를 가리키는 포인터
		ListNode *newNode = malloc(sizeof(ListNode));
		
		newNode->item = item;
		
		newNode->next = (ll->head == NULL) ? NULL : ll->head;
		
		ll->head = newNode;
		ll->size++;
		
		return 0;
	}
	
	// 현재 노드의 주소를 나타낼 포인터
	ListNode *cur;
	cur = ll->head;
	// 현재 인덱스 번호
	int idx = 1;
	// 인덱스 1번 부터 마지막 노드 전까지 탐색
	while (cur->next != NULL)
	{
		// 중복 값 제외
		if (cur->next->item == item)
		{
			return -1;
		}
		// 삽입할 위치 찾음
		if (cur->next->item > item)
		{
			ListNode *newNode = malloc(sizeof(ListNode));
			newNode->item = item;
			// 중간 삽입
			newNode->next = cur->next;
			cur->next = newNode;

			cur = newNode;
			ll->size++;

			return idx;
		}

		cur = cur->next;
		idx++;
	}
	// int item이 가장 큰 숫자
	if (cur->next == NULL && cur->item != item)
	{
		ListNode *newNode = malloc(sizeof(ListNode));
		newNode->item = item;
		// 마지막 삽입
		cur->next = newNode;
		newNode->next = NULL;
		ll->size++;

		return idx;
	}

	return -1;
}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll)
{

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}

void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL)
	{
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}

ListNode *findNode(LinkedList *ll, int index)
{

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0)
	{
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value)
{

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0)
	{
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}

	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL)
	{
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}

int removeNode(LinkedList *ll, int index)
{

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0)
	{
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL)
	{

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
