// C Program to delete all occurrences of a given key in linked list
#include <stdio.h>
#include <stdlib.h>

// A linked list node
struct node
{
    int data;
    struct node *next;
};

void push(struct node** head_ref, int new_data)
{
    struct node* new_node = (struct node*) malloc(sizeof(struct node));
    new_node->data  = new_data;
    new_node->next = (*head_ref);
    (*head_ref)    = new_node;
}


void deleteKey(struct node **head_ref, int key)
{
    struct node* temp = *head_ref, *prev;
    
    // If head node itself holds the key or multiple occurrences of key
    while (temp != NULL && temp->data == key)
    {
        *head_ref = temp->next;   // Changed head
        free(temp);               // free old head
        temp = *head_ref;         // Change Temp
    }
    
    // Delete occurrences other than head
    while (temp != NULL)
    {
        // Search for the key to be deleted, keep track of the
        // previous node as we need to change 'prev->next'
        if (temp->data != key)
        {
            prev = temp;
            temp = temp->next;
        }
        else
        {
            // Unlink the node from linked list
            prev->next = temp->next;
            
            free(temp);  // Free memory
            
            //Update Temp for next iteration of outer loop
            temp = prev->next;
        }
    }
}

// This function prints contents of linked list starting from
// the given node
void printList(struct node *node)
{
    while (node != NULL)
    {
        printf(" %d ", node->data);
        node = node->next;
    }
}

/* Drier program to test above functions*/
int main()
{
    /* Start with the empty list */
    struct node* head = NULL;
    
    push(&head, 7);
    push(&head, 2);
    push(&head, 3);
    push(&head, 2);
    push(&head, 8);
    push(&head, 1);
    push(&head, 2);
    push(&head, 2);
    
    int key = 2; // key to delete
    
    puts("Created Linked List: ");
    printList(head);
    
    deleteKey(&head, key);
    puts("\nLinked List after Deletion of 2: ");
    
    printList(head);
    return 0;
}


/**
// Short Recursive Solution in C++

//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        
        if(!head)
            return NULL;
        
        head->next = removeElements(head->next, val);
        return (head->val == val) ? (head->next) : head;
    }
};

*/