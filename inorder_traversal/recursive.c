#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

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
