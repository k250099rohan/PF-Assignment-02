#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_TITLE_LEN 50

void addBook(int isbns[], char titles[][MAX_TITLE_LEN], float prices[], int quantities[], int *count);
void processSale(int isbns[], char titles[][MAX_TITLE_LEN], float prices[], int quantities[], int count);
void lowStockReport(int isbns[], char titles[][MAX_TITLE_LEN], float prices[], int quantities[], int count);
int findIndexByISBN(int isbns[], int count, int isbn);

int main() {
    int isbns[MAX_BOOKS] = {0};
    char titles[MAX_BOOKS][MAX_TITLE_LEN];
    float prices[MAX_BOOKS] = {0.0f};
    int quantities[MAX_BOOKS] = {0};
    int count = 0;
    int choice;

    while (1) {
        printf("\n=== Liberty Books Inventory ===\n");
        printf("1. Add New Book\n");
        printf("2. Process a Sale\n");
        printf("3. Low-Stock Report (qty < 5)\n");
        printf("4. Exit\n");
        printf("Select option: ");
        if (scanf("%d", &choice) != 1) { fflush(stdin); break; }
        getchar(); 

        switch (choice) {
            case 1: addBook(isbns, titles, prices, quantities, &count); break;
            case 2: processSale(isbns, titles, prices, quantities, count); break;
            case 3: lowStockReport(isbns, titles, prices, quantities, count); break;
            case 4: printf("Exiting...\n"); return 0;
            default: printf("Invalid option. Try again.\n");
        }
    }
    return 0;
}

void addBook(int isbns[], char titles[][MAX_TITLE_LEN], float prices[], int quantities[], int *count) {
    if (*count >= MAX_BOOKS) {
        printf("Inventory full. Cannot add more books.\n");
        return;
    }

    int isbn;
    char title[MAX_TITLE_LEN];
    float price;
    int qty;

    printf("Enter ISBN (numeric): ");
    scanf("%d", &isbn);
    getchar(); 
    if (findIndexByISBN(isbns, *count, isbn) != -1) {
        printf("Error: ISBN %d already exists. Duplicate not allowed.\n", isbn);
        return;
    }

    printf("Enter Title: ");
    fgets(title, MAX_TITLE_LEN, stdin);
    if (title[strlen(title)-1] == '\n') title[strlen(title)-1] = '\0';

    printf("Enter Price: ");
    scanf("%f", &price);
    printf("Enter Quantity: ");
    scanf("%d", &qty);

    isbns[*count] = isbn;
    strncpy(titles[*count], title, MAX_TITLE_LEN-1);
    titles[*count][MAX_TITLE_LEN-1] = '\0';
    prices[*count] = price;
    quantities[*count] = qty;
    (*count)++;

    printf("Book added successfully. Total books: %d\n", *count);
}

void processSale(int isbns[], char titles[][MAX_TITLE_LEN], float prices[], int quantities[], int count) {
    if (count == 0) { printf("No books in inventory.\n"); return; }
    int isbn, sold;
    printf("Enter ISBN to sell: ");
    scanf("%d", &isbn);
    int idx = findIndexByISBN(isbns, count, isbn);
    if (idx == -1) {
        printf("Book with ISBN %d not found.\n", isbn);
        return;
    }
    printf("Enter number of copies to sell: ");
    scanf("%d", &sold);
    if (sold <= 0) { printf("Enter a positive number.\n"); return; }
    if (quantities[idx] < sold) {
        printf("Out of stock / insufficient quantity. Available: %d\n", quantities[idx]);
        return;
    }
    quantities[idx] -= sold;
    printf("Sale processed. Remaining quantity of '%s' (ISBN %d): %d\n", titles[idx], isbn, quantities[idx]);
}

void lowStockReport(int isbns[], char titles[][MAX_TITLE_LEN], float prices[], int quantities[], int count) {
    int found = 0;
    printf("\n--- Low Stock Report (quantity < 5) ---\n");
    for (int i = 0; i < count; i++) {
        if (quantities[i] < 5) {
            found = 1;
            printf("ISBN: %d | Title: %s | Price: %.2f | Qty: %d\n", isbns[i], titles[i], prices[i], quantities[i]);
        }
    }
    if (!found) printf("No low-stock items.\n");
}

int findIndexByISBN(int isbns[], int count, int isbn) {
    for (int i = 0; i < count; i++) if (isbns[i] == isbn) return i;
    return -1;
}

