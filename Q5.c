#include <stdio.h>
#include <string.h>

#define MASK ((1 << 1) | (1 << 4))

void encodeMessage(char message[]) {
    int len = strlen(message);
    for (int i = 0; i < len/2; i++) {
        char tmp = message[i];
        message[i] = message[len-1-i];
        message[len-1-i] = tmp;
    }
    for (int i = 0; i < len; i++) {
        unsigned char ch = (unsigned char)message[i];
        ch ^= MASK;
        message[i] = (char)ch;
    }
}

void decodeMessage(char message[]) {
    int len = strlen(message);
    for (int i = 0; i < len; i++) {
        unsigned char ch = (unsigned char)message[i];
        ch ^= MASK;
        message[i] = (char)ch;
    }
    for (int i = 0; i < len/2; i++) {
        char tmp = message[i];
        message[i] = message[len-1-i];
        message[len-1-i] = tmp;
    }
}

int main() {
    char input[1024];
    int choice;
    while (1) {
        printf("\n--- TCS Message Encoder/Decoder ---\n");
        printf("1. Encode Message\n");
        printf("2. Decode Message\n");
        printf("3. Exit\n");
        printf("Choose option: ");
        if (scanf("%d", &choice) != 1) break;
        getchar(); 

        if (choice == 1) {
            printf("Enter message to encode: ");
            fgets(input, sizeof(input), stdin);
            if (input[strlen(input)-1] == '\n') input[strlen(input)-1] = '\0';
            encodeMessage(input);
            printf("Encoded message:\n%s\n", input);
        } else if (choice == 2) {
            printf("Enter message to decode: ");
            fgets(input, sizeof(input), stdin);
            if (input[strlen(input)-1] == '\n') input[strlen(input)-1] = '\0';
            decodeMessage(input);
            printf("Decoded message:\n%s\n", input);
        } else if (choice == 3) {
            printf("Exiting...\n");
            break;
        } else {
            printf("Invalid option.\n");
        }
    }
    return 0;
}
