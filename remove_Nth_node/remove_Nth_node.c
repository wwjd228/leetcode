#include <stdlib.h>
#include <stdio.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

static inline struct ListNode *removeNthFromENd( struct ListNode *head, int n )
{
    unsigned numOfNode = 0;
    struct ListNode *cur = NULL;
    struct ListNode *tmp = NULL;
    if (n != 0 && head != NULL) {
        for (cur = head ; cur -> next != NULL && cur ->next ->next != NULL ; cur = cur -> next)
	    numOfNode++;
	
	numOfNode++;
	if (n == 1) {
	    if ( cur ->next == NULL ) {
	        tmp = cur;
		head = NULL;
		free(tmp);
		return head;
	    }
	    
	    else {
	        tmp = cur -> next;
	        cur ->next = NULL;
		free(tmp);
	    }
	}

	else if ( n == (numOfNode+1)) {
	    tmp = head;
	    head = head ->next;
	    free(tmp);
	}
	
	else {
            for (cur = head ; numOfNode != n ; cur = cur -> next)
	        numOfNode--;
	    tmp = cur ->next;
	    cur ->next = tmp ->next;
            free(tmp);

	}
    }

    return head;
}

static inline struct ListNode *insert( struct ListNode *head, int val )
{
    struct ListNode *node = malloc(sizeof(struct ListNode));
    node ->val = val;
    node ->next = head;
    head = node;

    return head;
}

int main(void)
{
    struct ListNode *head = NULL;
    int node = 0;
    for (int i = 0 ; i < 2 ; i++) {
        head = insert(head, i);
    }
    
    for (struct ListNode *cur = head ; cur != NULL ; cur = cur ->next)
        printf("%d ", cur ->val);

    printf("\nPlz input the Nth node want to remove : ");
    scanf("%d", &node);
    head = removeNthFromENd(head, node);
    printf("the result is :\n");
    for (struct ListNode *cur = head ; cur != NULL ; cur = cur ->next)
        printf("%d ", cur ->val);

    printf("\n");
    //free(head);
    return 0;
}
