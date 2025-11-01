#ifndef DLL_H
#define DLL_H

#include <errno.h>  // for Unix-style error codes

struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
};
/*
consider 0-base indexing. 
Try to use Unix Standard error..
*/
int createNode(int data, struct Node **newNode);
int insertFirst(struct Node **head, int data);
int insertLast(struct Node **head, int data);
int insertAfter(struct Node **head, int pos, int data);
int deleteNode(struct Node **head, int pos);
void printList(const struct Node *head);
void freeList(struct Node **head);

#endif
