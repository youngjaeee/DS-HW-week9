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
	struct node *left;
	struct node *right;
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
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

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
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)
{
	if (ptr){
		inorderTraversal(ptr->left);
		printf("[%d] ", ptr->key);
		inorderTraversal(ptr->right);
	}
}

void preorderTraversal(Node* ptr)
{
		if (ptr){
		printf("[%d] ", ptr->key);
		inorderTraversal(ptr->left);
		inorderTraversal(ptr->right);
	}
}

void postorderTraversal(Node* ptr)
{
		inorderTraversal(ptr->left);
		inorderTraversal(ptr->right);
		printf("[%d] ", ptr->key);
}


int insert(Node* head, int key)
{
	Node* temp = (Node*)malloc(sizeof(Node*));
	Node* ptr = head->left;
	temp->key = key;
	temp->left = NULL;
	temp->right = NULL;
	if(!ptr)
	{
		head->left = temp;
		printf("first node\n");
	}
	else
	{
	while(ptr)
	{
		if(key == ptr->key)
		{
			printf("BST에 같은 값을 가지는 노드를 추가할 수 없습니다.\n");
			return 0;
		}
		if(key < ptr->key)
		{
			printf("key < ptr->key\n");
			if(ptr->left!=NULL)
				ptr = ptr->left;
			else
			{
				ptr->left = temp;
				printf("기존 leaf 노드의 자식노드 추가\n");
				break;
			}
		}	
		else if(key > ptr->key)
		{
			printf("key > ptr->key\n");
			if(ptr->right!=NULL)
			{
			printf("자식노드 존재\n");
			ptr = ptr->right;
			}
			else 
			{
				ptr->right = temp;
				printf("기존 leaf 노드의 자식노드 추가\n");
				break;
			}
		}
	}
	}



}

int deleteLeafNode(Node* head, int key)
{
	Node* temp = searchIterative(head, key);
	if(temp == NULL)
	{
		printf("해당 노드가 없습니다.\n");
		return 0;
	}
	else if(temp->right!=NULL||temp->right!=NULL)
	{
		printf("해당 노드는 단말 노드가 아닙니다.\n");
		return 0;
	}
	Node* prevtemp = head->left;
	while(prevtemp)
	{
		if(prevtemp->left == temp)
			{
				prevtemp->left = NULL;
				return 0;
			}
		else if(prevtemp->right == temp)
			{
				prevtemp->right = NULL;
				return 0;
			}

		if(key < prevtemp->key)
			prevtemp = prevtemp->left;
		else prevtemp = prevtemp->right;
	}

	free(temp);



}

Node* searchRecursive(Node* ptr, int key)
{
	if(!ptr)
		return NULL;
	if(key == ptr->key)
		return ptr;
	if(key < ptr->key)
		return searchRecursive(ptr->left, key);
	else return searchRecursive(ptr->right, key);
}

Node* searchIterative(Node* head, int key)
{
	Node* ptr = head->left;
	while(ptr)
	{
		if(key == ptr->key)
			return ptr;
		if(key < ptr->key)
			ptr = ptr->left;
		else ptr = ptr->right;
	}
	return NULL;
}


int freeBST(Node* head)
{
	Node* temp;
	if(head->left == NULL && head->right == head)
		{
			temp = head->left;
		}
	else 
	{
		temp = head;
	}

	if(!temp)
	{
		freeBST(temp->left);
		freeBST(temp->right);
		free(temp);

	}
}





