#include <stdlib.h>
#include <stdio.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

static inline struct ListNode *removeNthFromENd( struct ListNode *head, int n )
{
    struct ListNode *front = head, *back= head, *tmp = NULL;
    if ( head == NULL || n == 0 )
        return head;

    while (front) {
        front = front->next;
	if (n-- < 0)
	    back = back->next;
    }

    if ( n <= 0 ) {
        if (n == 0) {
            tmp = head;
            head = head->next;

        }

        else {
            tmp = back ->next;
            back->next = back->next->next;

        }
    }

    free(tmp);
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
    for (int i = 0 ; i < 10 ; i++) {
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
    free(head);
    return 0;
}
