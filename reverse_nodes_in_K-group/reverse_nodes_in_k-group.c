#include <stdio.h>
#include <stdlib.h>
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode {
    int val;
    struct ListNode *next;
};

static inline int listlen( struct ListNode *head )
{
    int len = 0;
    for (struct ListNode *walk = head ; walk ; walk = walk ->next)
	len++;
    return len;
}

struct ListNode* reverseKGroup(struct ListNode* head, int k) {
    int len = 0, times = 0, change = 0, seg = 0;
    struct ListNode *front = head, *tail = head;
    len = listlen(head);
    seg = len / k;
    if ( k > 1 && k <= len ) {
        for (struct ListNode *walk = head ; walk ; walk = walk ->next) {
	    change %= k;
            if (change == 0) {
	        front = tail;
	        tail = walk;
	        times++;
	    }

	    if ( times <= seg ) {
	        if ( change > 0 && change < k ) {
	            tail ->next = walk ->next;
		    if (front != head) {
			// not head case
		        walk ->next = front ->next;
		        front ->next = walk;
		    }

		    else {
			// head case
			// head must be remembered
		        walk ->next = front;
			front = walk;
			head = walk;
		    }

		    walk = tail;
	        } 
	    }
        
	    else break; // done!

	    change++;
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

int main( int argc, char *argv[] )
{
    struct ListNode *head = NULL;
    int num = 0;
    if (argc == 2)
        num = atoi(argv[1]);

    else 
        return 1;

    for (int i = 10 ; i > 0 ; i--) {
        head = insert(head, i);
    }
    
    for (struct ListNode *cur = head ; cur != NULL ; cur = cur ->next)
        printf("%d ->", cur ->val);
    
    printf("NULL\nReversing the %d Group in linked list...\n", num);
    head = reverseKGroup(head, num);
    printf("the result is :\n");
    for (struct ListNode *cur = head ; cur != NULL ; cur = cur ->next)
        printf("%d ->", cur ->val);

    printf("NULL\n");
    free(head);
    return 0;
}
