#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PRODUCTS 4
#define MAX_CART_ITEMS 50
#define NAME_LEN 100

typedef struct {
    char code[4];
    int quantity;
    float price;
} Product;

typedef struct {
    char name[NAME_LEN];
    char cnic[20];
} Customer;

Product products[MAX_PRODUCTS] = {
    {"001", 50, 100.0f},
    {"002", 10, 200.0f},
    {"003", 20, 300.0f},
    {"004", 8, 150.0f}
};

void inputCustomer(Customer *c);
void displayInventory();
int findProductIndexByCode(const char *code);
void addItemToCart(int cartProdIndex[], int cartQty[], int *cartCount);
void updateInventoryFromCart(int cartProdIndex[], int cartQty[], int cartCount);
float calculateTotal(int cartProdIndex[], int cartQty[], int cartCount);
void showInvoice(Customer *c, int cartProdIndex[], int cartQty[], int cartCount, int discountApplied);

int main() {
    Customer cust = {"", ""};
    int cartProdIndex[MAX_CART_ITEMS];
    int cartQty[MAX_CART_ITEMS];
    int cartCount = 0;
    int choice;
    int discountApplied = 0;

    while (1) {
        printf("\n=== Supermarket System ===\n");
        printf("1. Enter Customer Info\n");
        printf("2. Display Inventory\n");
        printf("3. Add Item to Cart\n");
        printf("4. Display Total Bill (and apply promocode)\n");
        printf("5. Checkout & Show Invoice\n");
        printf("6. Exit\n");
        printf("Select option: ");
        if (scanf("%d", &choice) != 1) break;
        getchar();

        switch (choice) {
            case 1: inputCustomer(&cust); break;
            case 2: displayInventory(); break;
            case 3: addItemToCart(cartProdIndex, cartQty, &cartCount); break;
            case 4: {
                if (cartCount == 0) { printf("Cart is empty.\n"); break; }
                float total = calculateTotal(cartProdIndex, cartQty, cartCount);
                printf("Total before discount: %.2f\n", total);
                char code[50];
                printf("Do you have a promocode? Enter or press Enter to skip: ");
                fgets(code, sizeof(code), stdin);
                if (code[strlen(code)-1] == '\n') code[strlen(code)-1] = '\0';
                for (int i=0; code[i]; i++) code[i] = toupper((unsigned char)code[i]);
                if (strcmp(code, "EID2025") == 0) {
                    discountApplied = 1;
                    float discounted = total * 0.75f;
                    printf("Promocode accepted. Total after 25%% discount: %.2f\n", discounted);
                } else {
                    printf("No valid promocode applied.\n");
                }
                break;
            }
            case 5:
                if (cartCount == 0) { printf("Cart is empty.\n"); break; }
                updateInventoryFromCart(cartProdIndex, cartQty, cartCount);
                showInvoice(&cust, cartProdIndex, cartQty, cartCount, discountApplied);
                cartCount = 0;
                discountApplied = 0;
                break;
            case 6: printf("Exiting...\n"); return 0;
            default: printf("Invalid option.\n");
        }
    }
    return 0;
}

void inputCustomer(Customer *c) {
    printf("Enter customer name: ");
    fgets(c->name, NAME_LEN, stdin);
    if (c->name[strlen(c->name)-1] == '\n') c->name[strlen(c->name)-1] = '\0';
    printf("Enter CNIC: ");
    fgets(c->cnic, sizeof(c->cnic), stdin);
    if (c->cnic[strlen(c->cnic)-1] == '\n') c->cnic[strlen(c->cnic)-1] = '\0';
    printf("Customer saved: %s | CNIC: %s\n", c->name, c->cnic);
}

void displayInventory() {
    printf("\nCode\tQty\tPrice\n");
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        printf("%s\t%d\t%.2f\n", products[i].code, products[i].quantity, products[i].price);
    }
}

int findProductIndexByCode(const char *code) {
    for (int i = 0; i < MAX_PRODUCTS; i++)
        if (strcmp(products[i].code, code) == 0) return i;
    return -1;
}

void addItemToCart(int cartProdIndex[], int cartQty[], int *cartCount) {
    char code[10];
    int qty;
    displayInventory();
    printf("Enter product code to add: ");
    fgets(code, sizeof(code), stdin);
    if (code[strlen(code)-1] == '\n') code[strlen(code)-1] = '\0';
    int idx = findProductIndexByCode(code);
    if (idx == -1) { printf("Invalid product code.\n"); return; }
    printf("Enter quantity: ");
    if (scanf("%d", &qty) != 1) { getchar(); printf("Invalid input.\n"); return; }
    getchar();
    if (qty <= 0) { printf("Quantity must be positive.\n"); return; }
    if (qty > products[idx].quantity) { printf("Not enough stock. Available: %d\n", products[idx].quantity); return; }

    for (int i = 0; i < *cartCount; i++) {
        if (cartProdIndex[i] == idx) {
            cartQty[i] += qty;
            printf("Updated cart: product %s quantity now %d\n", products[idx].code, cartQty[i]);
            return;
        }
    }
    cartProdIndex[*cartCount] = idx;
    cartQty[*cartCount] = qty;
    (*cartCount)++;
    printf("Added to cart: %s x%d\n", products[idx].code, qty);
}

void updateInventoryFromCart(int cartProdIndex[], int cartQty[], int cartCount) {
    for (int i = 0; i < cartCount; i++) {
        int p = cartProdIndex[i];
        products[p].quantity -= cartQty[i];
        if (products[p].quantity < 0) products[p].quantity = 0;
    }
}

float calculateTotal(int cartProdIndex[], int cartQty[], int cartCount) {
    float total = 0.0f;
    for (int i = 0; i < cartCount; i++) {
        total += products[cartProdIndex[i]].price * cartQty[i];
    }
    return total;
}

void showInvoice(Customer *c, int cartProdIndex[], int cartQty[], int cartCount, int discountApplied) {
    printf("\n--- Invoice ---\n");
    if (strlen(c->name) > 0) printf("Customer: %s\n", c->name);
    if (strlen(c->cnic) > 0) printf("CNIC: %s\n", c->cnic);
    printf("Items:\nCode\tQty\tPrice\tSubtotal\n");
    float total = 0.0f;
    for (int i = 0; i < cartCount; i++) {
        Product *p = &products[cartProdIndex[i]];
        float sub = p->price * cartQty[i];
        printf("%s\t%d\t%.2f\t%.2f\n", p->code, cartQty[i], p->price, sub);
        total += sub;
    }
    printf("Total before discount: %.2f\n", total);
    if (discountApplied) {
        float discounted = total * 0.75f;
        printf("Promocode Eid2025 applied: 25%% off\n");
        printf("Total after discount: %.2f\n", discounted);
    } else {
        printf("No promocode applied.\n");
    }
    printf("--- End Invoice ---\n");
}
