#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structure.h"

struct vendor *vendors = NULL;
struct item *items = NULL;
struct staff *staffs = NULL;
struct customer *customers = NULL;
struct cart *carts = NULL;
struct payment *payments = NULL;

int vendor_id_counter = 1;
int item_id_counter = 1;
int staff_id_counter = 1;
int cart_id_counter = 1;
int payment_id_counter = 1;

struct order
{
    int order_id;
    char vendor_name[100];
    char customer_id[14];
    float total_amount;
    char status[20];
    struct order *next;
};

struct order *orders = NULL;
int order_id_counter = 1;

struct order *create_order(int order_id, char *vendor_name, char *customer_id, float total_amount)
{
    struct order *new_order = (struct order *)malloc(sizeof(struct order));
    if (new_order == NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    new_order->order_id = order_id;
    strcpy(new_order->vendor_name, vendor_name);
    strcpy(new_order->customer_id, customer_id);
    new_order->total_amount = total_amount;
    strcpy(new_order->status, "Pending");
    new_order->next = NULL;
    return new_order;
}

struct order *add_order(struct order *head, int order_id, char *vendor_name, char *customer_id, float total_amount)
{
    struct order *new_order = create_order(order_id, vendor_name, customer_id, total_amount);
    if (new_order == NULL)
    {
        return head;
    }
    if (head == NULL)
    {
        return new_order;
    }

    struct order *runner = head;
    while (runner->next != NULL)
    {
        runner = runner->next;
    }
    runner->next = new_order;
    return head;
}

void display_orders_by_vendor(struct order *head, char *vendor_name)
{
    if (head == NULL)
    {
        printf("No orders found!\n");
        return;
    }
    printf("\n=== ORDERS FOR %s ===\n", vendor_name);
    struct order *runner = head;
    int found = 0;
    while (runner != NULL)
    {
        if (strcmp(runner->vendor_name, vendor_name) == 0)
        {
            printf("\nOrder ID: %d\n", runner->order_id);
            printf("Customer ID: %d\n", runner->customer_id);
            printf("Amount: %.2f\n", runner->total_amount);
            printf("Status: %s\n", runner->status);
            found = 1;
        }
        runner = runner->next;
    }
    if (!found)
    {
        printf("No orders for this vendor!\n");
    }
    printf("\n=========================\n");
}

void update_order_status(struct order *head, int order_id, char *new_status)
{
    struct order *runner = head;
    while (runner != NULL)
    {
        if (runner->order_id == order_id)
        {
            strcpy(runner->status, new_status);
            printf("Order status updated to %s!\n", new_status);
            return;
        }
        runner = runner->next;
    }
    printf("Order not found!\n");
}

void display_position_menu()
{
    printf("\nSelect Position:\n");
    printf("1. Manager\n");
    printf("2. Chef\n");
    printf("3. Cashier\n");
    printf("4. Delivery\n");
    printf("Enter choice (1-4): ");
}

void flush_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void admin_menu()
{
    int choice;

    while (1)
    {
        printf("\n========== ADMIN MENU ==========\n");
        printf("1. Add Vendor\n");
        printf("2. View All Vendors\n");
        printf("3. View All Items\n");
        printf("4. View All Staff\n");
        printf("5. View All Customers\n");
        printf("6. View All Orders\n");
        printf("7. Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        flush_input_buffer();

        if (choice == 1)
        {
            char vendor_name[100], contact[12];
            printf("Enter vendor name: ");
            fgets(vendor_name, sizeof(vendor_name), stdin);
            vendor_name[strcspn(vendor_name, "\n")] = 0;

            while (1)
            {
                printf("Enter contact number (11 digits, must start with 01): ");
                fgets(contact, sizeof(contact), stdin);
                contact[strcspn(contact, "\n")] = 0;

                if (strlen(contact) != 11 || contact[0] != '0' || contact[1] != '1')
                {
                    printf("WARNING: Contact number must be 11 digits starting with 01! Please try again.\n");
                    continue;
                }
                break;
            }

            add_vendor(&vendors, vendor_id_counter++, vendor_name, contact);
            printf("Vendor added successfully! Vendor ID: %d\n", vendor_id_counter - 1);
        }
        else if (choice == 2)
        {
            display_all_vendors(vendors);
        }
        else if (choice == 3)
        {
            display_all_items(items);
        }
        else if (choice == 4)
        {
            display_all_staff(staffs);
        }
        else if (choice == 5)
        {
            display_all_customers(customers);
        }
        else if (choice == 6)
        {
            struct order *runner = orders;
            if (runner == NULL)
            {
                printf("No orders found!\n");
            }
            else
            {
                printf("\n=== ALL ORDERS ===\n");
                while (runner != NULL)
                {
                    printf("\nOrder ID: %d\n", runner->order_id);
                    printf("Vendor: %s\n", runner->vendor_name);
                    printf("Customer ID: %d\n", runner->customer_id);
                    printf("Amount: %.2f\n", runner->total_amount);
                    printf("Status: %s\n", runner->status);
                    runner = runner->next;
                }
                printf("\n==================\n");
            }
        }
        else if (choice == 7)
        {
            return;
        }
        else
        {
            printf("Invalid choice!\n");
        }
    }
}

void vendor_menu()
{
    int choice, pos_choice;
    char vendor_name[100], name[100], contact[12], position[50];
    float salary;

    printf("Enter vendor name: ");
    fgets(vendor_name, sizeof(vendor_name), stdin);
    vendor_name[strcspn(vendor_name, "\n")] = 0;

    struct vendor *v = search_vendor_by_name(vendors, vendor_name);
    if (v == NULL)
    {
        printf("Vendor not found!\n");
        return;
    }

    while (1)
    {
        printf("\n========== VENDOR: %s ==========\n", vendor_name);
        printf("1. View My Items\n");
        printf("2. Add Item\n");
        printf("3. View My Staff\n");
        printf("4. Add Staff\n");
        printf("5. View My Orders\n");
        printf("6. Update Order Status\n");
        printf("7. Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        flush_input_buffer();

        if (choice == 1)
        {
            display_items_by_vendor(items, v->vendor_id);
        }
        else if (choice == 2)
        {
            char item_name[100];
            float price;
            int quantity;
            printf("Enter item name: ");
            fgets(item_name, sizeof(item_name), stdin);
            item_name[strcspn(item_name, "\n")] = 0;
            printf("Enter price: ");
            scanf("%f", &price);
            flush_input_buffer();
            printf("Enter quantity available: ");
            scanf("%d", &quantity);
            flush_input_buffer();
            items = items;
            add_item(&items, item_id_counter++, item_name, price, quantity, v->vendor_id);
            printf("Item added successfully! Item ID: %d\n", item_id_counter - 1);
        }
        else if (choice == 3)
        {
            display_staff_by_vendor(staffs, v->vendor_id);
        }
        else if (choice == 4)
        {
            printf("Enter staff name: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = 0;

            display_position_menu();
            scanf("%d", &pos_choice);
            flush_input_buffer();

            if (pos_choice == 1)
            {
                strcpy(position, "Manager");
            }
            else if (pos_choice == 2)
            {
                strcpy(position, "Chef");
            }
            else if (pos_choice == 3)
            {
                strcpy(position, "Cashier");
            }
            else if (pos_choice == 4)
            {
                strcpy(position, "Delivery");
            }
            else
            {
                printf("Invalid position!\n");
                continue;
            }

            while (1)
            {
                printf("Enter contact number (11 digits, must start with 01): ");
                fgets(contact, sizeof(contact), stdin);
                contact[strcspn(contact, "\n")] = 0;

                if (strlen(contact) != 11 || contact[0] != '0' || contact[1] != '1')
                {
                    printf("WARNING: Contact number must be 11 digits starting with 01! Please try again.\n");
                    continue;
                }
                break;
            }
            printf("Enter salary: ");
            scanf("%f", &salary);
            flush_input_buffer();

            add_staff(&staffs, staff_id_counter++, name, position, contact, salary, v->vendor_id);
            printf("Staff added successfully!\n");
        }
        else if (choice == 5)
        {
            display_orders_by_vendor(orders, vendor_name);
        }
        else if (choice == 6)
        {
            int order_id;
            char status[20];
            printf("Enter order ID: ");
            scanf("%d", &order_id);
            flush_input_buffer();
            printf("Enter new status (Pending/Preparing/Ready/Completed): ");
            scanf("%19s", status);
            flush_input_buffer();
            update_order_status(orders, order_id, status);
        }
        else if (choice == 7)
        {
            return;
        }
        else
        {
            printf("Invalid choice!\n");
        }
    }
}

void customer_menu()
{
    int choice, item_id, quantity, cart_id;
    float price, total;
    char vendor_name[100], customer_id[14];

    printf("Enter customer ID (13 digits): ");
    fgets(customer_id, sizeof(customer_id), stdin);
    customer_id[strcspn(customer_id, "\n")] = 0;
    flush_input_buffer();

    if (strlen(customer_id) != 13)
    {
        printf("Invalid customer ID! Must be exactly 13 digits.\n");
        return;
    }

    struct customer *c = search_customer(customers, customer_id);
    if (c == NULL)
    {
        printf("Customer not found! Creating new customer...\n");
        printf("Enter your name: ");
        char name[100], contact[12];
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0;

        while (1)
        {
            printf("Enter contact number (No need to use country code): ");
            fgets(contact, sizeof(contact), stdin);
            contact[strcspn(contact, "\n")] = 0;

            if (strlen(contact) != 11 || contact[0] != '0' || contact[1] != '1')
            {
                printf("Contact number must be 11 digits starting with 01! Please try again.\n");
                continue;
            }
            break;
        }

        add_customer(&customers, customer_id, name, contact);
        c = search_customer(customers, customer_id);
    }

    while (1)
    {
        printf("\n========== CUSTOMER: %s ==========\n", c->customer_name);
        printf("1. View Items by Vendor\n");
        printf("2. Search Items by Name\n");
        printf("3. View My Cart\n");
        printf("4. Checkout\n");
        printf("5. Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        flush_input_buffer();

        if (choice == 1)
        {
            printf("Enter vendor name: ");
            fgets(vendor_name, sizeof(vendor_name), stdin);
            vendor_name[strcspn(vendor_name, "\n")] = 0;

            struct vendor *v = search_vendor_by_name(vendors, vendor_name);
            if (v != NULL)
            {
                printf("\n========== ITEMS FROM %s ==========\n", vendor_name);
                struct item *runner = items;
                int found = 0;
                int item_num = 1;
                while (runner != NULL)
                {
                    if (runner->vendor_id == v->vendor_id)
                    {
                        printf("%d. %s---%.2f TK.---%d Pcs. (ID: %d)\n", item_num, runner->item_name, runner->price, runner->quantity_available, runner->item_id);
                        found = 1;
                        item_num++;
                    }
                    runner = runner->next;
                }
                if (!found)
                {
                    printf("No items from this vendor!\n");
                }
                else
                {
                    printf("\nEnter item ID to add to cart (or 0 to skip): ");
                    scanf("%d", &item_id);
                    flush_input_buffer();
                    if (item_id != 0)
                    {
                        struct item *item = search_item(items, item_id);
                        if (item != NULL && item->vendor_id == v->vendor_id)
                        {
                            printf("How much you want? (Available: %d): ", item->quantity_available);
                            scanf("%d", &quantity);
                            flush_input_buffer();
                            if (quantity > 0 && quantity <= item->quantity_available)
                            {
                                add_to_cart(&carts, cart_id_counter++, customer_id, item_id, quantity, item->price);
                                printf("Item added to cart!\n");
                                item->quantity_available -= quantity;
                            }
                            else
                            {
                                printf("Invalid quantity!\n");
                            }
                        }
                        else
                        {
                            printf("Item not found or not from this vendor!\n");
                        }
                    }
                }
                printf("====================================\n");
            }
            else
            {
                printf("Vendor not found!\n");
            }
        }
        else if (choice == 2)
        {
            printf("Enter item name to search: ");
            getchar();
            char search_name[100];
            fgets(search_name, sizeof(search_name), stdin);
            search_name[strcspn(search_name, "\n")] = 0;

            printf("\n========== SEARCH RESULTS ==========\n");
            struct item *runner = items;
            int found = 0;
            int item_num = 1;
            while (runner != NULL)
            {
                if (strstr(runner->item_name, search_name) != NULL)
                {
                    struct vendor *v = search_vendor(vendors, runner->vendor_id);
                    if (v != NULL)
                    {
                        printf("%d. %s: %s---%.2f TK.---%d Pcs. (ID: %d)\n", item_num, v->vendor_name, runner->item_name, runner->price, runner->quantity_available, runner->item_id);
                        item_num++;
                    }
                    found = 1;
                }
                runner = runner->next;
            }
            if (!found)
            {
                printf("No items found!\n");
            }
            else
            {
                printf("\nEnter item ID to add to cart (or 0 to skip): ");
                scanf("%d", &item_id);
                flush_input_buffer();
                if (item_id != 0)
                {
                    struct item *item = search_item(items, item_id);
                    if (item != NULL)
                    {
                        printf("How much you want? (Available: %d): ", item->quantity_available);
                        scanf("%d", &quantity);
                        flush_input_buffer();
                        if (quantity > 0 && quantity <= item->quantity_available)
                        {
                            add_to_cart(&carts, cart_id_counter++, customer_id, item_id, quantity, item->price);
                            printf("Item added to cart!\n");
                            item->quantity_available -= quantity;
                        }
                        else
                        {
                            printf("Invalid quantity!\n");
                        }
                    }
                    else
                    {
                        printf("Item not found!\n");
                    }
                }
            }
            printf("====================================\n");
        }
        else if (choice == 3)
        {
            display_cart(carts, customer_id);
        }
        else if (choice == 4)
        {
            total = calculate_cart_total(carts, customer_id);
            if (total > 0)
            {
                int method_choice;
                char payment_method[20];

                printf("Total Amount: %.2f\n", total);
                printf("\nSelect Payment Method:\n");
                printf("1. Cash\n");
                printf("2. Card\n");
                printf("3. BKash\n");
                printf("Enter choice (1-3): ");
                scanf("%d", &method_choice);
                flush_input_buffer();

                if (method_choice == 1)
                {
                    strcpy(payment_method, "cash");
                }
                else if (method_choice == 2)
                {
                    strcpy(payment_method, "card");
                }
                else if (method_choice == 3)
                {
                    strcpy(payment_method, "bkash");
                }
                else
                {
                    printf("Invalid payment method!\n");
                    continue;
                }

                add_payment(&payments, payment_id_counter++, customer_id, 1, total, payment_method);

                struct item *first_item = search_item(items, 1);
                if (first_item != NULL)
                {
                    struct vendor *vendor = search_vendor(vendors, first_item->vendor_id);
                    if (vendor != NULL)
                    {
                        orders = add_order(orders, order_id_counter++, vendor->vendor_name, customer_id, total);
                    }
                }

                printf("Order placed successfully! Order ID: %d\n", order_id_counter - 1);

                struct cart *runner = carts;
                while (runner != NULL)
                {
                    if (strcmp(runner->customer_id, customer_id) == 0)
                    {
                        remove_from_cart(&carts, runner->cart_id);
                        runner = carts;
                    }
                    else
                    {
                        runner = runner->next;
                    }
                }
            }
            else
            {
                printf("Cart is empty!\n");
            }
        }
        else if (choice == 5)
        {
            return;
        }
        else
        {
            printf("Invalid choice!\n");
        }
    }
}

void main_menu()
{
    int choice, i = 1;

    while (i == 1)
    {
        printf("\n============================================\n");
        printf("    EWU E-CANTEEN MANAGEMENT SYSTEM\n");
        printf("============================================\n");
        printf("1. Admin\n");
        printf("2. Vendor\n");
        printf("3. Customer\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        flush_input_buffer();

        if (choice == 1)
        {
            admin_menu();
        }
        else if (choice == 2)
        {
            vendor_menu();
        }
        else if (choice == 3)
        {
            customer_menu();
        }
        else if (choice == 4)
        {
            printf("Exiting...\n");
            i = 0;
        }
        else
        {
            printf("Invalid choice!\n");
        }
    }
}

int main()
{
    main_menu();
    return 0;
}
