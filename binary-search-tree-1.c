/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left; // 왼쪽 자식 노드 포인터
	struct node *right; // 오른쪽 자식 노드 포인터
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command; // 사용자가 선택한 메뉴값 저장 변수 선언
	int key; // 노드에 입력할 값을 임시저장하는 변수 선언
	Node* head = NULL; // 프로그램 초기 실행시 head = NULL로 설정
	Node* ptr = NULL;	/* temp */

	printf("[----- 손영재 2018038080 -----]\n");
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head); // BST 초기화를 위한 함수 호출, 인자로 head의 주소를 넘김
			break;
		case 'q': case 'Q':
			freeBST(head); // BST의 모든 노드에 대한 할당 해제 및 초기화 함수 호출 후 종료
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key); // 삽입할 노드의 key값 입력받아
			insert(head, key); // insert()함수에 매개변수로 함께 전달
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key); // 제거할 단말노드의 key값 입력받아
			deleteLeafNode(head, key); // deleteLeafNode()함수 실행
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key); // 순환을 통한 탐색 함수 실행
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key); // 재귀를 통한 탐색 함수 실행
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left); // 중위 순회 함수 호출, 인자로 head->left, 즉 트리의 실질적인 root 주소를 보냄
			break;
		case 'p': case 'P':
			preorderTraversal(head->left); // 전위 순회 함수 호출, 인자로 head->left, 즉 트리의 실질적인 root 주소를 보냄
			break;
		case 't': case 'T':
			postorderTraversal(head->left); // 후위 순회 함수 호출, 인자로 head->left, 즉 트리의 실질적인 root 주소를 보냄
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) { // 헤드 노드의 값을 변경해야 하므로 이중포인터를 매개변수로 받음

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL) // 노드가 빈 노드가 아닐 경우
		freeBST(*h); // freeBST()함수를 통해 모든 노드에 대한 할당 해제 및 초기화

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); // 노드의 크기만큼 동적할당하여 헤드 노드 공간 할당
	(*h)->left = NULL;	/* root */
	(*h)->right = *h; // 헤드 노드의 오른쪽 자식은 자기 자신을 가리키도록 설정
	(*h)->key = -9999; // 헤드 노드의 key 값을 -9999로 설정
	return 1;
}



void inorderTraversal(Node* ptr) // 중위 순회 함수
{
	if (ptr){ // 매개변수로 받은 노드 포인터가 NULL이 아니면
		inorderTraversal(ptr->left); // 중위순회이므로 왼쪽 자식 탐색 먼저 실행, recursive로 호출
		printf("[%d] ", ptr->key); // 왼쪽 자식 탐색 마치면 ptr의 key 출력(visit)
		inorderTraversal(ptr->right); // ptr visit 후 오른쪽 자식 탐색 실행, recursive로 호출
	}
}

void preorderTraversal(Node* ptr) // 전위 순회 함수
{
		if (ptr){ // 매개변수로 받은 노드 포인터가 NULL이 아니면
		printf("[%d] ", ptr->key); // 전위순회이므로 먼저 ptr의 key 출력(visit)
		preorderTraversal(ptr->left); // ptr visit 후 왼쪽 자식 탐색 실행, recursive로 호출
		preorderTraversal(ptr->right); // 왼쪽 자식 탐색 마친 후 오른쪽 자식 탐색 실행, recursive로 호출
	}
}

void postorderTraversal(Node* ptr) // 후위 순회 함수
{
		if (ptr){ // 매개변수로 받은 노드 포인터가 NULL이 아니면
		postorderTraversal(ptr->left); // 후위순외이므로 먼저 왼쪽 자식 탐색 실행, recursive로 호출
		postorderTraversal(ptr->right); // 왼쪽 자식 탐색 마친 후 오른쪽 자식 탐색 실행, recursive로 호출
		printf("[%d] ", ptr->key); // 왼쪽, 오른쪽 자식 탐색을 마친후 ptr의 key 출력(visit)
		}
}


int insert(Node* head, int key) // 노드 삽입 함수, 매개변수로 헤드 노드 주소와 새로 추가하는 노드에 입력할 key값 받음
{
	Node* temp = (Node*)malloc(sizeof(Node*)); // 노드 포인터 temp 선언하여 노드만큼의 공간 동적할당
	Node* ptr = head->left; // ptr이 head->left 가리키게 하여 실질적인 tree의 root 가리키게 함
	temp->key = key; // temp의 key에 매개변수로 받은 key 입력
	temp->left = NULL; // temp->left와 temp->right를 각각 NULL로 초기화
	temp->right = NULL;
	if(!ptr) // ptr, 즉 head->left가 NULL일 때 NULL 트리이므로
	{
		head->left = temp; // head->left에 새로 추가한 temp로 설정 
	}
	else
	{
	while(ptr) // NULL 트리가 아닌 경우
	{
		if(key == ptr->key) // 기존 노드에 key값과 동일한 값을 가진 경우
		{
			printf("BST에 같은 값을 가지는 노드를 추가할 수 없습니다.\n");
			return 0; // 오류 메시지 출력 및 종료
		}
		if(key < ptr->key) // 입력할 key값이 ptr->key보다 작은 경우
		{
			if(ptr->left!=NULL) // ptr->left가 NULL이 아닌 경우, 즉 왼쪽 자식 노드가 있을 경우
				ptr = ptr->left; // ptr을 ptr->left로 변경
			else // ptr->left가 NULL일 경우, 즉 ptr의 왼쪽 자식노드로 추가해야 하는 경우
			{
				ptr->left = temp; // ptr->left에 temp 대입후 while문 탈출
				break;
			}
		}	
		else if(key > ptr->key) // 입력할 key값이 ptr->key보다 큰 경우
		{
			if(ptr->right!=NULL) // ptr->left가 NULL이 아닌 경우, 즉 오른쪽 자식 노드가 있을 경우
			{
			ptr = ptr->right; // ptr을 ptr->right로 변경
			}
			else // ptr->right가 NULL일 경우, 즉 ptr의 오른쪽 자식노드로 추가해야 하는 경우
			{
				ptr->right = temp; // ptr->right에 temp 대입후 while문 탈출
				break;
			}
		}
	}
	}



}

int deleteLeafNode(Node* head, int key) // 단말 노드를 제거하는 함수
{
	Node* temp = searchIterative(head, key); // 입력한 key값과 동일한 값을 가진 단말노드가 있는지 탐색
	if(temp == NULL) // key값과 동일한 단말 노드가 없는 경우
	{
		printf("해당 노드가 없습니다.\n"); // 오류 메시지 출력 및 함수 종료
		return 0;
	}
	else if(temp->left!=NULL||temp->right!=NULL) // 입력한 key값과 동일한 노드가 단말 노드가 아닌 경우
	{
		printf("해당 노드는 단말 노드가 아닙니다.\n"); // 오류 메시지 출력 및 함수 종료
		return 0;
	}
	Node* prevtemp = head->left; // 제거할 단말 노드의 부모노드 주소를 저장할 prevtemp 변수 선언
	while(prevtemp) // 부모 노드를 찾을 때까지 반복
	{
		if(prevtemp->left == temp) // 부모노드가 왼쪽 자식 노드로서 temp를 가질 경우
			{
				prevtemp->left = NULL; // prevtemp->left를 NULL로 하여 연결 관계 끊어줌
				return 0;
			}
		else if(prevtemp->right == temp) // 부모노드가 오른쪽 자식 노드로서 temp를 가질 경우
			{
				prevtemp->right = NULL;  // prevtemp->right를 NULL로 하여 연결 관계 끊어줌
				return 0;
			}

		if(key < prevtemp->key) // 부모 노드를 찾을 때까지 iterative 탐색 반복
			prevtemp = prevtemp->left;
		else prevtemp = prevtemp->right;
	}

	free(temp); // 부모 노드를 찾아 연결 관계를 끊은 후 해당 단말 노드에 대한 할당 해제



}

Node* searchRecursive(Node* ptr, int key) // Recursive 탐색 함수
{
	if(!ptr) // NULL tree이거나 탐색을 실패한 경우
		return NULL; // NULL값 반환
	if(key == ptr->key) // recursive 탐색을 성공한 경우
		return ptr; // 탐색한 노드의 주소 반환
	if(key < ptr->key) // 매개변수로 받은 key가 ptr->key보다 작은 경우
		return searchRecursive(ptr->left, key); // ptr의 좌측 subtree에 대한 recursive 탐색 함수 실행
	else return searchRecursive(ptr->right, key); // 반대로 큰 경우 ptr의 우측 subtree에 대한 recursive 탐색 함수 실행
}

Node* searchIterative(Node* head, int key) // Iterative 탐색 함수
{
	Node* ptr = head->left; // ptr을 tree의 root를 가리키도록 설정
	while(ptr) // 탐색을 성공할 때까지(ptr이 NULL이 아닐때까지)
	{
		if(key == ptr->key) // 동일한 값을 가지는 노드 탐색을 성공한 경우
			return ptr; // 해당 노드의 주소 반환
		if(key < ptr->key) // key 값이 ptr->key보다 작은 경우
			ptr = ptr->left; // ptr이 좌측 자식 노드를 가리키도록 설정
		else ptr = ptr->right; // 반대로 클 경우 ptr이 우측 자식 노드를 가리키도록 설정
	}
	return NULL; // 탐색을 실패한 경우 NULL 반환
}


int freeBST(Node* head) // BST의 모든 노드에 대한 할당을 해제하는 recursive 함수
{
	Node* temp; // 노드 포인터 temp 선언
	if(head->left == NULL && head->right == head) // 매개변수로 받은 head가 헤드 노드일 경우
		{
			temp = head->left; // temp가 tree의 root을 가리키도록 설정
		}
	else // 매개변수로 받은 head가 헤드 노드가 아닌 경우
	{
		temp = head; // temp를 head로 설정
	}

	if(!temp) // temp가 NULL이 아닌 경우, 즉 할당을 해제해야 하는 노드를 가리키는 경우
	{
		freeBST(temp->left); // temp의 좌측 자식 노드에 대한 freeBST()함수를 recursive로 실행
		freeBST(temp->right); // temp의 우측 자식 노드에 대한 freeBST()함수를 recursive로 실행
		free(temp); // 자식 노드에 대한 할당 해제 함수 실행을 모두 마친 경우 temp의 할당을 해제

	}
}





