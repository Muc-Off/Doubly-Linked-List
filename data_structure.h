#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

struct vendor
{
    struct vendor *prev;
    int vendor_id;
    char vendor_name[100];
    char contact_number[12];
    struct vendor *next;
};

struct vendor *create_vendor(int vendor_id, char *vendor_name, char *contact_number);
void add_vendor(struct vendor **head, int vendor_id, char *vendor_name, char *contact_number);
void delete_vendor(struct vendor **head, int vendor_id);
struct vendor *search_vendor(struct vendor *head, int vendor_id);
struct vendor *search_vendor_by_name(struct vendor *head, char *vendor_name);
void display_all_vendors(struct vendor *head);
void free_all_vendors(struct vendor *head);

struct item
{
    struct item *prev;
    int item_id;
    char item_name[100];
    float price;
    int quantity_available;
    int vendor_id;
    struct item *next;
};

struct item *create_item(int item_id, char *item_name, float price, int quantity_available, int vendor_id);
void add_item(struct item **head, int item_id, char *item_name, float price, int quantity_available, int vendor_id);
void delete_item(struct item **head, int item_id);
struct item *search_item(struct item *head, int item_id);
struct item *search_item_by_name(struct item *head, char *item_name);
struct item *search_items_by_vendor(struct item *head, int vendor_id);
void display_all_items(struct item *head);
void display_items_by_vendor(struct item *head, int vendor_id);
void update_item_quantity(struct item *head, int item_id, int new_quantity);
void free_all_items(struct item *head);

struct staff
{
    struct staff *prev;
    int staff_id;
    char staff_name[50];
    char position[50];
    char contact_number[12];
    float salary;
    int vendor_id;
    struct staff *next;
};

struct staff *create_staff(int staff_id, char *staff_name, char *position, char *contact_number, float salary, int vendor_id);
void add_staff(struct staff **head, int staff_id, char *staff_name, char *position, char *contact_number, float salary, int vendor_id);
void delete_staff(struct staff **head, int staff_id);
struct staff *search_staff(struct staff *head, int staff_id);
void display_all_staff(struct staff *head);
void update_staff_salary(struct staff *head, int staff_id, float new_salary);
struct staff *search_staff_by_vendor(struct staff *head, int vendor_id);
void display_staff_by_vendor(struct staff *head, int vendor_id);
void free_all_staff(struct staff *head);

struct customer
{
    struct customer *prev;
    char customer_id[14];
    char customer_name[50];
    char contact_number[12];
    struct customer *next;
};

struct customer *create_customer(char *customer_id, char *customer_name, char *contact_number);
void add_customer(struct customer **head, char *customer_id, char *customer_name, char *contact_number);
void delete_customer(struct customer **head, char *customer_id);
struct customer *search_customer(struct customer *head, char *customer_id);
void display_all_customers(struct customer *head);
void free_all_customers(struct customer *head);

struct cart
{
    struct cart *prev;
    int cart_id;
    char customer_id[14];
    int item_id;
    int quantity;
    float item_price;
    struct cart *next;
};

struct cart *create_cart(int cart_id, char *customer_id, int item_id, int quantity, float item_price);
void add_to_cart(struct cart **head, int cart_id, char *customer_id, int item_id, int quantity, float item_price);
void remove_from_cart(struct cart **head, int cart_id);
struct cart *search_cart(struct cart *head, int cart_id);
struct cart *search_cart_by_customer(struct cart *head, char *customer_id);
void display_cart(struct cart *head, char *customer_id);
void display_all_cart(struct cart *head);
float calculate_cart_total(struct cart *head, char *customer_id);
void free_all_cart(struct cart *head);

struct payment
{
    struct payment *prev;
    int payment_id;
    char customer_id[14];
    int cart_id;
    float total_amount;
    char payment_method[20];
    struct payment *next;
};

struct payment *create_payment(int payment_id, char *customer_id, int cart_id, float total_amount, char *payment_method);
void add_payment(struct payment **head, int payment_id, char *customer_id, int cart_id, float total_amount, char *payment_method);
void delete_payment(struct payment **head, int payment_id);
struct payment *search_payment(struct payment *head, int payment_id);
void display_all_payments(struct payment *head);
void free_all_payments(struct payment *head);

#endif