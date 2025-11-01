#include <stdio.h>
#include <stdlib.h>
#include "DLL.h"

int main()
{
    struct node *head = NULL;
    int result, data, pos, choice;

    printf("=====Doubly linked list : =====\n");

    while (1) // loop will continue till user want to exit from loop
    {
        printf("\nChoose an option:\n");
        printf("1. Insert at beginning\n");
        printf("2. Insert at end\n");
        printf("3. Insert in between (at position)\n");
        printf("4. Delete a node (by position)\n");
        printf("5. Display list\n");
        printf("6. Exit\n");
        printf("Enter choice: \n");
        scanf("%d", &choice);

        if (choice == 1)
        {
            printf("Enter data to insert: ");
            scanf("%d", &data);
            result = insert_first(&head, data);
            if (result == 0)
                printf("Inserted %d at the beginning.\n", data);
            else
                printf("Error inserting node.\n");
        }

        else if (choice == 2)
        {
            printf("Enter data to insert: ");
            scanf("%d", &data);
            result = insert_last(&head, data);
            if (result == 0)
                printf("Inserted %d at the end.\n", data);
            else
                printf("Error inserting node.\n");
        }

        else if (choice == 3)
        {
            printf("Enter position (0-base index): ");
            scanf("%d", &pos);
            printf("Enter data to insert: ");
            scanf("%d", &data);
            result = insert_in_between(&head, pos, data);
            if (result == 0)
                printf("Inserted %d after position %d.\n", data, pos);
            else
                printf("Invalid position or error.\n");
        }

        else if (choice == 4)
        {
            printf("Enter position to delete: ");
            scanf("%d", &pos);
            result = delete_node(&head, pos);
            if (result == 0)
                printf("Deleted node at position %d.\n", pos);
            else
                printf("Invalid position or empty list.\n");
        }

        else if (choice == 5)
        {
            print_list(head);
        }

        else if (choice == 6)
        {
            printf("Exiting...\n");
            free_list(&head);
            break;
        }

        else
            printf("Invalid choice. Please try again.\n");
    }

    return 0;
}