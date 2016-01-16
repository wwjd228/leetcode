#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define MAX(a,b) (a>b?a:b)

// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct Stack {
  struct TreeNode *node;
  struct Stack *next;
};

struct Stack *head = NULL;

static inline void push( struct TreeNode *node )
{
    if ( node == NULL )
        return;

    struct Stack *temp = malloc(sizeof(struct Stack));
    temp ->node = node;
    temp ->next = head;
    head = temp;
}

static inline struct TreeNode *pop()
{
    struct Stack *temp = head;
    struct TreeNode *result = head ->node;
    head = head ->next;
    free(temp);
    temp = NULL;
    return result;
}

int NumOfSubtree(struct TreeNode *subtree)
{
    if (subtree == NULL)
        return 0;

    else {
        int lnum = NumOfSubtree(subtree ->left);
	int rnum = NumOfSubtree(subtree ->right);
        return 1 + MAX(lnum, rnum);
    }
}

bool isBalanced(struct TreeNode *root)
{
    bool done = false;
    struct TreeNode *current = NULL;
    if (root == NULL)
        return true;
    
    current = root;
    while ( !done ) {
        push(current ->right);
	push(current ->left);
        if (abs(NumOfSubtree(current ->left) - NumOfSubtree(current ->right))>1)
            return false;

        if (head != NULL)
	    current = pop();

	else
	    done = true;
    }

    return true;
}

struct TreeNode * InsertNode(struct TreeNode *root, int value)
{
    if ( root == NULL ) {
        root = malloc(sizeof(struct TreeNode));
        root ->val = value;
	root ->left = NULL;
	root ->right = NULL;
    }

    else if ( value > root -> val )
        root ->right = InsertNode(root ->right, value);

    else
        root ->left = InsertNode(root ->left, value);

    return root;
}

struct TreeNode * CreateTree(struct TreeNode *root)
{
    int value;
    while (scanf("%d", &value) != EOF)
	root = InsertNode(root, value);

    return root;
}

int main(void)
{
    struct TreeNode *tree = NULL;
    clock_t begin, end;
    double spend_time;
    tree = CreateTree(tree);
    begin = clock();
    if (isBalanced(tree)) {
        end = clock();
	spend_time = (double) ( end - begin ) / CLOCKS_PER_SEC;
	printf("spend time = %lf\n", spend_time);
        return 1;
    }

    else {
        end = clock();
	spend_time = (double) ( end - begin ) / CLOCKS_PER_SEC;  
        printf("spend time = %lf\n", spend_time);
        return 0;
    }
}
