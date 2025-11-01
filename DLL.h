#ifndef DLL_H /*header guard*/
#define DLL_H 
/*It prevents the file from being included more than once by mistake.
If this file is already included, this part makes sure it’s not included again
 (avoiding redefinition errors).*/
#include <stdio.h>
#include <stdlib.h> //for malloc() and free()
#include <errno.h> //for ENOMEM, EINVAL

struct node
{
    int data;
    struct node *prev;
    struct node *next;
};

int create_node(struct node **newNode, int data);
int insert_first(struct node **head, int data);
int insert_last(struct node **head, int data);
int insert_in_between(struct node **head, int pos, int data);
int delete_node(struct node **head, int pos);
void print_list(const struct node *head);
void free_list(struct node **head);

#endif // Closes the #ifndef DLL_H guard
