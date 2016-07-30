#include <stdlib.h>
#include <stdio.h>

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

struct ListNode* reverseBetween(struct ListNode* head, int m, int n) {
    int len = 0, i = 1;
    len = listlen(head);
    struct ListNode *parent = NULL, *child = NULL;
    if ( m == 1 ) // case : head
        child = head;

    if (m > 0 && n > m && n <= len) {
        for (struct ListNode *walk = head ; walk ; walk = walk -> next) {
	    if ( i == (m - 1) ) {
	        parent = walk;
		child = walk ->next;
	    }

	    if ( i > m && i <= n) {
	        child ->next = walk ->next;
	        if ( m != 1 ) {
	            walk ->next = parent ->next;
		    parent ->next = walk;
		}

		else {
		    walk ->next = head;
                    head = walk;
                }

		walk = child;
	    }

	    i++;
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
    int m = 0, n = 0;
    if (argc == 3) {
        m = atoi(argv[1]);
	n = atoi(argv[2]);
    }

    else 
        return 1;

    for (int i = 5 ; i > 0 ; i--) {
        head = insert(head, i);
    }
    
    for (struct ListNode *cur = head ; cur != NULL ; cur = cur ->next)
        printf("%d ->", cur ->val);
    
    printf("NULL\nReversing the linked list between node %dth and %dth...\n", m, n);
    head = reverseBetween(head, m, n);
    printf("the result is :\n");
    for (struct ListNode *cur = head ; cur != NULL ; cur = cur ->next)
        printf("%d ->", cur ->val);

    printf("NULL\n");
    free(head);
    return 0;
}
