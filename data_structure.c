#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "data_structure.h"

struct vendor *create_vendor(int vendor_id, char *vendor_name, char *contact_number)
{
    struct vendor *v = (struct vendor *)malloc(sizeof(struct vendor));
    if (v == NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    v->vendor_id = vendor_id;

    if (vendor_name != NULL)
    {
        strcpy(v->vendor_name, vendor_name);
    }

    if (contact_number != NULL)
    {
        strcpy(v->contact_number, contact_number);
    }

    v->next = NULL;
    v->prev = NULL;
    return v;
}

void add_vendor(struct vendor **head, int vendor_id, char *vendor_name, char *contact_number)
{
    struct vendor *v = create_vendor(vendor_id, vendor_name, contact_number);
    if (v == NULL)
    {
        return;
    }
    if (*head == NULL)
    {
        *head = v;
        return;
    }

    struct vendor *current = *head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = v;
    v->prev = current;
}

void delete_vendor(struct vendor **head, int vendor_id)
{
    struct vendor *current = *head;
    while (current != NULL && current->vendor_id != vendor_id)
    {
        current = current->next;
    }

    if (current == NULL)
    {
        printf("not found!\n");
        return;
    }

    if (current == *head)
    {
        *head = current->next;
        if (*head != NULL)
        {
            (*head)->prev = NULL;
        }
    }
    else
    {
        if (current->prev != NULL)
        {
            current->prev->next = current->next;
        }
        if (current->next != NULL)
        {
            current->next->prev = current->prev;
        }
    }

    free(current);
}

struct vendor *search_vendor(struct vendor *head, int vendor_id)
{
    for (struct vendor *current = head; current != NULL; current = current->next)
    {
        if (current->vendor_id == vendor_id)
        {
            return current;
        }
    }
    return NULL;
}

struct vendor *search_vendor_by_name(struct vendor *head, char *vendor_name)
{
    if (vendor_name == NULL)
    {
        return NULL;
    }

    for (struct vendor *current = head; current != NULL; current = current->next)
    {
        if (strcmp(current->vendor_name, vendor_name) == 0)
        {
            return current;
        }
    }
    return NULL;
}

void display_all_vendors(struct vendor *head)
{
    if (head == NULL)
    {
        printf("No vendor records found\n");
        return;
    }

    printf("\n");
    printf("===== VENDOR DATABASE =====\n");
    int count = 0;
    for (struct vendor *v = head; v != NULL; v = v->next)
    {
        count++;
        printf("Entry #%d\n", count);
        printf("  ID: %d\n", v->vendor_id);
        printf("  Name: %s\n", v->vendor_name);
        printf("  Contact: %s\n", v->contact_number);
        printf("---\n");
    }
    printf("Total vendors: %d\n", count);
    printf("===========================\n\n");
}

void free_all_vendors(struct vendor *head)
{
    struct vendor *current = head;
    while (current != NULL)
    {
        struct vendor *temp = current;
        current = current->next;
        free(temp);
    }
}

struct item *create_item(int item_id, char *item_name, float price, int quantity_available, int vendor_id)
{
    struct item *item = (struct item *)malloc(sizeof(struct item));
    if (item == NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    item->item_id = item_id;
    item->price = (price >= 0) ? price : 0.0;
    item->quantity_available = (quantity_available >= 0) ? quantity_available : 0;
    item->vendor_id = vendor_id;

    if (item_name != NULL)
    {
        strcpy(item->item_name, item_name);
    }

    item->next = NULL;
    item->prev = NULL;
    return item;
}

void add_item(struct item **head, int item_id, char *item_name, float price, int quantity_available, int vendor_id)
{
    struct item *item = create_item(item_id, item_name, price, quantity_available, vendor_id);
    if (item == NULL)
    {
        return;
    }
    if (*head == NULL)
    {
        *head = item;
        return;
    }

    struct item *tail = *head;
    while (tail->next != NULL)
    {
        tail = tail->next;
    }
    tail->next = item;
    item->prev = tail;
}

void delete_item(struct item **head, int item_id)
{
    struct item *current = *head;
    while (current != NULL && current->item_id != item_id)
    {
        current = current->next;
    }

    if (current == NULL)
    {
        printf("not found!\n");
        return;
    }

    if (current == *head)
    {
        *head = current->next;
        if (*head != NULL)
        {
            (*head)->prev = NULL;
        }
    }
    else
    {
        if (current->prev != NULL)
        {
            current->prev->next = current->next;
        }
        if (current->next != NULL)
        {
            current->next->prev = current->prev;
        }
    }
    free(current);
}

struct item *search_item(struct item *head, int item_id)
{
    for (struct item *it = head; it != NULL; it = it->next)
    {
        if (it->item_id == item_id)
        {
            return it;
        }
    }
    return NULL;
}

struct item *search_item_by_name(struct item *head, char *item_name)
{
    if (item_name == NULL)
    {
        return NULL;
    }

    for (struct item *it = head; it != NULL; it = it->next)
    {
        if (strcmp(it->item_name, item_name) == 0)
        {
            return it;
        }
    }
    return NULL;
}

struct item *search_items_by_vendor(struct item *head, int vendor_id)
{
    for (struct item *it = head; it != NULL; it = it->next)
    {
        if (it->vendor_id == vendor_id)
        {
            return it;
        }
    }
    return NULL;
}

void display_items_by_vendor(struct item *head, int vendor_id)
{
    if (head == NULL)
    {
        printf("No items in inventory\n");
        return;
    }

    printf("\n===== VENDOR %d INVENTORY =====\n", vendor_id);
    int count = 0;

    for (struct item *it = head; it != NULL; it = it->next)
    {
        if (it->vendor_id == vendor_id)
        {
            count++;
            printf("Item #%d\n", count);
            printf("  ID: %d\n", it->item_id);
            printf("  Product: %s\n", it->item_name);
            printf("  Price: $%.2f\n", it->price);
            printf("  In Stock: %d units\n", it->quantity_available);
            printf("---\n");
        }
    }

    if (count == 0)
    {
        printf("No items found for vendor %d\n", vendor_id);
    }
    else
    {
        printf("Total items: %d\n", count);
    }
    printf("==============================\n\n");
}

void display_all_items(struct item *head)
{
    if (head == NULL)
    {
        printf("Inventory is empty\n");
        return;
    }

    printf("\n===== COMPLETE INVENTORY =====\n");
    int count = 0;
    float total_value = 0;

    for (struct item *it = head; it != NULL; it = it->next)
    {
        count++;
        printf("Item #%d\n", count);
        printf("  ID: %d | Vendor: %d\n", it->item_id, it->vendor_id);
        printf("  Name: %s\n", it->item_name);
        printf("  Unit Price: $%.2f\n", it->price);
        printf("  Quantity: %d\n", it->quantity_available);
        total_value += it->price * it->quantity_available;
        printf("---\n");
    }

    printf("Total items in inventory: %d\n", count);
    printf("Total inventory value: $%.2f\n", total_value);
    printf("===============================\n\n");
}

void update_item_quantity(struct item *head, int item_id, int new_quantity)
{
    struct item *it = search_item(head, item_id);
    if (it == NULL)
    {
        printf("not found!\n");
        return;
    }

    int old_qty = it->quantity_available;
    it->quantity_available = (new_quantity >= 0) ? new_quantity : 0;
    printf("Item %d: quantity updated from %d to %d\n", item_id, old_qty, it->quantity_available);
}

void free_all_items(struct item *head)
{
    struct item *current = head;
    while (current != NULL)
    {
        struct item *temp = current;
        current = current->next;
        free(temp);
    }
}

struct staff *create_staff(int staff_id, char *staff_name, char *position, char *contact_number, float salary, int vendor_id)
{
    struct staff *emp = (struct staff *)malloc(sizeof(struct staff));
    if (emp == NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    emp->staff_id = staff_id;
    emp->salary = (salary >= 0) ? salary : 0.0;
    emp->vendor_id = vendor_id;

    if (staff_name != NULL)
    {
        strcpy(emp->staff_name, staff_name);
    }

    if (position != NULL)
    {
        strcpy(emp->position, position);
    }

    if (contact_number != NULL)
    {
        strcpy(emp->contact_number, contact_number);
    }

    emp->next = NULL;
    emp->prev = NULL;
    return emp;
}

void add_staff(struct staff **head, int staff_id, char *staff_name, char *position, char *contact_number, float salary, int vendor_id)
{
    struct staff *emp = create_staff(staff_id, staff_name, position, contact_number, salary, vendor_id);
    if (emp == NULL)
    {
        return;
    }
    if (*head == NULL)
    {
        *head = emp;
        return;
    }

    struct staff *tail = *head;
    while (tail->next != NULL)
    {
        tail = tail->next;
    }
    tail->next = emp;
    emp->prev = tail;
}

void delete_staff(struct staff **head, int staff_id)
{
    struct staff *current = *head;
    while (current != NULL && current->staff_id != staff_id)
    {
        current = current->next;
    }

    if (current == NULL)
    {
        printf("not found!\n");
        return;
    }

    if (current == *head)
    {
        *head = current->next;
        if (*head != NULL)
        {
            (*head)->prev = NULL;
        }
    }
    else
    {
        if (current->prev != NULL)
        {
            current->prev->next = current->next;
        }
        if (current->next != NULL)
        {
            current->next->prev = current->prev;
        }
    }
    free(current);
}

struct staff *search_staff(struct staff *head, int staff_id)
{
    for (struct staff *emp = head; emp != NULL; emp = emp->next)
    {
        if (emp->staff_id == staff_id)
        {
            return emp;
        }
    }
    return NULL;
}

void display_all_staff(struct staff *head)
{
    if (head == NULL)
    {
        printf("No employees in system\n");
        return;
    }

    printf("\n===== EMPLOYEE ROSTER =====\n");
    int count = 0;
    double total_payroll = 0;

    for (struct staff *emp = head; emp != NULL; emp = emp->next)
    {
        count++;
        printf("Employee #%d\n", count);
        printf("  ID: %d | Vendor: %d\n", emp->staff_id, emp->vendor_id);
        printf("  Name: %s\n", emp->staff_name);
        printf("  Position: %s\n", emp->position);
        printf("  Phone: %s\n", emp->contact_number);
        printf("  Salary: $%.2f\n", emp->salary);
        total_payroll += emp->salary;
        printf("---\n");
    }

    printf("Total employees: %d\n", count);
    printf("Total monthly payroll: $%.2f\n", total_payroll);
    printf("===========================\n\n");
}

void update_staff_salary(struct staff *head, int staff_id, float new_salary)
{
    struct staff *emp = search_staff(head, staff_id);
    if (emp == NULL)
    {
        printf("not found!\n");
        return;
    }

    float old_salary = emp->salary;
    emp->salary = (new_salary >= 0) ? new_salary : 0.0;
    printf("Staff %d: salary updated from $%.2f to $%.2f\n", staff_id, old_salary, emp->salary);
}

void display_staff_by_vendor(struct staff *head, int vendor_id)
{
    if (head == NULL)
    {
        printf("No employees in system\n");
        return;
    }

    printf("\n===== VENDOR %d STAFF =====\n", vendor_id);
    int count = 0;

    for (struct staff *emp = head; emp != NULL; emp = emp->next)
    {
        if (emp->vendor_id == vendor_id)
        {
            count++;
            printf("Employee #%d\n", count);
            printf("  ID: %d\n", emp->staff_id);
            printf("  Name: %s\n", emp->staff_name);
            printf("  Role: %s\n", emp->position);
            printf("  Contact: %s\n", emp->contact_number);
            printf("  Salary: $%.2f\n", emp->salary);
            printf("---\n");
        }
    }

    if (count == 0)
    {
        printf("No employees assigned to vendor %d\n", vendor_id);
    }
    else
    {
        printf("Total: %d employee(s)\n", count);
    }
    printf("==========================\n\n");
}

void free_all_staff(struct staff *head)
{
    struct staff *current = head;
    while (current != NULL)
    {
        struct staff *temp = current;
        current = current->next;
        free(temp);
    }
}

struct customer *create_customer(char *customer_id, char *customer_name, char *contact_number)
{
    struct customer *customer = (struct customer *)malloc(sizeof(struct customer));
    if (customer == NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    if (customer_id != NULL)
    {
        strcpy(customer->customer_id, customer_id);
    }

    if (customer_name != NULL)
    {
        strcpy(customer->customer_name, customer_name);
    }

    if (contact_number != NULL)
    {
        strcpy(customer->contact_number, contact_number);
    }

    customer->next = NULL;
    customer->prev = NULL;
    return customer;
}

void add_customer(struct customer **head, char *customer_id, char *customer_name, char *contact_number)
{
    struct customer *cust = create_customer(customer_id, customer_name, contact_number);
    if (cust == NULL)
    {
        return;
    }
    if (*head == NULL)
    {
        *head = cust;
        return;
    }

    struct customer *tail = *head;
    while (tail->next != NULL)
    {
        tail = tail->next;
    }
    tail->next = cust;
    cust->prev = tail;
}

void delete_customer(struct customer **head, char *customer_id)
{
    if (customer_id == NULL)
    {
        return;
    }

    struct customer *current = *head;
    while (current != NULL && strcmp(current->customer_id, customer_id) != 0)
    {
        current = current->next;
    }

    if (current == NULL)
    {
        printf("not found!\n");
        return;
    }

    if (current == *head)
    {
        *head = current->next;
        if (*head != NULL)
        {
            (*head)->prev = NULL;
        }
    }
    else
    {
        if (current->prev != NULL)
        {
            current->prev->next = current->next;
        }
        if (current->next != NULL)
        {
            current->next->prev = current->prev;
        }
    }
    free(current);
}

struct customer *search_customer(struct customer *head, char *customer_id)
{
    if (customer_id == NULL)
    {
        return NULL;
    }

    for (struct customer *cust = head; cust != NULL; cust = cust->next)
    {
        if (strcmp(cust->customer_id, customer_id) == 0)
        {
            return cust;
        }
    }
    return NULL;
}

void display_all_customers(struct customer *head)
{
    if (head == NULL)
    {
        printf("No customers registered\n");
        return;
    }

    printf("\n===== CUSTOMER DATABASE =====\n");
    int count = 0;

    for (struct customer *cust = head; cust != NULL; cust = cust->next)
    {
        count++;
        printf("Customer #%d\n", count);
        printf("  ID: %s\n", cust->customer_id);
        printf("  Name: %s\n", cust->customer_name);
        printf("  Contact: %s\n", cust->contact_number);
        printf("---\n");
    }

    printf("Total customers: %d\n", count);
    printf("=============================\n\n");
}

void free_all_customers(struct customer *head)
{
    struct customer *current = head;
    while (current != NULL)
    {
        struct customer *temp = current;
        current = current->next;
        free(temp);
    }
}

struct cart *create_cart(int cart_id, char *customer_id, int item_id, int quantity, float item_price)
{
    struct cart *entry = (struct cart *)malloc(sizeof(struct cart));
    if (entry == NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    entry->cart_id = cart_id;
    entry->item_id = item_id;
    entry->quantity = (quantity > 0) ? quantity : 0;
    entry->item_price = (item_price >= 0) ? item_price : 0.0;

    if (customer_id != NULL)
    {
        strcpy(entry->customer_id, customer_id);
    }

    entry->next = NULL;
    entry->prev = NULL;
    return entry;
}

void add_to_cart(struct cart **head, int cart_id, char *customer_id, int item_id, int quantity, float item_price)
{
    struct cart *entry = create_cart(cart_id, customer_id, item_id, quantity, item_price);
    if (entry == NULL)
    {
        return;
    }
    if (*head == NULL)
    {
        *head = entry;
        return;
    }

    struct cart *tail = *head;
    while (tail->next != NULL)
    {
        tail = tail->next;
    }
    tail->next = entry;
    entry->prev = tail;
}

void remove_from_cart(struct cart **head, int cart_id)
{
    struct cart *current = *head;
    while (current != NULL && current->cart_id != cart_id)
    {
        current = current->next;
    }

    if (current == NULL)
    {
        printf("not found!\n");
        return;
    }

    if (current == *head)
    {
        *head = current->next;
        if (*head != NULL)
        {
            (*head)->prev = NULL;
        }
    }
    else
    {
        if (current->prev != NULL)
        {
            current->prev->next = current->next;
        }
        if (current->next != NULL)
        {
            current->next->prev = current->prev;
        }
    }
    free(current);
}

struct cart *search_cart(struct cart *head, int cart_id)
{
    for (struct cart *entry = head; entry != NULL; entry = entry->next)
    {
        if (entry->cart_id == cart_id)
        {
            return entry;
        }
    }
    return NULL;
}

struct cart *search_cart_by_customer(struct cart *head, char *customer_id)
{
    if (customer_id == NULL)
    {
        return NULL;
    }

    for (struct cart *entry = head; entry != NULL; entry = entry->next)
    {
        if (strcmp(entry->customer_id, customer_id) == 0)
        {
            return entry;
        }
    }
    return NULL;
}

void display_cart(struct cart *head, char *customer_id)
{
    if (head == NULL)
    {
        printf("No items in carts\n");
        return;
    }

    if (customer_id == NULL)
    {
        printf("ERROR: Customer ID required\n");
        return;
    }

    printf("\n===== SHOPPING CART: %s =====\n", customer_id);
    int item_count = 0;
    float total = 0.0;

    for (struct cart *entry = head; entry != NULL; entry = entry->next)
    {
        if (strcmp(entry->customer_id, customer_id) == 0)
        {
            item_count++;
            float subtotal = entry->quantity * entry->item_price;
            printf("Cart Entry #%d\n", entry->cart_id);
            printf("  Item ID: %d\n", entry->item_id);
            printf("  Qty: %d @ $%.2f = $%.2f\n", entry->quantity, entry->item_price, subtotal);
            total += subtotal;
        }
    }

    if (item_count == 0)
    {
        printf("Cart is empty for customer %s\n", customer_id);
    }
    else
    {
        printf("---\n");
        printf("Items in cart: %d\n", item_count);
        printf("Total: $%.2f\n", total);
    }
    printf("=============================\n\n");
}

float calculate_cart_total(struct cart *head, char *customer_id)
{
    if (customer_id == NULL)
        return 0.0;

    float total = 0.0;
    for (struct cart *entry = head; entry != NULL; entry = entry->next)
    {
        if (strcmp(entry->customer_id, customer_id) == 0)
        {
            total += entry->quantity * entry->item_price;
        }
    }
    return total;
}

void display_all_cart(struct cart *head)
{
    if (head == NULL)
    {
        printf("No items in any cart\n");
        return;
    }

    printf("\n===== ALL SHOPPING CARTS =====\n");
    int count = 0;
    float grand_total = 0;

    for (struct cart *entry = head; entry != NULL; entry = entry->next)
    {
        count++;
        float line_total = entry->quantity * entry->item_price;
        printf("Cart Entry #%d\n", count);
        printf("  Cart ID: %d\n", entry->cart_id);
        printf("  Customer: %s\n", entry->customer_id);
        printf("  Item ID: %d\n", entry->item_id);
        printf("  Qty: %d @ $%.2f = $%.2f\n", entry->quantity, entry->item_price, line_total);
        grand_total += line_total;
        printf("---\n");
    }

    printf("Total line items: %d\n", count);
    printf("Grand total: $%.2f\n", grand_total);
    printf("===============================\n\n");
}

void free_all_cart(struct cart *head)
{
    struct cart *current = head;
    while (current != NULL)
    {
        struct cart *temp = current;
        current = current->next;
        free(temp);
    }
}

struct payment *create_payment(int payment_id, char *customer_id, int cart_id, float total_amount, char *payment_method)
{
    struct payment *txn = (struct payment *)malloc(sizeof(struct payment));
    if (txn == NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    txn->payment_id = payment_id;
    txn->cart_id = cart_id;
    txn->total_amount = (total_amount >= 0) ? total_amount : 0.0;

    if (customer_id != NULL)
    {
        strcpy(txn->customer_id, customer_id);
    }

    if (payment_method != NULL)
    {
        strcpy(txn->payment_method, payment_method);
    }

    txn->next = NULL;
    txn->prev = NULL;
    return txn;
}

void add_payment(struct payment **head, int payment_id, char *customer_id, int cart_id, float total_amount, char *payment_method)
{
    struct payment *txn = create_payment(payment_id, customer_id, cart_id, total_amount, payment_method);
    if (txn == NULL)
    {
        return;
    }
    if (*head == NULL)
    {
        *head = txn;
        return;
    }

    struct payment *tail = *head;
    while (tail->next != NULL)
    {
        tail = tail->next;
    }
    tail->next = txn;
    txn->prev = tail;
}

void delete_payment(struct payment **head, int payment_id)
{
    struct payment *current = *head;
    while (current != NULL && current->payment_id != payment_id)
    {
        current = current->next;
    }

    if (current == NULL)
    {
        printf("not found!\n");
        return;
    }

    if (current == *head)
    {
        *head = current->next;
        if (*head != NULL)
        {
            (*head)->prev = NULL;
        }
    }
    else
    {
        if (current->prev != NULL)
        {
            current->prev->next = current->next;
        }
        if (current->next != NULL)
        {
            current->next->prev = current->prev;
        }
    }
    free(current);
}

struct payment *search_payment(struct payment *head, int payment_id)
{
    for (struct payment *txn = head; txn != NULL; txn = txn->next)
    {
        if (txn->payment_id == payment_id)
        {
            return txn;
        }
    }
    return NULL;
}

void display_all_payments(struct payment *head)
{
    if (head == NULL)
    {
        printf("No payments recorded\n");
        return;
    }

    printf("\n===== PAYMENT TRANSACTION LOG =====\n");
    int count = 0;
    double total_revenue = 0;

    for (struct payment *txn = head; txn != NULL; txn = txn->next)
    {
        count++;
        printf("Transaction #%d\n", count);
        printf("  Payment ID: %d\n", txn->payment_id);
        printf("  Customer: %s\n", txn->customer_id);
        printf("  Cart ID: %d\n", txn->cart_id);
        printf("  Amount: $%.2f\n", txn->total_amount);
        printf("  Method: %s\n", txn->payment_method);
        total_revenue += txn->total_amount;
        printf("---\n");
    }

    printf("Total transactions: %d\n", count);
    printf("Total revenue: $%.2f\n", total_revenue);
    printf("====================================\n\n");
}

void free_all_payments(struct payment *head)
{
    struct payment *current = head;
    while (current != NULL)
    {
        struct payment *temp = current;
        current = current->next;
        free(temp);
    }
}
