#include <stdio.h>

#define MAX_ROWS 10
#define MAX_COLS 10

void updateSector(int grid[][MAX_COLS], int rows, int cols);
void querySector(int grid[][MAX_COLS], int rows, int cols);
void runDiagnostic(int grid[][MAX_COLS], int rows, int cols);
int getInt(const char *prompt);

int main() {
    int rows = getInt("Enter number of rows (1-10): ");
    int cols = getInt("Enter number of cols (1-10): ");
    if (rows < 1 || rows > MAX_ROWS || cols < 1 || cols > MAX_COLS) {
        printf("Invalid dimensions. Using 5x5 default.\n");
        rows = cols = 5;
    }

    static int grid[MAX_ROWS][MAX_COLS];
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            grid[r][c] = 0;

    int choice;
    while (1) {
        printf("\n=== IESCO Grid Monitor ===\n");
        printf("1. Update Sector Status\n");
        printf("2. Query Sector Status\n");
        printf("3. Run System Diagnostic\n");
        printf("4. Exit\n");
        printf("Choose: ");
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1: updateSector(grid, rows, cols); break;
            case 2: querySector(grid, rows, cols); break;
            case 3: runDiagnostic(grid, rows, cols); break;
            case 4: printf("Exiting...\n"); return 0;
            default: printf("Invalid choice.\n");
        }
    }
    return 0;
}

void printStatus(int val) {
    printf("Power: %s\n", (val & (1 << 0)) ? "ON" : "OFF");
    printf("Overload Warning: %s\n", (val & (1 << 1)) ? "YES" : "NO");
    printf("Maintenance Required: %s\n", (val & (1 << 2)) ? "YES" : "NO");
}

void updateSector(int grid[][MAX_COLS], int rows, int cols) {
    int r, c;
    printf("Enter row (0-based): ");
    scanf("%d", &r);
    printf("Enter col (0-based): ");
    scanf("%d", &c);
    if (r < 0 || r >= rows || c < 0 || c >= cols) { printf("Invalid coordinates.\n"); return; }

    printf("Current status at (%d,%d):\n", r, c);
    printStatus(grid[r][c]);

    printf("Which flag to modify?\n1. Power (Bit0)\n2. Overload (Bit1)\n3. Maintenance (Bit2)\nChoice: ");
    int f;
    scanf("%d", &f);
    if (f < 1 || f > 3) { printf("Invalid flag.\n"); return; }
    printf("Set or Clear? (1=set, 0=clear): ");
    int set;
    scanf("%d", &set);
    int mask = 1 << (f - 1);
    if (set) grid[r][c] |= mask;
    else grid[r][c] &= ~mask;
    printf("Updated status:\n");
    printStatus(grid[r][c]);
}

void querySector(int grid[][MAX_COLS], int rows, int cols) {
    int r, c;
    printf("Enter row (0-based): ");
    scanf("%d", &r);
    printf("Enter col (0-based): ");
    scanf("%d", &c);
    if (r < 0 || r >= rows || c < 0 || c >= cols) { printf("Invalid coordinates.\n"); return; }
    printf("Status at (%d,%d):\n", r, c);
    printStatus(grid[r][c]);
}

void runDiagnostic(int grid[][MAX_COLS], int rows, int cols) {
    int overloadCount = 0, maintenanceCount = 0;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int val = grid[r][c];
            if (val & (1 << 1)) overloadCount++;
            if (val & (1 << 2)) maintenanceCount++;
        }
    }
    printf("Diagnostic Report:\n");
    printf("Total overloaded sectors: %d\n", overloadCount);
    printf("Total sectors requiring maintenance: %d\n", maintenanceCount);
}

int getInt(const char *prompt) {
    int x;
    printf("%s", prompt);
    if (scanf("%d", &x) != 1) { while (getchar()!='\n'); return 5; }
    return x;
}
