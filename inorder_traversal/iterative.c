#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

static struct Stack *head = NULL;

static inline void push( struct TreeNode *node )
{
    if ( node != NULL ) {
        struct Stack *tmp = malloc(sizeof(struct Stack));
	tmp ->node = node;
	tmp ->next = head;
	head = tmp;
    }

    else
        return;
}

static inline struct TreeNode * pop()
{
    struct TreeNode *returnNode = head ->node;
    struct Stack *tmp = head;
    head = head ->next;
    free(tmp);
    tmp = NULL;
    return returnNode;
}

static inline int *addToArray( int *array, int value, int size )
{
    int *resArray = malloc(size*sizeof(int));
    int indx = 0;
    for ( int i = 0 ; i < (size-1) ; i++) {
        resArray[indx] = array[i];
	indx++;
    }

    free(array);
    resArray[indx] = value;

    return resArray;
}

int *inorderTraversal(struct TreeNode *root, int *returnSize)
{
    int *resArray = NULL;
    if ( root == NULL ) 
        return NULL;

    int done = 0;
    struct TreeNode *walk = root;
    push(walk);
    while (!done) {
        if ( walk != NULL ) {
	    walk = walk ->left;
            push(walk);
	}

	else {
	    walk = pop();
	    (*returnSize)++;
            resArray = addToArray(resArray, walk ->val, (*returnSize));
	    walk = walk ->right;
	    push(walk);
	}

	if ( head == NULL )
	    done = 1;
	    
    }

    return resArray;
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
    for (int i = 0 ; i < 10 ; i++) {
        int tmp = scanf("%d", &value);
	if (tmp == EOF)
	    break;

	root = InsertNode(root, value);
    }   

    return root;
}

int main(void)
{
    struct TreeNode *tree = NULL;
    clock_t begin, end;
    double spend_time;
    int sizeOftree = 0;
    tree = CreateTree(tree);
    begin = clock();
    int *inorderArray = inorderTraversal(tree, &sizeOftree);
    end = clock();
    spend_time = (double) ( end - begin ) / CLOCKS_PER_SEC;  
    printf("[%d", inorderArray[0]);
    for ( int i = 1 ; i < sizeOftree ; i++ )
        printf(", %d", inorderArray[i]);

    printf("]\ntree size = %d, spend time = %lf\n", sizeOftree, spend_time);
    return 0;
}
