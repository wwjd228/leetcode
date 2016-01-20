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

struct Stack *s = NULL;

static inline void push( struct TreeNode *n )
{
    if ( n == NULL ) return;

    struct Stack *tmp = malloc(sizeof(struct Stack));
    tmp ->node = n;
    tmp ->next = s;
    s = tmp;
}

static inline struct TreeNode *pop()
{
    if ( s == NULL ) return NULL;

    struct TreeNode *res = NULL;
    struct Stack *tmp = s;
    res = tmp ->node;
    s = s ->next;
    free(tmp);
    tmp = NULL;
    return res;
}

static inline int isErrorNode( struct TreeNode **prev, struct TreeNode *cur )
{
    if ( *prev == NULL ) {
        *prev = malloc(sizeof(struct TreeNode));
	return 0;

    }

    else {
        if ( cur ->val >= (*prev) ->val )
	    return 0;

	else 
	    return 1;
    }
}

void findErrorNode( struct TreeNode *root, struct TreeNode **error, struct TreeNode **min, struct TreeNode **prev,  struct TreeNode *par )
{
    if (root == NULL)
        return;
    
    int done = 0;
    struct TreeNode *walk = root;
    push(walk);
    while ( !done ) {
        if ( walk != NULL ) {
	    walk = walk ->left;
            push(walk);
	}

	else {
	    walk = pop();
            if ( *error == NULL ) {
                if (isErrorNode(&(*prev), walk)) {
	            *error = *prev;
	            *min = malloc(sizeof(struct TreeNode));
	            (*min) = walk;
	        }

	        else
	            (*prev) = walk;
            } 

            else {
                if (walk ->val < (*min) ->val)
	            (*min) = walk;
            }
            
	    walk = walk ->right;
	    push(walk);
	}

	if ( s == NULL )
	    done = 1;
    }
}

static inline void swap( struct TreeNode **px, struct TreeNode **py )
{
    (*px) ->val ^= (*py) ->val;
    (*py) ->val ^= (*px) ->val;
    (*px) ->val ^= (*py) ->val;
}

void recoverTree(struct TreeNode *root)
{
    struct TreeNode *prev = NULL;
    struct TreeNode *error1 = NULL;
    struct TreeNode *error2 = NULL;
    findErrorNode(root, &error1, &error2, &prev, NULL);
    if ( error1 != NULL && error2 != NULL )
        swap( &error1, &error2 );
}

static inline int *combineSubtree( int *rtree, int *ltree, int value, int size, int lsize, int rsize )
{
    int *resArray = malloc(size*sizeof(int));
    int indx = 0;
    for ( int i = 0 ; i < lsize ; i++) {
        resArray[indx] = ltree[i];
	indx++;
    }

    free(ltree);
    resArray[indx] = value;
    indx++;

    for ( int i = 0 ; i < rsize ; i++ ) {
        resArray[indx] = rtree[i];
	indx++;
    }
    
    free(rtree);
    return resArray;
}

int *inorderTraversal(struct TreeNode *root, int *returnSize)
{
    int *rArray = NULL;
    int *lArray = NULL;
    if ( root == NULL ) 
        return NULL;
    
    int tmpSize = (*returnSize);
    lArray = inorderTraversal(root ->left, returnSize);
    int lsize = (*returnSize) - tmpSize;
    (*returnSize)++;
    tmpSize = (*returnSize);
    rArray = inorderTraversal(root ->right, returnSize);
    int rsize = (*returnSize) - tmpSize;
    return combineSubtree(rArray, lArray, root ->val, *returnSize, lsize, rsize);
}

struct TreeNode * InsertNode(struct TreeNode *root, int value)
{
    if ( root == NULL ) {
        root = malloc(sizeof(struct TreeNode));
        root ->val = value;
	root ->left = NULL;
	root ->right = NULL;
    }

    else {
        if ( root ->left == NULL )
            root ->left = InsertNode(root ->left, value);

        else if (root ->right == NULL)
            root ->right = InsertNode(root ->right, value);
	
	else 
	    root ->left = InsertNode(root ->left, value);
    }

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
    int sizeOftree = 0;
    tree = CreateTree(tree);
    begin = clock();
    recoverTree(tree);
    end = clock();
    spend_time = (double) ( end - begin ) / CLOCKS_PER_SEC; 
    int *inorderArray = inorderTraversal(tree, &sizeOftree);
    printf("[%d", inorderArray[0]);
    for ( int i = 1 ; i < sizeOftree ; i++ )
        printf(", %d", inorderArray[i]);

    printf("]\ntree size = %d, spend time = %lf\n", sizeOftree, spend_time);
    return 0;
}
