/* UNDERSTANDING DOUBLE POINTER
MEMORY ADDRESS = 1000, VALUE = 45
head = 1000, *head = 45
CREATE DOUBLE POINTER **head
*head = 2000, **head = 1000 (memory address of head)
*/
#include <stdio.h>
#include <stdlib.h>
#include "DLL.h"
#include <errno.h>

int create_node(struct node **newNode, int data)
{
    *newNode = malloc(sizeof(struct node));
    if (*newNode == NULL)
        return ENOMEM; // MEMORY ALLOCATION FAILED
                       // (standard Unix error for “no memory”)
    (*newNode)->data = data;
    (*newNode)->prev = NULL;
    (*newNode)->next = NULL;
    return 0;
}

int insert_first(struct node **head, int data)
{
    struct node *newNode;
    int result = create_node(&newNode, data); // result = 0 or ENOMEM
    if (result != 0)
        return result; // result = ENOMEM

    newNode->next = *head;
    if (*head != NULL)           // head = NULL means there's no linked list avilable
        (*head)->prev = newNode; // then we don't need to link. cz we've created only 1 node

    *head = newNode;
    return 0;
}

int insert_last(struct node **head, int data)
{
    struct node *newNode, *ptr;
    int result = create_node(&newNode, data);
    if (result != 0)
        return result;

    if (*head == NULL) // CHECKING IF THE LIST IS EMPTY
    {
        *head = newNode; // THEN HEAD = 1ST NODE
        return 0;        // FUNCTION IMMIDIATELY STOPS & GOES BACK WHERE IT WAS CALLED (IN main function)
    }

    ptr = *head;
    while (ptr->next != NULL)
        /*Ekhane ptr != NULL dile , ptr last node er porer node e chole jabe.
        That means age ptr = NULL hoye jabe , then loop er condition check korbe*/
        ptr = ptr->next;

    ptr->next = newNode;
    newNode->prev = ptr;
    return 0;
}

int insert_in_between(struct node **head, int pos, int data)
{
    if (*head == NULL)
        return EINVAL;

    struct node *ptr = *head;
    int i = 0;
    while (ptr != NULL && i < pos)
    {
        ptr = ptr->next;
        i++;
    }
    if (ptr == NULL)   // You tell the program: “Insert after position 5
        return EINVAL; // But the list only has 2 nodes
                       // When the loop finishes searching, there is no node at position 5
    struct node *newNode;
    int result = create_node(&newNode, data);
    if (result != 0)
        return result;

    newNode->next = ptr->next;
    newNode->prev = ptr;
    if (ptr->next != NULL)
        ptr->next->prev = newNode;

    ptr->next = newNode;
    return 0;
}

int delete_node(struct node **head, int pos)
{
    if (*head == NULL)
        return EINVAL;

    struct node *ptr = *head;
    int i = 0;
    while (ptr != NULL && i < pos)
    {
        ptr = ptr->next;
        i++;
    }

    if (ptr == NULL)
        return EINVAL;

    if (ptr->prev != NULL)           // DELETING EXCEPT 1ST NODE
        ptr->prev->next = ptr->next; // UPDATE NEXT LINK OF ptr's PREVIOUS NODE
    else                             // DELETING 1ST NODE
        *head = ptr->next;           // MOVING HEAD TO 2ND NODE
    if (ptr->next != NULL)
        ptr->next->prev = ptr->prev; // UPDATE PREV LINK OF ptr's NEXT NODE

    free(ptr);
    return 0;
}

void print_list(const struct node *head)
{ // const means the function promises not to change nodes (read-only).
    const struct node *ptr = head;
    printf("Doubly Linked List : ");
    while (ptr != NULL)
    {
        printf("%d ", ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}

void free_list(struct node **head)
{ // Purpose: free every node’s memory so there is no memory leak.
    struct node *ptr = *head;
    while (ptr != NULL)
    {                            /*Ekhane ptr->next != NULL dile last node print hobe na.
                                   ptr last node e jabe thiki , kintu condition false dekhe
                                   print korar agei loop theke ber hoye jabe*/
        struct node *temp = ptr; // temp , for not to lose the next pointer
        ptr = ptr->next;
        free(temp);
    }
    *head = NULL;

}
